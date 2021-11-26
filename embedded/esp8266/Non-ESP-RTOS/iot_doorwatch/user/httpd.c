/*
              UNKNOWN PUBLIC LICENSE

 Copyright (C) 2019 Wira S.T. M.T.

 Currently no license applied because author liv in
 Indonesia, a country which doesn't really concern
 about digital content copyright.

 */

/**
 * @file    httpd.c
 * @brief   TCP Server code.
 *
 * @addtogroup Webserver
 * @{
 */

#include "ets_sys.h"
#include "osapi.h"
#include "gpio.h"
#include "os_type.h"
#include "ip_addr.h"
#include "mem.h"
#include "espconn.h"
#include "user_interface.h"
#include "driver/uart.h"
#include "driver/uart_register.h"

#include "httpd.h"
#include "rwflash.h"
#include "json.h"
#include "blinky.h"

extern char strConfigs[FLASH_CONFIGS_LEN];

/**
 * @brief Connection object
 */
LOCAL struct espconn esp_conn;

/**
 * @brief TCP/IP object
 */
LOCAL esp_tcp esptcp;

/**
 * @brief Default HTML Response
 */
LOCAL const char index_html[] = \
        "<!DOCTYPE html>"\
        "<html>"\
        "<body>"\
            "<h1>ESP8266 HTTP server demo </h1>"\
        "</body>"\
        "</html>";

LOCAL const char help_html[] = \
        "<!DOCTYPE html>"\
        "<html>"\
        "<body>"\
            "http://192.168.4.1:3000<br>"\
            "========================<br>"\
            "/ssid/name/  : Set station SSID name<br>"\
            "/pass/word/  : Set station password<br>"\
            "/userid/name/: Set username<br>"\
            "/devsid/name/: Set deviceID<br>"\
            "/jsoninfo/   : Get All Info in JSON<br>"\
            "/switch/     : Switch Wifi mode<br>"\
            "/restart/    : Restart/Reboot unit<br>"\
            "/help/       : Show this help message<br>"\
        "</body>"\
        "</html>";

/**
 * @brief HTTP Response
 * @param[in] Connection object
 * @param[in] Error value
 * @param[in] HTML string
 */
LOCAL void ICACHE_FLASH_ATTR http_resp(struct espconn *pespconn, int error, char *html_txt){
    char *buffer = NULL;
    int html_len = 0;

    buffer = (char*) os_malloc(256*sizeof(char));
    if(buffer != NULL){
        if(html_txt != NULL){
            html_len = os_strlen(html_txt);
        }
        else{
            html_len = 0;
        }

        os_sprintf(buffer, "HTTP/1.1 %d OK\r\n"
                                    "Content-Length: %d\r\n"
                                    "Content-Type: text/html\r\n"
                                    "Connection: Closed\r\n"
                                    "\r\n"
        ,error, html_len);

        if(html_len>0){
            buffer = (char*) os_realloc(buffer,(256+html_len)*sizeof(char));
            os_strcat(buffer,html_txt);
        }

        espconn_sent(pespconn,buffer,os_strlen(buffer));
        os_free(buffer);
    }
}

/**
 * @brief TCP Send Callback
 * @details Callback Function not called directly
 */
LOCAL void ICACHE_FLASH_ATTR tcp_server_sent_cb(void *arg){
    os_printf("tcp data sent\r\n");
}

/**
 * @brief TCP server parse
 * @details Get request string from GET URL
 * @param[in] URL String input
 * @param[out] Parsed String output
 */
LOCAL void ICACHE_FLASH_ATTR tcp_server_parse(char *strIN, char *strOUT){
    char strInput[90];
    char strSplit[3][30];
    uint8 i,j,cnt;

    os_strcpy(strInput,strIN);
    j=0; cnt=0;
    for(i=0;i<=os_strlen(strInput);i++){
        if(strInput[i]==' ' || strInput[i]=='\0'){
            strSplit[cnt][j]='\0';
            cnt++;
            j=0;
        }
        else {
            strSplit[cnt][j]=strInput[i];
            j++;
        }
    }

    os_strcpy(strOUT,strSplit[1]);
}

/**
 * @brief TCP config parse
 * @details Split String by "/"
 * @param[in] String Input
 * @param[out] Desired part string output
 * @param[in] Position of desired string
 */
LOCAL void ICACHE_FLASH_ATTR tcp_conf_parse(char *strIN, char *strOUT, uint8 num){
    char strInput[90];
    char strSplit[3][30];
    uint8 i,j,cnt;

    os_strcpy(strInput,strIN);
    j=0; cnt=0;
    for(i=0;i<=os_strlen(strInput);i++){
        if(strInput[i]==' ' || strInput[i]=='\0' || strInput[i]=='/'){
            strSplit[cnt][j]='\0';
            cnt++;
            j=0;
        }
        else {
            strSplit[cnt][j]=strInput[i];
            j++;
        }
    }

    os_strcpy(strOUT,strSplit[num]);
}

/**
 * @brief TCP recieve Callback
 * @details Callback Function not called directly
 * @param[in] URL Request String
 */
LOCAL void ICACHE_FLASH_ATTR tcp_server_recv_cb(void *arg,char *pusrdata, unsigned short len){
    char *ptr = 0;
    char txthtml[200];
    char strRecv[64];
    char strReq[32];

    char ssid[32];
    char password[64];
    char user_id[FLASH_STRING_BUFF];
    char devs_id[FLASH_STRING_BUFF];
    struct station_config stationConf;

#if SERVER_RESP_TEST
    char strTest[FLASH_CONFIGS_LEN];
    uint16 tempint[1] = {0x05};
    uint16 buffint[1];
    char tempstr[8];
    char buffstr[8];
#endif

    char json_resp[JSON_RESP_LEN];
    struct espconn *pespconn = arg;

    ptr = (char*) os_strstr(pusrdata,"\r\n");
    ptr[0] = '\0';

//===================================================================
// Define all HTTP request here

    os_printf("tcp recv : %s\r\n", pusrdata);

    if (os_strcmp(pusrdata, "GET / HTTP/1.1") == 0){
        http_resp(pespconn,200,(char*)index_html);
    }

    else{
        tcp_server_parse(pusrdata,strRecv);
        tcp_conf_parse(strRecv,strReq,STR_REQ);

        os_printf_plus("parsed recv: %s\r\n",strRecv);

        if(os_strcmp("ssid",strReq)==0){
            wifi_set_opmode_current(STATIONAP_MODE);

            tcp_conf_parse(strRecv,ssid,STR_DATA);
            os_printf("new ssid: %s\r\n",ssid);

            os_sprintf(txthtml,"new ssid: %s",ssid);
            http_resp(pespconn,200,(char*)txthtml);

            os_memset(stationConf.ssid, 0, 32);
            stationConf.bssid_set = 0;

            wifi_station_get_config(&stationConf);
            os_memcpy(&stationConf.ssid, ssid, 32);
            wifi_station_set_config(&stationConf);

            wifi_set_opmode_current(SOFTAP_MODE);
        }
        else if(os_strcmp("pass",strReq)==0){
            wifi_set_opmode_current(STATIONAP_MODE);

            tcp_conf_parse(strRecv,password,STR_DATA);
            os_printf("new password: %s\r\n",password);

            os_sprintf(txthtml,"new password: %s",password);
            http_resp(pespconn,200,(char*)txthtml);

            os_memset(stationConf.password, 0, 64);
            stationConf.bssid_set = 0;

            wifi_station_get_config(&stationConf);
            os_memcpy(&stationConf.password, password, 64);
            wifi_station_set_config(&stationConf);

            wifi_set_opmode_current(SOFTAP_MODE);
        }
        else if(os_strcmp("userid",strReq)==0){
            tcp_conf_parse(strRecv,user_id,STR_DATA);
            os_printf("new username: %s\r\n",user_id);

            os_sprintf(txthtml,"new username: %s",user_id);
            http_resp(pespconn,200,(char*)txthtml);

            rwflash_str_read(CONFIGS_FLASH_ADDR,strConfigs);
            rwflash_conf_parse(strConfigs,devs_id,FLASH_DEVSID);

            os_sprintf(strConfigs,"/%s/%s",user_id,devs_id);
            rwflash_str_write(CONFIGS_FLASH_ADDR,strConfigs);
        }
        else if(os_strcmp("devsid",strReq)==0){
            tcp_conf_parse(strRecv,devs_id,STR_DATA);
            os_printf("new deviceid: %s\r\n",devs_id);

            os_sprintf(txthtml,"new deviceid: %s",devs_id);
            http_resp(pespconn,200,(char*)txthtml);

            rwflash_str_read(CONFIGS_FLASH_ADDR,strConfigs);
            rwflash_conf_parse(strConfigs,user_id,FLASH_USERID);

            os_sprintf(strConfigs,"/%s/%s",user_id,devs_id);
            rwflash_str_write(CONFIGS_FLASH_ADDR,strConfigs);
        }
        else if(os_strcmp("infosta",strReq)==0){
            wifi_station_get_config(&stationConf);

            os_printf("Station Mode Information\r\n");
            os_printf("SSID: %s\r\nPASS: %s\r\n",stationConf.ssid,stationConf.password);
            os_sprintf(txthtml,"Station Mode Information with SSID: %s and PASS: %s",stationConf.ssid,stationConf.password);
            http_resp(pespconn,200,(char*)txthtml);
        }
        else if(os_strcmp("jsoninfo",strReq)==0){
            os_printf("Building JSON info \r\n");
            json_infoall(json_resp);
            os_printf("JSON Data: %s\r\n",json_resp);
            http_resp(pespconn,200,json_resp);
        }
        else if(os_strcmp("switch",strReq)==0){
            http_resp(pespconn,200,NULL);
            user_wifi_switch();
        }
        else if(os_strcmp("restart",strReq)==0){
            http_resp(pespconn,200,NULL);
            uint8 i;for(i=0;i<100;i++){os_delay_us(10000);}
            system_restart();
        }
        else if(os_strcmp("help",strReq)==0){
            http_resp(pespconn,200,(char*)help_html);
        }
#if SERVER_RESP_TEST
        else if(os_strcmp("serial",strReq)==0){
            os_printf("Serial Response as HTTP request\r\n");
            os_sprintf(txthtml,"Serial Response Requested");
            http_resp(pespconn,200,(char*)txthtml);
        }
        else if(os_strcmp("flashconf",strReq)==0){
            char strTes0[8];
            char strTes1[8];

            http_resp(pespconn,200,NULL);

            os_strcpy(strTest,"userid;devsid");
            rwflash_str_write(CONFIGS_FLASH_ADDR,strTest);
            os_printf("Write 0x%X sec: %s\r\n",CONFIGS_FLASH_ADDR,strTest);

            os_memset(strTest,0,FLASH_CONFIGS_LEN);
            rwflash_str_read(CONFIGS_FLASH_ADDR,strTest);
            os_printf("Read 0x%X sec: %s\r\n",CONFIGS_FLASH_ADDR,strTest);

            rwflash_conf_parse(strTest,strTes0,0);
            rwflash_conf_parse(strTest,strTes1,1);

            os_printf("Test-0: %s\r\n",strTes0);
            os_printf("Test-1: %s\r\n",strTes1);
        }
        else if(os_strcmp("flashint",strReq)==0){
            http_resp(pespconn,200,NULL);

            rwflash_int_write(FLASH_START_ADDR,tempint);
            os_printf("Write 0x%X:0x%02x \r\n", FLASH_START_ADDR, tempint[0]);

            rwflash_int_read(FLASH_START_ADDR,buffint);
            os_printf("Read 0x%X sec:0x%02x \r\n", FLASH_START_ADDR, buffint[0]);
        }
        else if(os_strcmp("flashstr",strReq)==0){
            http_resp(pespconn,200,NULL);

            os_strcpy(tempstr,"hello");

            rwflash_str_write(FLASH_START_ADDR,tempstr);
            os_printf("Write 0x%X sec: %s\r\n",FLASH_START_ADDR,tempstr);

            rwflash_str_read(FLASH_START_ADDR,buffstr);
            os_printf("Read 0x%X sec: %s\r\n",FLASH_START_ADDR,buffstr);
        }
#endif
        else{ http_resp(pespconn,200,NULL); }
    }
}

/**
 * @brief TCP disconnected callback
 * @details Callback Function not called directly
 */
LOCAL void ICACHE_FLASH_ATTR tcp_server_disconn_cb(void *arg){
    os_printf("tcp disconnected\r\n");
}

/**
 * @brief TCP reconnecting callback
 * @details Callback Function not called directly
 */
LOCAL void ICACHE_FLASH_ATTR tcp_server_reconn_cb(void *arg,int8 err){
    os_printf("reconnecting, error code %d !!! \r\n",err);
}

/**
 * @brief TCP callbacks initialization
 */
LOCAL void ICACHE_FLASH_ATTR tcp_server_listen(void *arg){
    struct espconn *pesp_conn = arg;

    os_printf("tcp_server_listen !!! \r\n");

    espconn_regist_recvcb(pesp_conn, tcp_server_recv_cb);
    espconn_regist_sentcb(pesp_conn, tcp_server_sent_cb);

    espconn_regist_reconcb(pesp_conn, tcp_server_reconn_cb);
    espconn_regist_disconcb(pesp_conn, tcp_server_disconn_cb);
}

void ICACHE_FLASH_ATTR user_tcpserver_init(uint32 port){
    esp_conn.type = ESPCONN_TCP;
    esp_conn.state = ESPCONN_NONE;
    esp_conn.proto.tcp = &esptcp;
    esp_conn.proto.tcp->local_port = port;

    espconn_regist_connectcb(&esp_conn,tcp_server_listen);

    int8 ret = espconn_accept(&esp_conn);
    os_printf("espconn_accepted at [%d]\r\n", ret);
}

void ICACHE_FLASH_ATTR user_wifi_switch(void){
    uint8 wifi_mode = wifi_get_opmode();

    uint8 i;for(i=0;i<200;i++){os_delay_us(10000);}

    if(wifi_mode == SOFTAP_MODE){
        wifi_set_opmode(STATION_MODE);
    }
    else if(wifi_mode == STATION_MODE){
        wifi_set_opmode(SOFTAP_MODE);
    }
    else if(wifi_mode == STATIONAP_MODE){
        wifi_set_opmode(SOFTAP_MODE);
    }

#if SWITCH_REBOOT
    system_restart();
#endif
}

/** @} */
