#include "ta_dac.h"

dacsample_t dacbuffer[DAC_BUFFER_SIZE] = {0,0};

static const DACConfig daccfg = {
  2047U,
  DAC_DHRM_12BIT_RIGHT_DUAL,
};

static const DACConversionGroup dacgrpcfg = {
  1U,
  NULL,
  NULL,
  DAC_TRG(0)
};

static const GPTConfig gpt6cfg = {
  1000000U,
  NULL,
  TIM_CR2_MMS_1,  /* MMS = 010 = TRGO on Update Event.        */
  0U
};

void Dac_Init(void){
    palSetPadMode(GPIOA, 4, PAL_MODE_INPUT_ANALOG);
    palSetPadMode(GPIOA, 5, PAL_MODE_INPUT_ANALOG);

    dacStart(&DACD1, &daccfg);
    gptStart(&GPTD6, &gpt6cfg);

    dacStartConversion(&DACD1, &dacgrpcfg, dacbuffer, DAC_BUFFER_SIZE);
    gptStartContinuous(&GPTD6, 2U);
}
