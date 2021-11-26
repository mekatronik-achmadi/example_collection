//id:main.cpp,portout,1-8-2012,sidiknur@yahoo.com
#include <avr/io.h>
#include <util/delay.h>

#include "portout.h"


int main(void)
{
    PortOut<PD> LED_array;

    while(1){
        //led nyala geser kiri
        for(uint8_t i=0x01; i>0; i<<=1){
            LED_array.Put(i);
            _delay_ms(250);
        }
        LED_array.Put(0);
        _delay_ms(250);
        //led nyala geser kanan
        for(uint8_t i=0x80; i>0; i>>=1){
            LED_array.Put(i);
            _delay_ms(250);
        }
        LED_array.Put(0);
        _delay_ms(250);
        //led bersilangan
        for(uint8_t i=0x01, j =0x80; i>0; i<<=1, j>>=1){
            LED_array.Put(i | j);
            _delay_ms(250);
        }
        LED_array.Put(0);
        _delay_ms(250);
        //led bertabrakan terus menghilang
        for(uint8_t i=0x01, j =0x08; i<0x10; i<<=1, j>>=1){
            LED_array.PutLowNible(i);
            LED_array.PutHighNible(j);
            _delay_ms(250);
        }
        LED_array.Put(0);
        _delay_ms(250);
        //led selang-seling per nible
        uint8_t a = 0x0f;
        uint8_t b = 0x00;
        uint8_t temp;
        for(uint8_t i=0; i<4; i++){
            LED_array.PutHighNible(a);
            LED_array.PutLowNible(b);
            _delay_ms(250);
            temp = b;
            b = a;
            a = temp;
        }
        LED_array.Put(0);
        _delay_ms(250);
    }
    return 0;
}
