#include "ta_mmc.h"

FATFS MMC_FS;
MMCDriver MMCD1;
bool fs_ready = FALSE;

FRESULT err;
uint32_t clusters;
FATFS *fsp;
uint8_t fbuff[1024];

static SPIConfig hs_spicfg = {NULL, GPIOB, 12, 0};
static SPIConfig ls_spicfg = {NULL, GPIOB, 12,SPI_CR1_BR_2 | SPI_CR1_BR_1};
static MMCConfig mmccfg = {&SPID2, &ls_spicfg, &hs_spicfg};

FRESULT scan_files(BaseSequentialStream *chp, char *path) {
  FRESULT res;
  FILINFO fno;
  DIR dir;
  int i;
  char *fn;

#if _USE_LFN
  fno.lfname = 0;
  fno.lfsize = 0;
#endif
  res = f_opendir(&dir, path);
  if (res == FR_OK) {
    i = strlen(path);
    for (;;) {
      res = f_readdir(&dir, &fno);
      if (res != FR_OK || fno.fname[0] == 0)
        break;
      if (fno.fname[0] == '.')
        continue;
      fn = fno.fname;
      if (fno.fattrib & AM_DIR) {
        path[i++] = '/';
        strcpy(&path[i], fn);
        res = scan_files(chp, path);
        if (res != FR_OK)
          break;
        path[--i] = 0;
      }
      else {
        chprintf(chp, "%s/%s\r\n", path, fn);
      }
    }
  }
  return res;
}

void Mmc_Mount(void) {

    if (fs_ready) {
        return;
    }

    if (mmcConnect(&MMCD1)) {
        return;
    }

    err = f_mount(&MMC_FS,"/",1);
    if (err != FR_OK) {
        mmcDisconnect(&MMCD1);
        fs_ready = FALSE;
        return;
    }
    fs_ready = TRUE;
}

void Mmc_Unmount(void) {

  f_mount(NULL,"/",1);
  mmcDisconnect(&MMCD1);
  fs_ready = FALSE;
}

FRESULT f_append (
    FIL* fp,            /* [OUT] file object to create */
    const char* path    /* [IN]  file name to be opened */
)
{
    FRESULT fr;

    /* Opens an existing file. If not exist, creates a new file. */
    fr = f_open(fp, path, FA_WRITE | FA_OPEN_ALWAYS | FA_READ);
    if (fr == FR_OK) {
        /* Seek to end of the file to append data */
        fr = f_lseek(fp, f_size(fp));
        if (fr != FR_OK)
            f_close(fp);
    }
    return fr;
}

void Mmc_Init(){
    palSetPadMode(GPIOB,13,PAL_MODE_ALTERNATE(5) | PAL_STM32_OSPEED_HIGHEST); //SCK
    palSetPadMode(GPIOB,12,PAL_MODE_OUTPUT_PUSHPULL | PAL_STM32_OSPEED_HIGHEST); //NSS
    palSetPadMode(GPIOC,2,PAL_MODE_ALTERNATE(5)); //MISO
    palSetPadMode(GPIOC,3,PAL_MODE_ALTERNATE(5) | PAL_STM32_OSPEED_HIGHEST); //MOSI
    palSetPad(GPIOB, 12);
    mmcObjectInit(&MMCD1);
    mmcStart(&MMCD1, &mmccfg);
    chThdSleepMilliseconds(50);
    Mmc_Mount();
}
