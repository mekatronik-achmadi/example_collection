/*
              UNKNOWN PUBLIC LICENSE

 Copyright (C) 2019 Wira S.T. M.T.

 Currently no license applied because author liv in
 Indonesia, a country which doesn't really concern
 about digital content copyright.

 */

/**
 * @file    wifi_sap.h
 * @brief   Wifi SoftAP header.
 *
 * @addtogroup Network
 * @{
 */

#ifndef WIFI_SAP_H
#define WIFI_SAP_H

/**
 * @brief IP Base First
 */
#define IP_BASE0 192

/**
 * @brief IP Base Second
 */
#define IP_BASE1 168

/**
 * @brief IP Address Class
 */
#define IP_CLASS 4

/**
 * @brief IP Address ID and Gateway
 */
#define IP_GTWAY 1

/**
 * @brief DHCP Address Range Start
 */
#define IP_START 100

/**
 * @brief DHCP Address Range End
 */
#define IP_END   105

/**
 * @brief Wifi SoftAP Initialization
 */
void user_wifi_softap_init(void);

#endif // WIFI_SAP_H
