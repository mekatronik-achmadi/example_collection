/**
 * @file   m_shell.c
 * @brief  Communication Shell handler code
 *
 * @addtogroup M_USB
 * @{
 */

#include "m_shell.h"
#include "m_gui.h"

/*===========================================================================*/
/* Command line commands                                                     */
/*===========================================================================*/

/**
 * @brief   Serial Driver object.
 */
SerialUSBDriver SDU1;

/**
 * @brief   shell thread object.
 */
static thread_t *shelltp = NULL;

/*===========================================================================*/
/* Additional Command line commands                                          */
/*===========================================================================*/

static void cmd_snd(BaseSequentialStream *chp, int argc, char *argv[]) {
    (void) chp;
    (void) argc;
    (void) argv;

    uint8_t i;
    uint32_t val;

    for(i=0;i<6;i++){
        val = rand() % 100;
        m_data_set(val);
    }
}

static void cmd_mic(BaseSequentialStream *chp, int argc, char *argv[]) {
    (void) chp;
    (void) argc;
    (void) argv;

    chprintf((BaseSequentialStream *)&SD3,"snd\r\n");
    chprintf(chp,"mic test\r\n");
}

/*===========================================================================*/
/* Command line serial usb                                                   */
/*===========================================================================*/

/**
 * @brief   commands enumeration.
 */
static const ShellCommand commands[] = {
  {"snd",cmd_snd},
  {"mic",cmd_mic},
  {NULL, NULL}
};

/**
 * @brief   shell driver command structure.
 */
static const ShellConfig shell_cfg1 = {
  (BaseSequentialStream *)&SDU1,
  commands
};

void m_shell_start(void){
    sduObjectInit(&SDU1);
    sduStart(&SDU1, &serusbcfg);

    usbDisconnectBus(serusbcfg.usbp);
    chThdSleepMilliseconds(1000);
    usbStart(serusbcfg.usbp, &usbcfg);
    usbConnectBus(serusbcfg.usbp);
}

/**
 * @brief   Setup shell function to loop.
 */
void m_shell_term(void){
    if (!shelltp) {
      if (SDU1.config->usbp->state == USB_ACTIVE) {
        shelltp = shellCreate(&shell_cfg1, SHELL_WA_SIZE, NORMALPRIO);
      }
    }
    else {
      if (chThdTerminatedX(shelltp)) {
        chThdRelease(shelltp);
        shelltp = NULL;
      }
    }
}
/** @} */
