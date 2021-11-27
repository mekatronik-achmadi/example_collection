#include "lib_mmc_spi.h"
#include "lib_lcd.h"
#include "lib_adc.h"
#include "lib_serial.h"

extern LcdStream myLCD;

extern adcsample_t offset_v0,offset_i0,offset_v1,offset_i1;
extern adcsample_t calib_nom_v0,calib_nom_i0,calib_nom_v1,calib_nom_i1,calib_denom;

extern uint8_t setting_session;

bool_t saving_flag=FALSE;
bool_t hasHeader=FALSE;

bool_t filesystem_ready=TRUE;
uint8_t mmc_spi_status_flag=MMC_SPI_OK;

FATFS MMC_FS;

MMCDriver MMCD1;

FRESULT err;
uint32_t clusters;
FATFS *fsp;

static SPIConfig hs_spicfg = {NULL, GPIOB, 12, 0};

static SPIConfig ls_spicfg = {NULL, GPIOB, 12, SPI_CR1_BR_2 | SPI_CR1_BR_1};

static MMCConfig mmccfg = {&SPID2, &ls_spicfg, &hs_spicfg};

void Mmc_Check(){

    mmc_spi_status_flag=MMC_SPI_OK;

    filesystem_ready=FALSE;

    if (mmcConnect(&MMCD1)) {
        filesystem_ready = TRUE;
    }
    else{
        err = f_mount(0, &MMC_FS);
        if (err == FR_OK){
            filesystem_ready = TRUE;
        }
        else{
        }
    }

    if (!filesystem_ready) {
        mmc_spi_status_flag=MMC_SPI_FAIL;
        return;
    }

    err = f_getfree("/", &clusters, &fsp);
    if (err != FR_OK) {
        mmc_spi_status_flag=MMC_SPI_ERROR;
        return;
    }

    chThdSleepMilliseconds(10);
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
    palSetPadMode(GPIOB, 15, PAL_MODE_STM32_ALTERNATE_PUSHPULL);
    palSetPadMode(GPIOB, 14, PAL_MODE_INPUT);
    palSetPadMode(GPIOB, 13, PAL_MODE_STM32_ALTERNATE_PUSHPULL);
    palSetPadMode(GPIOB, 12, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPad(GPIOB, 12);
    mmcObjectInit(&MMCD1);
    mmcStart(&MMCD1, &mmccfg);
    chThdSleepMilliseconds(50);
}

void Mmc_Example(){
    Mmc_Check();

#if _USE_STRFUNC
    FATFS FatFs;
    fil fil;
    if((filesystem_ready==TRUE)&&(mmc_spi_status_flag==MMC_SPI_OK)){
        f_mount(0,&FatFs);
        f_append(&fil, "/text.txt");
        f_printf(&fil, "%5d", 1234);
        f_printf(&fil,"String\n");
        f_close(&fil);
        f_mount(0,NULL);
    }
#else
    char buffer[36];
    FATFS FatFs;
    UINT bw;
    FIL *fil;
    fil =(FIL *)malloc(sizeof (FIL));
    if((filesystem_ready==TRUE)&&(mmc_spi_status_flag==MMC_SPI_OK)){
        chsnprintf(buffer,36,"String\n\r");
        f_mount(0,&FatFs);
        f_open(fil, "/text.txt" , FA_WRITE | FA_OPEN_ALWAYS);
        f_lseek(fil, f_size(fil));
        f_write(fil, buffer, strlen(buffer), &bw);
        f_close(fil);
        f_mount(0,NULL);
    }
    free(fil);
#endif
}

void Mmc_Reload(){
    Mmc_Check();

    adcsample_t value_zero=0;
    char data_in[buffer_size];
    FATFS FatFs;
    UINT bw;
    FIL *fil;
    fil =(FIL *)malloc(sizeof (FIL));

    if((filesystem_ready==TRUE)&&(mmc_spi_status_flag==MMC_SPI_OK)){

        f_mount(0,&FatFs);
        f_open(fil, "/offset_v0", FA_READ);
        f_read(fil,data_in,strlen(data_in),&bw);
        offset_v0=atoi(data_in);
        f_close(fil);
        f_mount(0,NULL);
        chsnprintf(data_in,buffer_size,"%4d",value_zero);
        chThdSleepMicroseconds(100);

        f_mount(0,&FatFs);
        f_open(fil, "/offset_i0", FA_READ);
        f_read(fil,data_in,strlen(data_in),&bw);
        offset_i0=atoi(data_in);
        f_close(fil);
        f_mount(0,NULL);
        chsnprintf(data_in,buffer_size,"%4d",value_zero);
        chThdSleepMicroseconds(100);

        f_mount(0,&FatFs);
        f_open(fil, "/offset_v1", FA_READ);
        f_read(fil,data_in,strlen(data_in),&bw);
        offset_v1=atoi(data_in);
        f_close(fil);
        f_mount(0,NULL);
        chsnprintf(data_in,buffer_size,"%4d",value_zero);
        chThdSleepMicroseconds(100);

        f_mount(0,&FatFs);
        f_open(fil, "/offset_i1", FA_READ);
        f_read(fil,data_in,strlen(data_in),&bw);
        offset_i1=atoi(data_in);
        f_close(fil);
        f_mount(0,NULL);
        chsnprintf(data_in,buffer_size,"%4d",value_zero);
        chThdSleepMicroseconds(100);

        f_mount(0,&FatFs);
        f_open(fil, "/calib_nom_v0", FA_READ);
        f_read(fil,data_in,strlen(data_in),&bw);
        calib_nom_v0=atoi(data_in);
        f_close(fil);
        f_mount(0,NULL);
        chsnprintf(data_in,buffer_size,"%4d",value_zero);
        chThdSleepMicroseconds(100);

        f_mount(0,&FatFs);
        f_open(fil, "/calib_nom_i0", FA_READ);
        f_read(fil,data_in,strlen(data_in),&bw);
        calib_nom_i0=atoi(data_in);
        f_close(fil);
        f_mount(0,NULL);
        chsnprintf(data_in,buffer_size,"%4d",value_zero);
        chThdSleepMicroseconds(100);

        f_mount(0,&FatFs);
        f_open(fil, "/calib_nom_v1", FA_READ);
        f_read(fil,data_in,strlen(data_in),&bw);
        calib_nom_v1=atoi(data_in);
        f_close(fil);
        f_mount(0,NULL);
        chsnprintf(data_in,buffer_size,"%4d",value_zero);
        chThdSleepMicroseconds(100);

        f_mount(0,&FatFs);
        f_open(fil, "/calib_nom_i1", FA_READ);
        f_read(fil,data_in,strlen(data_in),&bw);
        calib_nom_i1=atoi(data_in);
        f_close(fil);
        f_mount(0,NULL);
        chsnprintf(data_in,buffer_size,"%4d",value_zero);
        chThdSleepMicroseconds(100);
    }

    free(fil);

    //Load default value if memory load if fail
    if(offset_v0==0){offset_v0=20;}
    if(offset_i0==0){offset_i0=3290;}
    if(offset_v1==0){offset_v1=20;}
    if(offset_i1==0){offset_i1=3280;}

    if(calib_nom_v0==0){calib_nom_v0=76;}
    if(calib_nom_i0==0){calib_nom_i0=180;}
    if(calib_nom_v1==0){calib_nom_v1=76;}
    if(calib_nom_i1==0){calib_nom_i1=180;}
}
