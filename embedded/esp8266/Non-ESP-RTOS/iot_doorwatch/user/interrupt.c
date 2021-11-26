/*
              UNKNOWN PUBLIC LICENSE

 Copyright (C) 2019 Wira S.T. M.T.

 Currently no license applied because author liv in
 Indonesia, a country which doesn't really concern
 about digital content copyright.

 */

/**
 * @file    interrupt.c
 * @brief   GPIO Interrupt code.
 *
 * @addtogroup Sensor
 * @{
 */

#include "ets_sys.h"
#include "osapi.h"
#include "gpio.h"
#include "os_type.h"

#include "interrupt.h"
#include "httpd.h"

#if GPIO_INTRR_USE_POLL

/**
 * @brief Magnet sensor lock check
 */
uint8 magnet_chk;

/**
 * @brief PIR sensor lock check
 */
uint8 pir_chk;

/**
 * @brief Interrupt polling timer
 */
LOCAL os_timer_t gpio_poll_timer;

LOCAL uint8 gpio12_stt,gpio13_stt, gpio14_stt;

/**
 * @brief GPIO Interrupt polling handler
 * @details All GPIO Interrupt response defined here
 */
LOCAL void ICACHE_FLASH_ATTR gpio_poll_handler(){
    if( !(GPIO_INPUT_GET(GPIO_ID_PIN(MAGNET_INTRR_PINNUM))) ){
        if(gpio12_stt==0){
            os_printf_plus("MAGNET LEVEL Switched !!!\r\n");
            gpio12_stt = 1;
            magnet_chk = 1;
        }
    }
    else{
        gpio12_stt = 0;
    }

    if( !(GPIO_INPUT_GET(GPIO_ID_PIN(PIR_INTRR_PINNUM))) ){
        if(gpio13_stt==0){
            os_printf_plus("PIR Movement Detected!!!\r\n");
            gpio13_stt = 1;
            pir_chk = 1;
        }
    }
    else{
        gpio13_stt = 0;
    }

    if( !(GPIO_INPUT_GET(GPIO_ID_PIN(SW_INTRR_PINNUM))) ){
        if(gpio14_stt==0){
            os_printf_plus("Wifi Mode Switched!!!\r\n");
            user_wifi_switch();
            gpio14_stt = 1;
        }
    }
    else{
        gpio14_stt = 0;
    }
}

void ICACHE_FLASH_ATTR user_poll_gpio_init(void){
    PIN_FUNC_SELECT(MAGNET_INTRR_PINNAME, MAGNET_INTRR_PINFUNC);
    PIN_PULLUP_EN(MAGNET_INTRR_PINNAME);
    GPIO_DIS_OUTPUT(GPIO_ID_PIN(MAGNET_INTRR_PINNUM));

    PIN_FUNC_SELECT(PIR_INTRR_PINNAME, PIR_INTRR_PINFUNC);
    PIN_PULLUP_EN(PIR_INTRR_PINNAME);
    GPIO_DIS_OUTPUT(GPIO_ID_PIN(PIR_INTRR_PINNUM));

    PIN_FUNC_SELECT(SW_INTRR_PINNAME, SW_INTRR_PINFUNC);
    PIN_PULLUP_EN(SW_INTRR_PINNAME);
    GPIO_DIS_OUTPUT(GPIO_ID_PIN(SW_INTRR_PINNUM));

    os_timer_setfn(&gpio_poll_timer, (os_timer_func_t *)gpio_poll_handler, NULL);
    os_timer_arm(&gpio_poll_timer, 1, 1);
}

#else

/**
 * @brief HW Interrupt handler
 */
LOCAL void gpio_intrr_handler(void *arg){
    uint32 gpio_status = GPIO_REG_READ(GPIO_STATUS_ADDRESS);
    GPIO_REG_WRITE(GPIO_STATUS_W1TC_ADDRESS, gpio_status);

    if (gpio_status & BIT(MAGNET_INTRR_PINNUM)){
        if(GPIO_INPUT_GET(MAGNET_INTRR_PINNUM)){
            os_printf_plus("GPIO Interrupt Triggered\r\n");
        }
    }
}

void ICACHE_FLASH_ATTR user_intrr_gpio_init(void){
    ETS_GPIO_INTR_ATTACH(gpio_intrr_handler,NULL);
    ETS_GPIO_INTR_DISABLE();

    PIN_FUNC_SELECT(MAGNET_INTRR_PINNAME, MAGNET_INTRR_PINFUNC);
    PIN_PULLUP_EN(MAGNET_INTRR_PINNAME);
    GPIO_DIS_OUTPUT(GPIO_ID_PIN(MAGNET_INTRR_PINNUM));

    gpio_register_set(GPIO_PIN_ADDR(GPIO_ID_PIN(MAGNET_INTRR_PINNUM)),
                            GPIO_PIN_INT_TYPE_SET(GPIO_PIN_INTR_DISABLE) |
                            GPIO_PIN_PAD_DRIVER_SET(GPIO_PAD_DRIVER_DISABLE) |
                            GPIO_PIN_SOURCE_SET(GPIO_AS_PIN_SOURCE));

    GPIO_REG_WRITE(GPIO_STATUS_W1TC_ADDRESS, BIT(MAGNET_INTRR_PINNUM));

    gpio_pin_intr_state_set(GPIO_ID_PIN(MAGNET_INTRR_PINNUM), GPIO_PIN_INTR_POSEDGE);

    ETS_GPIO_INTR_ENABLE();
}

#endif
/** @} */
