/*
              UNKNOWN PUBLIC LICENSE

 Copyright (C) 2019 Wira S.T. M.T.

 Currently no license applied because author liv in
 Indonesia, a country which doesn't really concern
 about digital content copyright.

 */

/**
 * @file    blinky.c
 * @brief   LED Indicator code.
 *
 * @addtogroup Indicator
 * @{
 */

#include "ets_sys.h"
#include "osapi.h"
#include "gpio.h"
#include "driver/gpio16.h"
#include "os_type.h"
#include "user_interface.h"

#include "blinky.h"

/**
 * @brief Wifi Station blinky timer
 */
LOCAL os_timer_t wifista_timer;

/**
 * @brief Wifi SoftAP blinky timer
 */
LOCAL os_timer_t wifisap_timer;

/**
 * @brief Unconnected blinky timer
 */
LOCAL os_timer_t wifinon_timer;

/**
 * @brief Wifi Status blinky flag
 */
LOCAL uint8 wifi_led = 0;

/**
 * @brief Wifi Off blinky flag
 */
LOCAL uint8 wifi_none_stt = 0;

#if LED16_BLINKY
/**
 * @brief LED-16 blinky timer
 */
LOCAL os_timer_t blinky_timer;

/**
 * @brief LED-16 blinky flag
 */
LOCAL uint8 blink_led = 0;
#endif

/**
 * @brief Disable all Wifi blinky timer
 */
LOCAL void ICACHE_FLASH_ATTR user_wifi_blink_off(void){
    os_timer_disarm(&wifisap_timer);
    os_timer_disarm(&wifista_timer);
    os_timer_disarm(&wifinon_timer);
    wifi_led = 0;
}

/**
 * @brief Wifi Station and SoftAP blinky handler
 */
LOCAL void ICACHE_FLASH_ATTR wifi_on_timer_handler(void *prv){
    if (wifi_led==1) { gpio_output_set(0, BIT2, BIT2, 0); wifi_led=0; }
    else { gpio_output_set(BIT2, 0, BIT2, 0); wifi_led=1; }
}

/**
 * @brief Wifi Unconnected blinky handler
 */
LOCAL void ICACHE_FLASH_ATTR wifi_off_timer_handler(void *prv){
    if (wifi_led==17 || wifi_led==19) {
        gpio_output_set(BIT2, 0, BIT2, 0);

    }
    else if(wifi_led==16 || wifi_led==18) {
        gpio_output_set(0, BIT2, BIT2, 0);
    }
    else if(wifi_led==20){
        wifi_led = 0;
    }else{
        gpio_output_set(BIT2, 0, BIT2, 0);
    }

    wifi_led++;
}

#if LED16_BLINKY
/**
 * @brief LED-16 blinky handler
 */
LOCAL void ICACHE_FLASH_ATTR blinky_timer_handler(void *prv){
    if (blink_led==1) { gpio16_output_set(1); blink_led=0; }
    else { gpio16_output_set(0); blink_led=1; }
}
#endif

void ICACHE_FLASH_ATTR blinky_wifi_softap(void){
    user_wifi_blink_off();

    os_timer_setfn(&wifisap_timer, (os_timer_func_t *)wifi_on_timer_handler, NULL);
    os_timer_arm(&wifisap_timer, 500, 1);
}

void ICACHE_FLASH_ATTR blinky_wifi_station(void){
    if(wifi_none_stt==1){
        user_wifi_blink_off();

        os_timer_setfn(&wifista_timer, (os_timer_func_t *)wifi_on_timer_handler, NULL);
        os_timer_arm(&wifista_timer, 100, 1);

        wifi_none_stt = 0;
    }
}

void ICACHE_FLASH_ATTR blinky_wifi_none(void){
    if(wifi_none_stt==0){
        user_wifi_blink_off();

        os_timer_setfn(&wifinon_timer, (os_timer_func_t *)wifi_off_timer_handler, NULL);
        os_timer_arm(&wifinon_timer, 100, 1);

        wifi_none_stt = 1;
    }
}

void ICACHE_FLASH_ATTR blinky_init(void){
    PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO2_U, FUNC_GPIO2);
    PIN_PULLUP_DIS(PERIPHS_IO_MUX_GPIO2_U);

#if LED16_BLINKY
    gpio16_output_conf();
    os_timer_setfn(&blinky_timer, (os_timer_func_t *)blinky_timer_handler, NULL);
    os_timer_arm(&blinky_timer, 500, 1);
#endif
}
/** @} */
