//id:main.cpp,uart_master,uart_avr2avr
//12-8-2012,sidiknur@yahoo.com
//Atmega8,11059200Hz eksternal
#include <avr/io.h>
#include <stdlib.h>

#include "../textlcd.h"
#include "../uart_soft.h"

#define CMD_READ_SUHU   'A'
#define CMD_READ_POT    'P'

int main(void)
{
    uint16_t data;
    char str[10];

    TextLCD<PB,0,PB,1,PB,3,PD,3,PD,4,PD,5,16> Display;
    UartSoft_8N1<PD,6,PD,7,BAUD_9600> serial;

    while(1){
        serial.PutChar(CMD_READ_POT);
        data = (uint8_t)serial.GetChar();
        data <<= 8;
        data += (uint8_t)serial.GetChar();

        Display.GotoXY(1,1);
        Display.PutStr("Pot=");
        utoa(data,str,10);
        Display.PutStr(str);
        Display.PutStr("    ");

        serial.PutChar(CMD_READ_SUHU);
        data = serial.GetChar();
        Display.GotoXY(2,1);
        Display.PutStr("LM35=");
        utoa(data,str,10);
        Display.PutStr(str);
        Display.PutStr("    ");
    }

    return 0;
}
