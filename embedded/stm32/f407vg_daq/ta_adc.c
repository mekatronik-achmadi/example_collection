#include "ta_adc.h"

static adcsample_t samples[ADC_GRP1_NUM_CHANNELS * ADC_GRP1_BUF_DEPTH];

adcsample_t adc0,adc1,adc2,adc3;
uint32_t sum_adc0,sum_adc1,sum_adc2,sum_adc3;

void adccb(ADCDriver *adcp, adcsample_t *buffer, size_t n){
  (void) buffer; (void) n;
  int i;
  if (adcp->state == ADC_COMPLETE) {

    sum_adc0=0;
    sum_adc1=0;
    sum_adc2=0;
    sum_adc3=0;

    for(i=0;i<ADC_GRP1_BUF_DEPTH;i++){
        sum_adc0=sum_adc0+samples[0+(i*ADC_GRP1_NUM_CHANNELS)];
        sum_adc1=sum_adc1+samples[1+(i*ADC_GRP1_NUM_CHANNELS)];
        sum_adc2=sum_adc2+samples[2+(i*ADC_GRP1_NUM_CHANNELS)];
        sum_adc3=sum_adc3+samples[3+(i*ADC_GRP1_NUM_CHANNELS)];
    }

    adc0=sum_adc0/ADC_GRP1_BUF_DEPTH;
    adc1=sum_adc1/ADC_GRP1_BUF_DEPTH;
    adc2=sum_adc2/ADC_GRP1_BUF_DEPTH;
    adc3=sum_adc3/ADC_GRP1_BUF_DEPTH;
   }
 }

static const ADCConversionGroup adcgrpcfg = {
  FALSE,
  ADC_GRP1_NUM_CHANNELS,
  adccb,
  NULL,
  /* HW dependent part.*/
  0,
  ADC_CR2_SWSTART,
  0,
  ADC_SMPR2_SMP_AN0(ADC_SAMPLE_112) | ADC_SMPR2_SMP_AN1(ADC_SAMPLE_112) | ADC_SMPR2_SMP_AN2(ADC_SAMPLE_112) | ADC_SMPR2_SMP_AN3(ADC_SAMPLE_112),
  ADC_SQR1_NUM_CH(ADC_GRP1_NUM_CHANNELS),
  0,
  ADC_SQR3_SQ1_N(ADC_CHANNEL_IN0) | ADC_SQR3_SQ2_N(ADC_CHANNEL_IN1) | ADC_SQR3_SQ3_N(ADC_CHANNEL_IN2) | ADC_SQR3_SQ4_N(ADC_CHANNEL_IN3)
};


static THD_WORKING_AREA(wa_adcThread, 128);
static THD_FUNCTION(adcThread, arg) {
  (void)arg;
  chRegSetThreadName("ADC Run");
  while (TRUE) {
    chThdSleepMilliseconds(100);
    palSetPad(GPIOD, 12); /* Yellow.  */
    adcStartConversion(&ADCD1, &adcgrpcfg, samples, ADC_GRP1_BUF_DEPTH);
    chThdSleepMilliseconds(100);
    palClearPad(GPIOD, 12); /* Yellow.  */
  }
}

void Adc_Init(){
    palSetPadMode(GPIOA,0,PAL_MODE_INPUT_ANALOG);
    palSetPadMode(GPIOA,1,PAL_MODE_INPUT_ANALOG);
    palSetPadMode(GPIOA,2,PAL_MODE_INPUT_ANALOG);
    palSetPadMode(GPIOA,3,PAL_MODE_INPUT_ANALOG);
    adcStart(&ADCD1, NULL);

    palSetPadMode(GPIOD,12,PAL_MODE_OUTPUT_PUSHPULL);
    chThdCreateStatic(wa_adcThread, sizeof(wa_adcThread), NORMALPRIO, adcThread, NULL);
}

