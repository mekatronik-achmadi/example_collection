#include <nvs_flash.h>
#include <esp_err.h>

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include <driver/gpio.h>

#include "blink.h"

#define GPIO_OUTPUT_LED     16
#define GPIO_OUTPUT_PINSEL  (1ULL << GPIO_OUTPUT_LED)
#define GPIO_BLINK_DELAY    100

void nvs_Init(void){
    esp_err_t ret = nvs_flash_init();

    if((ret==ESP_ERR_NVS_NO_FREE_PAGES)||(ret==ESP_ERR_NVS_NEW_VERSION_FOUND)){
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }

    ESP_ERROR_CHECK(ret);
}

static void ledTask(void *arg){
    gpio_set_level(GPIO_OUTPUT_LED,1);

    while (1) {
       gpio_set_level(GPIO_OUTPUT_LED,0);
       vTaskDelay(GPIO_BLINK_DELAY / portTICK_PERIOD_MS);

       gpio_set_level(GPIO_OUTPUT_LED,1);
       vTaskDelay(GPIO_BLINK_DELAY / portTICK_PERIOD_MS);
    }
}

void blink_Init(void){
    gpio_config_t gpio_Conf;

    gpio_Conf.intr_type = GPIO_INTR_DISABLE;
    gpio_Conf.mode = GPIO_MODE_OUTPUT;
    gpio_Conf.pin_bit_mask = GPIO_OUTPUT_PINSEL;
    gpio_Conf.pull_down_en = 0;
    gpio_Conf.pull_up_en = 0;
    gpio_config(&gpio_Conf);

    xTaskCreate(ledTask,
            "led task",
            256,
            NULL,
            tskIDLE_PRIORITY+1,
            NULL);
}
