#include <stdio.h>
#include <math.h>

#include <esp_err.h>

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include <driver/i2s.h>
#include <driver/gpio.h>

#include "i2smic.h"

static int16_t i2s_in_raw_buff[SAMPLES_NUM];

uint8_t mic_TaskRun = AUTOPRINT_TASK;

static void mic_Zero(void){
    for(uint16_t i=0;i<SAMPLES_NUM;i++)
        i2s_in_raw_buff[i] = 0;
}

static size_t mic_Raw(void){
    size_t bytesRead;

    esp_err_t err_Mic  = i2s_read(I2S_CH,
    (char*)i2s_in_raw_buff,
    sizeof(i2s_in_raw_buff),
    &bytesRead,
    portMAX_DELAY);

    if(err_Mic!=ESP_OK){
        printf("Mic read error\n");
        return -1;
    }

    return bytesRead;
}

void mic_Get(void){
    size_t readByte;

    mic_Zero();
    readByte = mic_Raw();

    printf("Bytes: %i\n",(uint16_t)readByte);
    if(readByte==-1) return;

    for(uint16_t i=0;i<SAMPLES_NUM;i++){
        printf("%i\n",(int16_t)i2s_in_raw_buff[i]);
        vTaskDelay(10/portTICK_PERIOD_MS);
    }

    return;
}

uint16_t mic_Max(void){
    size_t readByte;
    uint16_t valMax = 0;
    uint16_t valAbs = 0;

    mic_Zero();
    readByte = mic_Raw();

    if(readByte==-1) return -1;

    for(uint16_t i=0;i<SAMPLES_NUM;i++){
        valAbs = abs(i2s_in_raw_buff[i]);
        if(valAbs>=valMax) valMax=valAbs;
    }

    return valMax;
}

static void mic_Task(void *pvParameter){
    while (1) {
       if(mic_TaskRun)
#if AUTOPRINT_MAX
           printf("%i\n",mic_Max());
#else
           mic_Get();
#endif

       vTaskDelay(10/portTICK_PERIOD_MS);
    }
}

void  mic_Init(void){
    i2s_config_t micConf = {
        .mode = I2S_MODE_MASTER | I2S_MODE_RX,
        .sample_rate = AUDIO_SAMPLE_RATE,
        .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
        .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT, //LRC (WS) pin must to GND
        .communication_format = I2S_COMM_FORMAT_STAND_I2S,
        .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
        .dma_buf_count = 8,
        .dma_buf_len = 256,
    };

    i2s_pin_config_t micPin = {
        .bck_io_num = 14,
        .ws_io_num = 13,
        .data_out_num = I2S_PIN_NO_CHANGE,
        .data_in_num = 12,
    };

    if(i2s_driver_install(I2S_CH, &micConf, 0, NULL) != ESP_OK){
        printf("I2S driver install error\n");
    }

    if(i2s_set_pin(I2S_CH, &micPin) != ESP_OK){
        printf("I2S pin set error\n");
    }

    if(i2s_set_clk(I2S_CH, AUDIO_SAMPLE_RATE, I2S_BITS_PER_SAMPLE_16BIT, I2S_CHANNEL_MONO) != ESP_OK){
        printf("I2S clock set error\n");
    }

    xTaskCreate(&mic_Task,
            "mic_task",
            4096,
            NULL,
            tskIDLE_PRIORITY+2,
            NULL);
}

