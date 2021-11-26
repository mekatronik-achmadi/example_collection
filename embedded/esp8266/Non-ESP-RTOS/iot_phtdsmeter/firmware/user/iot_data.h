/*
              UNKNOWN PUBLIC LICENSE

 Copyright (C) 2020 Achmadi S.T. M.T.

 Currently no license applied because author liv in
 Indonesia, a country which doesn't really concern
 about digital content copyright.

 */

/**
 * @file    iot_data.h
 * @brief   Main data processing header.
 *
 * @addtogroup IoT
 * @{
 */
#ifndef IOT_DATA_H
#define IOT_DATA_H

#define SCALE_PH    1
#define SCALE_NTC   1
#define SCALE_T     1
#define SCALE_TDS   1

#define OFSET_PH    0
#define OFSET_NTC   0
#define OFSET_T     0
#define OFSET_TDS   0

#include <stdint.h>

void run_loop(uint8_t interval);

#endif // IOT_DATA_H
/** @} */
