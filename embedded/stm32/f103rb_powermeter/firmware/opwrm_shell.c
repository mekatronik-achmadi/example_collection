#include "srcconf.h"

Thread *shelltp = NULL;

static void cmd_test(BaseSequentialStream *chp, int argc, char *argv[]) {
  (void)argv;
  
  if(argc>0){
    chprintf(chp,"bad commands");
    return;
  }
  
  chprintf(chp,"shell is well");
  return;
}

static const ShellCommand commands[] = {
  {"test",cmd_test},
  {NULL, NULL}
};

static const ShellConfig shell_cfg1 = {
  (BaseSequentialStream *)&SD1,
  commands
};

void Serial_Setup(void){
  palSetPadMode(GPIOA,9,16);
  palSetPadMode(GPIOA,10,2);
  sdStart(&SD1,NULL);
  shellInit();
  //chThdCreateStatic(wa_dataThread, sizeof(wa_dataThread), NORMALPRIO, dataThread, NULL);
}

void Shell_Setup(void){
    if (!shelltp){
      shelltp = shellCreate(&shell_cfg1, SHELL_WA_SIZE, NORMALPRIO);} /* create shell tread */
    else if (chThdTerminated(shelltp)) {
      chThdRelease(shelltp);    /* Recovers memory of the previous shell.   */
      shelltp = NULL;           /* Triggers spawning of a new shell.        */
    }
}