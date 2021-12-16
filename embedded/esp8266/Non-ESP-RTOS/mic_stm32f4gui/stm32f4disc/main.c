/*
    ChibiOS - Copyright (C) 2006..2015 Giovanni Di Sirio

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
#include "gfx.h"

#include "chprintf.h"
#include "shell.h"

#include "math.h"
#include "stdlib.h"
#include "stdio.h"

#include "usbcfg.h"

#include "m_shell.h"
#include "m_gui.h"
#include "m_uart.h"

static THD_WORKING_AREA(waLed1, 128);
/**
 * @brief  LED G14 as indicator.
 *
 */
static THD_FUNCTION(thdLed1, arg) {

  (void)arg;
  chRegSetThreadName("led run");
  while (true) {
    palClearPad(GPIOG, 14);
    chThdSleepMilliseconds(500);
    palSetPad(GPIOG, 14);
    chThdSleepMilliseconds(500);
  }
}

/**
 * @brief   Starting LED routine.
 *
 */
static void m_led_start(void){
    palSetPadMode(GPIOG,14,PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOG,13,PAL_MODE_OUTPUT_PUSHPULL);
    palClearPad(GPIOG,13);

    chThdCreateStatic(waLed1, sizeof(waLed1),	NORMALPRIO, thdLed1, NULL);
}

/**
 * @brief   Main Function
 *
 * @return              Status of execution
 * @retval 0	        Success
 * @retval 1			Not Success
 *
 */
int main(void) {

    gfxInit();

    m_led_start();

    shellInit();
    m_shell_start();
    m_uart_init();

    m_gui_start();

    while(true) {
        m_uart_term();
        m_shell_term();

        gfxSleepMilliseconds(500);
    }
}
