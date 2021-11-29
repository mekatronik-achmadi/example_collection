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
 * @file    din_fuzzy.h
 * @brief   Fuzzy Logic header.
 *
 * @addtogroup Fuzzy
 * @{
 */

#ifndef DIN_FUZZY_H
#define DIN_FUZZY_H

#include "ch.h"
#include "hal.h"

#include "math.h"
#include "stdlib.h"
#include "stdio.h"

/**
 * @brief  Fuzzy rule array size
 */
#define RULE_SIZE 9

/**
 * @brief  Last Fuzzy Logic response at Low
 */
#define OUT_BIASA 0

/**
 * @brief  Last Fuzzy Logic response at Mid
 */
#define OUT_AWAS  1

/**
 * @brief  Last Fuzzy Logic response at High
 */
#define OUT_JATUH 2

u_int8_t d_fuzzy(float vmag, float vmic);

#endif // DIN_FUZZY_H
/** @} */
