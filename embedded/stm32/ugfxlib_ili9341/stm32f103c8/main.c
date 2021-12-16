#include "ch.h"
#include "hal.h"
#include "gfx.h"

#include "chprintf.h"
#include "shell.h"

#include "term.h"

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

static thread_t *shelltp = NULL;

static void usage(BaseSequentialStream *chp, char *p) {

  chprintf(chp, "Usage: %s\r\n", p);
}

static void cmd_test(BaseSequentialStream *chp, int argc, char *argv[]) {
    (void)argv;
    if (argc > 0) {usage(chp, "test");return;}

    chprintf(chp,"Serial OK\r\n");
    term_strbuff("Console OK");
}

static void cmd_clr(BaseSequentialStream *chp, int argc, char *argv[]) {
    (void)argv;
    if (argc > 0) {usage(chp, "clr");return;}

    term_clear();
}

static void cmd_show(BaseSequentialStream *chp, int argc, char *argv[]) {

  (void)argv;
  if (argc > 0) {usage(chp, "show");return;}

  char strBuffer[STR_BUFFER_SIZE];

  // On Serial Terminal
  chprintf(chp, "Kernel:       %s\r\n", CH_KERNEL_VERSION);
#ifdef PORT_COMPILER_NAME
  chprintf(chp, "Compiler:     %s\r\n", PORT_COMPILER_NAME);
#endif
  chprintf(chp, "Architecture: %s\r\n", PORT_ARCHITECTURE_NAME);
#ifdef PORT_CORE_VARIANT_NAME
  chprintf(chp, "Core Variant: %s\r\n", PORT_CORE_VARIANT_NAME);
#endif
#ifdef PORT_INFO
  chprintf(chp, "Port Info:    %s\r\n", PORT_INFO);
#endif
#ifdef PLATFORM_NAME
  chprintf(chp, "Platform:     %s\r\n", PLATFORM_NAME);
#endif
#ifdef BOARD_NAME
  chprintf(chp, "Board:        %s\r\n", BOARD_NAME);
#endif
#ifdef __DATE__
#ifdef __TIME__
  chprintf(chp, "Build time:   %s%s%s\r\n", __DATE__, " - ", __TIME__);
#endif
#endif
#ifdef CH_LICENSE_TYPE_STRING
  chprintf(chp, "License:   %s\r\n", CH_LICENSE_TYPE_STRING);
#endif

  // On LCD Console
  chsnprintf(strBuffer,STR_BUFFER_SIZE,"\r\n");
  term_string(strBuffer);

  chsnprintf(strBuffer,STR_BUFFER_SIZE,"Kernel: %s\r\n", CH_KERNEL_VERSION);
  term_string(strBuffer);
#ifdef PORT_COMPILER_NAME
  chsnprintf(strBuffer,STR_BUFFER_SIZE,"Compiler: %s\r\n", PORT_COMPILER_NAME);
  term_string(strBuffer);
#endif
  chsnprintf(strBuffer,STR_BUFFER_SIZE,"Architecture: %s\r\n", PORT_ARCHITECTURE_NAME);
  term_string(strBuffer);
#ifdef PORT_CORE_VARIANT_NAME
  chsnprintf(strBuffer,STR_BUFFER_SIZE,"Core Variant: %s\r\n", PORT_CORE_VARIANT_NAME);
  term_string(strBuffer);
#endif
#ifdef PORT_INFO
  chsnprintf(strBuffer,STR_BUFFER_SIZE,"Port Info: %s\r\n", PORT_INFO);
  term_string(strBuffer);
#endif
#ifdef PLATFORM_NAME
  chsnprintf(strBuffer,STR_BUFFER_SIZE,"Platform: %s\r\n", PLATFORM_NAME);
  term_string(strBuffer);
#endif
#ifdef BOARD_NAME
  chsnprintf(strBuffer,STR_BUFFER_SIZE,"Board: %s\r\n", BOARD_NAME);
  term_string(strBuffer);
#endif
#ifdef __DATE__
#ifdef __TIME__
  chsnprintf(strBuffer,STR_BUFFER_SIZE,"Build time: %s%s%s\r\n", __DATE__, " - ", __TIME__);
  term_string(strBuffer);
#endif
#endif
#ifdef CH_LICENSE_TYPE_STRING
  chsnprintf(strBuffer,STR_BUFFER_SIZE,"License: %s\r\n", CH_LICENSE_TYPE_STRING);
  term_string(strBuffer);
#endif

}

static const ShellCommand commands[] = {
    {"test", cmd_test},
    {"clr", cmd_clr},
    {"show", cmd_show},
    {NULL, NULL}
};

static const ShellConfig shell_cfg = {
    (BaseSequentialStream *)&SD1,
    commands
};

int main(void) {

  gfxInit();

  term_start();

  palSetPadMode(GPIOA,9,PAL_MODE_STM32_ALTERNATE_PUSHPULL); //TX
  palSetPadMode(GPIOA,10,PAL_MODE_INPUT); //RX
  sdStart(&SD1,NULL);

  shellInit();

  chThdCreateStatic(waLED, sizeof(waLED), NORMALPRIO, thdLED, NULL);

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
