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
 * @file    reg_mpu.h
 * @brief   MPU Sensor register collection header.
 *
 * @addtogroup MPU60
 * @{
 */

#ifndef DIN_ACCELREG_H
#define DIN_ACCELREG_H

/////////////////////////// Register (hasil nyolong kerjaan orang) /////////////////////////
#define MPU_ADDR_LO     0x68 //AD0 to GND
#define MPU_ADDR_HI     0x68 //AD0 to VDD

#define AUX_VDDIO 			0x01
#define SMPRT_DIV 			0x19
#define CONFIG				0x1A
#define GYRO_CONFIG			0x1B
#define ACCEL_CONFIG		0x1C
#define FIFO_EN				0x23
#define INT_PIN_CFG			0x37
#define INT_ENABLE			0x38
#define SIGNAL_PATH_RESET	0x68	/* Write Only Register */
#define USER_CTRL			0x6A
#define PWR_MGMT_1			0x6B	/* Default value 0x40 */
#define PWR_MGMT_2			0x6C

#define INT_STATUS          0x3A 	/* Read Only Register. Status of each interrupt generation source */

/*
 * FIFO Counter register must be read in high-low order in order to get accurate FIFO Count
 */
#define FIFO_COUNT_H	0x72	/* Read Only Register */
#define FIFO_COUNT_L	0x73	/* Read Only Register */

/*
 * Data is written to the FIFO in order of register number (from lowest to highest). If all the FIFO enable
 * flags  (see  below)  are  enabled  and  all  External  Sensor  Data  registers  (Registers  73  to  96)  are
 * associated with a Slave device, the contents of registers 59 through 96 will be written in order at the Sample Rate.
 */
#define FIFO_R_W		0x74
#define WHO_AM_I		0x75 	/* Read Only Register. Default value 0x68 */

/*
 * Register output
 */

#define ACCEL_XOUT_H	0x3B	/* Read Only Register */
#define ACCEL_XOUT_L	0X3C	/* Read Only Register */
#define ACCEL_YOUT_H	0x3D	/* Read Only Register */
#define ACCEL_YOUT_L	0X3E	/* Read Only Register */
#define ACCEL_ZOUT_H	0x3F	/* Read Only Register */
#define ACCEL_ZOUT_L	0X40	/* Read Only Register */
#define TEMP_OUT_H		0x41	/* Read Only Register */
#define TEMP_OUT_L		0x42	/* Read Only Register */
#define GYRO_XOUT_H		0x43	/* Read Only Register */
#define GYRO_XOUT_L		0x44	/* Read Only Register */
#define GYRO_YOUT_H		0x45	/* Read Only Register */
#define GYRO_YOUT_L		0x46	/* Read Only Register */
#define GYRO_ZOUT_H		0x47	/* Read Only Register */
#define GYRO_ZOUT_L		0x48	/* Read Only Register */

/*
 * The reset value is 0x00 for all registers other than following registers
 * Register 0x6B Default Value 0x40.
 * Register 0x75 Default Value 0x68.
 */

/*
 * EXT_SYNC_SET and DLPF_CFG is part of CONFIG Register
 */

/*
 * Configures External Frame Synchronization Pin Sampling.
 */
#define EXT_SYNC_SET0		0<<3	/* Disable Input. Use this in pluto since FSYNC pin is not used. */
#define EXT_SYNC_SET1		1<<3
#define EXT_SYNC_SET2		2<<3
#define EXT_SYNC_SET3		3<<3
#define EXT_SYNC_SET4		4<<3
#define EXT_SYNC_SET5		5<<3
#define EXT_SYNC_SET6		6<<3
#define EXT_SYNC_SET7		7<<3

/*
 * Digital Low Pass Filter is configured by DLPF_CFG Register
 * | DLPF_CFG	|	Accelerometer (FS = 1kHz)	|			 Gyroscope							|
 * |			|	Bandwidth(Hz)	| Delay (ms)|	Bandwidth(Hz)	| Delay (ms)	| FS (kHz)	|
 * |------------|-------------------|-----------|-------------------|---------------|-----------|
 * |    0		|	260				| 0			|	256				| 0.98			| 8			|
 * |    1		|	180				| 2.0		|	188				| 1.9			| 1			|
 * |	2		|	94				| 3.0		|	98				| 2.8			| 1			|
 * |	3		|	44				| 4.9		| 	42				| 4.8			| 1			|
 * |	4		|	21				| 8.5		| 	20				| 8.3			| 1			|
 * |	5		|	10				| 13.8		| 	10				| 13.4			| 1			|
 * |	6		|	5				| 19.0		| 	5				| 18.6			| 1			|
 * |	7		|	RESERVED			 		| 	RESERVED						| 8			|
 * |------------|-------------------------------|-----------------------------------|-----------|
 */
#define DLPF_CFG0			0
#define DLPF_CFG1			1
#define DLPF_CFG2			2
#define DLPF_CFG3			3
#define DLPF_CFG4			4
#define DLPF_CFG5			5
#define DLPF_CFG6			6

/*
 * Gyro self test and Gyro range select registers are part of GYRO_CONFIG register.
 * Self test of each Gyroscope can be activated by controlling XG_ST, YG_ST and ZG_ST bit of GYRO_CONFIG register.
 * Self test of each axis can be performed simultaneously or independently.
 * Self test output = output with self test enabled - output with self test disabled.
 */
#define XG_ST_EN			1<<7
#define XG_ST_DIS			0<<7
#define YG_ST_EN			1<<6
#define YG_ST_DIS			0<<6
#define ZG_ST_EN			1<<5
#define ZG_ST_DIS			0<<5

/*
 * FS_SEL selects full scale range of gyroscope outputs.
 */
#define FS_SEL_250			0<<3
#define FS_SEL_500			1<<3
#define FS_SEL_1000			2<<3
#define FS_SEL_2000			3<<3

/*
 * Accelerometer self test, Accelerometer range select and DHPF (Digital high pass filter ) are part of
 * ACCEL_CONFIG register.
 * Self test of each Accelerometer can be activated by controlling XA_ST, YA_ST and ZA_ST bit of ACCEL_CONFIG register.
 * Self test of each axis can be performed simultaneously or independently.
 * Self test output = output with self test enabled - output with self test disabled.
 */
#define XA_ST_EN			1<<7
#define XA_ST_DIS			0<<7
#define YA_ST_EN			1<<6
#define YA_ST_DIS			0<<6
#define ZA_ST_EN			1<<5
#define ZA_ST_DIS			0<<5

/*
 * AFS_SEL selects full scale range of accelerometer outputs.
 */
#define AFS_SEL_2g			0<<3
#define AFS_SEL_4g			1<<3
#define AFS_SEL_8g			2<<3
#define AFS_SEL_16g			3<<3

/*
 * ACCEL_HPF configures DHPF available in the path leading to motion detectors (Free fall,
 * Motion threshold,Zero Motion).
 * This high pass filter output is not available to the data registers.
 * When 0 this filter is disabled, when in hold mode is triggered filter holds the present sample and output will be
 * difference between input sample and held sample.
 */
#define ACCEL_HPF0			0
#define ACCEL_HPF5Hz		1
#define ACCEL_HPF2Hz5		2
#define ACCEL_HPF1Hz25		3
#define ACCEL_HPF0Hz63		4
#define ACCEL_HPFHOLD		7

/*
 * TMEP_FIFO, GYRO_FIFO, ACCEL_FIFO and SLVx_FIFO are part of FIFO Enable Register.
 * When corresponding FIFO bit is enabled that particular data is written FIFO.
 */
#define TEMP_FIFO_EN		1<<7
#define TEMP_FIFO_DIS		0<<7
#define XG_FIFO_EN			1<<6
#define XG_FIFO_DIS			0<<6
#define YG_FIFO_EN			1<<5
#define XG_FIFO_DIS			0<<6
#define ZG_FIFO_EN			1<<4
#define ZG_FIFO_DIS			0<<4
#define ACCEL_FIFO_EN		1<<3
#define ACCEL_FIFO_DIS		0<<3
#define SLV2_FIFO_EN		1<<2
#define SLV2_FIFO_DIS		0<<2
#define SLV1_FIFO_EN		1<<1
#define SLV1_FIFO_DIS		0<<1
#define SLV0_FIFO_EN		1<<0
#define SLV0_FIFO_DIS		0<<0

/*
 * These are part of INT_PIN_CFG registers. They configures behavior of interrupt signal at INT Pin.
 */
#define INT_LEVEL_LOW		1<<7	/* Logic level for INT pin is active low */
#define INT_LEVEL_HIGH		0<<7	/* Logic level for INT pin is active high */
#define INT_OPEN_EN			1<<6 	/* INT pin is open-drain */
#define INT_OPEN_DIS		0<<6 	/* INT pin is push-pull  */
#define LATCH_INT_EN		1<<5	/* INT pin is held high until the interrupt it cleared */
#define LATCH_INT_DIS		0<<5	/* INT pin emits 50uS long pulse */
#define INT_RD_CLEAR_EN		1<<4 	/* Interrupt status bits are cleared by any read operation */
#define INT_RD_CLEAR_DIS	0<<4 	/* Interrupt status bits are cleared by only by reading INT_STATUS */
#define FSYNC_INT_LEVEL_LOW		1<<3	/* Logic level on FSYNC pin is active low (When FSYNC is configured as interrupt) */
#define FSYNC_INT_LEVEL_HIGH	0<<3	/* Logic level on FSYNC pin is active high (When FSYNC is configured as interrupt) */
#define FSYNC_INT_EN		1<<2	/* FSYNC interrupt is enabled */
#define FSYNC_INT_DIS		0<<2	/* FSYNC interrupt is disabled */
#define I2C_BYPASS_EN		1<<1 	/* When I2C_MST_EN = 1 direct access between host and auxiliary I2C */
#define I2C_BYPASS_DIS		0<<1 	/* No direct access between host and auxiliary I2C */
#define CLOCK_EN			1<<0	/* Reference clout output is provided at the CLKOUT pin  */
#define CLOCK_DIS			0<<0	/* Clock output is disabled */

/*
 * These are part of INT_ENABLE registers. They controls interrupt generation sources.
 */
#define FF_EN				1<<7 	/* Enable Free Fall detection to generate interrupt */
#define FF_DIS				0<<7
#define MOT_EN				1<<6	/* Enables Motion detection to generate interrupt */
#define MOT_DIS				0<<6
#define ZMOT_EN				1<<5	/* Enables Zero Motion Detection to generate interrupt */
#define ZMOT_DIS			0<<5
#define FIFO_OFLOW_EN		1<<4	/* Enables fifo buffer overflow to generate interrupt */
#define FIFO_OFLOW_DIS		0<<4
#define I2C_MST_INT_EN		1<<3	/* Enable any of I2C master sources to generate interrupt */
#define I2C_MST_INT_DIS		0<<3
#define DATA_RDY_EN			1<<0	/* Data ready interrupt. Generated each time write operation to all sensors registers is completed */
#define DATA_RDY_DIS		0<<0

/*
 * These are part of SIGNAL_PATH_RESET register.
 * Bits in this register are used to reset analog and digital signal path of gyro, accelerometer and
 * temperature sensor.
 */
#define GYRO_RESET_EN		1<<2	/* Resets gyroscope analog and digital paths */
#define GYRO_RESET_DIS		0<<2
#define ACCEL_RESET_EN		1<<1	/* Reset accelerometer analog and digital paths */
#define ACCEL_RESET_DIS		0<<1
#define TEMP_RESET_EN		1<<0	/* Reset temperature analog and digital paths */
#define TEMP_RESET_DIS		0<<0

/*
 * These are part of USER_CTRL register. They allows user to enable or disable FIFO buffer, I2C master mode  and
 * primary I2C interface.
 */
#define USER_FIFO_EN		1<<6	/* Enables fifo operations */
#define USER_FIFO_DIS		0<<6	/* Disables fifo operations */
#define I2C_MST_EN			1<<5	/* Enable I2C master mode. When cleared auxiliary I2C = primary I2C */
#define I2C_MST_DIS			0<<5	/* Disables I2C master mode. When cleared auxiliary I2C = primary I2C */
#define I2C_IF_EN			1<<4 	/* Enables SPI in MPU6000. Always write 0 in MPU6050 */
#define I2C_IF_DIS			0<<4	/* Disables SPI in MPU6000. Always write 0 in MPU6050 */
#define FIFO_RESET_EN		1<<2	/* Enables fifo reset when USER_FIFO_EN = 1 */
#define FIFO_RESET_DIS		0<<2	/* Disables fifo reset  */
#define I2C_MST_RESET_EN	1<<1	/* Resets I2C master */
#define I2C_MST_RESET_DIS	0<<1
#define SIG_COND_RESET_EN	1<<0	/* Resets signal paths and sensor registers */
#define SIG_COND_RESET_DIS	0<<0

/*
 * These are part of PWR_MGMT_1 register. These allows user to configure power mode and clock source
 */
#define DEVICE_RESET_EN		1<<7	/* Rsets all internal registers to their default values */
#define DEVICE_RESET_DIS	0<<7
#define SLEEP_EN			1<<6	/* Puts device into sleep mode */
#define SLEEP_DIS			0<<6
#define CYCLE_EN			1<<5	/* When 1 and sleep is disabled device will cycle between sleep and measurement mode at rate determined by LP_WAKE_CTRL*/
#define CYCLE_DIS			0<<5
#define TEMPERATURE_DIS		1<<3	/* Disables temperature sensor */
#define TEMPERATURE_EN		0<<3	/* Enables temperature sensor */
#define CLKSEL0				0		/* Internal 8 MHz clock source */
#define CLKSEL_XG			1		/* PLL with X axis gyroscope reference */
#define CLKSEL_YG			2		/* PLL with Y axis gyroscope reference */
#define CLKSEL_ZG			3		/* PLL with Z axis gyroscope reference */
#define CLKSEL_32Khz		4		/* PLL with external 32.768 kHz reference */
#define CLKSEL_19MHz		5		/* PLL with external 19.2MHzreference */

#endif // DIN_ACCELREG_H
/** @} */
