#ifndef I2SMIC_H
#define I2SMIC_H

#include <esp_err.h>

#define MIC_SAMPLE_RATE (16000)
#define I2S_CH          I2S_NUM_0
#define SAMPLE_SIZE     (1024)

void mic_Init(void);
esp_err_t mic_Get(void);

#endif
