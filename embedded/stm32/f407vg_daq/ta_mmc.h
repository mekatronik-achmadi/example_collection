#ifndef TA_MMC_H
#define TA_MMC_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "ch.h"
#include "hal.h"
#include "chprintf.h"
#include "memstreams.h"
#include "chstreams.h"
#include "evtimer.h"
#include "chvt.h"

#include "ff.h"
#include "ffconf.h"

#define buffer_size 16

FRESULT f_append (FIL* fp,const char* path);
FRESULT scan_files(BaseSequentialStream *chp, char *path);

void Mmc_Mount(void);
void Mmc_Unmount(void);
void Mmc_Init(void);

#endif // TA_MMC_H
