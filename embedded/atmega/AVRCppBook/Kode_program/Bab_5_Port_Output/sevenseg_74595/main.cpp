//id:main.cpp,sevenseg_74595,
//1-8-2012,sidiknur@yahoo.com
#include <avr/io.h>
#include <util/delay.h>

#include "sevenseg_74595.h"

int main(void)
{
    uint16_t data = 0;
    SevenSeg_74595<PC,0,PB,0,PB,2,3> Display;

    while(1){

        Display.Put(data);
        if(++data>999)
            data = 0;
        _delay_ms(250);
    }
    ;

    return 0;
}
