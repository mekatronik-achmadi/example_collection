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

#include "avr_inc.h"

uint16_t tunda=500;

static WORKING_AREA(waThread1, 32);
static msg_t Thread1(void *arg) {

  while (TRUE) {
    PORTA^=1<<0;
    chThdSleepMilliseconds(1000);
  }
  return 0;
}

static WORKING_AREA(waThread2, 32);
static msg_t Thread2(void *arg) {

  while (TRUE) {
    PORTA^=1<<1;
    chThdSleepMilliseconds(1000);
  }
  return 0;
}

static WORKING_AREA(waThread3, 32);
static msg_t Thread3(void *arg) {
  char press1=0,press2=0;
  while (TRUE) {
    if(tunda>100&&tunda<1000){
      if((!(PINA&1<<2))&&(press1==0)){
	tunda=tunda+100;
	press1=1;
      }else{chThdSleepMilliseconds(100);press1=0;}
      if((!(PINA&1<<3))&&(press2==0)){
	tunda=tunda-100;
	press2=1;
      }else{chThdSleepMilliseconds(100);press2=0;}
    }
  }
  return 0;
}

static WORKING_AREA(waThread4, 32);
static msg_t Thread4(void *arg) {

  while (TRUE) {
    PORTD^=1<<0;
    chThdSleepMilliseconds(tunda);
  }
  return 0;
}

/*
 * Application entry point.
 */
int main(void) {
  
  /*
   * Hardware register configuration in low level layer.
   */
  DDRA|=1<<0|1<<1;
  PORTA|=1<<0|1<<2|1<<3;
  PORTA&=~(1<<1);
  DDRD|=1<<0;
  /*
   * System initializations.
   * - HAL initialization, this also initializes the configured device drivers
   *   and performs the board-specific initializations.
   * - Kernel initialization, the main() function becomes a thread and the
   *   RTOS is active.
   */
  halInit();
  chSysInit();
  /*
   * Starts all threads.
   */
   chThdCreateStatic(waThread1, sizeof(waThread1), NORMALPRIO, Thread1, NULL);
   chThdCreateStatic(waThread2, sizeof(waThread2), NORMALPRIO, Thread2, NULL);
   chThdCreateStatic(waThread3, sizeof(waThread3), NORMALPRIO, Thread3, NULL);
   chThdCreateStatic(waThread4, sizeof(waThread4), NORMALPRIO, Thread4, NULL);

  while(TRUE) {
    chThdSleepMilliseconds(500);
  }
}
