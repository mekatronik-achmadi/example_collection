/*
    ChibiOS - Copyright (C) 2006..2016 Giovanni Di Sirio

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

#include "shell.h"
#include "chprintf.h"

#define LED_RUN 1
#define SHELL_WA_SIZE 2048

static THD_WORKING_AREA(waRunLed, 128);
#define ThdFunc_RunLED THD_FUNCTION

/**
 * @brief Thread for System Running Indicator
 * @details Smallest Thread to check either system in Run or Freeze
 */
static ThdFunc_RunLED(thdRunLed, arg) {
  (void)arg;
  chRegSetThreadName("run_led");

  while (true) {
    palTogglePad(GPIOA, LED_RUN);
    chThdSleepMilliseconds(500);
  }
}

static void cmd_coba(BaseSequentialStream *chp, int argc, char *argv[]){
    (void)argc;
    (void)argv;

    if (argc > 0) {
      chprintf(chp, "Usage: coba\r\n");
      return;
    }
    chprintf(chp,"Serial Console at %d & buffer size %d bit\r\n",SERIAL_DEFAULT_BITRATE,SERIAL_BUFFERS_SIZE);
}

static const ShellCommand commands[] = {
  {"coba", cmd_coba},
  {NULL, NULL}
};

static thread_t *shelltp_uart = NULL;

static const ShellConfig shell_uart_cfg = {
  (BaseSequentialStream *)&SD1,
  commands
};

/*
 * Application entry point.
 */
int main(void) {

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
   * Activates the serial driver 1, PA9 and PA10 are routed to USART1.
   */
  sdStart(&SD1, NULL);
  palSetPadMode(GPIOA, 9, PAL_MODE_ALTERNATE(7));       /* USART1 TX.       */
  palSetPadMode(GPIOA, 10, PAL_MODE_ALTERNATE(7));      /* USART1 RX.       */

  chprintf((BaseSequentialStream *)&SD1,"UART Send OK\r\n");

  palSetPadMode(GPIOA,LED_RUN,PAL_MODE_OUTPUT_PUSHPULL);
  palClearPad(GPIOA,LED_RUN);

  chThdCreateStatic(waRunLed, sizeof(waRunLed),NORMALPRIO, thdRunLed, NULL);

  /*
   * Normal main() thread activity, in this demo it does nothing.
   */
  while (true) {
    if (!shelltp_uart) {
      shelltp_uart = chThdCreateFromHeap(NULL, SHELL_WA_SIZE, "shell_uart", NORMALPRIO, shellThread, (void *)&shell_uart_cfg);
    }
    else {
      if (chThdTerminatedX(shelltp_uart)) {
          chThdRelease(shelltp_uart);
          shelltp_uart = NULL;
      }
    }

    chThdSleepMilliseconds(500);
  }
}
