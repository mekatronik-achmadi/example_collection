#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>

#include "lcdpcf8574.h"
#include "icp.h"

extern volatile uint32_t period;

int main(void){
		char text[16];

		icp_init();

		lcd_init(LCD_DISP_ON);
		lcd_led(0);
		lcd_clrscr();
		lcd_home();


		lcd_gotoxy(0,0);
   		lcd_puts("test I2C LCD");

		while(1){

			sprintf(text,"I=%10lu",period);
			lcd_gotoxy(0,1);
			lcd_puts(text);
		}

		return 0;
}
