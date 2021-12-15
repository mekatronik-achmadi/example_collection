#ifndef ALCD_H_INCLUDED
#define ALCD_H_INCLUDED

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LCD_RS		0
#define LCD_RW		1
#define LCD_E		2
#define LCD_D4		4
#define LCD_D5		5
#define LCD_D6		6
#define LCD_D7		7

#define LDP     PORTC
#define LCP     PORTC
#define LDDR    DDRC
#define LCDR    DDRC

#define LCD_CGRAM 6
#define LCD_DDRAM 7
#define LCD_CLR   0

#define LCD_LINE0_DDRAMADDR 0x00
#define LCD_LINE1_DDRAMADDR 0x40
#define LCD_LINE2_DDRAMADDR 0x14
#define LCD_LINE3_DDRAMADDR 0x54

void alcd_init(void);
void alcd_clear(void);
void alcd_xy(uint8_t x, uint8_t y);
void alcd_printf(uint8_t x, uint8_t y, char *ptr);

#endif // ALCD_H_INCLUDED
