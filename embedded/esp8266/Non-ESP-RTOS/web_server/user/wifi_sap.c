/*
              UNKNOWN PUBLIC LICENSE

 Copyright (C) 2019 Wira S.T. M.T.

 Currently no license applied because author liv in
 Indonesia, a country which doesn't really concern
 about digital content copyright.

 */

/**
 * @file    wifi_sap.c
 * @brief   Wifi SoftAP code.
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
#include "wifi_sap.h"
#include "httpd.h"

/**
 * @brief Wifi SoftAP set IP Address
 */
LOCAL void ICACHE_FLASH_ATTR user_wifi_softap_set_ip(void){
    struct dhcps_lease dhcplease;
    struct ip_info ipinfo;

    wifi_softap_dhcps_stop();

    IP4_ADDR(&ipinfo.ip, IP_BASE0, IP_BASE1, IP_CLASS, 1);
    IP4_ADDR(&ipinfo.gw, IP_BASE0, IP_BASE1, IP_GTWAY, 1);
    IP4_ADDR(&ipinfo.netmask, 255, 255, 255, 0);
    wifi_set_ip_info(SOFTAP_IF,&ipinfo);

    IP4_ADDR(&dhcplease.start_ip, IP_BASE0, IP_BASE1, IP_CLASS, IP_START);
    IP4_ADDR(&dhcplease.end_ip, IP_BASE0, IP_BASE1, IP_CLASS, IP_END);
    wifi_softap_set_dhcps_lease(&dhcplease);

    wifi_softap_dhcps_start();
}

/**
 * @brief Wifi SoftAP configs
 */
LOCAL void ICACHE_FLASH_ATTR user_wifi_softap_conf(void){
    char wifi_id[16];

    struct softap_config softapConf;

    os_memset(softapConf.ssid,0,32);
    os_memset(softapConf.password,0,32);

    wifi_softap_get_config(&softapConf);

    softapConf.ssid_len = 0;
    softapConf.authmode = AUTH_WPA2_PSK;

    os_strcpy(wifi_id,"Test_Server");

    os_strcpy(softapConf.ssid,wifi_id);
    os_printf("WiFi SSID: %s\r\n",wifi_id);
    os_strcpy(softapConf.password,"testserver");

    user_wifi_softap_set_ip();

    wifi_softap_set_config(&softapConf);
}

void ICACHE_FLASH_ATTR user_wifi_softap_init(void){
    wifi_set_opmode(SOFTAP_MODE);
    user_tcpserver_init(SERVER_LOCAL_PORT);
    user_wifi_softap_conf();
}
/** @} */
