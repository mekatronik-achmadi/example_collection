#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_system.h"

#include "my_led.h"

#define GPIO_OUTPUT_LED    16
#define GPIO_OUTPUT_PIN_SEL  (1ULL << GPIO_OUTPUT_LED)

static void gpio_task_blink(void *arg){
    while(1){
        gpio_set_level(GPIO_OUTPUT_LED, 0);
        vTaskDelay(100 / portTICK_RATE_MS);
        gpio_set_level(GPIO_OUTPUT_LED, 1);
        vTaskDelay(100 / portTICK_RATE_MS);
    }
}

void start_blink(void){
    gpio_config_t io_conf;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = GPIO_OUTPUT_PIN_SEL;
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 0;
    gpio_config(&io_conf);

    xTaskCreate(gpio_task_blink, "gpio blink", 2048, NULL, 10, NULL);
}