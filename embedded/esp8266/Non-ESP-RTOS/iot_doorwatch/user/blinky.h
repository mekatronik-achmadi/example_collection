/*
              UNKNOWN PUBLIC LICENSE

 Copyright (C) 2019 Wira S.T. M.T.

 Currently no license applied because author liv in
 Indonesia, a country which doesn't really concern
 about digital content copyright.

 */

/**
 * @file    blinky.h
 * @brief   LED Indicator header.
 *
 * @addtogroup Indicator
 * @{
 */

#ifndef _BLINKY_
#define _BLINKY_

/**
 * @brief Use LED-16 definition
 */
#define LED16_BLINKY    0

/**
 * @brief GPIO blinky initialize
 */
void blinky_init(void);

/**
 * @brief Wifi Unconnected blinky initialize
 */
void blinky_wifi_none(void);

/**
 * @brief Wifi SoftAP blinky initialize
 */
void blinky_wifi_softap(void);

/**
 * @brief Wifi Station blinky initialize
 */
void blinky_wifi_station(void);

#endif
/** @} */
