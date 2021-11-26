#include "ta_adc.h"

uint16_t adc0=0;

void ta_adc_Init(void){
    ADMUX |= 1<<REFS0;
    ADMUX &=~(1<<ADLAR);

    ADCSRA|=(1<<ADEN);
    ADCSRA|=(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
}

uint16_t ta_adc_Read(uint8_t pin){
    pin = pin & 0b00000111;
    ADMUX |= pin;

    ta_adc_Init();
    _delay_us(10);

    ADCSRA|=1<<ADSC;
    while (!(ADCSRA & 1<<ADIF));
    ADCSRA|=1<<ADIF;

    return ADCW;
}



