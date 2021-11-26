#ifndef GPIO_H
#define GPIO_H

//this is just a help file. DON'T USE THIS FILE DIRECTLY!

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/eeprom.h>
#include <avr/pgmspace.h>

//input pins INT0..2 as external interrupt input

#define GPIOx_Input		DDRx &= ~(1<<bit)
#define GPIOx_Output	DDRx |= 1<<bit 
#define GPIOx_Switch	DDRx ^= 1<<bit
#define GPIOx_Clear		PORTx &= ~(1<<bit)
#define GPIOx_Set		PORTx |= 1<<bit
#define GPIOx_Toggle	PORTX ^= 1<<bit
#define GPIOx_IsHigh	(PINx & (1<<bit))

#define EXTI0_low		MCUCR|=(0<<ISC01)|(0<<ISC00)
#define EXTI0_toggle	MCUCR|=(0<<ISC01)|(1<<ISC00)
#define EXTI0_falling	MCUCR|=(1<<ISC01)|(0<<ISC00)
#define EXTI0_rising	MCUCR|=(1<<ISC01)|(1<<ISC00)

#define EXTI1_low		MCUCR|=(0<<ISC11)|(0<<ISC10)
#define EXTI1_toggle	MCUCR|=(0<<ISC11)|(1<<ISC10)
#define EXTI1_falling	MCUCR|=(1<<ISC11)|(0<<ISC10)
#define EXTI1_rising	MCUCR|=(1<<ISC11)|(1<<ISC10)

#define EXTI2_falling	MCUCSR|=0<<ISC2
#define EXTI2_rising	MCUCSR|=1<<ISC2

#define EXTI0_IT	GICR|=1<<INT0
#define EXTI1_IT	GICR|=1<<INT1
#define EXTI2_IT	GICR|=1<<INT2

#define EXTI0_IRQ ISR(INT0_vect)
#define EXTI1_IRQ ISR(INT1_vect)
#define EXTI2_IRQ ISR(INT2_vect)

#define IRQ_Start sei()

#endif