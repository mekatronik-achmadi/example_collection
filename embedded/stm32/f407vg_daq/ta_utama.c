#include "ta_utama.h"

extern LcdStream myLCD;
extern adcsample_t adc0,adc1,adc2,adc3;
uint16_t adc_co,adc_so2,adc_co2,adc_nox;
float v_co,v_so2,v_co2,v_nox;

extern SerialUSBDriver SDU1;

extern FATFS MMC_FS;

static THD_WORKING_AREA(waBlink, 128);
static THD_FUNCTION(Blink, arg)  {

  (void)arg;
  chRegSetThreadName("Blinker");
  while (TRUE) {
    palSetPad(GPIOD, 13);       /* Orange.  */
    chThdSleepMilliseconds(500);
    palClearPad(GPIOD, 13);     /* Orange.  */
    chThdSleepMilliseconds(500);
  }
}

static THD_WORKING_AREA(waADCLCD, 128);
static THD_FUNCTION(ADCLCD, arg)  {

  (void)arg;
  chRegSetThreadName("ADC LCD");
  while (TRUE) {
    Hasil_Adc();
  }
}

void Run_Init(void){
    chThdCreateStatic(waADCLCD, sizeof(waADCLCD), NORMALPRIO, ADCLCD, NULL);

    palSetPadMode(GPIOD,13,PAL_MODE_OUTPUT_PUSHPULL);
    chThdCreateStatic(waBlink, sizeof(waBlink), NORMALPRIO, Blink, NULL);
}

void Hasil_Adc(void){
    adc_co=adc0;
    adc_so2=adc1;
    adc_co2=adc2;
    adc_nox=adc3;

    //v_co = (calib_co*adc_co)-offset_co;
    v_co = ((adc0* 490)/4095)*0.1;
    v_so2 = ((adc1* 199)/4095)*0.1;
    v_co2 = ((adc2* 9650)/4095)*0.1;
    v_nox = ((adc3* 9.9)/4095);

    Lcd_Cursor(0,0);
    chprintf((BaseSequentialStream *)&myLCD,"adc_co =%4i",adc_co);

    Lcd_Cursor(0,1);
    chprintf((BaseSequentialStream *)&myLCD,"adc_so2=%4i",adc_so2);

    Lcd_Cursor(0,2);
    chprintf((BaseSequentialStream *)&myLCD,"adc_co2=%4i",adc_co2);

    Lcd_Cursor(0,3);
    chprintf((BaseSequentialStream *)&myLCD,"adc_nox=%4i",adc_nox);

    chThdSleepMilliseconds(8000);

    Lcd_Cursor(0,0);
    chprintf((BaseSequentialStream *)&myLCD,"ppm_co =%3.1f",v_co);

    Lcd_Cursor(0,1);
    chprintf((BaseSequentialStream *)&myLCD,"ppm_so2=%3.1f ",v_so2);

    Lcd_Cursor(0,2);
    chprintf((BaseSequentialStream *)&myLCD,"ppm_co2=%3.1f ",v_co2);

    Lcd_Cursor(0,3);
    chprintf((BaseSequentialStream *)&myLCD,"ppm_nox=%3.1f ",v_nox);

    chThdSleepMilliseconds(8000);
    Lcd_Clear();

}

void Tulis_Adc(void){

    FIL FDLogFile;
    memset(&FDLogFile, 0, sizeof(FIL));
    FRESULT err_file;

    UINT bw;
    char buffer[buffer_size];

    err_file = f_open(&FDLogFile, "Test.csv", FA_WRITE | FA_OPEN_ALWAYS );
    if (err_file == FR_OK || err_file == FR_EXIST){
        err_file = f_lseek(&FDLogFile, f_size(&FDLogFile));
        if(err_file == FR_OK){

            chsnprintf(buffer,buffer_size,"%4i,%4i,%4i,%4i\n\r",adc_co,adc_so2,adc_co2,adc_nox);
            f_write(&FDLogFile, buffer, strlen(buffer), &bw);

            f_close(&FDLogFile);

            chprintf((BaseSequentialStream *)&SDU1, "Some text written\r\n");
            return;
        }else{
            chprintf((BaseSequentialStream *)&SDU1, "Failed to seek file\r\n");
            return;
        }
    }else{
        chprintf((BaseSequentialStream *)&SDU1, "Cannot Write file\r\n");
        return;
    }
}
