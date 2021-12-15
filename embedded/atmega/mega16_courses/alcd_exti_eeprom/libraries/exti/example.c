#include <avr/io.h>

#include "exti.h"

extern unsigned char vI;

int main(void){
	exti_0_init(FALL);
	exti_1_init(FALL);

	while(1);
	return 0;
}
