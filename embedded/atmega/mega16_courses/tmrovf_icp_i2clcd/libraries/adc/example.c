#include <avr/io.h>
#include <utils/delay.h>

#include "adc.h"

int main(void){
	unsigned char vADC;

	while(1){
		vADC=adc_read(0);
		_delay_ms(255);
	}
	return 0;

}
