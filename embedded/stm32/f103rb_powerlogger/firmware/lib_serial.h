#ifndef LIB_SERIAL_H
#define LIB_SERIAL_H

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdlib.h>
#include <math.h>

#include "ch.h"
#include "hal.h"

#include "shell.h"
#include "chprintf.h"
#include "memstreams.h"
#include "evtimer.h"

#define SHELL_WA_SIZE   THD_WA_SIZE(2048)

void Serial_Setup(void);
void Shell_Setup(void);

#endif // LIB_SERIAL_H
