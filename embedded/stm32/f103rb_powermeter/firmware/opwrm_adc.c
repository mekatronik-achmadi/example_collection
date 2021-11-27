#include "srcconf.h" 

static adcsample_t samples[ADC_GRP1_NUM_CHANNELS * ADC_GRP1_BUF_DEPTH];

adcsample_t adc_volt1,adc_amp1,adc_amp2,adc_amp3;
uint32_t sum_adc_volt1,sum_adc_amp1,sum_adc_amp2,sum_adc_amp3;

void adccb(ADCDriver *adcp, adcsample_t *buffer, size_t n){
  (void) buffer; (void) n;
  int i;
  if (adcp->state == ADC_COMPLETE) {
    sum_adc_volt1=sum_adc_amp1=sum_adc_amp2=sum_adc_amp3=0;
    for(i=0;i<ADC_GRP1_BUF_DEPTH;i++){
	sum_adc_volt1=sum_adc_volt1+samples[0+(i*ADC_GRP1_NUM_CHANNELS)];
	sum_adc_amp1=sum_adc_amp1+samples[1+(i*ADC_GRP1_NUM_CHANNELS)];
	sum_adc_amp2=sum_adc_amp2+samples[2+(i*ADC_GRP1_NUM_CHANNELS)];
	sum_adc_amp3=sum_adc_amp3+samples[3+(i*ADC_GRP1_NUM_CHANNELS)];
    }
    adc_volt1=sum_adc_volt1/10;
    adc_amp1=sum_adc_amp1/10;
    adc_amp2=sum_adc_amp2/10;
    adc_amp3=sum_adc_amp3/10;
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

void Adc_Setup(void){
  palSetPadMode(GPIOA,0,PAL_MODE_INPUT_ANALOG);
  palSetPadMode(GPIOA,1,PAL_MODE_INPUT_ANALOG);
  palSetPadMode(GPIOA,2,PAL_MODE_INPUT_ANALOG);
  palSetPadMode(GPIOA,3,PAL_MODE_INPUT_ANALOG);
  adcStart(&ADCD1, NULL);
  chThdCreateStatic(wa_adcThread, sizeof(wa_adcThread), NORMALPRIO, adcThread, NULL);
}