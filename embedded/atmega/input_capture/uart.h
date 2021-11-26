#ifndef UART_H_INCLUDED
#define UART_H_INCLUDED

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BAUDRATE 9600

#define USE_RECV_INT    0 //pakai receiver interrupt

void uart_init(void);

#endif // UART_H_INCLUDED
