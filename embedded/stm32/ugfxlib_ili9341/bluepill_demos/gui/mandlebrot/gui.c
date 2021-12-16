#include "ch.h"
#include "hal.h"
#include "gfx.h"

#include "../gui.h"

static float zoom = 1.0f;
static float cx = -0.086f;
static float cy = 0.85f;

static void mandelbrot(float x1, float y1, float x2, float y2) {
    unsigned int i,j, width, height;
    uint16_t iter;
    color_t color;
    float fwidth, fheight;

    float sy = y2 - y1;
    float sx = x2 - x1;
    const int MAX = 512;

    width = (unsigned int)gdispGetWidth();
    height = (unsigned int)gdispGetHeight();
    fwidth = width;
    fheight = height;

    for(i = 0; i < width; i++) {
        for(j = 0; j < height; j++) {
            float cy = j * sy / fheight + y1;
            float cx = i * sx / fwidth + x1;
            float x=0.0f, y=0.0f, xx=0.0f, yy=0.0f;
            for(iter=0; iter <= MAX && xx+yy<4.0f; iter++) {
                xx = x*x;
                yy = y*y;
                y = 2.0f*x*y + cy;
                x = xx - yy + cx;
            }
            //color = ((iter << 8) | (iter&0xFF));
            color = RGB2COLOR(iter<<7, iter<<4, iter);
            gdispDrawPixel(i, j, color);
        }
    }
}

void gui_init(void){

}

void gui_test(void){

}

void gui_loop(void){
    chThdSleepMilliseconds(100);

    mandelbrot(-2.0f*zoom+cx, -1.5f*zoom+cy, 2.0f*zoom+cx, 1.5f*zoom+cy);

    zoom *= 0.7f;
    if(zoom <= 0.00001f) zoom = 1.0f;
}
