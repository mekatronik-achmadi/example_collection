#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <avr/eeprom.h>
#include <avr/pgmspace.h>

#include "ta_mmc.h"
#include "ta_led.h"
#include "ta_uart.h"
#include "ta_adc.h"

extern uint16_t adc0;

int main (void){

    ta_led_LEDInit();
    ta_uart_Init();
    ta_adc_Init();
//	ta_mmc_WriteTest();

    sei(); // Enable all interrupt callback

	while(1){
        ta_led_LEDTest();
        adc0 = ta_adc_Read(PIN_ADC);
	}
}


