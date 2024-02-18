#include <nvs_flash.h>
#include <esp_err.h>

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include <driver/gpio.h>

#include "blink.h"

static void led_Task(void *pvParameter){
    gpio_set_level(BLINK_GPIO,1);

    while (1) {
        gpio_set_level(BLINK_GPIO,0);
        vTaskDelay(100 / portTICK_PERIOD_MS);

        gpio_set_level(BLINK_GPIO,1);
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}

void nvs_Init(void){
    esp_err_t ret = nvs_flash_init();

    if((ret==ESP_ERR_NVS_NO_FREE_PAGES)||(ret==ESP_ERR_NVS_NEW_VERSION_FOUND)){
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }

    ESP_ERROR_CHECK(ret);
}

void led_Init(void){
    gpio_reset_pin(BLINK_GPIO);
    gpio_set_direction(BLINK_GPIO, GPIO_MODE_DEF_OUTPUT);

    xTaskCreate(&led_Task,
    "led task",
    256,
    NULL,
    tskIDLE_PRIORITY+1,
    NULL);
}
