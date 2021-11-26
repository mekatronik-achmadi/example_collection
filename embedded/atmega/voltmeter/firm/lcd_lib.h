#ifndef LCD_H
#define LCD_H

//this is just a help file. DON'T USE THIS FILE DIRECTLY!

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

//===============================================================================================

static int lcd_putchar(char ch,FILE*stream)
{
	if(ch=='\n'){lcd_putchar('\r',stream);}
	LCDsendChar(ch);
	return 0;
}

static FILE lcd_stdout=FDEV_SETUP_STREAM(lcd_putchar,NULL,_FDEV_SETUP_WRITE);

#define LCD_Out stdout=&lcd_stdout;

//===============================================================================================

void LCDsendChar(uint8_t ch)
{
	LDP=(ch&0b11110000);
	LCP|=1<<LCD_RS;
	LCP|=1<<LCD_E;		
	_delay_ms(1);
	LCP&=~(1<<LCD_E);	
	LCP&=~(1<<LCD_RS);
	_delay_ms(1);
	LDP=((ch&0b00001111)<<4);
	LCP|=1<<LCD_RS;
	LCP|=1<<LCD_E;		
	_delay_ms(1);
	LCP&=~(1<<LCD_E);	
	LCP&=~(1<<LCD_RS);
	_delay_ms(1);
}

void LCDsendCommand(uint8_t cmd)
{
	LDP=(cmd&0b11110000);
	LCP|=1<<LCD_E;		
	_delay_ms(1);
	LCP&=~(1<<LCD_E);
	_delay_ms(1);
	LDP=((cmd&0b00001111)<<4);	
	LCP|=1<<LCD_E;		
	_delay_ms(1);
	LCP&=~(1<<LCD_E);
	_delay_ms(1);
}

void LCD_Init(void){

	stdout=&lcd_stdout;
	_delay_ms(15);
	LDP=0x00;
	LCP=0x00;
	LDDR|=1<<LCD_D7|1<<LCD_D6|1<<LCD_D5|1<<LCD_D4;
	LCDR|=1<<LCD_E|1<<LCD_RW|1<<LCD_RS;
	LDP=0<<LCD_D7|0<<LCD_D6|1<<LCD_D5|0<<LCD_D4; //4 bit mode
	LCP|=1<<LCD_E|0<<LCD_RW|0<<LCD_RS;		
	_delay_ms(1);
	LCP&=~(1<<LCD_E);
	_delay_ms(1);
	LCDsendCommand(0x28);
	LCDsendCommand(0x0c);
}

void LCD_Clear(void){
	LCDsendCommand(1<<LCD_CLR);
}
 
void LCD_XY(uint8_t x, uint8_t y){
	register uint8_t DDRAMAddr;
	switch(y)
	{
	case 0: DDRAMAddr = LCD_LINE0_DDRAMADDR+x; break;
	case 1: DDRAMAddr = LCD_LINE1_DDRAMADDR+x; break;
	case 2: DDRAMAddr = LCD_LINE2_DDRAMADDR+x; break;
	case 3: DDRAMAddr = LCD_LINE3_DDRAMADDR+x; break;
	default: DDRAMAddr = LCD_LINE0_DDRAMADDR+x;
	}
	LCDsendCommand(1<<LCD_DDRAM | DDRAMAddr);
}

#endif