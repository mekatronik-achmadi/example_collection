//id:main.cpp,sevenseg_direct,1-8-2012,sidiknur@yahoo.com

#include <avr/io.h>
#include <util/delay.h>

#include "sevenseg_direct.h"

int main(void)
{
    uint8_t data = 0;
    SevenSeg_Direct_2dgt<PB,PD> Display;

    while(1){
        Display.Put(data);
        if(++data>99)
            data = 0;
        _delay_ms(500);
    }


    return 0;
}
