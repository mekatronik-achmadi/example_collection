//Id:main.cpp,pinout,1-8-2012,sidiknur@yahoo.com

#include <avr/io.h>
#include <util/delay.h>
#include "pinout.h"

int main(void)
{
    PinOut<PB,1> LED_MERAH;
    PinOut<PC,2> LED_KUNING;

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
