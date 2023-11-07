/**
 * @file main.c
 * @brief Main code
 *
 * @addtogroup MAIN
 * @{
 */

#include <string.h>

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

static THD_WORKING_AREA(waLora, 128);
static THD_FUNCTION(thdLora, arg) {

    (void)arg;
    unsigned char data[50] = {0};
    char strData[16] = {0};

    chRegSetThreadName("receive lora");
    while (true) {
        uint16_t packetSize = lora_parsePacket();
        if(packetSize>0){
            chprintf((BaseSequentialStream*)&SD1, "Received packet size %i data: ",packetSize);

            while(lora_available())
            for(uint16_t i=0;i<packetSize;i++){
                data[i] = lora_read();
                chprintf((BaseSequentialStream*)&SD1, " %i ", data[i]);

                char chr = (char) data[i];
                strncat(strData, &chr, 1);
            }
            chprintf((BaseSequentialStream*)&SD1, " as '%s' with RSSI: %i\r\n",strData,lora_packetRssi());
            strcpy(strData, "");
        }
        chThdSleepMicroseconds(1);
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

  lora_begin(433E6);
  chThdCreateStatic(waLora, sizeof(waLora), NORMALPRIO, thdLora, NULL);

  chprintf((BaseSequentialStream *)&SD1, "System Initiated \r\n");

  while(true){
   chThdSleepMilliseconds(100);
  }
}

/**  @} */

