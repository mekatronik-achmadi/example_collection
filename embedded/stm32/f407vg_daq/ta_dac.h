#ifndef TA_DAC_H
#define TA_DAC_H

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

#define DAC_BUFFER_SIZE 2

void Dac_Init(void);

#endif // TA_DAC_H
