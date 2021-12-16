#ifndef TA_UTAMA_H
#define TA_UTAMA_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "ch.h"
#include "hal.h"
#include "chprintf.h"
#include "memstreams.h"
#include "chstreams.h"

#include "ta_adc.h"
#include "ta_lcd.h"
#include "ta_rtc.h"
#include "ta_mmc.h"
#include "ta_dac.h"

#define calib_co 0.1066
#define offset_co 143.54

void Run_Init(void);
void Hasil_Adc(void);
void Tulis_Adc(void);

#endif // TA_UTAMA_H
