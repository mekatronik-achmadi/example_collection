#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/eeprom.h>
#include <avr/pgmspace.h>

#define v0 vc=0x00;va=0x00

#define v1 vc=0x01;va=0x00
#define v2 vc=0x03;va=0x00
#define v3 vc=0x07;va=0x00
#define v4 vc=0x0f;va=0x00
#define v5 vc=0x1f;va=0x00
#define v6 vc=0x3f;va=0x00
#define v7 vc=0x7f;va=0x00
#define v8 vc=0xff;va=0x00

#define v9 vc=0xff;va=0x80
#define v10 vc=0xff;va=0xc0
#define v11 vc=0xff;va=0xe0
#define v12 vc=0xff;va=0xf0
#define v13 vc=0xff;va=0xf8
#define v14 vc=0xff;va=0xfc
#define v15 vc=0xff;va=0xfe
#define v16 vc=0xff;va=0xff

#define tick_all 13107000

volatile unsigned char va,vc,flag;
volatile unsigned int rpm,tick;

void led(unsigned int val);

int main(void){
  
  DDRC=0xff;
  DDRA=0xff;
  PORTD|=1<<4;
  
  TCCR1B|=(0<<CS12)|(0<<CS11)|(1<<CS10);
  TCCR1B&=~(1<<ICNC1);
  TCCR1B|=1<<ICES1;
  TIMSK|=1<<TOIE1;
  TIMSK|=1<<TICIE1;
  TCNT1=0;
  
  rpm=0;
  led(rpm);
  
  sei();
  
  while(1);
  
  return 0;
}

void led(unsigned int val){
    
    if(val==0)			    {v0;}
    if(val>0&&val<1000)             {v1;}
    else if(val>1000&&val<2000)     {v2;}
    else if(val>2000&&val<3000)     {v3;}
    else if(val>3000&&val<4000)     {v4;}
    else if(val>4000&&val<5000)     {v5;}
    else if(val>5000&&val<6000)     {v6;}
    else if(val>6000&&val<7000)     {v7;}
    else if(val>7000&&val<8000)     {v8;}
    else if(val>8000&&val<9000)     {v9;}
    else if(val>9000&&val<10000)    {v10;}
    else if(val>10000&&val<11000)   {v11;}
    else if(val>11000&&val<12000)   {v12;}
    else if(val>12000&&val<13000)   {v13;}
    else if(val>13000&&val<14000)   {v14;}
    else if(val>14000&&val<15000)   {v15;}
    else if(val>15000)		    {v16;}
    
    PORTA=~(va);
    PORTC=~(vc);
}

ISR(TIMER1_CAPT_vect){
    
    tick=ICR1;
    TCNT1=0;
    
    if(tick>0){
      rpm=tick_all/tick;
      led(rpm);
    }
}

ISR(TIMER1_OVF_vect){
      rpm=0;
      led(rpm);
}
