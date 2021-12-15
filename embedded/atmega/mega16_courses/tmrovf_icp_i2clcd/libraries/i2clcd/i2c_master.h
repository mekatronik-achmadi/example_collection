#ifndef I2C_MASTER_H_INCLUDED
#define I2C_MASTER_H_INCLUDED

#include <avr/io.h>
#include <util/twi.h>

#ifndef  F_CPU
    #define F_CPU 8000000UL
#endif

#define I2C_READ 0x01
#define I2C_WRITE 0x00

#define F_SCL 100000UL // SCL frequency
#define Prescaler 1
#define TWBR_val ((((F_CPU / F_SCL) / Prescaler) - 16 ) / 2)

void i2c_init(void);
unsigned char i2c_start(unsigned char address);
unsigned char i2c_write(unsigned char data);
unsigned char i2c_readack(void);
unsigned char i2c_readnak(void);
void i2c_stop(void);

#endif // I2C_MASTER_H_INCLUDED
