/*
              UNKNOWN PUBLIC LICENSE

 Copyright (C) 2019 Wira S.T. M.T.

 Currently no license applied because author liv in
 Indonesia, a country which doesn't really concern
 about digital content copyright.

 */

/**
 * @file    analog.c
 * @brief   Analog Input Test code.
 *
 * @addtogroup Sensor
 * @{
 */

#include "ets_sys.h"
#include "osapi.h"
#include "gpio.h"
#include "os_type.h"
#include "user_interface.h"

#include "analog.h"

uint16 ICACHE_FLASH_ATTR user_get_adc(void){
    uint16 vres;

    uint8 i;
    for(i=0;i<ADC_MEASURES_NUM;i++){
        vres += system_adc_read();
    }

    return vres / ADC_MEASURES_NUM;
}
/** @} */
