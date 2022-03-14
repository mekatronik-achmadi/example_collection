/**
 * @file my_btspp.c
 * @brief Bluetooth Serial Acceptor code
 *
 * @addtogroup Bluetooth
 * @{
 */

#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

#include "nvs.h"
#include "nvs_flash.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

#include "esp_bt.h"
#include "esp_bt_main.h"
#include "esp_gap_bt_api.h"
#include "esp_bt_device.h"
#include "esp_spp_api.h"

#include "time.h"
#include "sys/time.h"

#include "my_btspp.h"
#include "input.h"

/**
 * @brief Serial Port Protocol Mode Callback
 *
 */
static const esp_spp_mode_t esp_spp_mode = ESP_SPP_MODE_CB;

/**
 * @brief  Serial Port Protocol Security Mask
 *
 */
static const esp_spp_sec_t sec_mask = ESP_SPP_SEC_AUTHENTICATE;

/**
 * @brief  Serial Port Protocol as Bluetooth Slave (Acceptor)
 *
 */
static const esp_spp_role_t role_slave = ESP_SPP_ROLE_SLAVE;

#if (SPP_SHOW_MODE == SPP_SHOW_SPEED)
static long data_num = 0;
static struct timeval time_new, time_old;

/**
 * @brief Get Speed response
 *
 */
static void print_speed(void){
    float time_old_s = time_old.tv_sec + time_old.tv_usec / 1000000.0;
    float time_new_s = time_new.tv_sec + time_new.tv_usec / 1000000.0;

    float time_interval = time_new_s - time_old_s;
    float speed = data_num * 8 / time_interval / 1000.0;

    ESP_LOGI(SPP_TAG, "speed(%fs ~ %fs): %f kbit/s" , time_old_s, time_new_s, speed);

    data_num = 0;
    time_old.tv_sec = time_new.tv_sec;
    time_old.tv_usec = time_new.tv_usec;
}
#endif

/**
 * @brief  Serial Port Protocol event callback
 *
 * @param event
 * @param param
 */
static void esp_spp_cb(esp_spp_cb_event_t event, esp_spp_cb_param_t *param){
    switch (event) {

        case ESP_SPP_INIT_EVT:
            ESP_LOGI(SPP_TAG, "ESP_SPP_INIT_EVT");
            esp_bt_dev_set_device_name(EXAMPLE_DEVICE_NAME);
            esp_bt_gap_set_scan_mode(ESP_BT_CONNECTABLE, ESP_BT_GENERAL_DISCOVERABLE);
            esp_spp_start_srv(sec_mask,role_slave, 0, SPP_SERVER_NAME);
            break;

        case ESP_SPP_DISCOVERY_COMP_EVT:
            ESP_LOGI(SPP_TAG, "ESP_SPP_DISCOVERY_COMP_EVT");
            break;

        case ESP_SPP_OPEN_EVT:
            ESP_LOGI(SPP_TAG, "ESP_SPP_OPEN_EVT");
            break;

        case ESP_SPP_CLOSE_EVT:
            ESP_LOGI(SPP_TAG, "ESP_SPP_CLOSE_EVT");
            break;

        case ESP_SPP_START_EVT:
            ESP_LOGI(SPP_TAG, "ESP_SPP_START_EVT");
            break;

        case ESP_SPP_CL_INIT_EVT:
            ESP_LOGI(SPP_TAG, "ESP_SPP_CL_INIT_EVT");
            break;

        case ESP_SPP_DATA_IND_EVT:
#if (SPP_SHOW_MODE == SPP_SHOW_DATA)
            ESP_LOGI(SPP_TAG, "ESP_SPP_DATA_IND_EVT len=%d handle=%d", param->data_ind.len, param->data_ind.handle);
            esp_log_buffer_hex("",param->data_ind.data,param->data_ind.len);

            bt_log_char(param->data_ind.data);
#else
            gettimeofday(&time_new, NULL);
            data_num += param->data_ind.len;
            if (time_new.tv_sec - time_old.tv_sec >= 3){print_speed();}
#endif
            break;

        case ESP_SPP_CONG_EVT:
            ESP_LOGI(SPP_TAG, "ESP_SPP_CONG_EVT");
            break;

        case ESP_SPP_WRITE_EVT:
            ESP_LOGI(SPP_TAG, "ESP_SPP_WRITE_EVT");
            break;

        case ESP_SPP_SRV_OPEN_EVT:
            ESP_LOGI(SPP_TAG, "ESP_SPP_SRV_OPEN_EVT");
#if (SPP_SHOW_MODE == SPP_SHOW_SPEED)
            gettimeofday(&time_old, NULL);
#endif
            break;

        case ESP_SPP_SRV_STOP_EVT:
            ESP_LOGI(SPP_TAG, "ESP_SPP_SRV_STOP_EVT");
            break;

        case ESP_SPP_UNINIT_EVT:
            ESP_LOGI(SPP_TAG, "ESP_SPP_UNINIT_EVT");
            break;

        default:
            break;
    }
}

/**
 * @brief Generic Access Profile event callback
 *
 * @param event
 * @param param
 */
void esp_bt_gap_cb(esp_bt_gap_cb_event_t event, esp_bt_gap_cb_param_t *param){
    switch (event) {
        case ESP_BT_GAP_AUTH_CMPL_EVT:{
            if (param->auth_cmpl.stat == ESP_BT_STATUS_SUCCESS) {
                ESP_LOGI(SPP_TAG, "authentication success: %s", param->auth_cmpl.device_name);
                esp_log_buffer_hex(SPP_TAG, param->auth_cmpl.bda, ESP_BD_ADDR_LEN);
            } else {
                ESP_LOGE(SPP_TAG, "authentication failed, status:%d", param->auth_cmpl.stat);
            }
            break;
        }

        case ESP_BT_GAP_PIN_REQ_EVT:{
            ESP_LOGI(SPP_TAG, "ESP_BT_GAP_PIN_REQ_EVT min_16_digit:%d", param->pin_req.min_16_digit);
            if (param->pin_req.min_16_digit) {
                ESP_LOGI(SPP_TAG, "Input pin code: 0000 0000 0000 0000");
                esp_bt_pin_code_t pin_code = {0};
                esp_bt_gap_pin_reply(param->pin_req.bda, true, 16, pin_code);
            } else {
                ESP_LOGI(SPP_TAG, "Input pin code: 1234");
                esp_bt_pin_code_t pin_code;
                pin_code[0] = '1';
                pin_code[1] = '2';
                pin_code[2] = '3';
                pin_code[3] = '4';
                esp_bt_gap_pin_reply(param->pin_req.bda, true, 4, pin_code);
            }
            break;
        }

#if (CONFIG_BT_SSP_ENABLED == true)
        case ESP_BT_GAP_CFM_REQ_EVT:
            ESP_LOGI(SPP_TAG, "ESP_BT_GAP_CFM_REQ_EVT Please compare the numeric value: %d", param->cfm_req.num_val);
            esp_bt_gap_ssp_confirm_reply(param->cfm_req.bda, true);
            break;

        case ESP_BT_GAP_KEY_NOTIF_EVT:
            ESP_LOGI(SPP_TAG, "ESP_BT_GAP_KEY_NOTIF_EVT passkey:%d", param->key_notif.passkey);
            break;

        case ESP_BT_GAP_KEY_REQ_EVT:
            ESP_LOGI(SPP_TAG, "ESP_BT_GAP_KEY_REQ_EVT Please enter passkey!");
            break;
#endif

        case ESP_BT_GAP_MODE_CHG_EVT:
            ESP_LOGI(SPP_TAG, "ESP_BT_GAP_MODE_CHG_EVT mode:%d", param->mode_chg.mode);
            break;

        default: {
            ESP_LOGI(SPP_TAG, "event: %d", event);
            break;
        }
    }

    return;
}

/**
 * @brief Bluetooth Serial Port Protocol initialization
 *
 */
void btsppInit(void){
    esp_err_t btret;

    ESP_ERROR_CHECK(esp_bt_controller_mem_release(ESP_BT_MODE_BLE));

    esp_bt_controller_config_t bt_cfg = BT_CONTROLLER_INIT_CONFIG_DEFAULT();

    if ((btret = esp_bt_controller_init(&bt_cfg)) != ESP_OK) {
        ESP_LOGE(SPP_TAG, "%s initialize controller failed: %s\n", __func__, esp_err_to_name(btret));
        return;
    }

    if ((btret = esp_bt_controller_enable(ESP_BT_MODE_CLASSIC_BT)) != ESP_OK) {
        ESP_LOGE(SPP_TAG, "%s enable controller failed: %s\n", __func__, esp_err_to_name(btret));
        return;
    }

    if ((btret = esp_bluedroid_init()) != ESP_OK) {
        ESP_LOGE(SPP_TAG, "%s initialize bluedroid failed: %s\n", __func__, esp_err_to_name(btret));
        return;
    }

    if ((btret = esp_bluedroid_enable()) != ESP_OK) {
        ESP_LOGE(SPP_TAG, "%s enable bluedroid failed: %s\n", __func__, esp_err_to_name(btret));
        return;
    }

    if ((btret = esp_bt_gap_register_callback(esp_bt_gap_cb)) != ESP_OK) {
        ESP_LOGE(SPP_TAG, "%s gap register failed: %s\n", __func__, esp_err_to_name(btret));
        return;
    }

    if ((btret = esp_spp_register_callback(esp_spp_cb)) != ESP_OK) {
        ESP_LOGE(SPP_TAG, "%s spp register failed: %s\n", __func__, esp_err_to_name(btret));
        return;
    }

    if ((btret = esp_spp_init(esp_spp_mode)) != ESP_OK) {
        ESP_LOGE(SPP_TAG, "%s spp init failed: %s\n", __func__, esp_err_to_name(btret));
        return;
    }

#if (CONFIG_BT_SSP_ENABLED == true)
    /* Set default parameters for Secure Simple Pairing */
    esp_bt_sp_param_t param_type = ESP_BT_SP_IOCAP_MODE;
    esp_bt_io_cap_t iocap = ESP_BT_IO_CAP_IO;
    esp_bt_gap_set_security_param(param_type, &iocap, sizeof(uint8_t));
#endif

    /*
     * Set default parameters for Legacy Pairing
     * Use variable pin, input pin code when pairing
     */
    esp_bt_pin_type_t pin_type = ESP_BT_PIN_TYPE_VARIABLE;
    esp_bt_pin_code_t pin_code;
    esp_bt_gap_set_pin(pin_type, 0, pin_code);
}

/** @} */