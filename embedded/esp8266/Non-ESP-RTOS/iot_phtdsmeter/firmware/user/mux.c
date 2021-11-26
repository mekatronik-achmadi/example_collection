/*
              UNKNOWN PUBLIC LICENSE

 Copyright (C) 2020 Achmadi S.T. M.T.

 Currently no license applied because author liv in
 Indonesia, a country which doesn't really concern
 about digital content copyright.

 */

/**
 * @file    mux.c
 * @brief   HC4067 mux code.
 *
 * @addtogroup IO
 * @{
 */

#include "ets_sys.h"
#include "osapi.h"
#include "gpio.h"
#include "os_type.h"

#include "mux.h"

/**
 * @brief Initiate pin for mux selector
 */
void mux_init(void){
    PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTDO_U, FUNC_GPIO15); //Mux S0
    PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTCK_U, FUNC_GPIO13); //Mux S1
    PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTDI_U, FUNC_GPIO12); //Mux S2
    PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTMS_U, FUNC_GPIO14); //Mux S3

    PIN_PULLUP_DIS(PERIPHS_IO_MUX_MTDO_U);
    PIN_PULLUP_DIS(PERIPHS_IO_MUX_MTCK_U);
    PIN_PULLUP_DIS(PERIPHS_IO_MUX_MTDI_U);
    PIN_PULLUP_DIS(PERIPHS_IO_MUX_MTMS_U);

    mux_channel(0);
}

/**
 * @brief Set Mux active channel
 * @param channel
 */
void mux_channel(uint8_t channel){

    switch(channel){

        case 0:
            MUX_PIN_0 (MUX_S0);
            MUX_PIN_0 (MUX_S1);
            MUX_PIN_0 (MUX_S2);
            MUX_PIN_0 (MUX_S3);
        break;

        case 1:
            MUX_PIN_1 (MUX_S0);
            MUX_PIN_0 (MUX_S1);
            MUX_PIN_0 (MUX_S2);
            MUX_PIN_0 (MUX_S3);
        break;

        case 2:
            MUX_PIN_0 (MUX_S0);
            MUX_PIN_1 (MUX_S1);
            MUX_PIN_0 (MUX_S2);
            MUX_PIN_0 (MUX_S3);
        break;

        case 3:
            MUX_PIN_1 (MUX_S0);
            MUX_PIN_1 (MUX_S1);
            MUX_PIN_0 (MUX_S2);
            MUX_PIN_0 (MUX_S3);
        break;

        default:
            os_printf("mux channel number outside preset\r\n");
        break;
    }
}
/** @} */
