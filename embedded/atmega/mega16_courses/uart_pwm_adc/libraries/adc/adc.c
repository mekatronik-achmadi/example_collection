#include "adc.h"

#if USE_ADC_8BIT
	unsigned char adc_read(unsigned char pin){
		ADMUX=pin;
		ADMUX|=1<<ADLAR;

	#if USE_ADC_AVCC
		ADMUX|=1<<REFS0;
	#endif

		ADCSRA|=1<<ADEN;

		_delay_us(10);

		ADCSRA|=1<<ADSC;
		while (!(ADCSRA & 1<<ADIF));
		ADCSRA|=1<<ADIF;

		return ADCH;
	}
#else
	unsigned int adc_read(unsigned char pin){
		ADMUX=pin;

	#if USE_ADC_AVCC
		ADMUX|=1<<REFS0;
	#endif
		ADCSRA|=1<<ADEN;

		_delay_us(10);

		ADCSRA|=1<<ADSC;
		while (!(ADCSRA & 1<<ADIF));
		ADCSRA|=1<<ADIF;

		return ADCW;
	}
#endif
