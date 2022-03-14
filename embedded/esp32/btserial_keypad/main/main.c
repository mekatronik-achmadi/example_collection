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
#include "ssd1306i2c.h"
#include "myconfig.h"

/**
 * @brief Main entry function
 * @details First main function app
 */
void app_main(void){
    nvsInit();
    btsppInit();
    start_ssd1306();
    shellInit();
    ledInit();

    while(1){
        int loop = shellLoop();
        if(loop==1)printf("Empty Command\r\n");
    }
}

/** @} */