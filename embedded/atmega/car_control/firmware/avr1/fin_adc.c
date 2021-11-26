#include "fin_inc.h"

void ADC_Setup(void){
  
  ADMUX&=~(1<<ADLAR);
  ADMUX|=(0<<REFS1)|(1<<REFS0);
  ADCSRA|=(1<<ADPS2)|(0<<ADPS1)|(0<<ADPS0);
  ADCSRA|=1<<ADEN;
  
}

unsigned int read_adc(unsigned char pin){
  
  ADMUX=pin;
	  
  ADMUX&=~(1<<ADLAR);
  ADMUX|=(0<<REFS1)|(1<<REFS0);
  ADCSRA|=1<<ADEN;
	  
  _delay_us(10);
	  
  ADCSRA|=1<<ADSC;
  while (!(ADCSRA & 1<<ADIF));
  ADCSRA|=1<<ADIF;

  return ADCW;

}
