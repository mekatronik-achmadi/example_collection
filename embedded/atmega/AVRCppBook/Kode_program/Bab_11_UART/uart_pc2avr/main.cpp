//id:main.cpp,uart_pc2avr,
//12-8-2012,sidiknur@yahoo.com
//ATmega8,11059200Hz external

#include <avr/io.h>
#include <stdlib.h>
#include <string.h>
#include <util/delay.h>

#include "uart.h"
#include "adc.h"

int main(void)
{
    char id[] = "ABCD";
    uint8_t data[4];
    char str[5];
    uint8_t len;

    Uart_8N1<BAUD_9600> uart;
    Adc<ADC_REF_2V56,ADC_RES8,0> SuhuA;
    Adc<ADC_REF_2V56,ADC_RES8,1> SuhuB;
    Adc<ADC_REF_2V56,ADC_RES8,2> SuhuC;
    Adc<ADC_REF_2V56,ADC_RES8,3> SuhuD;

    uart.PutStr("UART PC2AVR\r\n");

    while(1){
        data[0] = SuhuA.Get();
        data[1] = SuhuB.Get();
        data[2] = SuhuC.Get();
        data[3] = SuhuD.Get();
        for(uint8_t i=0; i<4; i++){
            uart.PutChar(id[i]);
            uart.PutChar('=');
            utoa(data[i],str,10);
            len = 3-strlen(str);
            while(len--)
                uart.PutChar(' ');
            uart.PutStr(str);
            uart.PutStr(" ");
        }
        uart.PutStr("\r\n");
        _delay_ms(250);
    }
    return 0;
}
