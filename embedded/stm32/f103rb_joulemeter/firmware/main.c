
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdlib.h>
#include <math.h>

#include "ch.h"
#include "hal.h"

#include "shell.h"
#include "chprintf.h"
#include "memstreams.h"
#include "evtimer.h"

#include "lib_lcd.h"
#include "lib_adc.h"

#define volt adc0
#define amp adc1

extern adcsample_t volt,amp;
extern LcdStream myLCD;

int main(void) {

  halInit();
  chSysInit();

  Adc_Init();

  Lcd_Init();
  Lcd_Clear();

  while (TRUE) {
      Lcd_Cursor(0,0);
      chprintf((BaseSequentialStream *)&myLCD,"v= %4d         ",volt);
      Lcd_Cursor(0,1);
      chprintf((BaseSequentialStream *)&myLCD,"i= %4d         ",amp);
  }
}
