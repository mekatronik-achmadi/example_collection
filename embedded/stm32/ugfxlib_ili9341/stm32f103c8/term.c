#include "gfx.h"

#include "chprintf.h"

#include "term.h"

/**
 * @brief   object for console window
 */
static GHandle     gc;

void term_start(void){

    font_t	font;
    font = gdispOpenFont("UI2");
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

void term_clear(void){
    gwinClear(gc);
}

void term_string(char *str){
    gwinPrintf(gc, str);
}

void term_strbuff(char *str){
    char strBuffer[STR_BUFFER_SIZE];

    chsnprintf(strBuffer,STR_BUFFER_SIZE,"%s\n",str);
    gwinPrintf(gc, strBuffer);
}
