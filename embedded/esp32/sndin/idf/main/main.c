#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include "blink.h"

void app_main(void){
    nvs_Init();
    led_Init();

    while (1) {
        vTaskDelay(BLINK_DELAY / portTICK_PERIOD_MS);
    }
}