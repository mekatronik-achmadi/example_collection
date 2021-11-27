#ifndef LIB_MMC_SPI_H
#define LIB_MMC_SPI_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "ch.h"
#include "hal.h"
#include "chprintf.h"
#include "ff.h"

#define MMC_SPI_OK 0
#define MMC_SPI_FAIL 1
#define MMC_SPI_ERROR 2

#define buffer_size 16

FRESULT f_append (FIL* fp,const char* path);

void Mmc_Init(void);
void Mmc_Check(void);
void Mmc_Example(void);
void Mmc_Reload(void);

#endif // LIB_MMC_SPI_H
