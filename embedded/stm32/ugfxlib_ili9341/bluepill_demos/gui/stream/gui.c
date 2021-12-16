#include "ch.h"
#include "hal.h"
#include "gfx.h"

#include "../gui.h"

#define BALLCOLOR1		Red
#define BALLCOLOR2		Yellow
#define WALLCOLOR		HTML2COLOR(0x303030)
#define BACKCOLOR		HTML2COLOR(0xC0C0C0)
#define flooorCOLOR		HTML2COLOR(0x606060)
#define SHADOWALPHA		(255-255*0.2)

static coord_t		width, height, x, y, radius, ballx, bally, dx, flooor;
static coord_t		minx, miny, maxx, maxy;
static coord_t		ballcx, ballcy;
static color_t		colour;
static float		ii, spin, dy, spinspeed, h, f, g;

void gui_init(void){

    width = gdispGetWidth();
    height = gdispGetHeight();

    radius=height/5+height%2+1;	// The ball radius
    ii = 1.0/radius;			// radius as easy math
    flooor=height/5-1;			// flooor position
    spin=0.0;					// current spin angle on the ball
    spinspeed=0.1;				// current spin speed of the ball
    ballx=width/2;				// ball x position (relative to the ball center)
    bally=height/4;				// ball y position (relative to the ball center)
    dx=.01*width;				// motion in the x axis
    dy=0.0;						// motion in the y axis
    ballcx = 12*radius/5;		// ball x diameter including the shadow
    ballcy = 21*radius/10;		// ball y diameter including the shadow


    minx = miny = 0; maxx = width; maxy = height;		// The clipping window for this frame.
}

void gui_test(void){

}

void gui_loop(void){
    chThdSleepMicroseconds(100);

    gdispStreamStart(minx, miny, maxx-minx, maxy-miny);
    for (y=miny; h = (bally-y)*ii, y<maxy; y++) {
        for (x=minx; x < maxx; x++) {
            g=(ballx-x)*ii;
            f=-.3*g+.954*h;
            if (g*g < 1-h*h) {
                /* The inside of the ball */
                if ((((int)(9-spin+(.954*g+.3*h)*invsqrt(1-f*f))+(int)(2+f*2))&1))
                    colour = BALLCOLOR1;
                else
                    colour = BALLCOLOR2;
            } else {
                // The background (walls and flooor)
                if (y > height-flooor) {
                    if (x < height-y || height-y > width-x)
                        colour = WALLCOLOR;
                    else
                        colour = flooorCOLOR;
                } else if (x<flooor || x>width-flooor)
                    colour = WALLCOLOR;
                else
                    colour = BACKCOLOR;

                // The ball shadow is darker
                if (g*(g+.4)+h*(h+.1) < 1)
                    colour = gdispBlendColor(colour, Black, SHADOWALPHA);
            }
            gdispStreamColor(colour);	/* pixel to the LCD */
        }
    }
    gdispStreamStop();

    // Force a display update if the controller supports it
    gdispFlush();

    // Calculate the new frame size (note this is a drawing optimisation only)
    minx = ballx - radius; miny = bally - radius;
    maxx = minx + ballcx; maxy = miny + ballcy;
    if (dx > 0) maxx += dx; else minx += dx;
    if (dy > 0) maxy += dy; else miny += dy;
    if (minx < 0) minx = 0;
    if (maxx > width) maxx = width;
    if (miny < 0) miny = 0;
    if (maxy > height) maxy = height;

    // Motion
    spin += spinspeed;
    ballx += dx; bally += dy;
    dx = ballx < radius || ballx > width-radius ? spinspeed=-spinspeed,-dx : dx;
    dy = bally > height-1.75*flooor ? -.04*height : dy+.002*height;
}
