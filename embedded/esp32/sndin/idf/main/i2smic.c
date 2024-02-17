#include <stdint.h>
#include <stdio.h>
#include <esp_err.h>

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include <driver/i2s.h>
#include <driver/gpio.h>

#include "i2smic.h"

/**
 * @brief Raw Input Buffer Array
 *
 */
static int16_t i2s_in_raw_buff[SAMPLES_NUM];

/**
 * @brief FFT Complex Vector Array
 *
 */
float y_fft[SAMPLES_NUM*2];

/**
 * @brief Zero-ing a Int16 Array
 *
 */
static void mic_Zero(void){
    for(uint16_t i=0;i<SAMPLES_NUM;i++)
        i2s_in_raw_buff[i] = 0;
}

/**
 * @brief Get raw read of I2S
 *
 * @return int Exit Code
 */
static int mic_Raw(void){
    size_t bytesRead;

    esp_err_t err_Mic  = i2s_read(I2S_CH,
    (char*)i2s_in_raw_buff,
    sizeof(i2s_in_raw_buff),
    &bytesRead,
    (100/portTICK_RATE_MS));

    return err_Mic;
}

/**
 * @brief Get I2S Read and print to console
 *
 * @return int Exit Code
 */
int mic_Get(void){
    mic_Zero();

    esp_err_t err_Get = mic_Raw();
    if(err_Get!=ESP_OK) {
        printf("I2S Read Error\n");
        return err_Get;
    }

    for(uint16_t i=0;i<SAMPLES_NUM;i++)
        printf("%i,",i2s_in_raw_buff[i]);

    return err_Get;
}

/**
 * @brief Mic I2S Initialize
 *
 */
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
        .ws_io_num = 15,
        .data_out_num = I2S_PIN_NO_CHANGE,
        .data_in_num = 23,
    };

    if(i2s_driver_install(I2S_CH, &micConf, 0, NULL) != ESP_OK){
        printf("I2S driver install error\r\n");
    }

    if(i2s_set_pin(I2S_CH, &micPin) != ESP_OK){
        printf("I2S pin set error\r\n");
    }

    if(i2s_set_clk(I2S_CH, AUDIO_SAMPLE_RATE, I2S_BITS_PER_SAMPLE_16BIT, I2S_CHANNEL_MONO) != ESP_OK){
        printf("I2S clock set error\r\n");
    }
}
