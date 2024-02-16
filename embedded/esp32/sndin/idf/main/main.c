#include "blink.h"
#include "shell.h"

void app_main(void){
    nvs_Init();
    led_Init();
    shell_Init();

    while (1) {
        int sh = shell_Loop();
        if(sh==1) break;
    }
}