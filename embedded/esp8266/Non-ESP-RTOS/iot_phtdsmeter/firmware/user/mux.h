/*
              UNKNOWN PUBLIC LICENSE

 Copyright (C) 2020 Achmadi S.T. M.T.

 Currently no license applied because author liv in
 Indonesia, a country which doesn't really concern
 about digital content copyright.

 */

/**
 * @file    mux.h
 * @brief   HC4067 mux header.
 *
 * @addtogroup IO
 * @{
 */

#ifndef MUX_H
#define MUX_H

#include <stdint.h>

#define MUX_S0 BIT15
#define MUX_S1 BIT13 //MTCK_U //GPIO13
#define MUX_S2 BIT12 //MTDI_U //GPIO12
#define MUX_S3 BIT14 //MTMS_U //GPIO14

#define MUX_PIN_1(PIN_NUM) gpio_output_set(PIN_NUM, 0, PIN_NUM, 0)
#define MUX_PIN_0(PIN_NUM) gpio_output_set(0, PIN_NUM, PIN_NUM, 0)

void mux_init(void);
void mux_channel(uint8_t channel);

#endif // MUX_H
/** @} */
