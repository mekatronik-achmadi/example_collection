/*
    ChibiOS/RT - Copyright (C) 2006-2013 Giovanni Di Sirio

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#include "ch.h"
#include "hal.h"

#include "ta_adc.h"
#include "ta_lcd.h"
#include "ta_utama.h"
#include "ta_shell.h"
#include "ta_i2c.h"
#include "ta_rtc.h"
#include "ta_mmc.h"
#include "ta_uart.h"
#include "ta_dac.h"

int main(void) {

  halInit();
  chSysInit();

  Adc_Init();
  Dac_Init();

  Lcd_Init();
  Lcd_Clear();

  Ds1307_Init();
  Sms_Text();

  Mmc_Init();

  Shell_Init();

  Run_Init();

  while (TRUE) {
      Shell_Run();
 }
}
