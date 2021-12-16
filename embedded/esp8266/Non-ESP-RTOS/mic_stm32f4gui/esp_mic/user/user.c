/*
              UNKNOWN PUBLIC LICENSE

 Copyright (C) 2019 Wira S.T. M.T.

 Currently no license applied because author liv in
 Indonesia, a country which doesn't really concern
 about digital content copyright.

 */

/**
 * @file    user.c
 * @brief   Main code.
 *
 * @addtogroup Main
 * @{
 */

#include "ets_sys.h"
#include "osapi.h"
#include "gpio.h"
#include "os_type.h"

#include "mem.h"
#include "ip_addr.h"
#include "espconn.h"
#include "user_interface.h"

#include "driver/uart.h"
#include "driver/gpio16.h"
#include "i2s.h"
#include "user_config.h"


/**
 * @brief LED-16 blinky timer
 */
os_timer_t blinky_timer;

/**
 * @brief LED-16 blinky flag
 */
LOCAL uint8 blink_led = 0;

/**
 * @brief LED-16 blinky handler
 */
LOCAL void ICACHE_FLASH_ATTR blinky_timer_handler(void *prv){
    if (blink_led==1) { gpio_output_set(0, BIT2, BIT2, 0); blink_led=0; }
    else { gpio_output_set(BIT2, 0, BIT2, 0); blink_led=1; }
}

/**
 * @brief LED-16 blinky timer
 */
os_timer_t blinky_timer;

/**
 * @brief Print some OS information
 */
LOCAL void ICACHE_FLASH_ATTR print_os_info(){
    uint8 bootmode;

    os_printf("\r\n\r\n[INFO] -------------------------------------------\r\n");

    os_printf("[INFO] Compiled at %s %s\r\n", __DATE__,__TIME__);
    os_printf("[INFO] SDK: %s\r\n", system_get_sdk_version());
    os_printf("[INFO] Chip ID: %08X\r\n", system_get_chip_id());
    os_printf("[INFO] BOOT Version: %d\r\n",system_get_boot_version());
    os_printf("[INFO] BIN User addr: 0x%08X\r\n",system_get_userbin_addr());

    bootmode = system_get_boot_mode();
    if(bootmode == 0){ os_printf("[INFO] Boot using Enhance Mode\r\n"); }
    else{os_printf("[INFO] Boot using Normal Mode\r\n");}

    os_printf("[INFO] CPU Freq: %d MHz\r\n", system_get_cpu_freq());
    os_printf("[INFO] Memory Info:\r\n"); system_print_meminfo();

    os_printf("[INFO] -------------------------------------------\r\n");
    os_printf("\r\n\r\n");
}

/**
 * @brief Main Initialization
 */
void ICACHE_FLASH_ATTR user_init(){
    gpio_init();
    uart_init(SERIALBAUD,SERIALBAUD);
    uart_rx_intr_enable(UART0);
    print_os_info();

    PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO2_U, FUNC_GPIO2);
    PIN_PULLUP_DIS(PERIPHS_IO_MUX_GPIO2_U);

    mic_init();
    
    os_timer_setfn(&blinky_timer, (os_timer_func_t *)blinky_timer_handler, NULL);
    os_timer_arm(&blinky_timer, 1000, 1);
}
/** @} */
