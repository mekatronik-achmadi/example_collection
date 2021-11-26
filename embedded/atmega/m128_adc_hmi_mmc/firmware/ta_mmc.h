#ifndef TA_MMC_H
#define TA_MMC_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <avr/eeprom.h>
#include <avr/pgmspace.h>

#include "fatfs/ff.h"
#include "ta_led.h"

#define MMC_STR_LONG 32

/* SDMMC Hardware Abstraction Layer => fatfs/sdmm.h */
/* pinout for software based SPI

DO -> MISO / D11 -> PB.0
DI -> MOSI / D12 -> PB.1
CK -> SCK  / D13 -> PB.2
CS -> CS   / D4  -> PB.3

use ATMega128 powered by 3v3 only

*/

#define DO_INIT()					/* Initialize port for MMC DO as input */
#define DO			(PINB &	0x01)	/* Test for MMC DO ('H':true, 'L':false) */

#define DI_INIT()	DDRB  |= 0x02	/* Initialize port for MMC DI as output */
#define DI_H()		PORTB |= 0x02	/* Set MMC DI "high" */
#define DI_L()		PORTB &= 0xFD	/* Set MMC DI "low" */

#define CK_INIT()	DDRB  |= 0x04	/* Initialize port for MMC SCLK as output */
#define CK_H()		PORTB |= 0x04	/* Set MMC SCLK "high" */
#define	CK_L()		PORTB &= 0xFB	/* Set MMC SCLK "low" */

#define CS_INIT()	DDRB  |= 0x08	/* Initialize port for MMC CS as output */
#define	CS_H()		PORTB |= 0x08	/* Set MMC CS "high" */
#define CS_L()		PORTB &= 0xF7	/* Set MMC CS "low" */

void ta_mmc_WriteTest(void);

#endif // TA_MMC_H
