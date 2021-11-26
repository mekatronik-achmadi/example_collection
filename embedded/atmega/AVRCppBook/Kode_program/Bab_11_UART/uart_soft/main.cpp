//:main.cpp,uart_soft,4-8-2012,sidiknur@yahoo.com
//ATemga8,11059200Hz-eksternal

#include <avr/io.h>
#include "uart_soft.h"
int main(void)
{

    UartSoft_8N1<PD,1,PD,0,BAUD_9600> uart_soft;

    uart_soft.PutStr("Tes UartSoft");
    while(1){

    }

    return 0;
}
