#include "exti.h"

unsigned char vI=0;

void exti_0_init(unsigned char mode){
	PORTD |= 1<<2;

	switch(mode){
		case LOW:  MCUCR|=(0<<ISC01)|(0<<ISC00); break;
		case HIGH: MCUCR|=(0<<ISC01)|(1<<ISC00); break;
		case FALL: MCUCR|=(1<<ISC01)|(0<<ISC00); break;
		case RISE: MCUCR|=(1<<ISC01)|(1<<ISC00); break;
	}

	GICR|=1<<INT0;
	sei();
}

void exti_1_init(unsigned char mode){
	PORTD |= 1<<3;

	switch(mode){
		case LOW:  MCUCR|=(0<<ISC11)|(0<<ISC10); break;
		case HIGH: MCUCR|=(0<<ISC11)|(1<<ISC10); break;
		case FALL: MCUCR|=(1<<ISC11)|(0<<ISC10); break;
		case RISE: MCUCR|=(1<<ISC11)|(1<<ISC10); break;
	}

	GICR|=1<<INT1;
	sei();
}

//===============================================//

ISR(INT0_vect){
	vI++;
	return;
}

ISR(INT1_vect){
	vI = 0;
	return;
}
