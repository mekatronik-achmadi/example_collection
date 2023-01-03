#include <avr/io.h>
#include <util/delay.h>

int main(void){
    DDRC |= 1<<6; // A4 as output
    PORTC |= 1<<5; // A3 as Pull up Input

    while (1) {

        //if button unpressed pulled high
        if(PINC & (1<<5)){
            PORTC &= ~(1<<6);
        }

        else{
            PORTC |= 1<<6;
        }

        _delay_ms(100);
    }
    return 0;
}
