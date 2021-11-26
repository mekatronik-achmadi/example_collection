//id:main.cpp,sevenseg_7448,sidiknur@yahoo.com
//Atmega8, 8MHz-internal
#include <avr/io.h>
#include <util/delay.h>

#include "sevenseg_7448.h"

int main(void)
{
    SevenSeg7448_3dgt<PD,NIBLE_HIGH,PD,NIBLE_LOW,PC,NIBLE_LOW> Display;

    uint16_t i = 0;
    while(1){
        Display.Put(i);
        _delay_ms(250);
        if(++i>999)
            i = 0;
    }

    return 0;
}
