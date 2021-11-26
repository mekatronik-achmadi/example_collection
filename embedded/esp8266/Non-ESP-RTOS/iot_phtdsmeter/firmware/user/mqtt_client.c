/*
              UNKNOWN PUBLIC LICENSE

 Copyright (C) 2020 Achmadi S.T. M.T.

 Currently no license applied because author liv in
 Indonesia, a country which doesn't really concern
 about digital content copyright.

 */

/**
 * @file    mqtt_client.c
 * @brief   MQTT handler code.
 *
 * @addtogroup IoT
 * @{
 */

#include "ets_sys.h"
#include "osapi.h"
#include "mqtt.h"
#include "user_interface.h"
#include "mem.h"

/**
 * @brief Global MQTT object
 */
MQTT_Client mqttClient;

/**
 * @brief MQTT Broker connected callback
 */
LOCAL void mqttConnectedCb(uint32_t *args){
    MQTT_Client* client = (MQTT_Client*)args;
    os_printf("MQTT: Connected\r\n");
    MQTT_Subscribe(client, "hello/world", 0);
    MQTT_Publish(client, "hello/world", "hello_mqtt", 10, 0, 0);
}

/**
 * @brief MQTT Broker disconnected callback
 */
LOCAL void mqttDisconnectedCb(uint32_t *args){
    (void) args;
    os_printf("MQTT: Disconnected\r\n");
}

/**
 * @brief MQTT message published callback
 */
LOCAL void mqttPublishedCb(uint32_t *args){
    (void) args;
    os_printf("MQTT: Published\r\n");
}

/**
 * @brief MQTT message received callback
 */
LOCAL void mqttDataCb(uint32_t *args, const char* topic, uint32_t topic_len, const char *data, uint32_t data_len){
    (void) args;
    char *topicBuf = (char*)os_zalloc(topic_len+1),
            *dataBuf = (char*)os_zalloc(data_len+1);

    os_memcpy(topicBuf, topic, topic_len);
    topicBuf[topic_len] = 0;

    os_memcpy(dataBuf, data, data_len);
    dataBuf[data_len] = 0;

    os_printf("Receive topic: %s, data: %s \r\n", topicBuf, dataBuf);
    os_free(topicBuf);
    os_free(dataBuf);
}

/**
 * @brief Callback to connect to Broker as wifi connected
 * @param uint8 IP status
 */
void mqttWifiConnectCb(uint8_t status){
    if(status == STATION_GOT_IP){
        MQTT_Connect(&mqttClient);
    }
    else {
        MQTT_Disconnect(&mqttClient);
    }
}

/**
 * @brief MQTT Client initiate
 */
void mqttClientInit(void){
    uint8_t broker_ip[] = MQTT_BROKER;
    uint8_t client_name[] = MQTT_NAME;

    MQTT_InitConnection(&mqttClient, broker_ip, 1883, 0);
    MQTT_InitClient(&mqttClient, client_name, NULL, NULL, 120, 0);

    MQTT_OnConnected(&mqttClient, mqttConnectedCb);
    MQTT_OnDisconnected(&mqttClient, mqttDisconnectedCb);
    MQTT_OnPublished(&mqttClient, mqttPublishedCb);
    MQTT_OnData(&mqttClient, mqttDataCb);

    os_printf("MQTT Done!! \r\n");
}

/** @} */
