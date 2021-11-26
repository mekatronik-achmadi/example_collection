//Id:main.cpp,intro2cpp,1-8-2012,sidiknur@yahoo.com
//Atmega8,8MHz-internal

#include <avr/io.h>
#include <util/delay.h>
#include "pinout.h"

int main(void)
{
    PinOut LED_MERAH(PB,1);
    PinOut LED_KUNING(PC,2);

    while(1){
        LED_MERAH.On();
        LED_KUNING.Off();
        _delay_ms(500);

        LED_MERAH.Off();
        LED_KUNING.On();
        _delay_ms(500);
    }
    return 0;
}
