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
 * @file    din_mpu.c
 * @brief   MPU Sensor routine code.
 *
 * @addtogroup MPU60
 * @{
 */

#include "din_mpu.h"

extern adcsample_t adc0,adc00,adc01;

/////////////////////////////////////// Rutin MPU60x0 (hasil nyolong kerjaan orang) ////////////////

/**
 * @brief   Global variable for Accel vector X.
 */
float ax,ax0,ax1;

/**
 * @brief   Global variable for Accel vector Y.
 */
float ay,ay0,ay1;

/**
 * @brief   Global variable for Accel vector Z.
 */
float az,az0,az1;

/**
 * @brief   Global variable for Accel vector Magnitude.
 */
float mag;

/**
 * @brief   Global variable for Normalization at 2G.
 */
float rangePerDigit = .000061f;

/**
 * @brief   Global variable for Sample Rate Divisor.
 */
static u_int8_t smplrt_div= 0;

/**
 * @brief   Global variable for MPU Configuration.
 */
static u_int8_t mpu_config = 0;

/**
 * @brief   Global variable for Gyro Configuration.
 */
static u_int8_t gyro_config = 0;

/**
 * @brief   Global variable for Accel Configuration.
 */
static u_int8_t accel_config = 0;

/**
 * @brief   Global variable for User Control Configuration.
 */
static u_int8_t user_control = 0x00;

/**
 * @brief   Global variable for Power Management.
 */
static u_int8_t power_mgmt1 = 0x00;

//static u_int8_t fifo_enable = 0x00;
//static u_int8_t int_pin_config = 0x00;
//static u_int8_t int_pin_enable = 0x00;
//static u_int8_t signal_path_reset = 0x00;
//static u_int8_t power_mgmt2  = 0x00;
//static u_int8_t aux_vddio = 0x00;

/**
 * @brief   Defines value for SMPRT_DIV register.
 * @note    Sample Rate = Gyroscope Output Rate / (1 + SMPLRT_DIV)
 * @param[in] samplerate_divisor value of divisor
 */
static u_int8_t d_mpu_setSampleRate(u_int8_t samplerate_divisor){
    smplrt_div = samplerate_divisor;
#if MPU_DEBUG
    chprintf((BaseSequentialStream *)&SD1,"Sample rate value: 0x%x\r\n", smplrt_div);
#endif
    return smplrt_div;
}

/**
 * @brief   Defines register controls FSYNC and bandwidth of gyro and accelerometer.
 * @param[in] ext_sync_set typical @see EXT_SYNC_SET0
 * @param[in] dlpf_cfg typical @see DLPF_CFG0
 */
static u_int8_t d_mpu_configRegister(u_int8_t ext_sync_set, u_int8_t dlpf_cfg){
    mpu_config = 0x00;
    mpu_config = ext_sync_set | dlpf_cfg;
#if MPU_DEBUG
    chprintf((BaseSequentialStream *)&SD1,"CONFIG Register value: 0x%x\r\n", mpu_config);
#endif
    return mpu_config;
}

/**
 * @brief   Defines register controls self test and  range of gyroscopes.
 * @param[in] xgyro_st typical @see XG_ST_EN
 * @param[in] ygyro_st typical @see YG_ST_EN
 * @param[in] zgyro_st typical @see ZG_ST_EN
 * @param[in] gyro_range typical @see FS_SEL250
 */
static u_int8_t d_mpu_setGyro(u_int8_t xgyro_st, u_int8_t ygyro_st, u_int8_t zgyro_st, u_int8_t gyro_range){
    gyro_config = 0x00;
    gyro_config = xgyro_st | ygyro_st | zgyro_st | gyro_range;
#if MPU_DEBUG
    chprintf((BaseSequentialStream *)&SD1,"Gyro Config value: 0x%x\r\n", gyro_config);
#endif
    return gyro_config;
}

/**
 * @brief   Defines register controls self test, accelerometer range and DHPF for accelerometer.
 * @param[in] xaccel_st typical @see XA_ST_EN or @see XA_ST_DIS
 * @param[in] yaccel_st typical @see YA_ST_EN or @see YA_ST_DIS
 * @param[in] zaccel_st typical @see ZA_ST_EN or @see ZA_ST_DIS
 * @param[in] accel_range typical @see AFS_SEL0
 * @param[in] dhpf_accel typical @see ACCEL_HPF0
 */
static u_int8_t d_mpu_setAccel(u_int8_t xaccel_st, u_int8_t yaccel_st, u_int8_t zaccel_st, u_int8_t accel_range, u_int8_t dhpf_accel){
    accel_config = 0x00;
    accel_config = xaccel_st | yaccel_st | zaccel_st | accel_range | dhpf_accel;
#if MPU_DEBUG
    chprintf((BaseSequentialStream *)&SD1,"Accelerometer Config value: 0x%x\r\n", accel_config);
#endif
    return accel_config;
}

/*
 * This function defines value for FIFO_EN register. This register controls which sensor output to be
 * written in fifo regiser.
 * Typical funciton call: set_mpu_fifo_register(TEMP_FIFO_EN/DIS, XG_FIFO_EN/DIS, YG_FIFO_EN/DIS, ACCLE_FIFO_EN/DIS, SLVx_FIFO_EN/DIS...)
 */
//static u_int8_t d_mpu_fifoRegister(u_int8_t temperature_fifo, u_int8_t xg_fifo, u_int8_t yg_fifo, u_int8_t zg_fifo, u_int8_t accel_fifo, u_int8_t slv2_fifo, u_int8_t slv1_fifo,u_int8_t slv0_fifo){
//    fifo_enable = 0x00;
//    fifo_enable = temperature_fifo | xg_fifo | yg_fifo | zg_fifo | accel_fifo | slv2_fifo | slv1_fifo | slv0_fifo;
//#if MPU_DEBUG
//    chprintf((BaseSequentialStream *)&SD1,"FIFO Enable value: 0x%x\r\n", fifo_enable);
//#endif
//    return fifo_enable;
//}

/*
 * This function defines value for INT_PIN_CFG register. This controls behavior of Interrupt PIN
 */
//static u_int8_t d_mpu_intBehavior(u_int8_t int_level, u_int8_t int_pin_mode, u_int8_t latch_int, u_int8_t int_status_bits, u_int8_t fsync_level, u_int8_t fsync_enable, u_int8_t i2c_bypass, u_int8_t clock){
//    int_pin_config = 0x00;
//    int_pin_config = int_level | int_pin_mode | latch_int | int_status_bits | fsync_level | fsync_enable | i2c_bypass |clock;
//#if MPU_DEBUG
//    chprintf((BaseSequentialStream *)&SD1,"Interrupt behavior value: 0x%x\r\n", int_pin_config);
//#endif
//    return int_pin_config;
//}

/*
 * This function defines value for INT_ENABLE register. This register controls source of interrupt.
 * Typical function call: set_mpu_interrupt_sources(FF_EN/DIS, MOT_EN/DIS,.......,DATA_RDY_EN/DIS)
 */
//static u_int8_t d_mpu_intSource(u_int8_t free_fall, u_int8_t motion_threshold, u_int8_t zero_motion, u_int8_t fifo_overflow, u_int8_t i2c_mst, u_int8_t data_ready){
//    int_pin_enable = 0x00;
//    int_pin_enable = free_fall | motion_threshold | zero_motion | fifo_overflow | i2c_mst | data_ready;
//#if MPU_DEBUG
//    chprintf((BaseSequentialStream *)&SD1,"Interrupt Pin Source value value: 0x%x\r\n", int_pin_enable);
//#endif
//    return int_pin_enable;
//}

/*
 * This function defines value for SIGNAL_PATH_RESET register. This register can reset gyro, accelerometer and
 * temperature sensors' digital and analog signal path.
 * Typical function call: reset_mpu_signal_path(GYRO_RESET_EN/DIS, ACCEL_RESET_EN/DIS, TEMP_RESET_EN/DIS)
 */
//static u_int8_t d_mpu_Reset(u_int8_t gyro_reset, u_int8_t accel_reset, u_int8_t temperature_reset){
//    signal_path_reset = 0x00;
//    signal_path_reset = gyro_reset | accel_reset | temperature_reset;
//#if MPU_DEBUG
//    chprintf((BaseSequentialStream *)&SD1,"Signal Path Reset value: 0x%x\r\n", signal_path_reset);
//#endif
//    return signal_path_reset;
//}

/**
 * @brief   Defines value for USER_CTRL register.
 * @param[in] fifo_operation typical @see USER_FIFO_EN or @see USER_FIFO_DIS
 * @param[in] aux_i2c typical @see I2C_MST_EN or @see I2C_MST_DIS
 * @param[in] bus_select typical @see I2C_IF_EN or @see I2C_IF_DIS
 * @param[in] fifo_reset typical @see FIFO_RESET_EN or @see FIFO_RESET_DIS
 * @param[in] i2c_reset typical @see I2C_MST_EN or @see I2C_MST_DIS
 * @param[in] signal_cond_reset typical @see SIG_COND_RESET_EN or @see SIG_COND_RESET_DIS
 */
static u_int8_t d_mpu_userControl(u_int8_t fifo_operation, u_int8_t aux_i2c, u_int8_t bus_select, u_int8_t fifo_reset, u_int8_t i2c_reset, u_int8_t signal_cond_reset){
    user_control = 0x00;
    user_control = fifo_operation | aux_i2c | bus_select | fifo_reset | i2c_reset | signal_cond_reset;
#if MPU_DEBUG
    chprintf((BaseSequentialStream *)&SD1,"User Control value: 0x%x\r\n", user_control);
#endif
    return user_control;
}

/**
 * @brief   Defines register device reset, sleep mode, cycle between different mode and clock source.
 * @param[in] device_reset typical @see DEVICE_RESET_EN or @see DEVICE_RESET_DIS
 * @param[in] sleep typical @see SLEEP_EN or @see SLEEP_DIS
 * @param[in] cycle typical @see CYCLE_EN or @see CYCLE_DIS
 * @param[in] temperature typical @see TEMPERATURE_EN or @see TEMPERATURE_DIS
 * @param[in] clock_source typical @see CLKSEL_EN or @see CLKSEL_DIS
 */
static u_int8_t d_mpu_powerMGMT1(u_int8_t device_reset, u_int8_t sleep, u_int8_t cycle, u_int8_t temperature, u_int8_t clock_source){
    power_mgmt1 = 0x00;
    power_mgmt1 = device_reset | sleep | cycle | temperature | clock_source;
#if MPU_DEBUG
    chprintf((BaseSequentialStream *)&SD1,"Power Managemen1 value: 0x%x\r\n", power_mgmt1);
#endif
    return power_mgmt1;
}

/**
 * @brief   Write to @see SMPRT_DIV register
 */
static void d_mpu_writeSampleRate(void){
     d_mpu_i2cWrite(SMPRT_DIV, smplrt_div);
}

/*
 * This function writes value of configuration into CONFIG register.
 */
//static void d_mpu_writeConfigRegister(){
//    d_mpu_i2cWrite(CONFIG, mpu_config);
//}

/**
 * @brief   Write to @see GYRO_CONFIG register
 */
static void d_mpu_writeGyro(void){
    d_mpu_i2cWrite(GYRO_CONFIG, gyro_config);
}

/**
 * @brief   Write to @see ACCEL_CONFIG register
 */
static void d_mpu_writeAccel(void){
    d_mpu_i2cWrite(ACCEL_CONFIG, accel_config);
}

/**
 * @brief   Write to @see POWER_MGMT1 register
 */
static void d_mpu_writePowerMGMT1(void){
    d_mpu_i2cWrite(PWR_MGMT_1, power_mgmt1);
}

/*
 * This function writes value of user_control into USER_CTRL register.
 */
//static void d_mpu_writeUserControl(void){
//    d_mpu_i2cWrite(USER_CTRL, user_control);
//}

/**
 * @brief   Write to I2C bus
 * @param[in] addr Address to write
 * @param[in] value Value to write
 */
void d_mpu_i2cWrite(u_int8_t addr, u_int8_t value){
    u_int8_t mpu_txbuf[10], mpu_rxbuf[10];
    mpu_txbuf[0] = addr;
    mpu_txbuf[1] = value;

#if MPU_DEBUG
    chprintf((BaseSequentialStream *)&SD1,"Address: 0x%x Value: 0x%x\r\n", mpu_txbuf[0],mpu_txbuf[1]);
#endif

    i2cAcquireBus(&I2CD2);
    i2cMasterTransmit(&I2CD2, MPU_ADDR, mpu_txbuf, 2, mpu_rxbuf, 0);
    i2cReleaseBus(&I2CD2);

    chThdSleepMilliseconds(100);
}

/**
 * @brief   Write then Read to/from I2C bus
 * @param[in] addr Address to write. Typical 0x3B
 * @param[in] length Length of response. Typical 14
 * @note First three values are accelerometer.
 * @note Fourth one is temperature sensor.
 * @note Last three are gyro values.
 * @note Havent explored FIFO and interrupt part yet.
 */
void d_mpu_i2cReadData(u_int8_t addr, u_int8_t length){
    u_int8_t mpu_txbuf[20], mpu_rxbuf[20], i = 0;
    u_int16_t mpu_val[10];

    mpu_txbuf[0] = addr;
    for(i=0;i<length;i++)mpu_rxbuf[i] = 0x00;

    i2cAcquireBus(&I2CD2);
    i2cMasterTransmit(&I2CD2, MPU_ADDR, mpu_txbuf, 1, mpu_rxbuf, length);
    i2cReleaseBus(&I2CD2);

    mpu_val[0] = (mpu_rxbuf[0] << 8) + mpu_rxbuf[1];
    mpu_val[1] = (mpu_rxbuf[2] << 8) + mpu_rxbuf[3];
    mpu_val[2] = (mpu_rxbuf[4] << 8) + mpu_rxbuf[5];
    mpu_val[3] = (mpu_rxbuf[6] << 8) + mpu_rxbuf[7];
    mpu_val[4] = (mpu_rxbuf[8] << 8) + mpu_rxbuf[9];
    mpu_val[5] = (mpu_rxbuf[10] << 8) + mpu_rxbuf[11];
    mpu_val[6] = (mpu_rxbuf[12] << 8) + mpu_rxbuf[13];

    ax1 = mpu_val[0] * rangePerDigit * 9.80665f;
    ay1 = mpu_val[1] * rangePerDigit * 9.80665f;
    az1 = mpu_val[2] * rangePerDigit * 9.80665f;

    ax = abs(ax1-ax0);
    ay = abs(ay1-ay0);
    az = abs(az1-az0);

    ax0 = ax1;
    ay0 = ay1;
    az0 = az1;

    mag = d_mpu_vectorMag(ax,ay,az);

#if MPU_DEBUG
    chprintf((BaseSequentialStream *)&SD1, "Result:");
    chprintf((BaseSequentialStream *)&SD1, "\t%5.2f\t%5.2f\t%5.2f\t%5.2f",ax,ay,az,mag);
    chprintf((BaseSequentialStream *)&SD1, "\r\n");
#endif

}

void d_mpu_i2cReadFirst(u_int8_t addr, u_int8_t length){
    u_int8_t mpu_txbuf[20], mpu_rxbuf[20], i = 0;
    u_int16_t mpu_val[10];

    mpu_txbuf[0] = addr;
    for(i=0;i<length;i++)mpu_rxbuf[i] = 0x00;

    i2cAcquireBus(&I2CD2);
    i2cMasterTransmit(&I2CD2, MPU_ADDR, mpu_txbuf, 1, mpu_rxbuf, length);
    i2cReleaseBus(&I2CD2);

    mpu_val[0] = (mpu_rxbuf[0] << 8) + mpu_rxbuf[1];
    mpu_val[1] = (mpu_rxbuf[2] << 8) + mpu_rxbuf[3];
    mpu_val[2] = (mpu_rxbuf[4] << 8) + mpu_rxbuf[5];
    mpu_val[3] = (mpu_rxbuf[6] << 8) + mpu_rxbuf[7];
    mpu_val[4] = (mpu_rxbuf[8] << 8) + mpu_rxbuf[9];
    mpu_val[5] = (mpu_rxbuf[10] << 8) + mpu_rxbuf[11];
    mpu_val[6] = (mpu_rxbuf[12] << 8) + mpu_rxbuf[13];

    ax0 = mpu_val[0] * rangePerDigit * 9.80665f;
    ay0 = mpu_val[1] * rangePerDigit * 9.80665f;
    az0 = mpu_val[2] * rangePerDigit * 9.80665f;
    mag = d_mpu_vectorMag(ax0,ay0,az0);

#if MPU_DEBUG
    chprintf((BaseSequentialStream *)&SD1, "Result:");
    chprintf((BaseSequentialStream *)&SD1, "\t%5.2f\t%5.2f\t%5.2f\t%5.2f",ax,ay,az,mag);
    chprintf((BaseSequentialStream *)&SD1, "\r\n");
#endif

    adc00 = adc0;
}

///////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief   I2C Config Variable
 */
static const I2CConfig i2cfg = {
    OPMODE_I2C,
    400000,
    FAST_DUTY_CYCLE_2,
};

/**
 * @brief   Write to I2C bus
 * @param[in] vx Value of Accel at vector X
 * @param[in] vy Value of Accel at vector Y
 * @param[in] vz Value of Accel at vector Z
 * @return Magnitude of vector resultant
 */
float d_mpu_vectorMag(float vx, float vy, float vz){
    return sqrt( pow(vx,2) + pow(vy,2) + pow(vz,2) );
}

/**
 * @brief   Test ID of MPU60
 * @note    result must be either 0x68 or 0x69
 */
void d_mpu_whoAmI(void){
    u_int8_t tx_buff[8];
    u_int8_t rx_buff[8];

#if MPU_DEBUG
    i2cflags_t errors = 0;
    msg_t status = MSG_OK;
#endif

    tx_buff[0] = 0x75;

    i2cAcquireBus(&I2CD2);
#if MPU_DEBUG
    status = i2cMasterTransmit(&I2CD2, MPU_ADDR, tx_buff, 1, rx_buff, 2); //rx_buff length 1 failed
#else
    i2cMasterTransmit(&I2CD2, MPU_ADDR, tx_buff, 1, rx_buff, 2); //rx_buff length 1 failed
#endif
    i2cReleaseBus(&I2CD2);

#if MPU_DEBUG
    if (status != MSG_OK){
        errors = i2cGetErrors(&I2CD2);
        chprintf((BaseSequentialStream *)&SD1,"s=%i | e=%i\r\n",status,errors);
    }
    else{
        chprintf((BaseSequentialStream *)&SD1,"id: 0x%x\r\n",rx_buff[0]);
        chprintf((BaseSequentialStream *)&SD1,"i2c accel oke\r\n");
    }
#endif

}

/**
 * @brief   Setup for MPU60 module
 */
void d_mpu_setup(void){
    d_mpu_setSampleRate(9);
    d_mpu_configRegister(EXT_SYNC_SET0,DLPF_CFG0);
    d_mpu_setGyro(XG_ST_DIS,YG_ST_DIS,ZG_ST_DIS,FS_SEL_250);
    d_mpu_setAccel(XA_ST_DIS,YA_ST_DIS,ZA_ST_DIS,AFS_SEL_2g,ACCEL_HPF0);
    d_mpu_powerMGMT1(DEVICE_RESET_DIS,SLEEP_DIS,CYCLE_DIS,TEMPERATURE_EN,CLKSEL_XG);
    d_mpu_userControl(USER_FIFO_DIS, I2C_MST_DIS, I2C_IF_DIS, FIFO_RESET_DIS, I2C_MST_RESET_DIS, SIG_COND_RESET_DIS);

    d_mpu_writePowerMGMT1();
    d_mpu_writeGyro();
    d_mpu_writeAccel();
    d_mpu_writeSampleRate();
}

/**
 * @brief   Start I2C Peripheral and MPU60 module
 */
void d_mpu_start(void){
    palSetPadMode(GPIOB, 10, PAL_MODE_STM32_ALTERNATE_OPENDRAIN );   /* SCL */
    palSetPadMode(GPIOB, 11, PAL_MODE_STM32_ALTERNATE_OPENDRAIN );   /* SDA */
    i2cStart(&I2CD2, &i2cfg);

    chThdSleepMilliseconds(200);
    d_mpu_setup();

    chThdSleepMilliseconds(200);
    d_mpu_whoAmI();

    chThdSleepMilliseconds(200);
    d_mpu_i2cReadFirst(0x3B,14);
}
/** @} */
