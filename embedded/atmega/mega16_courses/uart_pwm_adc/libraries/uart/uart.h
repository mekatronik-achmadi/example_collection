#ifndef UART_H_INCLUDED
#define UART_H_INCLUDED

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CHAR_LEN 16

#define BAUDRATE 9600

void uart_init(void);

#endif // UART_H_INCLUDED
