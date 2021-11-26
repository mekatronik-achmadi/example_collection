//id:main.cpp,lcd_serial_master
//13-8-2012,sidiknur@yahoo.com
//Atmega8,11059200Hz-internal

#include <avr/io.h>
#include "../lcd_serial.h"

int main(void)
{
    LcdSerial<2,16> lcd;

    lcd.PutStr("LCD serial");
    lcd.GotoXY(2,1);
    lcd.PutStr("melalui UART");
    while(1){

    }

    return 0;
}
