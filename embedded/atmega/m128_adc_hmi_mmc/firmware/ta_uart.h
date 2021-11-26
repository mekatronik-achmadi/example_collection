#ifndef TA_UART_H
#define TA_UART_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <avr/eeprom.h>
#include <avr/pgmspace.h>

#include "ta_led.h"
#include "ta_mmc.h"
#include "ta_adc.h"

#define BAUDRATE 9600
#define CHAR_LONG 16

void ta_uart_Init(void);

#endif // TA_UART_H
