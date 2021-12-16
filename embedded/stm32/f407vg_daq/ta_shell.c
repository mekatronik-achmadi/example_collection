#include "ta_shell.h"

extern dacsample_t dacbuffer[DAC_BUFFER_SIZE];
extern uint16_t adc_co,adc_so2,adc_co2,adc_nox;

thread_t *shelltp = NULL;

extern const USBConfig usbcfg;
extern SerialUSBConfig serusbcfg;

extern struct ds1307_t calendar;

extern FATFS MMC_FS;
extern bool fs_ready;
extern uint32_t clusters;
extern FATFS *fsp;
extern uint8_t fbuff[1024];
extern FRESULT err;

SerialUSBDriver SDU1;

static void cmd_mem(BaseSequentialStream *chp, int argc, char *argv[]) {
  size_t n, size;

  (void)argv;
  if (argc > 0) {
    chprintf(chp, "Usage: mem\r\n");
    return;
  }
  n = chHeapStatus(NULL, &size);
  chprintf(chp, "core free memory : %u bytes\r\n", chCoreGetStatusX());
  chprintf(chp, "heap fragments   : %u\r\n", n);
  chprintf(chp, "heap free total  : %u bytes\r\n", size);
}

static void cmd_threads(BaseSequentialStream *chp, int argc, char *argv[]) {
  static const char *states[] = {CH_STATE_NAMES};
  thread_t *tp;

  (void)argv;
  if (argc > 0) {
    chprintf(chp, "Usage: threads\r\n");
    return;
  }
  chprintf(chp, "    addr    stack prio refs     state time\r\n");
  tp = chRegFirstThread();
  do {
    chprintf(chp, "%08lx %08lx %4lu %4lu %9s\r\n",
            (uint32_t)tp, (uint32_t)tp->p_ctx.r13,
            (uint32_t)tp->p_prio, (uint32_t)(tp->p_refs - 1),
            states[tp->p_state]);
    tp = chRegNextThread(tp);
  } while (tp != NULL);
}

static void cmd_now(BaseSequentialStream *chp, int argc, char *argv[]) {

  (void)argv;
  if (argc > 0) {
    chprintf(chp, "Usage: now\r\n");
    return;
  }

  chprintf(chp, "#year  = %d\r\n",calendar.year);
  chprintf(chp, "#month = %d\r\n",calendar.month);
  chprintf(chp, "#date  = %d\r\n",calendar.date);
  chprintf(chp, "#hour  = %d\r\n",calendar.hours);
  chprintf(chp, "#minute= %d\r\n",calendar.minutes);
  chprintf(chp, "#second= %d\r\n",calendar.seconds);
}

static void cmd_settime(BaseSequentialStream *chp, int argc, char *argv[]) {

  msg_t status = MSG_OK;
  systime_t timeOut = MS2ST ( 4 );

  if (argc != 3) {
    chprintf(chp, "Usage: settime sec min hr\r\n");
    return;
  }

  calendar.seconds    = atoi(argv[0]);
  calendar.minutes    = atoi(argv[1]);
  calendar.hours      = atoi(argv[2]);
  setDs1307Date( &status, &timeOut, calendar);

  chprintf(chp, "time was set\r\n");
}

static void cmd_setdate(BaseSequentialStream *chp, int argc, char *argv[]) {

  msg_t status = MSG_OK;
  systime_t timeOut = MS2ST ( 4 );

  if (argc != 3) {
    chprintf(chp, "Usage: setdate date month year\r\n");
    return;
  }

  calendar.date       = atoi(argv[0]);
  calendar.month      = atoi(argv[1]);
  calendar.year       = atoi(argv[2]);
  setDs1307Date( &status, &timeOut, calendar);

  chprintf(chp, "date was set\r\n");
}

static void cmd_dactest(BaseSequentialStream *chp, int argc, char *argv[]) {
  
  if (argc != 2) {
  ch  printf(chp, "adctest <1|2> value\r\n");
      return;
  }
  
  uint8_t nchan=atoi(argv[0]);
  uint16_t val=atoi(argv[1]);
  
  if(nchan==1){
    dacbuffer[0]=val;
  }
  else if(nchan==2){
    dacbuffer[1]=val;
  }
}

static void cmd_mmctree(BaseSequentialStream *chp, int argc, char *argv[]) {

    (void)argv;
    if (argc > 0) {
    chprintf(chp, "mmctree\r\n");
        return;
    }

    if (!fs_ready) {
      chprintf(chp, "File System not mounted\r\n");
      return;
    }

    err = f_getfree("/", &clusters, &fsp);
    if (err != FR_OK) {
        chprintf(chp, "FS: f_getfree() failed (%i)\r\n",err);
        return;
    }

    chprintf(chp,"FS: %lu free clusters, %lu sectors per cluster, %lu bytes free\r\n",clusters, (uint32_t)MMC_FS.csize,clusters * (uint32_t)MMC_FS.csize * (uint32_t)MMC_SECTOR_SIZE);
    fbuff[0] = 0;
    scan_files(chp, (char *)fbuff);
}

static void cmd_mmctest(BaseSequentialStream *chp, int argc, char *argv[]) {

    (void)argv;
    if (argc > 0) {
    chprintf(chp, "mmctest\r\n");
        return;
    }

    if (!fs_ready) {
      chprintf(chp, "File System not mounted\r\n");
      return;
    }

    FIL FDLogFile;
    memset(&FDLogFile, 0, sizeof(FIL));
    FRESULT err_file;

    UINT bw;
    char buffer[buffer_size];

    err_file = f_open(&FDLogFile, "Test.txt", FA_WRITE | FA_OPEN_ALWAYS );
    if (err_file == FR_OK || err_file == FR_EXIST){
        err_file = f_lseek(&FDLogFile, f_size(&FDLogFile));
        if(err_file == FR_OK){

            chsnprintf(buffer,buffer_size,"Aku Jomblo!!!\n\r");
            f_write(&FDLogFile, buffer, strlen(buffer), &bw);

            f_close(&FDLogFile);

            chprintf(chp, "Some text written\r\n");
            return;
        }else{
            chprintf(chp, "Failed to seek file\r\n");
            return;
        }
    }else{
        chprintf(chp, "Cannot Write file\r\n");
        return;
    }
}

static void cmd_mmcadc(BaseSequentialStream *chp, int argc, char *argv[]) {

    (void)argv;
    if (argc > 0) {
    chprintf(chp, "mmcadc\r\n");
        return;
    }

    if (!fs_ready) {
      chprintf(chp, "File System not mounted\r\n");
      return;
    }

    Tulis_Adc();
}

static void cmd_dataadc(BaseSequentialStream *chp, int argc, char *argv[]) {
  (void) argv;
  if (argc > 0) {
    chprintf(chp, "Usage: dataadc\r\n");
    return;
  }
{
  chprintf(chp, "adc_co = %4i\r\n",adc_co);
  chprintf(chp, "adc_so2= %4i\r\n",adc_so2);
  chprintf(chp, "adc_co2= %4i\r\n",adc_co2);
  chprintf(chp, "adc_nox= %4i\r\n",adc_nox);
}
}

static void cmd_testsms(BaseSequentialStream *chp, int argc, char *argv[]) {
  (void) argv;
  if (argc > 0) {
    chprintf(chp, "Usage: testsms\r\n");
    return;
  }

  Sms_Test();
}

static const ShellCommand commands[] = {
  {"mem", cmd_mem},
  {"threads", cmd_threads},
  {"now", cmd_now},
  {"settime", cmd_settime},
  {"setdate", cmd_setdate},
  {"dactest", cmd_dactest},
  {"mmctree", cmd_mmctree},
  {"mmctest", cmd_mmctest},
  {"mmcadc",  cmd_mmcadc },
  {"dataadc", cmd_dataadc},
  {"testsms", cmd_testsms},
  {NULL, NULL}
};

static const ShellConfig shell_cfg = {
  (BaseSequentialStream *)&SDU1,
  commands
};

void Shell_Init(void){

    sduObjectInit(&SDU1);
    sduStart(&SDU1, &serusbcfg);

    usbDisconnectBus(serusbcfg.usbp);
    chThdSleepMilliseconds(1000);
    usbStart(serusbcfg.usbp, &usbcfg);
    usbConnectBus(serusbcfg.usbp);

    shellInit();
}

void Shell_Run(void){
    if (!shelltp && (SDU1.config->usbp->state == USB_ACTIVE))
      shelltp = shellCreate(&shell_cfg, SHELL_WA_SIZE, NORMALPRIO);
    else if (chThdTerminatedX(shelltp)) {
      chThdRelease(shelltp);    /* Recovers memory of the previous shell.   */
      shelltp = NULL;           /* Triggers spawning of a new shell.        */
    }
    chThdSleepMilliseconds(1000);
}
