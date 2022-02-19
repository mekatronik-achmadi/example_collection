/**
 * @file my_i2smic.c
 * @brief I2S Mic driver
 * 
 * @addtogroup I2S_FFT
 * @{
 */


/**
 * example in use: https://github.com/pedrominatel/esp32-projects/blob/master/demo/sound_spectrum/main/i2s_spectrum_example_main.c
 */

#include <stdio.h>
#include <math.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "driver/i2s.h"
#include "driver/gpio.h"

#include "esp_system.h"
#include "esp_console.h"
#include "esp_log.h"
#include "esp_dsp.h"
#include "esp_err.h"

#include "my_i2smic.h"

/**
 * @brief Audio Sample rate
 * 
 */
#define AUDIO_SAMPLE_RATE       (16000)

/**
 * @brief I2S Channel Port 
 * 
 */
#define I2S_CH                  I2S_NUM_0

/**
 * @brief Sample Number
 * 
 */
#define SAMPLES_NUM             (1024)

/**
 * @brief Tag Mic FFT
 * 
 */
static const char *TAG = "MIC_FFT";

/**
 * @brief I2S read buffer array
 * 
 */
static int16_t i2s_readraw_buff[SAMPLES_NUM];

/**
 * @brief Complex vector for FFT
 * 
 */
float y_cf[SAMPLES_NUM*2];

/**
 * @brief Zero-ing the array buffer
 * 
 */
static void micZero(void){
    for(int i=0 ; i< SAMPLES_NUM ; i++){
            i2s_readraw_buff[i] = 0;
    }
}

/**
 * @brief Get raw data and saved to array buffer
 * 
 * @return int Non-zero if error happen
 */
static int micRaw(void){
    esp_err_t errMic;
    size_t bytesread;

    errMic= i2s_read(I2S_CH, (char *)i2s_readraw_buff, sizeof(i2s_readraw_buff), &bytesread, (100 / portTICK_RATE_MS));

    if(errMic != ESP_OK) printf("I2S read error\r\n");

    return errMic;
}

/**
 * @brief Print read buffer array
 * 
 */
static void micGet(void){
    micZero();
    micRaw();

    for(int i=0 ; i< SAMPLES_NUM ; i++){
        printf("%i,",i2s_readraw_buff[i]);
    }
}

/**
 * @brief Get Max dB
 * 
 * @return uint16_t 
 */
static uint16_t micMax(void){
    uint16_t valMax = 0;
    uint16_t valAbs = 0;

    micZero();
    micRaw();

    for(int i=0 ; i< SAMPLES_NUM ; i++){
            valAbs = abs(i2s_readraw_buff[i]);
            if(valAbs >= valMax) valMax = valAbs;
    }

    return valMax;
}

/**
 * @brief Print read buffer array command
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
static int micGetFunc(int argc, char **argv){
    micGet();
    printf("0\r\n");

    return 0;
}

/**
 * @brief Get Max dB buffer array command
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
static int micMaxFunc(int argc, char **argv){
    uint16_t maxVal = 0;

    maxVal = micMax();
    printf("micMax =  %i\r\n", maxVal);

    return 0;
}

/**
 * @brief Register Mic commands
 * 
 */
static void micRegister(void){
    const esp_console_cmd_t get = {
        .command = "get",
        .help = "Test data Mic",
        .hint = NULL,
        .func = &micGetFunc,
    };

    const esp_console_cmd_t max = {
        .command = "max",
        .help = "Test Max Mic",
        .hint = NULL,
        .func = &micMaxFunc,
    };

    esp_console_cmd_register(&get);
    esp_console_cmd_register(&max);
}

/**
 * @brief FFT Initialization
 * 
 */
static void fftInit(void){
    esp_err_t errfft;

    ESP_LOGI(TAG, "FFT Initialization");
    errfft = dsps_fft2r_init_fc32(NULL, CONFIG_DSP_MAX_FFT_SIZE);
    if(errfft != ESP_OK){
        ESP_LOGE(TAG, "FFT Init Error: %i",errfft);
    }

    return;
}

/**
 * @brief FFT Process dan Show in Console
 * 
 * @param data 
 * @param length 
 */
static void fftProcess(float * data, int length){
    dsps_fft2r_fc32_ansi(data, length);
    dsps_bit_rev_fc32(data,length);
    dsps_cplx2reC_fc32_ansi(data, length);
    dsps_view_spectrum(data, length/2,30,100);
}

/**
 * @brief FFT test command
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
static int micFftFunc(int argc, char **argv){
    esp_err_t errMic;

    micZero();
    errMic = micRaw();

    if(errMic == ESP_OK){
        for(int i=0; i<SAMPLES_NUM; i++){
            y_cf[i*2 + 0] = i2s_readraw_buff[i];
            y_cf[i*2 + 1] = 0;
        }

        fftProcess(y_cf, SAMPLES_NUM);
    }

    return 0;
}

/**
 * @brief Register FFT test command
 * 
 */
static void fftRegister(void){
    const esp_console_cmd_t fft = {
        .command = "fft",
        .help = "Test FFT Mic",
        .hint = NULL,
        .func = &micFftFunc,
    };

    esp_console_cmd_register(&fft);
}

/**
 * @brief I2S driver and Mic/FFT initialization
 * 
 */
void i2smicInit(void){

    i2s_config_t micConf = {
        .mode = I2S_MODE_MASTER | I2S_MODE_RX,
        .sample_rate = AUDIO_SAMPLE_RATE,
        .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
        .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT, //LRC pin must to GND
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

    fftInit();
    fftRegister();
    micRegister();
}

/** @} */