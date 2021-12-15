#include <avr/io.h>

#include "adc.h"

unsigned int vADC

int main(void){
	vADC = adc_read(0);

	while(1);
    return 0;
}
