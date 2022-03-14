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
#include "my_btspp.h"
#include "myconfig.h"

/**
 * @brief Main entry function
 * @details First main function app
 */
void app_main(void){
    nvsInit();
    ledInit();
    btsppInit();
    shellInit();

    while(1){
        int loop = shellLoop();
        if(loop==1)break;
    }
}

/** @} */