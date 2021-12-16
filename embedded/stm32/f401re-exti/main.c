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

/**
 * @brief Button interrupt callback
 * @details Enumerated and not called directly by any normal thread
 */
static void exti_func(EXTDriver *extp, expchannel_t channel) {
    (void)extp;
    (void)channel;

    palTogglePad(GPIOA, 5);

    return;
}

/**
 * @brief External Interrupt Channel Config
 */
static const EXTConfig extcfg = {
  {
    {EXT_CH_MODE_DISABLED, NULL}, //0
    {EXT_CH_MODE_DISABLED, NULL}, //1
    {EXT_CH_MODE_DISABLED, NULL}, //2
    {EXT_CH_MODE_DISABLED, NULL}, //3
    {EXT_CH_MODE_DISABLED, NULL}, //4
    {EXT_CH_MODE_DISABLED, NULL}, //5
    {EXT_CH_MODE_DISABLED, NULL}, //6
    {EXT_CH_MODE_DISABLED, NULL}, //7
    {EXT_CH_MODE_DISABLED, NULL}, //8
    {EXT_CH_MODE_DISABLED, NULL}, //9
    {EXT_CH_MODE_DISABLED, NULL}, //10
    {EXT_CH_MODE_DISABLED, NULL}, //11
    {EXT_CH_MODE_DISABLED, NULL}, //12
    {EXT_CH_MODE_FALLING_EDGE  | EXT_MODE_GPIOC, exti_func}, //13
    {EXT_CH_MODE_DISABLED, NULL}, //14
    {EXT_CH_MODE_DISABLED, NULL}, //15
    {EXT_CH_MODE_DISABLED, NULL}, //16
    {EXT_CH_MODE_DISABLED, NULL}, //17
    {EXT_CH_MODE_DISABLED, NULL}, //18
    {EXT_CH_MODE_DISABLED, NULL}, //19
    {EXT_CH_MODE_DISABLED, NULL}, //20
    {EXT_CH_MODE_DISABLED, NULL}, //21
    {EXT_CH_MODE_DISABLED, NULL}  //22
  }
};

/*
 * Application entry point.
 */
int main(void) {

  /*
   * System initializations.
   */
  halInit();
  chSysInit();

  palSetPadMode(GPIOA, 5, PAL_MODE_OUTPUT_PUSHPULL);
  palSetPadMode(GPIOC, GPIOC_BUTTON, PAL_MODE_INPUT_PULLUP);

  extStart(&EXTD1, &extcfg);
  extChannelEnable(&EXTD1, 13);

  /*
   * Normal main() thread activity, in this demo it does nothing
   */
  while (true) {
    chThdSleepMilliseconds(500);
  }
}
