#include "lora.h"

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
    palClearPad(GPIOA, LORA_DEFAULT_SS_PIN);

    uint8_t txbuf[1];
    uint8_t rxbuf[1];

    txbuf[0] = value;

    spiSelect(&SPID1);
    spiSend(&SPID1, sizeof(address), &address);
    spiExchange(&SPID1, sizeof(txbuf), txbuf, rxbuf);
    //spiSend(&SPID1, sizeof(address), &value);
    //spiReceive(&SPID1, sizeof(response), &response);
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

static void lora_implicitHeaderMode(void){
    lora_writeRegister(REG_MODEM_CONFIG_1, lora_readRegister(REG_MODEM_CONFIG_1) | 0x01);
}

static void lora_explicitHeaderMode(void){
    lora_writeRegister(REG_MODEM_CONFIG_1, lora_readRegister(REG_MODEM_CONFIG_1) & 0xfe);
}

void lora_setFrequency(long frequency){
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
        if (level < 2) {
            level = 2;
        } else if (level > 17) {
            level = 17;
        }

        lora_writeRegister(REG_PA_CONFIG, PA_BOOST | (level - 2));
    }
}

void lora_BeginPacket(uint8_t implicitheader){
    lora_idle();

    if(implicitheader){
        lora_implicitHeaderMode();
    }
    else{
        lora_explicitHeaderMode();
    }

    lora_writeRegister(REG_FIFO_ADDR_PTR, 0);
    lora_writeRegister(REG_PAYLOAD_LENGTH, 0);
}

size_t lora_WriteBuffer(char *buffer, size_t size){
    uint8_t currentLength = lora_readRegister(REG_PAYLOAD_LENGTH);

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

void lora_EndPacket(void){
    lora_writeRegister(REG_OP_MODE, MODE_LONG_RANGE_MODE | MODE_TX);

    // wait for TX done
    while ((lora_readRegister(REG_IRQ_FLAGS) & IRQ_TX_DONE_MASK) == 0) {
        chThdSleepMicroseconds(10);
    }

    // clear IRQ's
    lora_writeRegister(REG_IRQ_FLAGS, IRQ_TX_DONE_MASK);
}

void lora_Begin(long frequency){
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
