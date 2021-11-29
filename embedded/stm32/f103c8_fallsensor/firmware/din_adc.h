/*
              DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE

 Copyright (C) 2018 Achmadi S.T.

 Everyone is permitted to copy and distribute verbatim or modified
 copies of this license document, and changing it is allowed as long
 as the name is changed.

            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
   TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION

  0. You just DO WHAT THE FUCK YOU WANT TO.
 */

/**
 * @file    din_adc.h
 * @brief   ADC (for Mic) routine header.
 *
 * @addtogroup ADC
 * @{
 */

#ifndef DIN_ADC_H
#define DIN_ADC_H

#include "ch.h"
#include "hal.h"

/**
 * @brief   ADC channel number.
 */
#define ADC_GRP_NUM_CHANNELS   1

/**
 * @brief   ADC buffer size.
 */
#define ADC_GRP_BUF_DEPTH      10

#define ADC_SCALE              0.012

void d_adc_start(void);

#endif // DIN_ADC_H
/** @} */
