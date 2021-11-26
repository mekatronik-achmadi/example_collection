#include "adc.h"

uint16_t adc0;

void ADC_Init(void){
    ADMUX |= 1<<REFS0;
    ADMUX&=~(1<<ADLAR);

    ADCSRA|=1<<ADEN;
}

unsigned int ADC_Read(unsigned char pin){
    ADMUX=pin;

    ADC_Init();
    _delay_us(10);

    ADCSRA|=1<<ADSC;
    while (!(ADCSRA & 1<<ADIF));
    ADCSRA|=1<<ADIF;

    return ADCW;
}
