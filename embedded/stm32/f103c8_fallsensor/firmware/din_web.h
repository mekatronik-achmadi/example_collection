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
 * @file    din_web.h
 * @brief   Web server routine header.
 *
 * @addtogroup Communication
 * @{
 */

#ifndef DIN_WEB_H
#define DIN_WEB_H

#include "ch.h"
#include "hal.h"

#include "chprintf.h"
#include "shell.h"

#include "math.h"
#include "stdlib.h"
#include "stdio.h"

#include "din_adc.h"
#include "din_mpu.h"
#include "din_fuzzy.h"

/**
 * @brief   Notification Message.
 */
#define SERVER_NOTIF TRUE

/*
 * Definisi ukuran standar alokasi memori untuk thread dan shell
 */
#define SHELL_WA_SIZE   THD_WORKING_AREA_SIZE(512)
#define THREAD_WA_SIZE  THD_WORKING_AREA_SIZE(128)

void d_web_start(void);
void d_web_term(void);
void d_web_setup(void);
void d_web_data(void);

#endif // DIN_WEB_H
/** @} */
