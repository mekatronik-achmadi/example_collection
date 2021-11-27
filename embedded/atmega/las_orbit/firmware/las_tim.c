#include "avr_header.h"

volatile unsigned char loop_railing,vrailing;
volatile unsigned char loop_filler,vfiller;

void TIM0_Setup(void){
    TCCR0B|=(0<<CS02)|(0<<CS01)|(1<<CS00);
    TIMSK0|=(1<<TOIE0);
    TCNT0=0;
}

ISR(TIMER0_OVF_vect){
    TCNT0=0;

    if((PINE&(1<<SW1C))){
        PORTB&=~(1<<MB1);
        PORTH &= ~(1<<MA);
        loop_filler=0;
        loop_railing=0;
    }
    else{
        loop_filler++;
        if(loop_filler==vfiller){
            PORTH &= ~(1<<MA);
        }
        if(loop_filler==255){
            loop_filler=0;
            PORTH |=(1<<MA);
        }

        loop_railing++;
        if(loop_railing==vrailing){
            PORTB &= ~(1<<MB1);
        }
        if(loop_railing==255){
            PORTB|=(1<<MB1);
            loop_railing=0;
        }
    }
}
