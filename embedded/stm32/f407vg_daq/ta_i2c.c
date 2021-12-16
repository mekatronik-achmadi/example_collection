#include "ta_i2c.h"

static const I2CConfig i2cconfig= {
    OPMODE_I2C,
    400000,
    FAST_DUTY_CYCLE_2,
};

uint8_t readByteI2C(uint8_t addr){
    uint8_t data;
    i2cAcquireBus(&I2CD1);
    (void) i2cMasterReceiveTimeout(&I2CD1,addr,&data,1,TIME_INFINITE);
    i2cReleaseBus(&I2CD1);
    return data;
}

void writeByteI2C(uint8_t addr, uint8_t reg, uint8_t val){
    uint8_t cmd[] = {reg, val};
    i2cAcquireBus(&I2CD1);
    (void) i2cMasterTransmitTimeout(&I2CD1, addr, cmd, 2, NULL, 0, TIME_INFINITE);
    i2cReleaseBus(&I2CD1);
}

void I2c_Init(void){
    palSetPadMode(GPIOB,8,PAL_MODE_ALTERNATE(4) | PAL_STM32_OTYPE_OPENDRAIN);
    palSetPadMode(GPIOB,9,PAL_MODE_ALTERNATE(4) | PAL_STM32_OTYPE_OPENDRAIN);
    i2cStart(&I2CD1, &i2cconfig);
}
