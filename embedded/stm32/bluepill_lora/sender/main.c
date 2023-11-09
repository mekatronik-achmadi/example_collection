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
#include "shell.h"

#include "../lora/lora.h"

#define SHELL_WA_SIZE   THD_WORKING_AREA_SIZE(512)

#define SENDLOOPNUMBER  10

static THD_WORKING_AREA(waLED, 128);
static THD_FUNCTION(thdLED, arg) {

    (void)arg;

    chRegSetThreadName("blinker");
    while (true) {
        palTogglePad(GPIOC,13);
        chThdSleepMilliseconds(100);
    }
}

static thread_t *shelltp = NULL;

static void cmd_test(BaseSequentialStream *chp, int argc, char *argv[]) {
    (void)argv;
    if(argc > 0){chprintf(chp,"Usage: test\r\n");return;}

    chprintf(chp,"Serial OK\r\n");
}

static void cmd_send(BaseSequentialStream *chp, int argc, char *argv[]) {
    (void)argv;
    uint8_t packetsize;
    char packet[16] = {0};

    if(argc > 0){chprintf(chp,"Usage: send\r\n");return;}

    lora_beginPacket();
    chsnprintf(packet, sizeof(packet), "test data");
    packetsize = lora_writeChars(packet, sizeof(packet));
    lora_endPacket();

    chprintf(chp,"%i packet sent\r\n",packetsize);
}

static void cmd_loop(BaseSequentialStream *chp, int argc, char *argv[]) {
    (void)argv;
    uint8_t packetsize;
    char packet[16] = {0};

    if(argc > 0){chprintf(chp,"Usage: loop\r\n");return;}

    chprintf(chp, "Data Send Loop Start\r\n");
    for(uint8_t i=0;i<SENDLOOPNUMBER;i++){
        lora_beginPacket();
        chsnprintf(packet, sizeof(packet), "test data");
        packetsize = lora_writeChars(packet, sizeof(packet));
        lora_endPacket();

        chprintf(chp,"%i packet sent\r\n",packetsize);

        chThdSleepMilliseconds(500);
    }
    chprintf(chp, "Data Send Loop Finished\r\n");
}
static const ShellCommand commands[] = {
    {"test", cmd_test},
    {"send", cmd_send},
    {"loop", cmd_loop},
    {NULL, NULL}
};

static const ShellConfig shell_cfg = {
    (BaseSequentialStream *)&SD1,
    commands
};

int main(void) {

  halInit();
  chSysInit();

  palSetPadMode(GPIOC,13,PAL_MODE_OUTPUT_PUSHPULL);
  palClearPad(GPIOC,13);
  chThdCreateStatic(waLED, sizeof(waLED), NORMALPRIO, thdLED, NULL);

  palSetPadMode(GPIOA,9,PAL_MODE_STM32_ALTERNATE_PUSHPULL); //TX
  palSetPadMode(GPIOA,10,PAL_MODE_INPUT); //RX
  sdStart(&SD1,NULL);

  shellInit();

  lora_begin(433E6);

  chprintf((BaseSequentialStream *)&SD1, "System Initiated \r\n");

  while(true){
    if (!shelltp)
      shelltp = shellCreate(&shell_cfg, SHELL_WA_SIZE, NORMALPRIO);
    else if (chThdTerminatedX(shelltp)) {
      chThdRelease(shelltp);
      shelltp = NULL;
    }
    chThdSleepMilliseconds(100);
  }
}

/**  @} */

