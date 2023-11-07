/**
 * @file main.c
 * @brief Main code
 *
 * @addtogroup MAIN
 * @{
 */

#include "ch.h"
#include "hal.h"

#include "chprintf.h"

#include "../lora/lora.h"

#define SHELL_WA_SIZE   THD_WORKING_AREA_SIZE(512)

static THD_WORKING_AREA(waLED, 128);
static THD_FUNCTION(thdLED, arg) {

    (void)arg;

    chRegSetThreadName("blinker");
    while (true) {
        palTogglePad(GPIOC,13);
        chThdSleepMilliseconds(100);
    }
}

int main(void) {

  halInit();
  chSysInit();

  palSetPadMode(GPIOC,13,PAL_MODE_OUTPUT_PUSHPULL);
  palClearPad(GPIOC,13);
  chThdCreateStatic(waLED, sizeof(waLED), NORMALPRIO, thdLED, NULL);

  palSetPadMode(GPIOA,9,PAL_MODE_STM32_ALTERNATE_PUSHPULL); //TX
  palSetPadMode(GPIOA,10,PAL_MODE_INPUT); //RX
  sdStart(&SD1,NULL);


  lora_Begin(433E6);

  chprintf((BaseSequentialStream *)&SD1, "System Initiated \r\n");

  while(true){
   chThdSleepMilliseconds(100);
  }
}

/**  @} */

