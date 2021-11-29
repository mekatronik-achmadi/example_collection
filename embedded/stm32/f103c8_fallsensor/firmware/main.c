/*
              DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE

 Copyright (C) 2018 Achmadi S.T.

 Everyone is permitted to copy and distribute verbatim or modified
 copies of this license document, and changing it is allowed as long
 as the name is changed.

            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
   TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION

  0. You just DO WHAT THE FUCK YOU WANT TO.
 */

/**
 * @file    main.c
 * @brief   Main routine code.
 *
 * @addtogroup Main
 * @{
 */

#include "ch.h"
#include "hal.h"

#include "din_adc.h"
#include "din_web.h"
#include "din_uart.h"
#include "din_mpu.h"
#include "din_fuzzy.h"

static THD_WORKING_AREA(waLED, 128);
static THD_FUNCTION(thdLED, arg) {

    (void)arg;

    chRegSetThreadName("blinker");
    while (true) {
        palTogglePad(GPIOC,13);
        chThdSleepMilliseconds(500);
    }
}

/**
 * @brief  All Main function.
 */
int main(void) {

  halInit();
  chSysInit();

  d_adc_start();
  d_web_start();
  d_uart_start();
  d_uart_info();
  d_mpu_start();

#ifdef SERVER_NOTIF
  chprintf((BaseSequentialStream *)&SD1,"All Setup Finished\r\n");
#endif

  palSetPadMode(GPIOC,13,PAL_MODE_OUTPUT_PUSHPULL);
  palClearPad(GPIOC,13);
  chThdCreateStatic(waLED, sizeof(waLED), NORMALPRIO, thdLED, NULL);

  chThdSleepMilliseconds(200);
  d_web_data();

  chThdSleepMilliseconds(200);

  while(true){
    chThdSleepMilliseconds(1);
    d_web_term();
  }
}
/** @} */
