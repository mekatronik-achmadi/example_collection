/*
              UNKNOWN PUBLIC LICENSE

 Copyright (C) 2020 Achmadi S.T. M.T.

 Currently no license applied because author liv in
 Indonesia, a country which doesn't really concern
 about digital content copyright.

 */

/**
 * @file    mqtt_client.h
 * @brief   MQTT handler header.
 *
 * @addtogroup IoT
 * @{
 */

#ifndef MQTT_CLIENT_H
#define MQTT_CLIENT_H

#include <stdint.h>

void mqttWifiConnectCb(uint8_t status);
void mqttClientInit(void);

#endif // MQTT_CLIENT_H
/** @} */
