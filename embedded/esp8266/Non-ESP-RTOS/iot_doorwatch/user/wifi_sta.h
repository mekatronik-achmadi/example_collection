/*
              UNKNOWN PUBLIC LICENSE

 Copyright (C) 2019 Wira S.T. M.T.

 Currently no license applied because author liv in
 Indonesia, a country which doesn't really concern
 about digital content copyright.

 */

/**
 * @file    wifi_sta.h
 * @brief   Wifi Station header.
 *
 * @addtogroup Network
 * @{
 */

#ifndef WIFI_STA_H
#define WIFI_STA_H

/**
 * @brief Use default SSID/PASS or not
 */
#define USE_DEFAULT_SSID_PASS 1

/**
 * @brief Use SOFTAP as default
 */
#define USE_DEFAULT_STATION 1

/**
 * @brief Wifi Station Initialization
 */
void user_wifi_station_init(void);

#endif // WIFI_STA_H
/** @} */
