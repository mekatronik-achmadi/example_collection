//id:main.cpp,uart_soft,
//13-8-2012,sidiknur@yahoo.com
//Atmega8, 8MHz-internal

#include <avr/io.h>
#include "../uart_avr2avr/uart_soft.h"

int main(void)
{
    UartSoft_8N1<PB,0,PB,1,BAUD_9600> serial;

    serial.PutStr("selamat datang");
    while(1){

    }

    return 0;
}
