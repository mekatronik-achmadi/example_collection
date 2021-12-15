#include "pwm.h"

void pwm_init(void){
	DDRD |= 1<<4 | 1<<5;

	TCCR1B|=(1<<CS12)|(0<<CS11)|(0<<CS10);

	TCCR1A|=(1<<WGM11)|(0<<WGM10);
	TCCR1B|=(1<<WGM13)|(0<<WGM12);

	TCCR1A|=(1<<COM1A1)|(0<<COM1A0);
	TCCR1A|=(1<<COM1B1)|(0<<COM1B0);
}
