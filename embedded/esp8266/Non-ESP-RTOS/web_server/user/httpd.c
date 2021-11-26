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

    struct station_config stationConf;

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

        if(os_strcmp("restart",strReq)==0){
            http_resp(pespconn,200,NULL);
            uint8 i;for(i=0;i<100;i++){os_delay_us(10000);}
            system_restart();
        }
        else if(os_strcmp("help",strReq)==0){
            http_resp(pespconn,200,(char*)help_html);
        }
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
