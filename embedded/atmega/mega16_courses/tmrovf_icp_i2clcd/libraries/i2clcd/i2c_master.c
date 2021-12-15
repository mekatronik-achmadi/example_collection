#include "i2c_master.h"

void i2c_init(void){
	DDRC |= 1<<0;
    TWBR = TWBR_val;
}

unsigned char i2c_start(unsigned char address){
    TWCR = 0;
    TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);

    while( !(TWCR & (1<<TWINT)) );
    if((TWSR & 0xF8) != TW_START){ return 1; }

    TWDR = address;
    TWCR = (1<<TWINT) | (1<<TWEN);
    while( !(TWCR & (1<<TWINT)) );

    uint8_t twst = TW_STATUS & 0xF8;
	if ( (twst != TW_MT_SLA_ACK) && (twst != TW_MR_SLA_ACK) ) return 1;

	return 0;
}

unsigned char i2c_write(unsigned char data){
    TWDR = data;

    TWCR = (1<<TWINT) | (1<<TWEN);
    while( !(TWCR & (1<<TWINT)) );

    if( (TWSR & 0xF8) != TW_MT_DATA_ACK ){ return 1; }

    return 0;
}

unsigned char i2c_readack(void){
    TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWEA);
    while( !(TWCR & (1<<TWINT)) );
    return TWDR;
}

unsigned char i2c_readnak(void){
    TWCR = (1<<TWINT) | (1<<TWEN);
    while( !(TWCR & (1<<TWINT)) );
    return TWDR;
}

void i2c_stop(void){
    TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
}
