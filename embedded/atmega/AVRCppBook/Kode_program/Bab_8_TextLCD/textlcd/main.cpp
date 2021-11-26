//id:main.cpp,textlcd,2-8-2012,sidiknur@yahoo.com
//Atmega8,8MHz-internal

#include <avr/io.h>
#include <stdlib.h>

#include "textlcd.h"

int main(void)
{
    uint8_t data = 0;
    char str[10];

    TextLCD<PC,3,PD,1, PD,2,PD,3,PD,4,PD,5,16> Display;

    Display.PutStr("Testing LCD");
    while(1){
        utoa(data,str,10);
        Display.GotoXY(2,1);
        Display.PutStr("Counter: ");
        Display.PutStr(str);
        Display.PutStr("    ");
        data++;
        _delay_ms(250);
    }

    return 0;
}
