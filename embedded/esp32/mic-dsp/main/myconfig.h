/**
 * @file    myconfig.h
 * @brief   Global config header.
 *
 * @addtogroup Main
 * @{
 */

#ifndef _MY_CONFIG_H_
#define _MY_CONFIG_H_

/**
 * @brief LED Blink pin
 * 
 */
#define BLINK_GPIO  2

/**
 * @brief LED Blink delay in ms
 * 
 */
#define BLINK_DELAY 100

/**
 * @brief UART Port number
 * 
 */
#define CONFIG_ESP_CONSOLE_UART_NUM 0

/**
 * @brief Whether use prompt or not
 * 
 */
#define UART_USE_PROMPT 1

#endif

/** @} */
