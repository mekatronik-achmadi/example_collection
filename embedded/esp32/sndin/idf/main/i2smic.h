#ifndef I2SMIC_H
#define I2SMIC_H

#include <stdint.h>

#define AUDIO_SAMPLE_RATE   (44100)
#define I2S_CH              I2S_NUM_0
#define SAMPLES_NUM         (1024)

void mic_Init(void);
void mic_Get(void);
uint16_t mic_Max(void);

#endif
