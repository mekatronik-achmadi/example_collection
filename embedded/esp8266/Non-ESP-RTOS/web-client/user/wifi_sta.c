/*
              UNKNOWN PUBLIC LICENSE

 Copyright (C) 2019 Wira S.T. M.T.

 Currently no license applied because author liv in
 Indonesia, a country which doesn't really concern
 about digital content copyright.

 */

/**
 * @file    wifi_sta.c
 * @brief   Wifi Station code.
 *
 * @addtogroup Network
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

#include "user_config.h"
#include "wifi_sta.h"
#include "client.h"

/**
 * @brief Test IP routine timer
 */
LOCAL os_timer_t ip_test_timer;

/**
 * @brief ip_configured
 */
LOCAL uint8 ip_configured = 0;

/**
 * @brief Wifi Station IP check routine
 */
LOCAL void ICACHE_FLASH_ATTR user_wifi_station_check_ip(void){
    struct ip_info ipconfig;
    uint8 wifi_status;

    os_timer_disarm(&ip_test_timer);

    wifi_get_ip_info(STATION_IF,&ipconfig);

    wifi_status = wifi_station_get_connect_status();

    if(wifi_status == STATION_GOT_IP && ipconfig.ip.addr !=0 ){
        if(ip_configured == 0){
            os_printf("got ip !!! \r\n");
            ip_configured = 1;
        }
    }
    else{
        ip_configured = 0;
    }

    os_timer_setfn(&ip_test_timer, (os_timer_func_t *)user_wifi_station_check_ip, NULL);
    os_timer_arm(&ip_test_timer, 100, 0);
}

/**
 * @brief Wifi Station config
 */
LOCAL void ICACHE_FLASH_ATTR user_wifi_station_conf(void){
    struct station_config stationConf;
    char ssid[32];
    char password[64];

    os_memset(stationConf.ssid, 0, 32);
    os_memset(stationConf.password, 0, 64);
    stationConf.bssid_set = 0;

    wifi_station_get_config(&stationConf);

    os_strcpy(ssid,"Test_Server");
    os_memcpy(&stationConf.ssid, ssid, 32);

    os_strcpy(password,"testserver");
    os_memcpy(&stationConf.password, password, 64);

    wifi_station_set_config(&stationConf);

    os_timer_disarm(&ip_test_timer);
    os_timer_setfn(&ip_test_timer, (os_timer_func_t *)user_wifi_station_check_ip, NULL);
    os_timer_arm(&ip_test_timer, 100, 0);
}

void ICACHE_FLASH_ATTR user_wifi_station_init(void){
    wifi_set_opmode(STATION_MODE);
    user_wifi_station_conf();
}
/** @} */
