/**
 * @file my_wifiap.c
 * @brief WIFI AP source
 *
 * @addtogroup WIFI
 * @{
 */

#include "my_includes.h"

/**
 * @brief AP WIFI SSID
 *
 */
#define EXAMPLE_ESP_WIFI_SSID   "elbiCare"

/**
 * @brief AP WIFI Passwrod
 *
 */
#define EXAMPLE_ESP_WIFI_PASS   "audiometri"

/**
 * @brief AP WIFI Connection Number
 *
 */
#define EXAMPLE_MAX_STA_CONN    2

/**
 * @brief Flag if using AP or STA mode
 *
 */
bool wifi_ap = true;

/**
 * @brief Device IP info variable
 *
 */
tcpip_adapter_ip_info_t ipInfo;

/**
 * @brief Tag log for Wifi AP
 *
 */
static const char *TAG = "wifiAP";

/**
 * @brief WIFI event handler
 *
 * @param arg
 * @param event_base
 * @param event_id
 * @param event_data
 */
static void wifi_event_handler(void* arg, esp_event_base_t event_base,
                                    int32_t event_id, void* event_data){

    if (event_id == WIFI_EVENT_AP_STACONNECTED) {
        wifi_event_ap_staconnected_t* event = (wifi_event_ap_staconnected_t*) event_data;
        ESP_LOGI(TAG, "station "MACSTR" join, AID=%d",
                 MAC2STR(event->mac), event->aid);
    } else if (event_id == WIFI_EVENT_AP_STADISCONNECTED) {
        wifi_event_ap_stadisconnected_t* event = (wifi_event_ap_stadisconnected_t*) event_data;
        ESP_LOGI(TAG, "station "MACSTR" leave, AID=%d",
                 MAC2STR(event->mac), event->aid);
    }
}

/**
 * @brief Get the IP of wifiAP object
 *
 */
static void getIP_wifiAP(void){
    tcpip_adapter_get_ip_info((tcpip_adapter_if_t) ESP_IF_WIFI_AP, &ipInfo);
    ESP_LOGI(TAG, "Dev IP: %s", ip4addr_ntoa(&ipInfo.ip));
}

/**
 * @brief Start AP WIFI
 *
 */
void wifiapInit(void) {
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    esp_netif_create_default_wifi_ap();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT,
                                                        ESP_EVENT_ANY_ID,
                                                        &wifi_event_handler,
                                                        NULL,
                                                        NULL));
    wifi_config_t wifiap_cfg = {
        .ap = {
            .ssid = EXAMPLE_ESP_WIFI_SSID,
            .ssid_len = strlen(EXAMPLE_ESP_WIFI_SSID),
            .password = EXAMPLE_ESP_WIFI_PASS,
            .max_connection = EXAMPLE_MAX_STA_CONN,
            .authmode = WIFI_AUTH_WPA_WPA2_PSK
        },
    };

    if(strlen(EXAMPLE_ESP_WIFI_PASS)==0){
        wifiap_cfg.ap.authmode = WIFI_AUTH_OPEN;
    }

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_AP));
    ESP_ERROR_CHECK(esp_wifi_set_config((wifi_interface_t) ESP_IF_WIFI_AP, &wifiap_cfg));
    ESP_ERROR_CHECK(esp_wifi_start());

    ESP_LOGI(TAG, "SoftAP OK. SSID:%s password:%s",EXAMPLE_ESP_WIFI_SSID, EXAMPLE_ESP_WIFI_PASS);

    getIP_wifiAP();
}

/** @} */
