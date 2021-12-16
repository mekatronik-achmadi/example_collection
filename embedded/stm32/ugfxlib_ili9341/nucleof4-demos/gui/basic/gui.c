#include "ch.h"
#include "hal.h"
#include "gfx.h"

#include "../gui.h"

void gui_init(void){

    coord_t		width, height;
    coord_t		i, j;

    // Initialize and clear the display
    gfxInit();

    // Get the screen size
    width = gdispGetWidth();
    height = gdispGetHeight();

    // Code Here
    gdispDrawBox(10, 10, width/2, height/2, Yellow);
    gdispFillArea(width/2, height/2, width/2-10, height/2-10, Blue);
    gdispDrawLine(5, 30, width-50, height-40, Red);

    for(i = 5, j = 0; i < width && j < height; i += 7, j += i/20) gdispDrawPixel(i, j, White);
}

void gui_test(void){

}

void gui_loop(void){

}
