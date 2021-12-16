/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.org/license.html
 */

#ifndef GDISP_LLD_BOARD_H
#define GDISP_LLD_BOARD_H

#include "gfx.h"

#define SET_RST       palSetPad(GPIOE, 1)
#define CLR_RST       palClearPad(GPIOE, 1)

/*
 * LCD_RS is on A16 (PD11)
 */
#define GDISP_REG   (*((volatile uint16_t *) 0x60000000)) /* RS = 0 */
#define GDISP_RAM   (*((volatile uint16_t *) 0x60020000)) /* RS = 1 */
/*
 * STM32_DMA1_STREAM7
 * NOTE: conflicts w/ USART2_TX, TIM2_CH2, TIM2_CH4, TIM4_UP, I2C1_RX in case
 */
#define FSMC_BANK 0

static GFXINLINE void init_board(GDisplay *g) {
    (void) g;
    /* FSMC setup for F1 */
    rccEnableAHB(RCC_AHBENR_FSMCEN, 0);

    /* Group pins for FSMC setup as alternate function */
    IOBus busD = { GPIOD, (1 << 0) | (1 << 1) | (1 << 4) | (1 << 5) |          \
                   (1 << 7) | (1 << 8) | (1 << 9) | (1 << 10) | (1 << 11) |    \
                   (1 << 14) | (1 << 15), 0 };

    IOBus busE = { GPIOE, (1 << 7) | (1 << 8) | (1 << 9) | (1 << 10) |         \
                   (1 << 11) | (1 << 12) | (1 << 13) | (1 << 14) |             \
                   (1 << 15), 0 };

    /* FSMC as alternate function */
    palSetBusMode(&busD, PAL_MODE_STM32_ALTERNATE_PUSHPULL);
    palSetBusMode(&busE, PAL_MODE_STM32_ALTERNATE_PUSHPULL);
    
    palSetPadMode(GPIOD, 13, PAL_MODE_OUTPUT_PUSHPULL);
    palClearPad(GPIOD, 13);

    palSetPadMode(GPIOE, 1, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPad(GPIOE,1);

  /*
     * NOTE: stm32F10x.h is FAULTY on FSMC
     * NOTE: Used hardcore bit shifting below
     * NOTE: All timings for 72MHz HCLK - should be revised for lower HCLK
     */

    /* FSMC timing - Read: DATAST = 0x20; all the rest = 0.
     * 100ns cycle time for SSD1289 as per DataSheet
     */

    FSMC_Bank1->BTCR[FSMC_BANK+1] = (0x20 << 8);
//   FSMC_Bank1->BTCR[FSMC_BANK+1] = FSMC_BTR1_ADDSET_1 | FSMC_BTR1_DATAST_1 | FSMC_BTR1_BUSTURN_0 ;

    /* FSMC timing - Write: DATAST = 0x01, ADDSET = 0x01 all the rest = 0.
     * 1000ns cycle time for SSD1289 as per DataSheet
     */
    FSMC_Bank1E->BWTR[FSMC_BANK] = (0x1 << 8) | (0x01 << 0);

    /* Bank1 NOR/SRAM control register configuration
     * This is actually not needed as already set by default after reset
     * Note: different read and write cycle timing
     */
    FSMC_Bank1->BTCR[FSMC_BANK] = FSMC_BCR1_MWID_0 | FSMC_BCR1_WREN | FSMC_BCR1_MBKEN;
    
}

static GFXINLINE void post_init_board(GDisplay *g) {
  (void) g;
}

static GFXINLINE void setpin_reset(GDisplay *g, bool_t state) {
  (void) g;

  if(state){CLR_RST;}
  else{SET_RST;}
}

static GFXINLINE void set_backlight(GDisplay *g, uint8_t percent) {
  (void) g;
  (void) percent;
}

static GFXINLINE void acquire_bus(GDisplay *g) {
  (void) g;
}

static GFXINLINE void release_bus(GDisplay *g) {
  (void) g;
}

static GFXINLINE void write_index(GDisplay *g, uint16_t index) {
  (void) g;
    GDISP_REG = index;
}

static GFXINLINE void write_data(GDisplay *g, uint16_t data) {
  (void) g;
    GDISP_RAM = data;
}

static GFXINLINE void setreadmode(GDisplay *g) {
  (void) g;
}

static GFXINLINE void setwritemode(GDisplay *g) {
  (void) g;
}

static GFXINLINE uint16_t read_data(GDisplay *g) {
  (void) g;
    return GDISP_RAM;
}

#endif /* GDISP_LLD_BOARD_H */
