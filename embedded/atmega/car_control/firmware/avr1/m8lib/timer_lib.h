#ifndef TIMER_H
#define TIMER_H

//this is just a help file. DON'T USE THIS FILE DIRECTLY!

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/eeprom.h>
#include <avr/pgmspace.h>

//input pins is T0 and T1 as counter input
//input pin ICP1 as input capture input
//output pins OC0, OC1A, OC1B, OC2 as pulse output

#define TMR0_OFF	TCCR0|=(0<<CS02)|(0<<CS01)|(0<<CS00)
#define TMR0_1		TCCR0|=(0<<CS02)|(0<<CS01)|(1<<CS00)
#define TMR0_8		TCCR0|=(0<<CS02)|(1<<CS01)|(0<<CS00)
#define TMR0_64		TCCR0|=(0<<CS02)|(1<<CS01)|(1<<CS00)
#define TMR0_256	TCCR0|=(1<<CS02)|(0<<CS01)|(0<<CS00)
#define TMR0_1024	TCCR0|=(1<<CS02)|(0<<CS01)|(1<<CS00)
#define T0_falling	TCCR0|=(1<<CS02)|(1<<CS01)|(0<<CS00)
#define T0_rising	TCCR0|=(1<<CS02)|(1<<CS01)|(1<<CS00)

#define TMR0_Normal	TCCR0|=(0<<WGM01)|(0<<WGM00)
#define TMR0_PWM	TCCR0|=(0<<WGM01)|(1<<WGM00)
#define TMR0_CTC	TCCR0|=(1<<WGM01)|(0<<WGM00)
#define TMR0_FPWM	TCCR0|=(1<<WGM01)|(1<<WGM00)

#define TMR0_NorCTC_NotCon	TCCR0|=(0<<COM01)|(0<<COM00)
#define TMR0_NorCTC_Toggle	TCCR0|=(0<<COM01)|(1<<COM00)
#define TMR0_NorCTC_Clear	TCCR0|=(1<<COM01)|(0<<COM00)
#define TMR0_NorCTC_Set		TCCR0|=(1<<COM01)|(1<<COM00)

#define TMR0_FPWM_NotCon	TCCR0|=(0<<COM01)|(0<<COM00)
#define TMR0_FPWM_Noinvert	TCCR0|=(1<<COM01)|(0<<COM00)
#define TMR0_FPWM_Invert	TCCR0|=(1<<COM01)|(1<<COM00)

#define TMR0_PWM_NotCon		TCCR0|=(0<<COM01)|(0<<COM00)
#define TMR0_PWM_Noinvert	TCCR0|=(1<<COM01)|(0<<COM00)
#define TMR0_PWM_Invert		TCCR0|=(1<<COM01)|(1<<COM00)

#define TMR0_Counter	TCNT0
#define TMR0_Compare	OCR0

#define TMR0_OVF_IT		TIMSK|=1<<TOIE0
#define TMR0_COMP_IT	TIMSK|=1<<OCIE0

#define TMR0_OVF_IRQ	ISR(TIMER0_OVF_vect)
#define TMR0_COMP_IRQ	ISR(TIMER0_COMP_vect)

//================================================================================

#define TMR2_OFF	TCCR2|=(0<<CS22)|(0<<CS21)|(0<<CS20)
#define TMR2_1		TCCR2|=(0<<CS22)|(0<<CS21)|(1<<CS20)
#define TMR2_8		TCCR2|=(0<<CS22)|(1<<CS21)|(0<<CS20)
#define TMR2_32		TCCR2|=(0<<CS22)|(1<<CS21)|(1<<CS20)
#define TMR2_64		TCCR2|=(1<<CS22)|(0<<CS21)|(0<<CS20)
#define TMR2_128	TCCR2|=(1<<CS22)|(0<<CS21)|(1<<CS20)
#define TMR2_256	TCCR2|=(1<<CS22)|(1<<CS21)|(0<<CS20)
#define TMR2_1024	TCCR2|=(1<<CS22)|(1<<CS21)|(1<<CS20)

#define TMR2_Normal	TCCR2|=(0<<WGM21)|(0<<WGM20)
#define TMR2_PWM	TCCR2|=(0<<WGM21)|(1<<WGM20)
#define TMR2_CTC	TCCR2|=(1<<WGM21)|(0<<WGM20)
#define TMR2_FPWM	TCCR2|=(1<<WGM21)|(1<<WGM20)

#define TMR2_NorCTC_NotCon	TCCR2|=(0<<COM21)|(0<<COM20)
#define TMR2_NorCTC_Toggle	TCCR2|=(0<<COM21)|(1<<COM20)
#define TMR2_NorCTC_Clear	TCCR2|=(1<<COM21)|(0<<COM20)
#define TMR2_NorCTC_Set		TCCR2|=(1<<COM21)|(1<<COM20)

#define TMR2_FPWM_NotCon	TCCR2|=(0<<COM21)|(0<<COM20)
#define TMR2_FPWM_Noinvert	TCCR2|=(1<<COM21)|(0<<COM20)
#define TMR2_FPWM_Invert	TCCR2|=(1<<COM21)|(1<<COM20)

#define TMR2_PWM_NotCon		TCCR2|=(0<<COM21)|(0<<COM20)
#define TMR2_PWM_Noinvert	TCCR2|=(1<<COM21)|(0<<COM20)
#define TMR2_PWM_Invert		TCCR2|=(1<<COM21)|(1<<COM20)

#define TMR2_Counter	TCNT2
#define TMR2_Compare	OCR2

#define TMR2_OVF_IT		TIMSK|=1<<TOIE2
#define TMR2_COMP_IT	TIMSK|=1<<OCIE2

#define TMR2_OVF_IRQ	ISR(TIMER2_OVF_vect)
#define TMR2_COMP_IRQ	ISR(TIMER2_COMP_vect)

//================================================================================

#define TMR1_OFF	TCCR1B|=(0<<CS12)|(0<<CS11)|(0<<CS10)
#define TMR1_1		TCCR1B|=(0<<CS12)|(0<<CS11)|(1<<CS10)
#define TMR1_8		TCCR1B|=(0<<CS12)|(1<<CS11)|(0<<CS10)
#define TMR1_64		TCCR1B|=(0<<CS12)|(1<<CS11)|(1<<CS10)
#define TMR1_256	TCCR1B|=(1<<CS12)|(0<<CS11)|(0<<CS10)
#define TMR1_1024	TCCR1B|=(1<<CS12)|(0<<CS11)|(1<<CS10)
#define T1_falling	TCCR1B|=(1<<CS12)|(1<<CS11)|(0<<CS10)
#define T1_rising	TCCR1B|=(1<<CS12)|(1<<CS11)|(1<<CS10)

#define TMR1_Normal				TCCR1B|=(0<<WGM13)|(0<<WGM12);TCCR1A|=(0<<WGM11)|(0<<WGM10)
#define TMR1_PWM8				TCCR1B|=(0<<WGM13)|(0<<WGM12);TCCR1A|=(0<<WGM11)|(1<<WGM10)
#define TMR1_PWM10				TCCR1B|=(0<<WGM13)|(0<<WGM12);TCCR1A|=(1<<WGM11)|(1<<WGM10)
#define TMR1_CTC_OCR1A			TCCR1B|=(0<<WGM13)|(1<<WGM12);TCCR1A|=(0<<WGM11)|(0<<WGM10)
#define TMR1_FPWM8				TCCR1B|=(0<<WGM13)|(1<<WGM12);TCCR1A|=(0<<WGM11)|(1<<WGM10)
#define TMR1_FPWM10				TCCR1B|=(0<<WGM13)|(1<<WGM12);TCCR1A|=(1<<WGM11)|(1<<WGM10)
#define TMR1_PWMFREQ_ICR1		TCCR1B|=(1<<WGM13)|(0<<WGM12);TCCR1A|=(0<<WGM11)|(0<<WGM10)
#define TMR1_PWMFREQ_OCR1A		TCCR1B|=(1<<WGM13)|(0<<WGM12);TCCR1A|=(0<<WGM11)|(1<<WGM10)
#define TMR1_PWM_ICR1			TCCR1B|=(1<<WGM13)|(0<<WGM12);TCCR1A|=(1<<WGM11)|(0<<WGM10)
#define TMR1_PWM_OCR1A			TCCR1B|=(1<<WGM13)|(0<<WGM12);TCCR1A|=(1<<WGM11)|(1<<WGM10)
#define TMR1_CTC_ICR1			TCCR1B|=(1<<WGM13)|(1<<WGM12);TCCR1A|=(0<<WGM11)|(0<<WGM10)
#define TMR1_FPWM_ICR1			TCCR1B|=(1<<WGM13)|(1<<WGM12);TCCR1A|=(1<<WGM11)|(0<<WGM10)
#define TMR1_FPWM_OCR1A			TCCR1B|=(1<<WGM13)|(1<<WGM12);TCCR1A|=(1<<WGM11)|(1<<WGM10)

#define TMR1A_NorCTC_NotCon	TCCR1A|=(0<<COM1A1)|(0<<COM1A0)
#define TMR1A_NorCTC_Toggle	TCCR1A|=(0<<COM1A1)|(1<<COM1A0)
#define TMR1A_NorCTC_Clear	TCCR1A|=(1<<COM1A1)|(0<<COM1A0)
#define TMR1A_NorCTC_Set	TCCR1A|=(1<<COM1A1)|(1<<COM1A0)

#define TMR1A_FPWM_NotCon	TCCR1A|=(0<<COM1A1)|(0<<COM1A0)
#define TMR1A_FPWM_Noinvert	TCCR1A|=(1<<COM1A1)|(0<<COM1A0)
#define TMR1A_FPWM_Invert	TCCR1A|=(1<<COM1A1)|(1<<COM1A0)

#define TMR1A_PWM_NotCon	TCCR1A|=(0<<COM1A1)|(0<<COM1A0)
#define TMR1A_PWM_Noinvert	TCCR1A|=(1<<COM1A1)|(0<<COM1A0)
#define TMR1A_PWM_Invert	TCCR1A|=(1<<COM1A1)|(1<<COM1A0)

#define TMR1B_NorCTC_NotCon	TCCR1A|=(0<<COM1B1)|(0<<COM1B0)
#define TMR1B_NorCTC_Toggle	TCCR1A|=(0<<COM1B1)|(1<<COM1B0)
#define TMR1B_NorCTC_Clear	TCCR1A|=(1<<COM1B1)|(0<<COM1B0)
#define TMR1B_NorCTC_Set	TCCR1A|=(1<<COM1B1)|(1<<COM1B0)

#define TMR1B_FPWM_NotCon	TCCR1A|=(0<<COM1B1)|(0<<COM1B0)
#define TMR1B_FPWM_Noinvert	TCCR1A|=(1<<COM1B1)|(0<<COM1B0)
#define TMR1B_FPWM_Invert	TCCR1A|=(1<<COM1B1)|(1<<COM1B0)

#define TMR1B_PWM_NotCon	TCCR1A|=(0<<COM1B1)|(0<<COM1B0)
#define TMR1B_PWM_Noinvert	TCCR1A|=(1<<COM1B1)|(0<<COM1B0)
#define TMR1B_PWM_Invert	TCCR1A|=(1<<COM1B1)|(1<<COM1B0)

#define TMR1_IC_Normal			TCCR1B&=~(1<<ICNC1)
#define TMR1_IC_NoiseCancel		TCCR1B|=1<<ICNC1

#define TMR1_IC_Rising			TCCR1B|=1<<ICES1
#define TMR1_IC_Falling			TCCR1B&=~(1<<ICES1)

#define TMR1_Counter		TCNT1
#define TMR1_Counter_High	TCNT1H
#define TMR1_Counter_Low	TCNT1L

#define TMR1_Compare_A			OCR1A
#define TMR1_Compare_A_High		OCR1AH
#define TMR1_Compare_A_Low		OCR1AL

#define TMR1_Compare_B			OCR1B
#define TMR1_Compare_B_High		OCR1BH
#define TMR1_Compare_B_Low		OCR1BL

#define TMR1_InputCapture		ICR1
#define TMR1_InputCapture_High	ICR1H
#define TMR1_InputCapture_Low	ICR1L

#define TMR1_OVF_IT		TIMSK|=1<<TOIE1
#define TMR1_COMP_A_IT	TIMSK|=1<<OCIE1A
#define TMR1_COMP_B_IT	TIMSK|=1<<OCIE1B
#define TMR1_IC_IT		TIMSK|=1<<TICIE1

#define TMR1_OVF_IRQ	ISR(TIMER1_OVF_vect)
#define TMR1_COMP_A_IRQ	ISR(TIMER1_COMPA_vect)
#define TMR1_COMP_B_IRQ	ISR(TIMER1_COMPB_vect)
#define TMR1_IC_IRQ		ISR(TIMER1_CAPT_vect)

//================================================================================

#define IRQ_Start sei()

#endif