#ifndef TA_UART_H
#define TA_UART_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "ch.h"
#include "hal.h"
#include "chprintf.h"
#include "memstreams.h"
#include "chstreams.h"

void Uart_Init(void);

void Sms_Text(void);
void Sms_Test(void);

#endif // TA_UART_H
