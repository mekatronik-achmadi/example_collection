#include <stdint.h>
#include <stdio.h>

#include <esp_err.h>

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include <driver/i2s.h>
#include <driver/gpio.h>

#include "i2smic.h"

static int16_t mic_Raw_Buff[SAMPLES_NUM];

static void mic_Zero(void){
    for(uint16_t i=0;i<SAMPLES_NUM;i++)
        mic_Raw_Buff[i] = 0;
}

static size_t mic_Read(void){
    size_t byteRead;

    esp_err_t err_Mic = i2s_read(I2S_CH,
            (char*)mic_Raw_Buff,
            sizeof(mic_Raw_Buff),
            &byteRead,
            portMAX_DELAY);

    if(err_Mic!=ESP_OK){
        printf("Mic Read Error\n");
        return -1;
    }

    return byteRead;
}

void mic_Get(void){
    size_t readByte;

    mic_Zero();
    readByte = mic_Read();

    printf("Bytes: %lu\n",(uint16_t)readByte);
    if(readByte==-1) return;

    for(uint16_t i=0;i<SAMPLES_NUM;i++)
        printf("%i,",(int16_t)mic_Raw_Buff[i]);

    printf("\n");

    return;
}

void mic_Init(void){
    i2s_config_t mic_Conf = {
        .mode = I2S_MODE_MASTER | I2S_MODE_RX,
        .sample_rate = AUDIO_SAMPLE_RATE,
        .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
        .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
        .communication_format = I2S_COMM_FORMAT_I2S,
        .dma_buf_count = 8,
        .dma_buf_len = 256,
    };

    i2s_pin_config_t mic_Pin = {
        .bck_o_en = 1,
        .bck_i_en = 0,
        .ws_o_en = 1,
        .ws_i_en = 0,
        .data_in_en = 1
        .data_out_en = 0,
    };

    PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTDI_U, FUNC_I2SI_DATA);
    PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTCK_U, FUNC_I2SO_BCK);
    PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTMS_U, FUNC_I2SO_WS);

    if(i2s_driver_install(I2S_CH,&mic_Conf,0,NULL)!=ESP_OK)
        printf("I2S driver install error\n");

    if(i2s_set_pin(I2S_CH,&mic_Pin)!=ESP_OK)
        printf("I2S set pin error\n");

    if(i2s_set_clk(I2S_CH,AUDIO_SAMPLE_RATE,I2S_BITS_PER_SAMPLE_16BIT,I2S_CHANNEL_MONO)!=ESP_OK)
        printf("I2S set clock error\n");
}
