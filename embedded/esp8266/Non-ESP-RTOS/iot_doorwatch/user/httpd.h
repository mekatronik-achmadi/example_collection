/*
              UNKNOWN PUBLIC LICENSE

 Copyright (C) 2019 Wira S.T. M.T.

 Currently no license applied because author liv in
 Indonesia, a country which doesn't really concern
 about digital content copyright.

 */

/**
 * @file    httpd.h
 * @brief   TCP Server header.
 *
 * @addtogroup Webserver
 * @{
 */

#ifndef HTTPD_H
#define HTTPD_H

/**
 * @brief TCP server port
 */
#define SERVER_LOCAL_PORT   3000

/**
 * @brief TCP server test response
 */
#define SERVER_RESP_TEST    0

/**
 * @brief Request string position
 */
#define STR_REQ     1

/**
 * @brief Data string position
 */
#define STR_DATA    2

/**
 * @brief Reboot after Wifi switching or not
 */
#define SWITCH_REBOOT 1

/**
 * @brief TCP server initialization
 * @param[in] Port Number
 */
void user_tcpserver_init(uint32 port);

/**
 * @brief Wifi Mode Switch
 * @details Chip will restarted after mode switching
 */
void user_wifi_switch(void);

#endif // HTTPD_H
/** @} */
