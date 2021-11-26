/*
              UNKNOWN PUBLIC LICENSE

 Copyright (C) 2019 Wira S.T. M.T.

 Currently no license applied because author liv in
 Indonesia, a country which doesn't really concern
 about digital content copyright.

 */

/**
 * @file    analog.h
 * @brief   Analog Input Test header.
 *
 * @addtogroup Sensor
 * @{
 */

#ifndef ANALOG_H
#define ANALOG_H

/**
 * @brief ADC Averaging size
 */
#define ADC_MEASURES_NUM 10

/**
 * @brief Read ADC Input
 * @return ADC value in 10-bit
 */
uint16 user_get_adc(void);

#endif // ANALOG_H
/** @} */
