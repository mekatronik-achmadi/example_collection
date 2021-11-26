/*
              UNKNOWN PUBLIC LICENSE

 Copyright (C) 2020 Achmadi S.T. M.T.

 Currently no license applied because author liv in
 Indonesia, a country which doesn't really concern
 about digital content copyright.

 */

/**
 * @file    user.c
 * @brief   Main entry code.
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

#include "wifi_sta.h"
#include "user_config.h"
#include "http_client.h"
#include "mqtt_client.h"
#include "mux.h"
#include "iot_data.h"
#include "blinky.h"

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

#if USE_MQTT
    os_printf("MQTT used\r\n");
    mqttClientInit();
#else
    os_printf("HTTP used\r\n");
#endif

    user_wifi_station_init();

    mux_init();
    run_loop(0);

    blinky_init();
}
/** @} */
