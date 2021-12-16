#ifndef TA_ADC_H
#define TA_ADC_H

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdlib.h>
#include <math.h>

#include "ch.h"
#include "hal.h"
#include "chprintf.h"
#include "memstreams.h"

#if !defined(CHPRINTF_USE_FLOAT) || defined(__DOXYGEN__)
#define CHPRINTF_USE_FLOAT          FALSE
#endif
#define MAX_FILLER 16
#define FLOAT_PRECISION 100

#define ADC_GRP1_NUM_CHANNELS   4
#define ADC_GRP1_BUF_DEPTH      100

void Adc_Init(void);

#endif // TA_ADC_H
