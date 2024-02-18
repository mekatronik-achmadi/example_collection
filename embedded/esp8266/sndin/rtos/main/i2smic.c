#include <stdint.h>
#include <stdio.h>

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include <driver/i2s.h>
#include <driver/gpio.h>

#include "i2smic.h"

uint8_t mic_TaskFlag = 1;

static int16_t i2s_in_raw_buff[SAMPLE_SIZE];

static void mic_Zero(void){
    for (uint16_t i=0;i<SAMPLE_SIZE;i++) {
        i2s_in_raw_buff[i] = 0;
    }
}

static esp_err_t mic_Raw(void) {
    size_t bytesRead;

    esp_err_t err_Mic = i2s_read(I2S_CH,
            (char*)i2s_in_raw_buff,
            sizeof(i2s_in_raw_buff),
            &bytesRead,
            100/portTICK_PERIOD_MS);

    return err_Mic;
}

esp_err_t mic_Get(void){
    mic_Zero();

    esp_err_t err_Raw = mic_Raw();
    if(err_Raw!=ESP_OK){
        printf("I2S Read Error\n");
        return err_Raw;
    }

    for(uint16_t i=0;i<SAMPLE_SIZE;i++)
        printf("%i",i2s_in_raw_buff[i]);

    printf("\n");

    return err_Raw;
}

static void mic_Task(void *arg){
    while (1) {
       if(mic_TaskFlag) mic_Get();
       vTaskDelay(100/portTICK_PERIOD_MS);
    }
}

void mic_Init(void){
    i2s_config_t mic_Conf = {
        .mode = I2S_MODE_MASTER | I2S_MODE_RX,
        .sample_rate = MIC_SAMPLE_RATE,
        .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
        .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
        .communication_format = I2S_COMM_FORMAT_I2S,
        .dma_buf_count = 8,
        .dma_buf_len = 256,
    };

    i2s_pin_config_t mic_Pin = {
        .bck_o_en = 14,
        .ws_o_en = 15,
        .data_in_en = 12,
    };

    if(i2s_driver_install(I2S_CH,&mic_Conf,0,NULL) != ESP_OK)
        printf("I2S Install Driver Error\n");

    if(i2s_set_pin(I2S_CH,&mic_Pin) != ESP_OK)
        printf("I2S Pin Set Error\n");

    if(i2s_set_clk(I2S_CH,MIC_SAMPLE_RATE,I2S_BITS_PER_SAMPLE_16BIT,I2S_CHANNEL_MONO) != ESP_OK)
        printf("I2S Clock Set Error");

    xTaskCreate(&mic_Task,
            "mic Task",
            4096,
            NULL,
            tskIDLE_PRIORITY+3,
            NULL);
}
