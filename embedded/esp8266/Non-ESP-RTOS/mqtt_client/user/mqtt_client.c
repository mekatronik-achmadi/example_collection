#include "ets_sys.h"
#include "osapi.h"
#include "mqtt.h"
#include "user_interface.h"
#include "mem.h"

MQTT_Client mqttClient;

LOCAL void mqttConnectedCb(uint32_t *args){
    MQTT_Client* client = (MQTT_Client*)args;
    os_printf("MQTT: Connected\r\n");
    MQTT_Subscribe(client, "hello/world", 0);
    MQTT_Publish(client, "hello/world", "hello_mqtt", 10, 0, 0);
}

LOCAL void mqttDisconnectedCb(uint32_t *args){
    MQTT_Client* client = (MQTT_Client*)args;
    os_printf("MQTT: Disconnected\r\n");
}

LOCAL void mqttPublishedCb(uint32_t *args){
    MQTT_Client* client = (MQTT_Client*)args;
    os_printf("MQTT: Published\r\n");
}

LOCAL void mqttDataCb(uint32_t *args, const char* topic, uint32_t topic_len, const char *data, uint32_t data_len){
    char *topicBuf = (char*)os_zalloc(topic_len+1),
            *dataBuf = (char*)os_zalloc(data_len+1);

    MQTT_Client* client = (MQTT_Client*)args;

    os_memcpy(topicBuf, topic, topic_len);
    topicBuf[topic_len] = 0;

    os_memcpy(dataBuf, data, data_len);
    dataBuf[data_len] = 0;

    os_printf("Receive topic: %s, data: %s \r\n", topicBuf, dataBuf);
    os_free(topicBuf);
    os_free(dataBuf);
}

void mqttWifiConnectCb(uint8_t status){
    if(status == STATION_GOT_IP){
        MQTT_Connect(&mqttClient);
    }
    else {
        MQTT_Disconnect(&mqttClient);
    }
}

void mqttClientInit(void){
    MQTT_InitConnection(&mqttClient, "192.168.50.245", 1883, 0);
    MQTT_InitClient(&mqttClient, "esp8266", NULL, NULL, 120, 0);

    MQTT_OnConnected(&mqttClient, mqttConnectedCb);
    MQTT_OnDisconnected(&mqttClient, mqttDisconnectedCb);
    MQTT_OnPublished(&mqttClient, mqttPublishedCb);
    MQTT_OnData(&mqttClient, mqttDataCb);

    os_printf("MQTT Done!! \r\n");
}

