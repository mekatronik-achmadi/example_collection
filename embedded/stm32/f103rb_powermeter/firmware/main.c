#include "srcconf.h"

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
   * Project defined HAL Setup
   */
  
  Adc_Setup();
  Serial_Setup();
  
  palSetPadMode(GPIOA,8,PAL_MODE_OUTPUT_PUSHPULL);
  
  while (TRUE) {   
    Shell_Setup(); /* create shell */
    chThdSleepMilliseconds(500);
    palTogglePad(GPIOA,8);
  };
}
