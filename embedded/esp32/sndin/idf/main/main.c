#include "blink.h"
#include "shell.h"
#include "i2smic.h"

void app_main(void){
    nvs_Init();
    led_Init();
    shell_Init();
    mic_Init();

    while (1) {
        int sh = shell_Loop();
        if(sh==1) break;
    }
}
