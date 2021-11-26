#include "mqtt/mqtt_server.h"
#include "osapi.h"
#include "ets_sys.h"
#include "user_config.h"
#include "user_interface.h"
#include "mem.h"

#include "mqtt/mqtt.h"

LOCAL void ICACHE_FLASH_ATTR  mqttDataCB(uint32_t * args, const char *topic, uint32_t topic_len, const char *data, uint32_t length) {
    os_printf("Received: \"%s\" len: %d data: \"%s\" \r\n", topic, length, data);
}

LOCAL bool ICACHE_FLASH_ATTR  mqttConnectCB(struct espconn *pesp_conn, uint16_t client_count) {
    if (client_count > 30) {
        os_printf("Client disconnected - too many concurrent clients\r\n");
        return false;
    }

    return true;
}

LOCAL bool ICACHE_FLASH_ATTR mqttDisconnCB(struct espconn *pesp_conn, const char* client_id){
    return true;
}

LOCAL bool ICACHE_FLASH_ATTR mqttAuthCB(const char* username, const char *password, const char *client_id, struct espconn *pesp_conn) {

    /*if (os_strcmp(username, "username") != 0 || os_strcmp(password, "password") != 0) {
    	os_printf("Authentication with %s/%s failed\r\n", username, password);
	    return false;
    }*/

    return true;
}

void mqttBrokerInit(void){
    espconn_tcp_set_max_con(15);
    os_printf("Max number of TCP clients: %d\r\n", espconn_tcp_get_max_con());

    MQTT_server_onData(mqttDataCB);
    MQTT_server_onConnect(mqttConnectCB);
    MQTT_server_onDisconnect(mqttDisconnCB);
    MQTT_server_onAuth(mqttAuthCB);

    MQTT_server_start(1883, 30, 30);

    MQTT_local_subscribe("hello/world", 0);
}

