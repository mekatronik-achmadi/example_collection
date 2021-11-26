/*
              UNKNOWN PUBLIC LICENSE

 Copyright (C) 2020 Achmadi S.T. M.T.

 Currently no license applied because author liv in
 Indonesia, a country which doesn't really concern
 about digital content copyright.

 */

/**
 * @file    iot_data.c
 * @brief   Main data processing code.
 *
 * @addtogroup IoT
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

#include "wifi_sta.h"
#include "user_config.h"
#include "http_client.h"
#include "mqtt_client.h"
#include "mux.h"
#include "iot_data.h"
#include "blinky.h"

extern uint8_t ip_configured;

/**
 * @brief Timer for Data loop
 */
LOCAL os_timer_t data_timer;

/**
 * @brief ADC for PH output
 */
LOCAL uint16_t vadc0;

/**
 * @brief ADC for limiter output
 */
LOCAL uint16_t vadc1;

/**
 * @brief ADC for Temp output
 */
LOCAL uint16_t vadc2;

/**
 * @brief ADC for TDS output
 */
LOCAL uint16_t vadc3;

/**
 * @brief Loop timer handler function
 */
LOCAL void ICACHE_FLASH_ATTR data_timer_handler(void *prv){
    (void) prv;
    char url_req[32];

    mux_channel(0); vadc0 = SCALE_PH*system_adc_read()-OFSET_PH;
    mux_channel(1); vadc1 = SCALE_NTC*system_adc_read()-OFSET_NTC;
    mux_channel(2); vadc2 = SCALE_T*system_adc_read()-OFSET_T;
    mux_channel(3); vadc3 = SCALE_TDS*system_adc_read()-OFSET_TDS;

#if USE_HTTP
    if(ip_configured==1){
 #ifdef HTTP_PORT
        os_sprintf(url_req,"%s:%s/%d/%d/%d/%d/",HTTP_SERV,HTTP_PORT,vadc0,vadc1,vadc2,vadc3);
 #else
        os_sprintf(url_req,"%s/%d/%d/%d/%d/",HTTP_SERV,vadc0,vadc1,vadc2,vadc3);
 #endif

        os_printf("HTTP request to %s\r\n",url_req);
        tcp_client_get(url_req);
    }
    else{
        os_printf("HTTP Not Connected \r\n");
    }
#endif

#if LOOP_MSG
    os_printf("ADC: %4d |  %4d | %4d | %4d\r\n",vadc0,vadc1,vadc2,vadc3);
#endif
}

/**
 * @brief Loop starter function
 * @param uint8 Interval option
 * @details Options: 0 (stop), 1 (10s), 2 (30s), 3 (1m),
 */
void run_loop(uint8_t interval){

    switch(interval){
        case 0:
            os_timer_disarm(&data_timer);
            os_printf("data loop stopped\r\n");
            blinky_loop_stop();
        break;

        case 1:
            os_timer_disarm(&data_timer);
            os_timer_setfn(&data_timer, (os_timer_func_t *)data_timer_handler, NULL);
            os_timer_arm(&data_timer, 10000, 1);
            os_printf("data loop every 10s\r\n");
            blinky_loop_run();
        break;

        case 2:
            os_timer_disarm(&data_timer);
            os_timer_setfn(&data_timer, (os_timer_func_t *)data_timer_handler, NULL);
            os_timer_arm(&data_timer, 30000, 1);
            os_printf("data loop every 30s\r\n");
            blinky_loop_run();
        break;

        case 3:
            os_timer_disarm(&data_timer);
            os_timer_setfn(&data_timer, (os_timer_func_t *)data_timer_handler, NULL);
            os_timer_arm(&data_timer, 60000, 1);
            os_printf("data loop every 1m\r\n");
            blinky_loop_run();
        break;

        default:
            os_timer_disarm(&data_timer);
            os_printf("data loop option unrecognized\r\n");
            blinky_loop_stop();
        break;
    }
}
/** @} */
