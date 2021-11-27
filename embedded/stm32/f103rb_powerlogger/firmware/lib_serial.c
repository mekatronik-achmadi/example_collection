#include "lib_serial.h"
#include "lib_mmc_spi.h"
#include "lib_adc.h"

extern adcsample_t adc_v0,adc_i0,adc_v1,adc_i1;
extern uint16_t val_day,val_mid;

extern adcsample_t offset_v0,offset_i0,offset_v1,offset_i1;
extern adcsample_t calib_nom_v0,calib_nom_i0,calib_nom_v1,calib_nom_i1,calib_denom;

extern bool_t saving_flag;
extern bool_t hasHeader;

extern bool_t filesystem_ready;
extern uint8_t mmc_spi_status_flag;

uint8_t setting_session=0;

Thread *shelltp = NULL;

static void cmd_now(BaseSequentialStream *chp, int argc, char *argv[]) {
  (void)argv;

  if(argc>0){
    chprintf(chp,"usage: now\n\r");
    chprintf(chp,"help: menampilkan nilai sekarang dalam integer ADC\n\r");
    return;
  }

  chprintf(chp,"=================================\n\r");
  chprintf(chp,"v0=%4d i0=%4d d=%3d\n\r",adc_v0,adc_i0,val_day);
  chprintf(chp,"v1=%4d i1=%4d h=%3d\n\r",adc_v1,adc_i1,val_mid);
  chprintf(chp,"=================================\n\r");
  return;
}

static void cmd_set(BaseSequentialStream *chp, int argc, char *argv[]) {
  (void)argv;

  if(argc>0){
    chprintf(chp,"usage: set\n\r");
    chprintf(chp,"help: menampilkan nilai offset 0-ADC dan konstanta nominator untuk kalibrasi\n\r");
    return;
  }

  chprintf(chp,"=================================\n\r");
  chprintf(chp,"Offset: \n\r");
  chprintf(chp,"v0=%4d i0=%4d \n\r",offset_v0,offset_i0);
  chprintf(chp,"v1=%4d i1=%4d \n\r",offset_v1,offset_i1);
  chprintf(chp,"=================================\n\r");
  chprintf(chp,"Constant Nom: \n\r");
  chprintf(chp,"v0=%4d i0=%4d \n\r",calib_nom_v0,calib_nom_i0);
  chprintf(chp,"v1=%4d i1=%4d \n\r",calib_nom_v1,calib_nom_i1);
  chprintf(chp,"denom=%4d (default-fix) \n\r",calib_denom);
  chprintf(chp,"=================================\n\r");
  return;
}

static void cmd_offset(BaseSequentialStream *chp, int argc, char *argv[]) {

  if(argc!=4){
    chprintf(chp,"usage: offset v0 i0 v1 i1\n\r");
    chprintf(chp,"help: mengatur offset 0-ADC dalam integer ADC\n\r");
    return;
  }

  adcsample_t v0=atoi(argv[0]);
  adcsample_t i0=atoi(argv[1]);
  adcsample_t v1=atoi(argv[2]);
  adcsample_t i1=atoi(argv[3]);

  Mmc_Check();

  char buffer[buffer_size];
  FATFS FatFs;
  UINT bw;
  FIL *fil;
  fil =(FIL *)malloc(sizeof (FIL));

  if((filesystem_ready==TRUE)&&(mmc_spi_status_flag==MMC_SPI_OK)){
      setting_session=1;

      while(!hasHeader);
      while(saving_flag);

      f_mount(0,&FatFs);
      f_open(fil, "/offset_v0", FA_WRITE | FA_CREATE_ALWAYS);
      chsnprintf(buffer,buffer_size,"%4d",v0);
      f_write(fil, buffer, strlen(buffer), &bw);
      f_close(fil);
      f_mount(0,NULL);
      chThdSleepMicroseconds(100);

      f_mount(0,&FatFs);
      f_open(fil, "/offset_i0", FA_WRITE | FA_CREATE_ALWAYS);
      chsnprintf(buffer,buffer_size,"%4d",i0);
      f_write(fil, buffer, strlen(buffer), &bw);
      f_close(fil);
      f_mount(0,NULL);
      chThdSleepMicroseconds(100);

      f_mount(0,&FatFs);
      f_open(fil, "/offset_v1", FA_WRITE | FA_CREATE_ALWAYS);
      chsnprintf(buffer,buffer_size,"%4d",v1);
      f_write(fil, buffer, strlen(buffer), &bw);
      f_close(fil);
      f_mount(0,NULL);
      chThdSleepMicroseconds(100);

      f_mount(0,&FatFs);
      f_open(fil, "/offset_i1", FA_WRITE | FA_CREATE_ALWAYS);
      chsnprintf(buffer,buffer_size,"%4d",i1);
      f_write(fil, buffer, strlen(buffer), &bw);
      f_close(fil);
      f_mount(0,NULL);
      chThdSleepMicroseconds(100);

      Mmc_Reload();

      chprintf(chp,"Offset value set\n\r");
      setting_session=0;
  }
  free(fil);
  return;
}

static void cmd_calib(BaseSequentialStream *chp, int argc, char *argv[]) {
    if(argc!=4){
      chprintf(chp,"usage: calib v0 i0 v1 i1\n\r");
      chprintf(chp,"help: mengatur nominator faktor kalibrasi dalam integer per 10000\n\r");
      return;
    }

    adcsample_t v0=atoi(argv[0]);
    adcsample_t i0=atoi(argv[1]);
    adcsample_t v1=atoi(argv[2]);
    adcsample_t i1=atoi(argv[3]);

    Mmc_Check();

    char buffer[buffer_size];
    FATFS FatFs;
    UINT bw;
    FIL *fil;
    fil =(FIL *)malloc(sizeof (FIL));

    if((filesystem_ready==TRUE)&&(mmc_spi_status_flag==MMC_SPI_OK)){
        setting_session=1;

        while(!hasHeader);
        while(saving_flag);

        f_mount(0,&FatFs);
        f_open(fil, "/calib_nom_v0", FA_WRITE | FA_CREATE_ALWAYS);
        chsnprintf(buffer,buffer_size,"%4d",v0);
        f_write(fil, buffer, strlen(buffer), &bw);
        f_close(fil);
        f_mount(0,NULL);
        chThdSleepMicroseconds(100);

        f_mount(0,&FatFs);
        f_open(fil, "/calib_nom_i0", FA_WRITE | FA_CREATE_ALWAYS);
        chsnprintf(buffer,buffer_size,"%4d",i0);
        f_write(fil, buffer, strlen(buffer), &bw);
        f_close(fil);
        f_mount(0,NULL);
        chThdSleepMicroseconds(100);

        f_mount(0,&FatFs);
        f_open(fil, "/calib_nom_v1", FA_WRITE | FA_CREATE_ALWAYS);
        chsnprintf(buffer,buffer_size,"%4d",v1);
        f_write(fil, buffer, strlen(buffer), &bw);
        f_close(fil);
        f_mount(0,NULL);
        chThdSleepMicroseconds(100);

        f_mount(0,&FatFs);
        f_open(fil, "/calib_nom_i1", FA_WRITE | FA_CREATE_ALWAYS);
        chsnprintf(buffer,buffer_size,"%4d",i1);
        f_write(fil, buffer, strlen(buffer), &bw);
        f_close(fil);
        f_mount(0,NULL);
        chThdSleepMicroseconds(100);

        Mmc_Reload();

        chprintf(chp,"Calibration factor set\n\r");
        setting_session=0;
    }
    free(fil);
    return;
}

static const ShellCommand commands[] = {
  {"now",cmd_now},
  {"set",cmd_set},
  {"offset",cmd_offset},
  {"calib",cmd_calib},
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
}

void Shell_Setup(void){
    if (!shelltp){
      shelltp = shellCreate(&shell_cfg1, SHELL_WA_SIZE, NORMALPRIO);} /* create shell tread */
    else if (chThdTerminated(shelltp)) {
      chThdRelease(shelltp);    /* Recovers memory of the previous shell.   */
      shelltp = NULL;           /* Triggers spawning of a new shell.        */
    }
}
