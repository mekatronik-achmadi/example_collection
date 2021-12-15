#include <avr/io.h>
#include "alcd.h"

char text[16];

int main(void){
	alcd_init();
	alcd_clear();

	while(1){
		sprintf(text,"test");
		alcd_printf(0,0,text);
	}
	return 0;
}
