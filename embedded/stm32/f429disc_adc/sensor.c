#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "ch.h"
#include "hal.h"

#include "sensor.h"

adcsample_t v1, v2, dV;

static adcsample_t samples[ADC_GRP_NUM_CHANNELS * ADC_GRP_BUF_DEPTH];

static void sensorADC(void){  
  int i;
  uint32_t sum_adc1 = 0;
  uint32_t sum_adc2 = 0;

  for(i=0;i<ADC_GRP_BUF_DEPTH;i++){
      sum_adc1 = sum_adc1 + samples[0+(i*ADC_GRP_NUM_CHANNELS)];
      sum_adc2 = sum_adc2 + samples[1+(i*ADC_GRP_NUM_CHANNELS)];
  }

  v1=(sum_adc1/ADC_GRP_BUF_DEPTH);
  v2=(sum_adc2/ADC_GRP_BUF_DEPTH);

  if(v1>=v2) dV = v1 - v2;
  else if(v1<v2)dV = v2 - v1;
 }

 static const ADCConversionGroup adcgrpcfg = {
  FALSE,
  ADC_GRP_NUM_CHANNELS,
  NULL,
  NULL,
  /* HW dependent part.*/
    0,
    ADC_CR2_SWSTART,
    0,
    ADC_SMPR2_SMP_AN1(ADC_SAMPLE_56) | ADC_SMPR2_SMP_AN2(ADC_SAMPLE_56),
    ADC_SQR1_NUM_CH(ADC_GRP_NUM_CHANNELS),
    0,
    ADC_SQR3_SQ1_N(ADC_CHANNEL_IN1) | ADC_SQR3_SQ2_N(ADC_CHANNEL_IN2)
 };

static THD_WORKING_AREA(waAdc, 250);
static THD_FUNCTION(thdAdc,arg) {
  (void)arg;
  chRegSetThreadName("adctrigger");

  while (true) {
    adcStartConversion(&ADCD1, &adcgrpcfg, samples, ADC_GRP_BUF_DEPTH);
    sensorADC();
    chThdSleepMicroseconds(1000);
  }
}

void sensorInit(void){
  adcStart(&ADCD1, NULL);
  palSetGroupMode(GPIOA, PAL_PORT_BIT(1) | PAL_PORT_BIT(2),  0, PAL_MODE_INPUT_ANALOG);
  chThdCreateStatic(waAdc, sizeof(waAdc), NORMALPRIO, thdAdc, NULL);
}
