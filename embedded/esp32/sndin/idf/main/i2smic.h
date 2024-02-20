#ifndef I2SMIC_H
#define I2SMIC_H

#include <esp_err.h>

#define AUDIO_SAMPLE_RATE   (16000)
#define I2S_CH              I2S_NUM_0
#define SAMPLES_NUM         (1024)

void mic_Init(void);
void mic_Get(void);

#endif
