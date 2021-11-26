//id:main.cpp,keypad,2-8-2012,sidiknur@yahoo.com
//Atmega8,8MHz-internal

#include <avr/io.h>
#include "keypad3x4.h"
#include "portout.h"
#include "tombol.h"

int main(void)
{
    uint8_t key;
    char key_label;

    Keypad3x4<PC,0,PC,1,PB,0,
              PB,6,PB,7,PB,4,PB,5> Keypad;
    PortOut<PD> Output;
    Tombol<PB,1,ACTIVE_LOW> Selector;
    while(1){
        key = Keypad.Get();

        if(Selector.IsPressed())
            Output.Put(key);
        else{
            key_label = Keypad.GetLabel(key);
            Output.Put(key_label);
        }
    }
    return 0;
}
