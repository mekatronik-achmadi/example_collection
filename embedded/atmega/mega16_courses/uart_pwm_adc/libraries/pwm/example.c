#include <avr/io.h>

#include "pwm.h"

int main(void){
	pwm_init();

	ICR1 = 1023;
	OCR1A = 512;

	while(1);
    return 0;
}

