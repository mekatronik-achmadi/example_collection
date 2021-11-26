/*
              UNKNOWN PUBLIC LICENSE

 Copyright (C) 2019 Wira S.T. M.T.

 Currently no license applied because author liv in
 Indonesia, a country which doesn't really concern
 about digital content copyright.

 */

/**
 * @file    rwflash.h
 * @brief   Flash Memory header.
 *
 * @addtogroup Storage
 * @{
 */

#ifndef RWFLASH_H
#define RWFLASH_H

/**
 * @brief Flash memory storage start address
 */
#define FLASH_START_ADDR    0x80

/**
 * @brief Configs Flash memory start address
 */
#define CONFIGS_FLASH_ADDR  FLASH_START_ADDR

/**
 * @brief Configs string length
 */
#define FLASH_CONFIGS_LEN   64

/**
 * @brief Configs string numbers
 */
#define FLASH_CONFIGS_NUM   4

/**
 * @brief Configs string size
 * @details Should not filled by out of size string and
 *          no more than FLASH_CONFIGS_LEN/FLASH_CONFIGS_NUM
 */
#define FLASH_STRING_BUFF   12

/**
 * @brief UserID string position
 */
#define FLASH_USERID 1

/**
 * @brief DeviceID string position
 */
#define FLASH_DEVSID 2

/**
 * @brief Flash write integer
 * @param[in] Write Address
 * @param[in] Integer input array
 */
void rwflash_int_write(uint16 sec,uint16 *src);

/**
 * @brief Flash read integer
 * @param[in] read Address
 * @param[out] Integer output array
 */
void rwflash_int_read(uint16 sec,uint16 *des);

/**
 * @brief Flash write string
 * @param[in] Write Address
 * @param[in] String input
 */
void rwflash_str_write(uint16 sec,char *src);

/**
 * @brief Flash read string
 * @param[in] Read Address
 * @param[out] String output
 */
void rwflash_str_read(uint16 sec,char *des);

/**
 * @brief Flash configs string parse
 * @details Split String by ","
 * @param[in] String Input.
 * @param[out] Desired part string output
 * @param[in] Position of desired string
 */
void rwflash_conf_parse(char *strIN, char *strOUT, uint8 num);

#endif // RWFLASH_H
/** @} */
