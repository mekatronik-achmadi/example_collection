/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.org/license.html
 */

#ifndef _GDISP_LLD_CONFIG_H
#define _GDISP_LLD_CONFIG_H
#include "gfxconf.h"
#if GFX_USE_GDISP

/*===========================================================================*/
/* Driver hardware support.                                                  */
/*===========================================================================*/

#define GDISP_HARDWARE_STREAM_WRITE		FALSE
#define GDISP_HARDWARE_STREAM_READ		FALSE
#define GDISP_HARDWARE_CONTROL          FALSE
#define GDISP_HARDWARE_DRAWPIXEL        TRUE
#define GDISP_LLD_PIXELFORMAT			GDISP_PIXELFORMAT_MONO
#define GDISP_HARDWARE_FILLS            FALSE

#define KS0108_NEED_READ                FALSE
#define KS0108_HAS_RESET                FALSE
#define KS0108_NEED_BACKLIGHT           FALSE
#define KS0108_NEED_PWMBACKLIGHT        FALSE
#define KS0108_NOP_DLY                  TRUE  //doesn't work for me without!
// KS0108 Commands
#define KS0108_CHIP1_ON                0x003F
#define KS0108_CHIP2_ON                0x013F
#define KS0108_DISP1START              0x00C0
#define KS0108_DISP2START              0x01C0
#define KS0108_DISP1OFF                0x003E
#define KS0108_DISP2OFF                0x013E
#define KS0108_SET_ADDR                0x0040
#define KS0108_SET_PAGE                0x00B8
#define KS0108_BUSY (palReadLine(lcdpins.D[7]))
#endif	/* GFX_USE_GDISP */

#endif	/* _GDISP_LLD_CONFIG_H */
