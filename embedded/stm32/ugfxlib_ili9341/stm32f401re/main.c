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

#include "grafik.h"

/*
 * LED blinker thread, times are in milliseconds.
 */
static THD_WORKING_AREA(waThread1, 128);
static THD_FUNCTION(Thread1, arg) {

  (void)arg;
  chRegSetThreadName("blinker");
  while (true) {
    palClearPad(GPIOA, 5);
    chThdSleepMilliseconds(100);
    palSetPad(GPIOA, 5);
    chThdSleepMilliseconds(100);
  }
}

/*
 * Application entry point.
 */
int main(void) {

  /*
   * System initializations.
   */
  gfxInit();
  
  /*
   * Graph Button
   */
  palSetPadMode(GPIOC, GPIOC_BUTTON, PAL_MODE_INPUT_PULLUP); 

  /*
   * Draw an plane graph
   */
  draw_axisplanes();

  /*
   * Creates the blinker thread.
   */
  chThdCreateStatic(waThread1, sizeof(waThread1), NORMALPRIO, Thread1, NULL);

  /*
   * Normal main() thread activity, in this demo it does nothing
   */
  while (true) {
	/*
	 * Draw example graph  
	 */ 
	if (!palReadPad(GPIOC, GPIOC_BUTTON)) draw_example();
    chThdSleepMilliseconds(500);
  }
}
