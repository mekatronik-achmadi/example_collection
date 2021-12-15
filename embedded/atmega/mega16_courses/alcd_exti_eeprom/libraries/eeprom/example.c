#include <avr/io.h>
#include <util/delay.h>
#include <avr/eeprom.h>

#define VI_ADDR 0x01

unsigned char vI;

int main(void){

	vI=eeprom_read_byte((uint8_t*)VI_ADDR);

	_delay_ms(255);

	V++;
	eeprom_write_byte((uint8_t*)VI_ADDR,vI);

	while(1);
	return 0;
}
