//id:main.cpp,portin,sidiknur@yahoo.com
//22-8-2012
//Atmega8,8MHz-internal

#include <avr/io.h>
#include <util/delay.h>

#include "portin.h"
#include "portout.h"

int main(void)
{
    uint8_t data;

    PortIn<PB,PULLUP> Switch;
    PortOut<PD> Led;

    while(1){
        data = Switch.Get();
        Led.Put(data);
        _delay_ms(100);
    }


    return 0;
}
