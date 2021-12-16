/**
  Taken from https://github.com/joextodd/listener/blob/master/listener.ino
*/

#include "driver/spi.h"
#include "driver/spi_overlap.h"
#include "driver/slc_register.h"

#include "ets_sys.h"
#include "osapi.h"
#include "gpio.h"
#include "os_type.h"

#include "mem.h"
#include "ip_addr.h"
#include "espconn.h"
#include "user_interface.h"

#include "esp8266_peri.h"
#include "i2s_reg.h"
#include "i2s.h"

LOCAL sdio_queue_t i2s_slc_items[SLC_BUF_CNT];  // I2S DMA buffer descriptors
LOCAL uint32_t rx_buf_cnt = 0;
LOCAL bool rx_buf_flag = false;

uint32_t rx_buf_idx = 0;
uint32_t *i2s_slc_buf_pntr[SLC_BUF_CNT];  // Pointer to the I2S DMA buffer data

/**
 * @brief microphone timer
 */
LOCAL os_timer_t mic_timer;

/**
 * Set I2S clock.
 * I2S bits mode only has space for 15 extra bits,
 * 31 in total. The
 */
LOCAL void i2s_set_rate(uint32_t rate){
  uint32_t i2s_clock_div = (I2S_CLK_FREQ / (rate * 31 * 2)) & I2SCDM;
  uint32_t i2s_bck_div = (I2S_CLK_FREQ / (rate * i2s_clock_div * 31 * 2)) & I2SBDM;

  // RX master mode, RX MSB shift, right first, msb right
  I2SC &= ~(I2STSM | I2SRSM | (I2SBMM << I2SBM) | (I2SBDM << I2SBD) | (I2SCDM << I2SCD));
  I2SC |= I2SRF | I2SMR | I2SRMS | (i2s_bck_div << I2SBD) | (i2s_clock_div << I2SCD);
}

/**
 * Triggered when SLC has finished writing
 * to one of the buffers.
 */
LOCAL void slc_isr(void *para){
    int i;
    uint32_t status;

    status = SLCIS;
    SLCIC = 0xFFFFFFFF;

    if (status == 0) {return;}

    ETS_SLC_INTR_DISABLE();
    if (status & SLCITXEOF) {
        // We have received a frame
        sdio_queue_t *finished = (sdio_queue_t*)SLCTXEDA;

        finished->eof = 0;
        finished->owner = 1;
        finished->datalen = 0;

        for (i = 0; i < SLC_BUF_CNT; i++) {
            if (finished == &i2s_slc_items[i]) {
                rx_buf_idx = i;
            }
        }

        rx_buf_cnt++;
        rx_buf_flag = true;
    }
    ETS_SLC_INTR_ENABLE();
}

/**
 * Initialize the SLC module for DMA operation.
 * Counter intuitively, we use the TXLINK here to
 * receive data.
 */
LOCAL void slc_init(){
    int x,y;

    for (x=0; x<SLC_BUF_CNT; x++) {
        i2s_slc_buf_pntr[x] = (uint32_t *)os_malloc(SLC_BUF_LEN * 4);
        for (y=0; y<SLC_BUF_LEN; y++) i2s_slc_buf_pntr[x][y] = 0;

        i2s_slc_items[x].unused = 0;
        i2s_slc_items[x].owner = 1;
        i2s_slc_items[x].eof = 0;
        i2s_slc_items[x].sub_sof = 0;
        i2s_slc_items[x].datalen = SLC_BUF_LEN * 4;
        i2s_slc_items[x].blocksize = SLC_BUF_LEN * 4;
        i2s_slc_items[x].buf_ptr = (uint32_t *)&i2s_slc_buf_pntr[x][0];
        i2s_slc_items[x].next_link_ptr = (uint32_t *)((x < (SLC_BUF_CNT - 1)) ? (&i2s_slc_items[x + 1]) : (&i2s_slc_items[0]));
    }

    // Reset DMA
    ETS_SLC_INTR_DISABLE();
    SLCC0 |= SLCRXLR | SLCTXLR;
    SLCC0 &= ~(SLCRXLR | SLCTXLR);
    SLCIC = 0xFFFFFFFF;

    // Configure DMA
    SLCC0 &= ~(SLCMM << SLCM);      // Clear DMA MODE
    SLCC0 |= (1 << SLCM);           // Set DMA MODE to 1
    SLCRXDC |= SLCBINR | SLCBTNR;   // Enable INFOR_NO_REPLACE and TOKEN_NO_REPLACE

    // Feed DMA the 1st buffer desc addr
    SLCTXL &= ~(SLCTXLAM << SLCTXLA);
    SLCTXL |= (uint32_t)&i2s_slc_items[0] << SLCTXLA;

    ETS_SLC_INTR_ATTACH(slc_isr, NULL);

    // Enable EOF interrupt
    SLCIE = SLCITXEOF;
    ETS_SLC_INTR_ENABLE();

    // Start transmission
    SLCTXL |= SLCTXLS;
}

LOCAL void i2s_init(void){
    // Config RX pin function
    PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTDI_U, FUNC_I2SI_DATA);
    PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTCK_U, FUNC_I2SI_BCK);
    PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTMS_U, FUNC_I2SI_WS);

    // Config RX pin direction
    GPIO_OUTPUT_SET(GPIO_ID_PIN(I2SI_DATA), 0);
    GPIO_OUTPUT_SET(GPIO_ID_PIN(I2SI_BCK), 1);
    GPIO_OUTPUT_SET(GPIO_ID_PIN(I2SI_WS), 1);

    // Enable a 160MHz clock
    I2S_CLK_ENABLE();

    // Reset I2S
    I2SC &= ~(I2SRST);
    I2SC |= I2SRST;
    I2SC &= ~(I2SRST);

    // Reset DMA
    I2SFC &= ~(I2SDE | (I2SRXFMM << I2SRXFM));

    // Enable DMA
    I2SFC |= I2SDE | (I2S_24BIT << I2SRXFM);

    // Set RX single channel (left)
    I2SCC &= ~((I2STXCMM << I2STXCM) | (I2SRXCMM << I2SRXCM));
    I2SCC |= (I2S_LEFT << I2SRXCM);
    i2s_set_rate(16667);

    // Set RX data to be received
    I2SRXEN = SLC_BUF_LEN;

    // Bits mode
    I2SC |= (15 << I2SBM);

    // Start receiver
    I2SC |= I2SRXS;
}

/**
 * @brief Microphone Thread
 */
LOCAL void ICACHE_FLASH_ATTR mic_timer_handler(void *prv){
    mic_print();
}

void mic_print(void){
    int x;
    int32_t value;

    if (rx_buf_flag) {
        for (x = 0; x < SLC_BUF_LEN; x++) {
          if (i2s_slc_buf_pntr[rx_buf_idx][x] > 0) {
                value = convert(i2s_slc_buf_pntr[rx_buf_idx][x]);
                os_printf("5 %d -2.5\r\n", -((value/4960)+50));
          }
        }
        rx_buf_flag = false;
    }
}

void mic_init(void){
    rx_buf_cnt = 0;
    slc_init();
    i2s_init();

#if MIC_OUT
    os_timer_setfn(&mic_timer, (os_timer_func_t *)mic_timer_handler, NULL);
    os_timer_arm(&mic_timer, 100, 1);
#endif

}

void mic_loop(void){
    os_timer_setfn(&mic_timer, (os_timer_func_t *)mic_timer_handler, NULL);
    os_timer_arm(&mic_timer, 100, 1);
}
