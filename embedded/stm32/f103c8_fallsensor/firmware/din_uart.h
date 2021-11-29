/*
              DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE

 Copyright (C) 2018 Achmadi S.T.

 Everyone is permitted to copy and distribute verbatim or modified
 copies of this license document, and changing it is allowed as long
 as the name is changed.

            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
   TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION

  0. You just DO WHAT THE FUCK YOU WANT TO.
 */

/**
 * @file    din_uart.h
 * @brief   UART-1 starting header.
 *
 * @addtogroup Communication
 * @{
 */

#ifndef DIN_UART_H
#define DIN_UART_H

#include "ch.h"
#include "hal.h"

#include "chprintf.h"
#include "shell.h"

#include "math.h"
#include "stdlib.h"
#include "stdio.h"

#define UART_INFO   TRUE

void d_uart_start(void);
void d_uart_info(void);

#endif // DIN_UART_H
/** @} */
