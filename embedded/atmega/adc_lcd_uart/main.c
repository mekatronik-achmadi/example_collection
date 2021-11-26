#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/eeprom.h>
#include <avr/pgmspace.h>

#include "alcd.h"
#include "adc.h"
#include "uart.h"

extern uint16_t adc0;
extern char lcd_buffer[16];

int main(void){

    LCD_Init();
    LCD_Clear();

    LCD_String(0,0,"Bimo Jones nes");

    UART_Init();

    while(1){
        adc0 = ADC_Read(0);
        sprintf(lcd_buffer,"adc0 = %4i",adc0);
        LCD_String(0,1,lcd_buffer);
   }

    return 0;
}
