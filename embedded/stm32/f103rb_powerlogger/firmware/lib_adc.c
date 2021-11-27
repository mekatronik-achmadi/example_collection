#include "lib_adc.h"

static adcsample_t samples[ADC_GRP1_NUM_CHANNELS * ADC_GRP1_BUF_DEPTH];

adcsample_t adc_v0,adc_i0,adc_v1,adc_i1;
uint32_t sum_adc_v0,sum_adc_i0,sum_adc_v1,sum_adc_i1;
float val_v0,val_i0,val_v1,val_i1;

/**
 * @brief buat Offset
 * @brief nilai disini adalah pengurang untuk nilai ADC berupa bilangan bulat antara 0 dan 4095
 */
adcsample_t offset_v0;
adcsample_t offset_i0;

adcsample_t offset_v1;
adcsample_t offset_i1;

/**
 * @brief buat Kalibrasi
 * @brief nilai disini adalah pengali untuk nilai ADC berupa bilangan pecahan antara 0 dan 1
 */

adcsample_t calib_nom_v0;
adcsample_t calib_nom_i0;
adcsample_t calib_nom_v1;
adcsample_t calib_nom_i1;

adcsample_t calib_denom=10000;

float calib_v0,calib_i0,calib_v1,calib_i1;

/**
 * ===================================================
 */

void adccb(ADCDriver *adcp, adcsample_t *buffer, size_t n){
  (void) buffer; (void) n;
  int i;
  if (adcp->state == ADC_COMPLETE) {

    sum_adc_v0=0;
    sum_adc_i0=0;
    sum_adc_v1=0;
    sum_adc_i1=0;

    for(i=0;i<ADC_GRP1_BUF_DEPTH;i++){
        sum_adc_v0=sum_adc_v0+samples[0+(i*ADC_GRP1_NUM_CHANNELS)];
        sum_adc_i0=sum_adc_i0+samples[1+(i*ADC_GRP1_NUM_CHANNELS)];
        sum_adc_v1=sum_adc_v1+samples[2+(i*ADC_GRP1_NUM_CHANNELS)];
        sum_adc_i1=sum_adc_i1+samples[3+(i*ADC_GRP1_NUM_CHANNELS)];
    }

    adc_v0=sum_adc_v0/ADC_GRP1_BUF_DEPTH;
    adc_i0=sum_adc_i0/ADC_GRP1_BUF_DEPTH;
    adc_v1=sum_adc_v1/ADC_GRP1_BUF_DEPTH;
    adc_i1=sum_adc_i1/ADC_GRP1_BUF_DEPTH;
   }
 }

static const ADCConversionGroup adcgrpcfg = {
    FALSE,
    ADC_GRP1_NUM_CHANNELS,
    adccb,
    NULL,
    /* HW dependent part.*/
    0,
    0,
    ADC_SMPR2_SMP_AN0(ADC_SAMPLE_239P5) | ADC_SMPR2_SMP_AN1(ADC_SAMPLE_239P5) | ADC_SMPR2_SMP_AN2(ADC_SAMPLE_239P5) | ADC_SMPR2_SMP_AN3(ADC_SAMPLE_239P5),
    0,
    ADC_SQR1_NUM_CH(ADC_GRP1_NUM_CHANNELS),
    0,
    ADC_SQR3_SQ1_N(ADC_CHANNEL_IN0) | ADC_SQR3_SQ2_N(ADC_CHANNEL_IN1) | ADC_SQR3_SQ3_N(ADC_CHANNEL_IN2) | ADC_SQR3_SQ4_N(ADC_CHANNEL_IN3)
};

static WORKING_AREA(wa_adcThread, 128);
static msg_t adcThread(void *arg) {
  (void)arg;
  while (TRUE) {
    chThdSleepMilliseconds(100);
    adcStartConversion(&ADCD1, &adcgrpcfg, samples, ADC_GRP1_BUF_DEPTH);
  }
  return 0;
}

void Adc_Init(){
    palSetPadMode(GPIOA,0,PAL_MODE_INPUT_ANALOG);
    palSetPadMode(GPIOA,1,PAL_MODE_INPUT_ANALOG);
    palSetPadMode(GPIOA,2,PAL_MODE_INPUT_ANALOG);
    palSetPadMode(GPIOA,3,PAL_MODE_INPUT_ANALOG);
    adcStart(&ADCD1, NULL);
    chThdCreateStatic(wa_adcThread, sizeof(wa_adcThread), NORMALPRIO, adcThread, NULL);
}

void Adc_Calc(){

    calib_v0=(float) calib_nom_v0/calib_denom;
    calib_i0=(float) calib_nom_i0/calib_denom;
    calib_v1=(float) calib_nom_v1/calib_denom;
    calib_i1=(float) calib_nom_i1/calib_denom;

//=========================================

    if(adc_v0>=offset_v0){
        val_v0=(float) ((adc_v0-offset_v0)*calib_v0);
    }else{
        val_v0=0;
    }

/*
 * Pembacaan arus dibalik
 */

//    if(adc_i0>=offset_i0){
//        val_i0=(float) ((adc_i0-offset_i0)*calib_i0);
//    }else{
//        val_i0=0;
//    }

    if(adc_i0<=offset_i0){
        val_i0=(float) ((offset_i0-adc_i0)*calib_i0);
    }else{
        val_i0=0;
    }

//=========================================

    if(adc_v1>=offset_v1){
        val_v1=(float) ((adc_v1-offset_v1)*calib_v1);
    }else{
        val_v1=0;
    }

/*
 * Pembacaan arus dibalik
 */

//    if(adc_i1>=offset_i1){
//        val_i1=(float) ((adc_i1-offset_i1)*calib_i1);
//    }else{
//        val_i1=0;
//    }

    if(adc_i1<=offset_i1){
        val_i1=(float) ((offset_i1-adc_i1)*calib_i1);
    }else{
        val_i1=0;
    }

}
