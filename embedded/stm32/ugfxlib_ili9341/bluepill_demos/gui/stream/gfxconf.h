/**
 * This file has a different license to the rest of the GFX system.
 * You can copy, modify and distribute this file as you see fit.
 * You do not need to publish your source modifications to this file.
 * The only thing you are not permitted to do is to relicense it
 * under a different license.
 */

#ifndef _GFXCONF_H
#define _GFXCONF_H

/* The operating system to use. One of these must be defined - preferably in your Makefile */
#define GFX_USE_OS_CHIBIOS      TRUE
#define GFX_MEM_LT64K           FALSE

/* GFX sub-systems to turn on */
#define GFX_USE_GDISP			TRUE
#define GFX_USE_GMISC			TRUE

/* Features for the GDISP sub-system. */
#define GDISP_NEED_VALIDATION	TRUE
#define GDISP_NEED_STREAMING	TRUE

/* Features for the GMISC subsystem. */
#define GMISC_NEED_FASTTRIG         TRUE
#define GMISC_NEED_MATRIXFLOAT2D    TRUE
#define GMISC_NEED_MATRIXFIXED2D    TRUE
#define GMISC_NEED_INVSQRT			TRUE

/* Additional settings for display */
#define GDISP_NEED_CONTROL      TRUE
#define GDISP_NEED_MULTITHREAD	TRUE
#define GDISP_NEED_STARTUP_LOGO	TRUE
#define GDISP_DEFAULT_ORIENTATION GDISP_ROTATE_LANDSCAPE

#endif /* _GFXCONF_H */
