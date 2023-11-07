/**
 * @file lora.c
 * @brief LoRa module SPI code
 *
 * @addtogroup LORA
 * @{
 */

#include "lora.h"

static uint16_t packetIndex = 0;
static long moduleFreq;

static const SPIConfig spicfg = {
  NULL,
  GPIOA,
  LORA_DEFAULT_SS_PIN,
#if USE_LOWER_SPI
  SPI_CR1_BR_2 | SPI_CR1_BR_1 //281.250kHz, CPHA=0, CPOL=0, MSb first
#else
  0
#endif
};

static uint8_t lora_singleTransfer(uint8_t address, uint8_t value){
    uint8_t txbuf[1];
    uint8_t rxbuf[1];

    txbuf[0] = value;

    spiSelect(&SPID1);
    palClearPad(GPIOA, LORA_DEFAULT_SS_PIN);

    spiSend(&SPID1, sizeof(address), &address);
    spiExchange(&SPID1, sizeof(txbuf), txbuf, rxbuf);

    spiUnselect(&SPID1);
    palSetPad(GPIOA, LORA_DEFAULT_SS_PIN);

    return rxbuf[0];
}

static uint8_t lora_readRegister(uint8_t address){
    return lora_singleTransfer(address & 0x7f, 0x00);
}

static void lora_writeRegister(uint8_t address, uint8_t value){
    lora_singleTransfer(address | 0x80, value);
}

static void lora_sleep(void){
    lora_writeRegister(REG_OP_MODE, MODE_LONG_RANGE_MODE | MODE_SLEEP);
}

static void lora_idle(void){
    lora_writeRegister(REG_OP_MODE, MODE_LONG_RANGE_MODE | MODE_STDBY);
}

static void lora_setOCP(uint8_t mA){
    uint8_t ocpTrim = 27;

    if (mA <= 120) {
        ocpTrim = (mA - 45) / 5;
    } else if (mA <=240) {
        ocpTrim = (mA + 30) / 10;
    }

    lora_writeRegister(REG_OCP, 0x20 | (0x1F & ocpTrim));
}

static bool lora_isTransmitting(void){
    if ((lora_readRegister(REG_OP_MODE) & MODE_TX) == MODE_TX) return TRUE;


    if (lora_readRegister(REG_IRQ_FLAGS) & IRQ_TX_DONE_MASK)
        lora_writeRegister(REG_IRQ_FLAGS, IRQ_TX_DONE_MASK);

    return FALSE;
}

void lora_setFrequency(long frequency){
    moduleFreq = frequency;

    uint64_t frf = ((uint64_t)frequency << 19) / 32000000;

    lora_writeRegister(REG_FRF_MSB, (uint8_t)(frf >> 16));
    lora_writeRegister(REG_FRF_MID, (uint8_t)(frf >> 8));
    lora_writeRegister(REG_FRF_LSB, (uint8_t)(frf >> 0));
}

void lora_setTxPower(int level, uint8_t outputPin){
    // RFO
    if(outputPin==PA_OUTPUT_RFO_PIN){
        if (level < 0) {
            level = 0;
        } else if (level > 14) {
            level = 14;
        }
        lora_writeRegister(REG_PA_CONFIG, 0x70 | level);
    }

    // PA BOOST
    else{
        if (level > 17) {
            if (level > 20) {
                level = 20;
            }

            // subtract 3 from level, so 18 - 20 maps to 15 - 17
            level -= 3;

            // High Power +20 dBm Operation (Semtech SX1276/77/78/79 5.4.3.)
            lora_writeRegister(REG_PA_DAC, 0x87);
            lora_setOCP(140);
        }
        else {
            if (level < 2) {
                level = 2;
            }
            //Default value PA_HF/LF or +17dBm
            lora_writeRegister(REG_PA_DAC, 0x84);
            lora_setOCP(100);
        }

        lora_writeRegister(REG_PA_CONFIG, PA_BOOST | (level - 2));
    }
}

void lora_beginPacket(void){
    if(lora_isTransmitting()){
        return;
    }

    lora_idle();

    lora_writeRegister(REG_MODEM_CONFIG_1, lora_readRegister(REG_MODEM_CONFIG_1) & 0xfe);

    lora_writeRegister(REG_FIFO_ADDR_PTR, 0);
    lora_writeRegister(REG_PAYLOAD_LENGTH, 0);
}

size_t lora_writeChars(char *buffer, size_t size){
     int currentLength = lora_readRegister(REG_PAYLOAD_LENGTH);

    // check size
    if ((currentLength + size) > MAX_PKT_LENGTH) {
        size = MAX_PKT_LENGTH - currentLength;
    }

    // write data
    for (size_t i = 0; i < size; i++) {
        lora_writeRegister(REG_FIFO, buffer[i]);
    }

    // update length
    lora_writeRegister(REG_PAYLOAD_LENGTH, currentLength + size);

    return size;
}

void lora_endPacket(void){
    lora_writeRegister(REG_OP_MODE, MODE_LONG_RANGE_MODE | MODE_TX);

    // wait for TX done
    while ((lora_readRegister(REG_IRQ_FLAGS) & IRQ_TX_DONE_MASK) == 0) {
        chThdSleepMicroseconds(10);
    }

    // clear IRQ's
    lora_writeRegister(REG_IRQ_FLAGS, IRQ_TX_DONE_MASK);
}

uint16_t lora_parsePacket(void){
    uint16_t packetLength = 0;
    uint8_t irqFlags = lora_readRegister(REG_IRQ_FLAGS);

    lora_writeRegister(REG_MODEM_CONFIG_1, lora_readRegister(REG_MODEM_CONFIG_1) & 0xfe);

    // clear IRQs
    lora_writeRegister(REG_IRQ_FLAGS, irqFlags);

    if((irqFlags & IRQ_RX_DONE_MASK) && (irqFlags & IRQ_PAYLOAD_CRC_ERROR_MASK) == 0) {
        packetIndex = 0;
        packetLength = lora_readRegister(REG_RX_NB_BYTES);
        lora_writeRegister(REG_FIFO_ADDR_PTR, lora_readRegister(REG_FIFO_RX_CURRENT_ADDR));
    }
    else if(lora_readRegister(REG_OP_MODE) != (MODE_LONG_RANGE_MODE | MODE_RX_SINGLE)) {
        lora_writeRegister(REG_FIFO_ADDR_PTR, 0);
        lora_writeRegister(REG_OP_MODE, MODE_LONG_RANGE_MODE | MODE_RX_SINGLE);
    }

    return packetLength;
}

int lora_packetRssi(void){
    return (lora_readRegister(REG_PKT_RSSI_VALUE) - (moduleFreq < RF_MID_BAND_THRESHOLD ? RSSI_OFFSET_LF_PORT : RSSI_OFFSET_HF_PORT));
}

int lora_available(void){
    return (lora_readRegister(REG_RX_NB_BYTES) - packetIndex);
}

int lora_read(void){
    if(!lora_available()){
        return -1;
    }

    packetIndex++;

    return lora_readRegister(REG_FIFO);
}

void lora_begin(long frequency){
    (void) frequency;

    palSetPadMode(GPIOA, 5, PAL_MODE_STM32_ALTERNATE_PUSHPULL);
    palSetPadMode(GPIOA, 6, PAL_MODE_STM32_ALTERNATE_PUSHPULL);
    palSetPadMode(GPIOA, 7, PAL_MODE_STM32_ALTERNATE_PUSHPULL);

    palSetPadMode(GPIOA, LORA_DEFAULT_SS_PIN, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOA, LORA_DEFAULT_RESET_PIN, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOA, LORA_DEFAULT_DIO0_PIN, PAL_MODE_OUTPUT_PUSHPULL);

    palSetPad(GPIOA, LORA_DEFAULT_SS_PIN);
    palSetPad(GPIOA, LORA_DEFAULT_RESET_PIN);
    palSetPad(GPIOA, LORA_DEFAULT_DIO0_PIN);

    spiAcquireBus(&SPID1);
    spiStart(&SPID1, &spicfg);

    // LoRA Initialization

    //reset the module
    palClearPad(GPIOA, LORA_DEFAULT_RESET_PIN);
    chThdSleepMilliseconds(10);
    palSetPad(GPIOA, LORA_DEFAULT_RESET_PIN);
    chThdSleepMilliseconds(10);

    //check version
    uint8_t version = lora_readRegister(REG_VERSION);
    if (version == 0x12) {
        chprintf((BaseSequentialStream *)&SD1, "LoRA Verified \r\n");
    }
    else{
        chprintf((BaseSequentialStream *)&SD1, "LoRA Failed \r\n");
        return;
    }

    // put in sleep mode
    lora_sleep();

    // set frequency
    lora_setFrequency(frequency);

    // set base addresses
    lora_writeRegister(REG_FIFO_TX_BASE_ADDR, 0);
    lora_writeRegister(REG_FIFO_RX_BASE_ADDR, 0);

    // set LNA boost
    lora_writeRegister(REG_LNA, lora_readRegister(REG_LNA) | 0x03);

    // set auto AGC
    lora_writeRegister(REG_MODEM_CONFIG_3, 0x04);

    // set output power to 17 dBm
    lora_setTxPower(20,PA_OUTPUT_PA_BOOST_PIN);

    // put in standby mode
    lora_idle();

    chprintf((BaseSequentialStream *)&SD1, "LoRA Initiated \r\n");
}

/**  @} */

