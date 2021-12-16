#ifndef TA_I2C_H
#define TA_I2C_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "ch.h"
#include "hal.h"
#include "chprintf.h"
#include "memstreams.h"
#include "chstreams.h"

uint8_t readByteI2C(uint8_t addr);
void writeByteI2C(uint8_t addr, uint8_t reg, uint8_t val);

void I2c_Init(void);

#endif // TA_I2C_H
