//id:main.cpp,uart,3-8-2012,sidiknur@yahoo.com
//ATmega8,11059200Hz external

#include <avr/io.h>

#include "uart.h"

int main(void)
{
    Uart_8N1<BAUD_9600> uart;

    uart.PutStr("Testing serial\n");

    while(1){

    }

    return 0;
}
