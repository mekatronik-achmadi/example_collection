#include "avr_header.h"

extern volatile unsigned char loop_railing,vrailing,dirrailing;
extern volatile unsigned char loop_filler,vfiller;

int main(void){

    //    UART_Setup();

    DDRB |= (1<<LED);
    PORTB |= (1<<LED);

    DDRB |= (1<<MB1) | (1<<MC1);

    PORTE |= (1<<SW1C);

    DDRH |= (1<<MA)| (1<<MD);

    ADC_Setup();

    TIM0_Setup();
    sei();

    while(1){
        PORTB ^= (1<<LED);
        _delay_ms(500);

        vrailing=read_adc(TRRAILLING);
        if(vrailing<5){
            vrailing=5;
        }

        vfiller=read_adc(TRFILLER);
        if(vfiller<5){
            vfiller=5;
        }

    }
}
