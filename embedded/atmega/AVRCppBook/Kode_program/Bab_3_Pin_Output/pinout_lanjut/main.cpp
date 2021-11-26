//Id:main.cpp,pinout_lanjut,1-8-2012,sidiknur@yahoo.com
//ATmega8
#include <avr/io.h>
#include <util/delay.h>
#include "led.h"

int main(void)
{
    LED<PB,1,ACTIVE_HIGH> LED_MERAH;
    LED<PC,2,ACTIVE_LOW> LED_KUNING;

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
