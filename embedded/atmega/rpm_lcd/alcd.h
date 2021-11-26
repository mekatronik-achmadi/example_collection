#ifndef _ALCD_H_
#define _ALCD_H_

// preprocessor untuk avr-gcc
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/eeprom.h>
#include <avr/pgmspace.h>

#define LCD_RS		0
#define LCD_RW		1
#define LCD_E		2
#define LCD_D4		4
#define LCD_D5		5
#define LCD_D6		6
#define LCD_D7		7

#define LDP		PORTD
#define LCP		PORTD
#define LDDR	DDRD
#define LCDR	DDRD

#define LCD_CGRAM 6
#define LCD_DDRAM 7
#define LCD_CLR   0

#define LCD_LINE0_DDRAMADDR		0x00
#define LCD_LINE1_DDRAMADDR		0x40
#define LCD_LINE2_DDRAMADDR		0x14
#define LCD_LINE3_DDRAMADDR		0x54

void LCD_Init(void);
void LCD_Clear(void);
void LCD_XY(uint8_t x, uint8_t y);
void LCD_String(uint8_t x, uint8_t y, char *ptr);

#endif
