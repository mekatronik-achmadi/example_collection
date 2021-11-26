#ifndef TA_LED_H
#define TA_LED_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <avr/eeprom.h>
#include <avr/pgmspace.h>

#define TUNDA 500

#define DDR_LED DDRG
#define PORT_LED PORTG

#define LED_1 1

void tunda_us(unsigned int time);
void tunda_ms(unsigned int time);

void ta_led_LEDInit(void);
void ta_led_LEDTest(void);

#endif // TA_LED_H
