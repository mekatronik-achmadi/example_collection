/*
              UNKNOWN PUBLIC LICENSE

 Copyright (C) 2019 Wira S.T. M.T.

 Currently no license applied because author liv in
 Indonesia, a country which doesn't really concern
 about digital content copyright.

 */

/**
 * @file    json.c
 * @brief   JSON String Builder code.
 *
 * @addtogroup Webserver
 * @{
 */

#include "ets_sys.h"
#include "osapi.h"
#include "gpio.h"
#include "os_type.h"
#include "mem.h"
#include "spi_flash.h"
#include "user_interface.h"

#include "json.h"
#include "rwflash.h"

extern uint8 magnet_chk;
extern uint8 pir_chk;
extern char strConfigs[FLASH_CONFIGS_LEN];

void json_open(char* strJSON){
    os_strcpy(strJSON,"{");
}

void json_close(char* strJSON){
    if(os_strlen(strJSON)>2){
        strJSON[os_strlen(strJSON)-1] = '}';
    }
    else{
        os_strcpy(strJSON,"{}");
    }
}

void json_string(char* strJSON, char* field, char* value){
    os_sprintf(strJSON,"%s\"%s\": \"%s\",",strJSON,field,value);
}

void json_boolean(char* strJSON, char* field, uint8 value){
    if(value==0){
        os_sprintf(strJSON,"%s\"%s\": false,",strJSON,field);
    }
    else if (value==1) {
        os_sprintf(strJSON,"%s\"%s\": true,",strJSON,field);
    }
}

void json_infoall(char *strJSON){
    char user_id[FLASH_STRING_BUFF];
    char devs_id[FLASH_STRING_BUFF];
    struct station_config stationConf;

    wifi_station_get_config(&stationConf);

    rwflash_str_read(CONFIGS_FLASH_ADDR,strConfigs);
    rwflash_conf_parse(strConfigs,user_id,FLASH_USERID);
    rwflash_conf_parse(strConfigs,devs_id,FLASH_DEVSID);

    json_open(strJSON);
    json_string(strJSON,"ssid",stationConf.ssid);
    json_string(strJSON,"pass",stationConf.password);
    json_string(strJSON,"user_id",user_id);
    json_string(strJSON,"devs_id",devs_id);
    json_boolean(strJSON,"magnet",magnet_chk);
    json_boolean(strJSON,"pir",pir_chk);
    json_close(strJSON);

    // reset sensor status on checking
    magnet_chk = 0;
    pir_chk = 0;
}
/** @} */
