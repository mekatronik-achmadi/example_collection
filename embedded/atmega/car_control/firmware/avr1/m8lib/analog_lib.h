#ifndef ANA_COMPA_H
#define ANA_COMPA_H

//this is just a help file. DON'T USE THIS FILE DIRECTLY!

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/eeprom.h>
#include <avr/pgmspace.h>

//input pins is ADC0..7 and AIN1 as negative analog input
//input pin AIN0 as positive analog input

#define AnaCompa_Mux_AIN1		SFIOR&=~(1<<ACME)
#define	AnaCompa_Mux_ADC(bit)	SFIOR|=1<<ACME;ADCSRA&=~(1<<ADEN);ADMUX=bit;

#define	AnaCompa_Disable	ACSR|=1<<ACD;ACSR&=~(1<<ACIE)
#define AnaCompa_Bandgap	ACSR|=1<<ACBG
#define	AnaCompa_Output		(ACSR&(1<<ACO))
#define	AnaCompa_IT			ACSR|=1<<ACIE
#define	AnaCompa_IC_IT		ACSR|=1<<ACIC

#define	AnaCompa_Out_Toggle		ACSR|=(0<<ACIS1)|(0<<ACIS0)
#define	AnaCompa_Out_Falling	ACSR|=(1<<ACIS1)|(0<<ACIS0)
#define	AnaCompa_Out_Rising		ACSR|=(1<<ACIS1)|(1<<ACIS0)

#define	AnaCompa_IRQ	ISR(ANA_COMP_vect)

#define IRQ_Start sei()

#endif