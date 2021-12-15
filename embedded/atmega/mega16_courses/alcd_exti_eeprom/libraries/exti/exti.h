#ifndef EXTI_H_INCLUDED
#define EXTI_H_INCLUDED

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>

#define LOW		0
#define HIGH	1
#define FALL	2
#define RISE	3

void exti_0_init(unsigned char mode);
void exti_1_init(unsigned char mode);
void exti_2_init(unsigned char mode);

#endif // EXTI_H_INCLUDED
