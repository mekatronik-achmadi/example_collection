#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "m_uart.h"
#include "m_gui.h"
#include "m_shell.h"

extern char txt0[16];
static thread_t *shelltp_uart = NULL;

static void cmd_snd(BaseSequentialStream *chp, int argc, char *argv[]) {
    (void) chp;
    uint8_t i;
    int8_t val;

    if(argc!=10)return;

    chsnprintf(txt0,16,"updating");
    for(i=0;i<10;i++){
        val = (int8_t) atoi(argv[i]);
        m_data_set((val*20)+20);
    }
}

static const ShellCommand commands_uart[] = {
    {"snd",cmd_snd},
    {NULL, NULL}
};

static const ShellConfig shell_uart_cfg = {
  (BaseSequentialStream *)&SD3,
  commands_uart
};

void m_uart_term(void){
    if (!shelltp_uart) {
        shelltp_uart = shellCreate(&shell_uart_cfg, SHELL_WA_SIZE, NORMALPRIO);
    }
    else {
        if (chThdTerminatedX(shelltp_uart)) {
            chThdRelease(shelltp_uart);
            shelltp_uart = NULL;
        }
    }
}

static THD_WORKING_AREA(waReq, 256);
static THD_FUNCTION(thdReq, arg) {
    (void)arg;
    chRegSetThreadName("draw request");

    while(1){
        chprintf((BaseSequentialStream *)&SD3,"snd\r\n");
        gfxSleepMicroseconds(500);
    }
}

void m_uart_init(void){
    palSetPadMode(GPIOC,10,PAL_MODE_ALTERNATE(7) | PAL_STM32_OSPEED_HIGHEST); //TX
    palSetPadMode(GPIOC,11,PAL_MODE_ALTERNATE(7) | PAL_STM32_OSPEED_HIGHEST); //RX

    sdStart(&SD3,NULL);

    chThdCreateStatic(waReq, sizeof(waReq),	NORMALPRIO, thdReq, NULL);
}
