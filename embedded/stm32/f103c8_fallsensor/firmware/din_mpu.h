/*
              DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE

 Copyright (C) 2018 Achmadi S.T.

 Everyone is permitted to copy and distribute verbatim or modified
 copies of this license document, and changing it is allowed as long
 as the name is changed.

            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
   TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION

  0. You just DO WHAT THE FUCK YOU WANT TO.
 */

/**
 * @file    din_mpu.h
 * @brief   MPU Sensor routine header.
 *
 * @addtogroup MPU60
 * @{
 */

#ifndef DIN_ACCEL_H
#define DIN_ACCEL_H

#include "ch.h"
#include "hal.h"

#include "chprintf.h"
#include "shell.h"

#include "math.h"
#include "stdlib.h"
#include "stdio.h"

#include "reg_mpu.h"


/**
 * @brief   Enable MPU notification at SD1
 */
#define MPU_DEBUG   FALSE


/**
 * @brief   MPU60 I2C address
 * @note    For AD0 to GND or NC, use @see MPU_ADDR_LO
 * @note    For AD0 to VCC, use @see MPU_ADDR_HI
 */
#define MPU_ADDR    MPU_ADDR_LO

void d_mpu_start(void);
void d_mpu_setup(void);
void d_mpu_whoAmI(void);

void d_mpu_i2cWrite(u_int8_t addr, u_int8_t value);
void d_mpu_i2cReadData(u_int8_t addr, u_int8_t length);
void d_mpu_i2cReadFirst(u_int8_t addr, u_int8_t length);
float d_mpu_vectorMag(float vx, float vy, float vz);

#endif // DIN_ACCEL_H
/** @} */
