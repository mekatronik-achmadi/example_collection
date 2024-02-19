#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include "blink.h"
#include "shell.h"
#include "i2smic.h"

void app_main(){
    nvs_Init();
    blink_Init();
    shell_Init();

    mic_Init();
    vTaskDelay(100/portTICK_PERIOD_MS);
    mic_Get();

    while (1) {
        int shell = shell_Loop();
        if(shell==1) break;

        vTaskDelay(1/portTICK_PERIOD_MS);
    }
}
