#ifndef TA_SHELL_H
#define TA_SHELL_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "ch.h"
#include "hal.h"
#include "chprintf.h"
#include "memstreams.h"
#include "chstreams.h"
#include "shell.h"

#include "ta_usbcfg.h"
#include "ta_utama.h"
#include "ta_mmc.h"
#include "ta_dac.h"
#include "ta_uart.h"

#define SHELL_WA_SIZE   THD_WORKING_AREA_SIZE(4096)
#define TEST_WA_SIZE    THD_WORKING_AREA_SIZE(256)

void Shell_Init(void);
void Shell_Run(void);

#endif // TA_SHELL_H
