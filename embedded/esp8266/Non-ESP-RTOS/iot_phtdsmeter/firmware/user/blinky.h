/*
              UNKNOWN PUBLIC LICENSE

 Copyright (C) 2020 Achmadi S.T. M.T.

 Currently no license applied because author liv in
 Indonesia, a country which doesn't really concern
 about digital content copyright.

 */

/**
 * @file    blink.c
 * @brief   LED Indicator header.
 *
 * @addtogroup IO
 * @{
 */

#ifndef BLINKY_H
#define BLINKY_H

void blinky_init(void);
void blinky_loop_run(void);
void blinky_loop_stop(void);
void blinky_wifi_connect(void);
void blinky_wifi_disconnect(void);

#endif // BLINKY_H
/** @} */
