#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>

#include "uart.h"

int main(void){
	uart_init();
	printf("system run \n\r");

	while(1);
    return 0;
}
