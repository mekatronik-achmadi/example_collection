#include "pwmovf.h"

volatile unsigned int tick;
volatile unsigned char period=255;

void pwm_init(void){
	DDRB |= 1<<2;

	TCCR0|=(0<<CS02)|(0<<CS01)| (1<<CS00);
	TIMSK|=1<<TOIE0;

	tick = 0;

	sei();
}

ISR(TIMER0_OVF_vect){
	tick++;

	if(tick==period/2){
		PORTB &= ~(1<<2);
	}
	else if(tick==period){
		PORTB |= 1<<2;
		tick=0;
	}
}

