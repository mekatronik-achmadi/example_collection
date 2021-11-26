#ifndef VAR_H
#define VAR_H

//this is just a help file. DON'T USE THIS FILE DIRECTLY!

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/eeprom.h>
#include <avr/pgmspace.h>

typedef no_value	void

typedef character	char

typedef v8			char
typedef v8_u 		unsigned char
typedef v8_t		uint8_t

typedef v16			int
typedef v16_u		unsigned int
typedef	v16_t		uint16_t

typedef v32			long
typedef v32_u		unsigned long
typedef v32_t		uint32_t

typedef ratio		float

typedef large_val	double

#define in_file		extern
#define no_changes	static
#define var_in_IRQ	volatile
#define bit_size(x)	sizeof(x)

#define XTAL	8000000UL
#define CLOCK	1000000L
#define Hexa8	0xFF
#define Hexa16	0xFFFF
#define Decimal	255
#define Octal	0377
#define	Biner	0b11111111

/*
array[8]={bit_0,bit_1,bit_2,bit_3,bit_4,bit_5,bit_6,bit_7};

char string[8]={"avr-gcc"}={'a','v','r','-','g','c','c','\0'}

uint16_t *pointer=&var_vectored;

enum pin {bit_0,bit_1,bit_2,bit_3,bit_4,bit_5,bit_6,bit_7};

struct gpio_conf {uint8_t DDRx;uint8_t PINx;uint8_t PORTx;} GPIO;

const float pi=3.14

result= (typecast) statement;

const uint16_t ex_rom_var PROGMEM = value;
*/


#define flash_type					PROGMEM
#define flash_read8(&pgm_var)		pgm_read_byte(&pgm_var)
#define flash_read16(&pgm_var)		pgm_read_word(&pgm_var)

#define eeprom_type					EEMEM
#define ee_read8(&ee_var)			eeprom_read_byte(&ee_var)
#define ee_read16(&ee_var)			eeprom_read_word(&ee_var)
#define ee_write8(&ee_var,ram_var)	eeprom_write_byte(&ee_var,ram_var)
#define ee_write16(&ee_var,ram_var)	eeprom_write_word(&ee_var,ram_var)

#endif