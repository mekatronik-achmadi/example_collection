/**
 * This file has a different license to the rest of the uGFX system.
 * You can copy, modify and distribute this file as you see fit.
 * You do not need to publish your source modifications to this file.
 * The only thing you are not permitted to do is to relicense it
 * under a different license.
 */

/**
 * Copy this file into your project directory and rename it as gfxconf.h
 * Edit your copy to turn on the uGFX features you want to use.
 * The values below are the defaults. You should delete anything
 * you are leaving as default.
 *
 * Please use spaces instead of tabs in this file.
 */

#ifndef _GFXCONF_H
#define _GFXCONF_H

/* The operating system to use. One of these must be defined - preferably in your Makefile */
#define GFX_USE_OS_CHIBIOS      TRUE
#define GFX_MEM_LT64K           FALSE

/* GFX sub-systems to turn on */
#define GFX_USE_GDISP			TRUE
#define GFX_USE_GWIN			TRUE
#define GFX_USE_GMISC			TRUE
#define GFX_USE_GTIMER          TRUE
#define GFX_USE_GQUEUE          TRUE

/* Features for the GDISP sub-system. */
#define GDISP_NEED_VALIDATION	TRUE
#define GDISP_NEED_CLIP			TRUE
#define GDISP_NEED_TEXT			TRUE
#define GDISP_NEED_MULTITHREAD	TRUE
#define GDISP_NEED_CONTROL      TRUE
#define GDISP_INCLUDE_FONT_UI2	TRUE
#define GDISP_NEED_STARTUP_LOGO	FALSE

/* Features for the GWIN subsystem. */
#define GWIN_NEED_WINDOWMANAGER	TRUE
#define GWIN_NEED_GRAPH			TRUE
#define GWIN_NEED_CONSOLE		TRUE
    #define GWIN_CONSOLE_ESCSEQ             TRUE
    #define GWIN_CONSOLE_USE_HISTORY        TRUE
    #define GWIN_CONSOLE_HISTORY_AVERAGING	TRUE
    #define GWIN_CONSOLE_HISTORY_ATCREATE	TRUE

/* Features for the GQUEUE subsystem. */
#define GQUEUE_NEED_ASYNC       TRUE

/* Features for the GMISC subsystem. */
#define GMISC_NEED_FASTTRIG         TRUE
#define GMISC_NEED_MATRIXFLOAT2D    TRUE
#define GMISC_NEED_MATRIXFIXED2D    TRUE

#endif /* _GFXCONF_H */
