#ifndef TA_ADC_H
#define TA_ADC_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/eeprom.h>
#include <avr/pgmspace.h>

#define PIN_ADC 0

void ta_adc_Init(void);
uint16_t ta_adc_Read(uint8_t pin);

#endif // TA_ADC_H
