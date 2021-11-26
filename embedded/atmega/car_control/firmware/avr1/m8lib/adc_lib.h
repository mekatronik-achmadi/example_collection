#ifndef ADC_H
#define ADC_H

//this is just a help file. DON'T USE THIS FILE DIRECTLY!

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/eeprom.h>
#include <avr/pgmspace.h>

//input pins is ADC0..7 as analog input

#define ADC_10bit	ADMUX&=~(1<<ADLAR)
#define ADC_8bit	ADMUX|=1<<ADLAR

#define ADC_AVCC	ADMUX|=(0<<REFS1)|(1<<REFS0)
#define ADC_AREF	ADMUX|=(0<<REFS1)|(0<<REFS0)
#define ADC_2_5v	ADMUX|=(1<<REFS1)|(1<<REFS0)

#define ADC_Enabled	ADCSRA|=1<<ADEN

#define ADC_clk1 	ADCSRA|=(0<<ADPS2)|(0<<ADPS1)|(0<<ADPS0)
#define ADC_clk2 	ADCSRA|=(0<<ADPS2)|(0<<ADPS1)|(1<<ADPS0)
#define ADC_clk4 	ADCSRA|=(0<<ADPS2)|(1<<ADPS1)|(0<<ADPS0)
#define ADC_clk8 	ADCSRA|=(0<<ADPS2)|(1<<ADPS1)|(1<<ADPS0)
#define ADC_clk16	ADCSRA|=(1<<ADPS2)|(0<<ADPS1)|(0<<ADPS0)
#define ADC_clk32 	ADCSRA|=(1<<ADPS2)|(0<<ADPS1)|(1<<ADPS0)
#define ADC_clk64 	ADCSRA|=(1<<ADPS2)|(1<<ADPS1)|(0<<ADPS0)
#define ADC_clk128	ADCSRA|=(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0)

#define ADC_IT ADCSRA|=1<<ADIE

#define ADC_IRQ	ISR(ADC_vect)

#define IRQ_Start sei()

unsigned char read8_adc(unsigned char pin){
	ADMUX=pin;
	
	ADC_8bit;
	ADC_AVCC;
	ADC_Enabled;
	
	_delay_us(10);
	
	ADCSRA|=1<<ADSC;
	while (!(ADCSRA & 1<<ADIF));
	ADCSRA|=1<<ADIF;

	return ADCH;
}

unsigned int read10_adc(unsigned char pin){
	ADMUX=pin;
	
	ADC_10bit;
	ADC_AVCC;
	ADC_Enabled;
	
	_delay_us(10);
	
	ADCSRA|=1<<ADSC;
	while (!(ADCSRA & 1<<ADIF));
	ADCSRA|=1<<ADIF;

	return ADCW;
}

#endif