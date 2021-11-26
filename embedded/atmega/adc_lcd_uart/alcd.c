#include "alcd.h"

char lcd_buffer[16];

static void LCDsendChar(uint8_t ch){
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
	return;
}

static void LCDsendCommand(uint8_t cmd){
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
	return;
}

void LCD_Init(void){

	_delay_ms(15);
	LDP=0x00;
	LCP=0x00;
	LDDR|=1<<LCD_D7|1<<LCD_D6|1<<LCD_D5|1<<LCD_D4;
    LCDR|=1<<LCD_E|1<<LCD_RS;
	LDP=0<<LCD_D7|0<<LCD_D6|1<<LCD_D5|0<<LCD_D4; //4 bit mode
    LCP|=1<<LCD_E|0<<LCD_RS;
	_delay_ms(1);
	LCP&=~(1<<LCD_E);
	_delay_ms(1);
	LCDsendCommand(0x28);
	LCDsendCommand(0x0c);
	return;
}

void LCD_Clear(void){
	LCDsendCommand(1<<LCD_CLR);
	return;
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
	return;
}

void LCD_String(uint8_t x, uint8_t y, char *ptr){
    LCD_XY(x,y);

    while (*ptr != 0) {
    LCDsendChar(*ptr);
    ptr++;
    }

}
