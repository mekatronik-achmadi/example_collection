#ifndef ADC_H_INCLUDED
#define ADC_H_INCLUDED

#include <avr/io.h>
#include <util/delay.h>

#define USE_ADC_8BIT	0
#define USE_ADC_AVCC	1

#if USE_ADC_8BIT
	unsigned char adc_read(unsigned char pin);
#else
	unsigned int adc_read(unsigned char pin);
#endif

#endif // ADC_H_INCLUDED
