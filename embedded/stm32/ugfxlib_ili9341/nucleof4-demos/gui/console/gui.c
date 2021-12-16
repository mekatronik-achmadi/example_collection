#include "ch.h"
#include "hal.h"
#include "gfx.h"

#include "chprintf.h"

#include "../gui.h"

#define STR_BUFFER_SIZE 64

static GHandle     gc;

void gui_init(void){

/*
 * Font List
 * UI2, fixed_5x8, fixed_7x14, DejaVuSans10, DejaVuSans12_aa
 */
    font_t	font;
    font = gdispOpenFont("fixed_7x14");
    gwinSetDefaultFont(font);

    {
        GWindowInit wi;

        gwinClearInit(&wi);
        wi.show = TRUE;
        wi.x = 0;wi.y = 0;
        wi.width =  gdispGetWidth();
        wi.height = gdispGetHeight();
        gc = gwinConsoleCreate(0, &wi);
    }

    gwinSetColor(gc, White);
    gwinSetBgColor(gc, Black);

    gwinClear(gc);
    gwinPrintf(gc, "System Ready \n");
}

void gui_test(void){

    char strBuffer[STR_BUFFER_SIZE];

    chsnprintf(strBuffer,STR_BUFFER_SIZE,"\r\n");
    gwinPrintf(gc,strBuffer);

    chsnprintf(strBuffer,STR_BUFFER_SIZE,"Kernel: %s\r\n", CH_KERNEL_VERSION);
    gwinPrintf(gc,strBuffer);
#ifdef PORT_COMPILER_NAME
    chsnprintf(strBuffer,STR_BUFFER_SIZE,"Compiler: %s\r\n", PORT_COMPILER_NAME);
    gwinPrintf(gc,strBuffer);
#endif
    chsnprintf(strBuffer,STR_BUFFER_SIZE,"Architecture: %s\r\n", PORT_ARCHITECTURE_NAME);
    gwinPrintf(gc,strBuffer);
#ifdef PORT_CORE_VARIANT_NAME
    chsnprintf(strBuffer,STR_BUFFER_SIZE,"Core Variant: %s\r\n", PORT_CORE_VARIANT_NAME);
    gwinPrintf(gc,strBuffer);
#endif
#ifdef PORT_INFO
    chsnprintf(strBuffer,STR_BUFFER_SIZE,"Port Info: %s\r\n", PORT_INFO);
    gwinPrintf(gc,strBuffer);
#endif
#ifdef PLATFORM_NAME
    chsnprintf(strBuffer,STR_BUFFER_SIZE,"Platform: %s\r\n", PLATFORM_NAME);
    gwinPrintf(gc,strBuffer);
#endif
#ifdef BOARD_NAME
    chsnprintf(strBuffer,STR_BUFFER_SIZE,"Board: %s\r\n", BOARD_NAME);
    gwinPrintf(gc,strBuffer);
#endif
#ifdef __DATE__
#ifdef __TIME__
    chsnprintf(strBuffer,STR_BUFFER_SIZE,"Build time: %s%s%s\r\n", __DATE__, " - ", __TIME__);
    gwinPrintf(gc,strBuffer);
#endif
#endif
#ifdef CH_LICENSE_TYPE_STRING
    chsnprintf(strBuffer,STR_BUFFER_SIZE,"License: %s\r\n", CH_LICENSE_TYPE_STRING);
    gwinPrintf(gc,strBuffer);
#endif
}

void gui_loop(void){

}
