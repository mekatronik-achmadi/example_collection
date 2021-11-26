//id:main.cpp,pinin,1-8-2012,sidiknur@yahoo.com
//Atmega8,8MHz internal
#include <avr/io.h>
//#include "pinin.h"
#include "tombol.h"
#include "LED.h"

int main(void)
{
    //PinIn<PC,4,PULLUP> TOMBOL;
    Tombol<PC,4,ACTIVE_LOW> TOMBOL;
    LED<PC,5,ACTIVE_LOW> LED_MERAH;

    while(1){
        //if(TOMBOL.IsClear())
        if(TOMBOL.IsPressed())
            LED_MERAH.On();
        else
            LED_MERAH.Off();
    }
    return 0;
}
