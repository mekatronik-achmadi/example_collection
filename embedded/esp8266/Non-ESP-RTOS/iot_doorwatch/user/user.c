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

#include "blinky.h"
#include "httpd.h"
#include "wifi_sap.h"
#include "wifi_sta.h"
#include "interrupt.h"
#include "client.h"

/**
 * @brief Default UART BaudRate
 */
#define SERIALBAUD 9600

/**
 * @brief Initialize Wifi
 * @details Wifi Mode based on last saved config
 */
LOCAL void ICACHE_FLASH_ATTR run_wifi_mode(void){
    uint8 last_wifi_mode;

    last_wifi_mode = wifi_get_opmode_default();

#if USE_DEFAULT_SSID_PASS
    #if USE_DEFAULT_STATION
    last_wifi_mode = STATION_MODE;
    #endif
#endif

    if(last_wifi_mode == SOFTAP_MODE){
        user_wifi_softap_init();
    }
    else if (last_wifi_mode == STATION_MODE) {
        user_wifi_station_init();
    }
    else if (last_wifi_mode == STATIONAP_MODE) {
        user_wifi_station_init();
    }
}

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

#if GPIO_INTRR_USE_POLL
    user_poll_gpio_init();
#else
    user_intrr_gpio_init();
#endif

    blinky_init();
    run_wifi_mode();
}
/** @} */
