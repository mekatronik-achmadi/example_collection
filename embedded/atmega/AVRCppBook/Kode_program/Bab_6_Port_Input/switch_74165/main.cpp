//id:main.cpp,switch_74165,sidiknur@yahoo.com
//22-8-2012
//Atmega8, 8MHz-internal

#include <avr/io.h>
#include <util/delay.h>

#include "_74165.h"
#include "_74595.h"
#include "portout.h"

int main(void)
{
    uint8_t data[2];

    _74165<2,PB,1,PB,2,PB,3> Switch;
    _74595<PD,2,PD,3,PD,4> Led;

    while(1){
        Switch.Get(data);
        Led.Put(data,sizeof(data)/sizeof(data[0]));
        _delay_ms(100);
    }

    return 0;
}
