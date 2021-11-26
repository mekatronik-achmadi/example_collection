/*
              UNKNOWN PUBLIC LICENSE

 Copyright (C) 2020 Achmadi S.T. M.T.

 Currently no license applied because author liv in
 Indonesia, a country which doesn't really concern
 about digital content copyright.

 */

/**
 * @file    user_config.h
 * @brief   User Configuration header.
 *
 * @addtogroup Main
 * @{
 */

#ifndef _USER_CONF_
#define _USER_CONF_

/**
 * @brief Default UART BaudRate
 */
#define SERIALBAUD 9600

#define USE_HTTP TRUE
#define USE_MQTT FALSE
#define LOOP_MSG TRUE
#define ADC_MEAN FALSE

#define WIFI_SSID "PUDJI"
#define WiFI_PASS "Rahardjo"

#define HTTP_SERV   "http://192.168.1.4"
#define HTTP_PORT   "9000"

#define MQTT_BROKER "http://0.0.0.0"
#define MQTT_NAME   "esp8266"

#endif

/** @} */
