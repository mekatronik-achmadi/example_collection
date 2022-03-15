/**
 * @file input.h
 * @brief Input handler header
 *
 * @addtogroup Input
 * @{
 */

#ifndef _INPUT_H_
#define _INPUT_H_

#include <stdint.h>
#include "lcd_draw.h"

/**
 * @brief Maximum character to input
 *
 */
#define MAX_INPUT_LEN LCD_LINE_NUMS*LCD_BUFFER_LEN

void bt_Inputs(uint8_t* spp_data_ind);
void key_Inputs(char keynum);
void inputsInit(void);

#endif

/** @} */