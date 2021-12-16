#ifndef TA_RTC_H
#define TA_RTC_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "ch.h"
#include "hal.h"
#include "chprintf.h"
#include "memstreams.h"
#include "chstreams.h"
#include "shell.h"

#include "ta_i2c.h"

#define DS1307_RX_DEPTH 7
#define DS1307_TX_DEPTH 8

#define DS1307_ADDRESS      0x68
#define DS1307_SECONDS_REG	0x00

typedef struct ds1307_t
{
    uint8_t     seconds;
    uint8_t     minutes;
    uint8_t     hours;
    uint8_t     day;
    uint8_t     date;
    uint8_t     month;
    uint16_t    year;
} ds1307;

uint8_t bcd2Dec ( uint8_t val );
uint8_t dec2Bcd ( uint8_t val );
void Ds1307_Init ( void );
void setDs1307Date ( msg_t *status, systime_t *tmo, struct ds1307_t dsData );
struct ds1307_t getDs1307Date ( msg_t *status, systime_t *tmo );

#endif
