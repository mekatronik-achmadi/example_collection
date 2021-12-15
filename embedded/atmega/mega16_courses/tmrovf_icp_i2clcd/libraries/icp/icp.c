#include "icp.h"

volatile unsigned int freq,tick;

void icp_init(void){

	PORTD |= 1<<6;

	TCCR1B|=(0<<CS12)|(0<<CS11)|(1<<CS10);
	TCCR1B|=1<<ICES1;
	TIMSK |=1<<TOIE1;
	TIMSK |=1<<TICIE1;

	TCNT1=0;
	freq = 0;

	sei();
}

ISR(TIMER1_CAPT_vect){

	tick=ICR1;
	TCNT1=0;

	if(tick>0){
		freq=tick_all/tick;
	}
}

ISR(TIMER1_OVF_vect){
	freq=0;
}
