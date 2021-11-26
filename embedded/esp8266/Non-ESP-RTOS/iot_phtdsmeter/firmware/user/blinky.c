/*
              UNKNOWN PUBLIC LICENSE

 Copyright (C) 2020 Achmadi S.T. M.T.

 Currently no license applied because author liv in
 Indonesia, a country which doesn't really concern
 about digital content copyright.

 */

/**
 * @file    blink.c
 * @brief   LED Indicator code.
 *
 * @addtogroup IO
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

#include "driver/gpio16.h"
#include "blinky.h"

/**
 * @brief LED-16 blinky timer
 */
LOCAL os_timer_t blinky_timer;

/**
 * @brief connection blinky timer
 */
LOCAL os_timer_t wifi_timer;

/**
 * @brief LED-16 blinky flag
 */
LOCAL uint8_t blink_led = 0;

/**
 * @brief Conn blinky flag
 */
LOCAL uint8_t wifi_led = 0;

/**
 * @brief LED-16 blinky handler
 */
LOCAL void ICACHE_FLASH_ATTR blinky_standby_handler(void *prv){
    (void) prv;

    if (blink_led==1) { gpio16_output_set(1); blink_led=0; }
    else { gpio16_output_set(0); blink_led=1; }
}

/**
 * @brief wifi disconnect handler
 */
LOCAL void ICACHE_FLASH_ATTR wifi_standby_handler(void *prv){
    (void) prv;

    if(wifi_led==17 || wifi_led==19) {
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

/**
 * @brief wifi connect handler
 */
LOCAL void ICACHE_FLASH_ATTR wifi_connect_handler(void *prv){
    (void) prv;

    if (wifi_led==1) { gpio_output_set(0, BIT2, BIT2, 0); wifi_led=0; }
    else { gpio_output_set(BIT2, 0, BIT2, 0); wifi_led=1; }
}

/**
 * @brief Start LED as loop run status
 */
void blinky_loop_run(void){
    os_timer_disarm(&blinky_timer);
    blink_led = 0;

    os_timer_setfn(&blinky_timer, (os_timer_func_t *)blinky_standby_handler, NULL);
    os_timer_arm(&blinky_timer, 100, 1);
}

/**
 * @brief Start LED as loop stop status
 */
void blinky_loop_stop(void){
    os_timer_disarm(&blinky_timer);
    blink_led = 0;

    os_timer_setfn(&blinky_timer, (os_timer_func_t *)blinky_standby_handler, NULL);
    os_timer_arm(&blinky_timer, 500, 1);
}

/**
 * @brief Start LED as wifi connected
 */
void blinky_wifi_connect(void){
    os_timer_disarm(&wifi_timer);
    wifi_led = 0;

    os_timer_setfn(&wifi_timer, (os_timer_func_t *)wifi_connect_handler, NULL);
    os_timer_arm(&wifi_timer, 500, 1);
}

/**
 * @brief Start LED as wifi connected
 */
void blinky_wifi_disconnect(void){
    os_timer_disarm(&wifi_timer);
    wifi_led = 0;

    os_timer_setfn(&wifi_timer, (os_timer_func_t *)wifi_standby_handler, NULL);
    os_timer_arm(&wifi_timer, 100, 1);
}

/**
 * @brief Initiate LED indicator
 */
void blinky_init(void){
    PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO2_U, FUNC_GPIO2);
    PIN_PULLUP_DIS(PERIPHS_IO_MUX_GPIO2_U);

    gpio16_output_conf();

    blinky_loop_stop();
    blinky_wifi_disconnect();
}
/** @} */
