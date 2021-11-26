#include "icp.h"

volatile uint8_t step, ovf, rst;
volatile uint32_t period;

volatile uint16_t tik;

void icp_init(void){

	PORTB |= (1<<0);
	DDRB &= ~(1<<0);

	DDRC |= 1<<1;
	PORTC |= (1<<1);

	TCCR1B |= (1<<CS12)|(0<<CS11)|(0<<CS10);
	TCCR1B &= ~(1<<ICES1);
	TIMSK1 |= 1<<TOIE1;
	TIMSK1 |= 1<<ICIE1;

	TCCR0B |= (0<<CS02)|(0<<CS01)|(1<<CS00);
	TIMSK0 |= 1<<TOIE0;

	sei();
}

ISR(TIMER1_CAPT_vect){
	if(step==0){
		TCNT1 = 0;
		ICR1 = 0;
		step = 1;
		rst = 0;
	}
	else if(step==1){
		period = ICR1 + (ovf*65535);
		step = 0;
		ovf = 0;
		TCNT1=0;
		ICR1=0;
	}
}

ISR(TIMER1_OVF_vect){
	if(step==1)ovf++;

	rst++;
	if(rst>=2){
		period = 0;
		step = 0;
		ovf = 0;
		rst = 0;
	}
}

ISR(TIMER0_OVF_vect){
	tik++;

	if(tik==800){
		PORTC &= ~(1<<1);
	}
	else if(tik==1600){
		PORTC |=1<<1;
		tik=0;
	}
}
