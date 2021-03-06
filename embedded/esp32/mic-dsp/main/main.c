/**
 * @file    main.c
 * @brief   Main entry program code.
 *
 * @addtogroup Main
 * @{
 */

#include "my_nvs.h"
#include "my_led.h"
#include "my_cmd.h"
#include "my_shell.h"
#include "my_i2smic.h"
#include "myconfig.h"

/**
 * @brief Main entry function
 * @details First main function app
 */
void app_main(void){
    nvsInit();
    i2smicInit();
    ledInit();
    shellInit();

    while(1){
        int loop = shellLoop();
        if(loop==1)break;
    }
}

/** @} */
