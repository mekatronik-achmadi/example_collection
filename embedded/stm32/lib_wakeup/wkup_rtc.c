/*
    ChibiOS/RT - Copyright (C) 2006,2007,2008,2009,2010,
                 2011,2012 Giovanni Di Sirio.

    This file is part of ChibiOS/RT.

    ChibiOS/RT is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.

    ChibiOS/RT is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "ch.h"
#include "hal.h"
#include "test.h"
#include "shell.h"
#include "chprintf.h"
#include "evtimer.h"
#include "chrtclib.h"

/*===========================================================================*/
/* Command line related.                                                     */
/*===========================================================================*/

#define SHELL_WA_SIZE   THD_WA_SIZE(2048)
#define TEST_WA_SIZE    THD_WA_SIZE(256)

static void cmd_mem(BaseSequentialStream *chp, int argc, char *argv[]) {
  size_t n, size;

  (void)argv;
  if (argc > 0) {
    chprintf(chp, "Usage: mem\r\n");
    return;
  }
  n = chHeapStatus(NULL, &size);
  chprintf(chp, "core free memory : %u bytes\r\n", chCoreStatus());
  chprintf(chp, "heap fragments   : %u\r\n", n);
  chprintf(chp, "heap free total  : %u bytes\r\n", size);
}

static void cmd_threads(BaseSequentialStream *chp, int argc, char *argv[]) {
  static const char *states[] = {THD_STATE_NAMES};
  Thread *tp;

  (void)argv;
  if (argc > 0) {
    chprintf(chp, "Usage: threads\r\n");
    return;
  }
  chprintf(chp, "    addr    stack prio refs     state time\r\n");
  tp = chRegFirstThread();
  do {
    chprintf(chp, "%.8lx %.8lx %4lu %4lu %9s %lu\r\n",
            (uint32_t)tp, (uint32_t)tp->p_ctx.r13,
            (uint32_t)tp->p_prio, (uint32_t)(tp->p_refs - 1),
            states[tp->p_state], (uint32_t)tp->p_time);
    tp = chRegNextThread(tp);
  } while (tp != NULL);
}

static void cmd_test(BaseSequentialStream *chp, int argc, char *argv[]) {
  Thread *tp;

  (void)argv;
  if (argc > 0) {
    chprintf(chp, "Usage: test\r\n");
    return;
  }
  tp = chThdCreateFromHeap(NULL, TEST_WA_SIZE, chThdGetPriority(),
                           TestThread, chp);
  if (tp == NULL) {
    chprintf(chp, "out of memory\r\n");
    return;
  }
  chThdWait(tp);
}

static void cmd_reboot(BaseSequentialStream *chp, int argc, char *argv[]){
  (void)argv;
  if (argc > 0) {
    chprintf(chp, "Usage: rboot\r\n");
    return;
  }
  chprintf(chp, "rebooting...\r\n");
  chThdSleepMilliseconds(100);
  NVIC_SystemReset();
}

static void cmd_sleep(BaseSequentialStream *chp, int argc, char *argv[]){
  (void)argv;
  if (argc > 0) {
    chprintf(chp, "Usage: sleep\r\n");
    return;
  }
  chprintf(chp, "Going to sleep. Type any character to wake up.\r\n");

  chThdSleepMilliseconds(200);
  extChannelEnable(&EXTD1, 0);

  PWR->CR |= (PWR_CR_LPDS | PWR_CR_CSBF | PWR_CR_CWUF);
  PWR->CR &= ~PWR_CR_PDDS;
  SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
  __WFI();
}


static const ShellCommand commands[] = {
  {"mem", cmd_mem},
  {"threads", cmd_threads},
  {"test", cmd_test},
  {"reboot", cmd_reboot},
  {"sleep", cmd_sleep},
  {NULL, NULL}
};

static const ShellConfig shell_cfg1 = {
  (BaseSequentialStream *)&SD2,
  commands
};

/*===========================================================================*/

#define CR_DS_MASK              ((uint32_t)0xFFFFFFFC)
#define PWR_Regulator_LowPower  ((uint32_t)0x00000001)
#define PWR_FLAG_WU             ((uint32_t)0x00000001)

CH_IRQ_HANDLER(RTC_Alarm_IRQHandler) {
  uint32_t pr;

  CH_IRQ_PROLOGUE();

  pr = EXTI->PR & (1 << 17);
  EXTI->PR = pr;

  EXTD1.config->channels[17].cb(&EXTD1, 17);

  CH_IRQ_EPILOGUE();
}


/*
 * LED thread
 */
static WORKING_AREA(waThread1, 1024);
static msg_t Thread1(void *arg) {

  (void)arg;
  chRegSetThreadName("LED");

  while (TRUE) {

    palClearPad(GPIOA, GPIOA_LED);
    chThdSleepMilliseconds(100);
    palSetPad(GPIOA, GPIOA_LED);
    chThdSleepMilliseconds(100);

  }
}

/*
 * RTC callback function
 */
//BinarySemaphore alarm_sem;

void pwr_flag_clear(uint32_t PWR_FLAG)
{
    PWR->CR |=  PWR_FLAG << 2;
}

static void rtc_cb(RTCDriver *rtcp, rtcevent_t event) {

  (void)rtcp;

  switch (event) {
  case RTC_EVENT_OVERFLOW:
    break;
  case RTC_EVENT_SECOND:
    break;
  case RTC_EVENT_ALARM:
    break;
  }

  pwr_flag_clear(PWR_FLAG_WU);
}

/* Wake up callback.*/
static void extcb2(EXTDriver *extp, expchannel_t channel) {

  (void)extp;
  (void)channel;

  chSysLockFromIsr();
  /* we must reinit clocks after waking up ESPECIALLY if use HSE or HSI+PLL */
  stm32_clock_init();
  extChannelDisableI(&EXTD1, 10);
  chSysUnlockFromIsr();
}


/* Wake up callback.*/
static void extcb3(EXTDriver *extp, expchannel_t channel) {

  (void)extp;
  (void)channel;

  chSysLockFromIsr();
  /* we must reinit clocks after waking up ESPECIALLY if use HSE or HSI+PLL */
  stm32_clock_init();
  chSysUnlockFromIsr();

  palSetPad(GPIOA, GPIOA_LEDR);



}


static const EXTConfig extcfg = {
  {
    {EXT_CH_MODE_BOTH_EDGES | EXT_CH_MODE_AUTOSTART | EXT_MODE_GPIOA, extcb2},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_RISING_EDGE | EXT_CH_MODE_AUTOSTART, extcb3},
  }
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
   * Activates the serial driver 1,2 using the driver default configuration.
   */
  sdStart(&SD1, NULL);
  sdStart(&SD2, NULL);

  /*
   * Shell manager initialization.
   */
  shellInit();
  static WORKING_AREA(waShell1, SHELL_WA_SIZE);
  shellCreateStatic(&shell_cfg1, waShell1, sizeof(waShell1), NORMALPRIO);

  /*
   * Creates the rest of threads.
   */
  chThdCreateStatic(waThread1, sizeof(waThread1), NORMALPRIO, Thread1, NULL);

  palClearPad(GPIOA, GPIOA_LEDR);

  /* set alarm in the future */
  rtcGetTime(&RTCD1, &timespec);
  alarmspec.tv_sec = timespec.tv_sec + 10;
  rtcSetAlarm(&RTCD1, 0, &alarmspec);
  rtcSetCallback(&RTCD1, rtc_cb);

  /*
   * Activates the EXT driver 1.
   */
  extStart(&EXTD1, &extcfg);                  

  /*
   * Normal main() thread activity
   */
  while (TRUE) {
    chThdSleepSeconds(1);
  }
}
