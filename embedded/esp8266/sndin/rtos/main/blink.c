#include <nvs_flash.h>
#include <esp_err.h>

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include <driver/gpio.h>

#include "blink.h"

void nvs_Init(void){
    esp_err_t err = nvs_flash_init();

    if((err==ESP_ERR_NVS_NO_FREE_PAGES)||(err==ESP_ERR_NVS_NEW_VERSION_FOUND)){
        ESP_ERROR_CHECK(nvs_flash_erase());
        err = nvs_flash_init();
    }

    ESP_ERROR_CHECK(err);
}

static void led_Task(void *arg){
    while (1) {
        gpio_set_level(BLINK_LED, 0);
        vTaskDelay(BLINK_DELAY / portTICK_PERIOD_MS);
        gpio_set_level(BLINK_LED, 1);
        vTaskDelay(BLINK_DELAY / portTICK_PERIOD_MS);
    }
}

void led_Init(void){
    gpio_config_t io_Conf;

    io_Conf.intr_type = GPIO_INTR_DISABLE;
    io_Conf.mode = GPIO_MODE_OUTPUT;
    io_Conf.pin_bit_mask = BLINK_GPIO;
    io_Conf.pull_down_en = 0;
    io_Conf.pull_up_en = 0;
    gpio_config(&io_Conf);

    xTaskCreate(led_Task,
            "blink task",
            256,
            NULL,
            tskIDLE_PRIORITY+1,
            NULL);
}
