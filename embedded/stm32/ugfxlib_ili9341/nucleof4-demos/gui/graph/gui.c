#include "ch.h"
#include "hal.h"
#include "gfx.h"

#include "../gui.h"

static GHandle gh;

// A graph styling
static GGraphStyle myGraphStyle = {
    { GGRAPH_POINT_DOT, 0, Blue },          // Point
    { GGRAPH_LINE_NONE, 2, Gray },          // Line
    { GGRAPH_LINE_SOLID, 0, White },        // X axis
    { GGRAPH_LINE_SOLID, 0, White },        // Y axis
    { GGRAPH_LINE_DASH, 5, Gray, 50 },      // X grid
    { GGRAPH_LINE_DOT, 7, Yellow, 50 },     // Y grid
    GWIN_GRAPH_STYLE_POSITIVE_AXIS_ARROWS   // Flags
};

void gui_init(void){

    uint16_t i;

    // Create the graph window
    {
        GWindowInit wi;

        wi.show = TRUE;
        wi.x = wi.y = 0;
        wi.width = gdispGetWidth();
        wi.height = gdispGetHeight();
        gh = gwinGraphCreate(0, &wi);
    }

    // Set the graph origin and style
    gwinGraphSetOrigin(gh, gwinGetWidth(gh)/2, gwinGetHeight(gh)/2);
    gwinGraphSetStyle(gh, &myGraphStyle);
    gwinGraphDrawAxis(gh);

    // Modify the style
    gwinGraphStartSet(gh);
    myGraphStyle.point.color = Blue;
    gwinGraphSetStyle(gh, &myGraphStyle);

    // Draw a sine wave
    for(i = 0; i < gwinGetWidth(gh); i++) {
        gwinGraphDrawPoint(gh, i-gwinGetWidth(gh)/2, 80*sin(2*2*GFX_PI*i/180));
    }

    // Modify the style
    gwinGraphStartSet(gh);
    myGraphStyle.point.color = Green;
    gwinGraphSetStyle(gh, &myGraphStyle);

    // Draw a different sine wave
    for(i = 0; i < gwinGetWidth(gh)*5; i++) {
        gwinGraphDrawPoint(gh, i/5-gwinGetWidth(gh)/2, 95*sin(2*0.2*GFX_PI*i/180));
    }
}

void gui_test(void){
    uint16_t i;

    // Clear display
    gwinClear(gh);

    // Set the graph origin and style
    gwinGraphSetOrigin(gh, gwinGetWidth(gh)/2, gwinGetHeight(gh)/2);
    gwinGraphSetStyle(gh, &myGraphStyle);
    gwinGraphDrawAxis(gh);

    // Modify the style
    gwinGraphStartSet(gh);
    myGraphStyle.point.color = Blue;
    gwinGraphSetStyle(gh, &myGraphStyle);

    // Draw a sine wave
    for(i = 0; i < gwinGetWidth(gh); i++) {
        gwinGraphDrawPoint(gh, i-gwinGetWidth(gh)/2, 80*sin(2*2*GFX_PI*i/180));
    }

    // Modify the style
    gwinGraphStartSet(gh);
    myGraphStyle.point.color = Green;
    gwinGraphSetStyle(gh, &myGraphStyle);

    // Draw a different sine wave
    for(i = 0; i < gwinGetWidth(gh)*5; i++) {
        gwinGraphDrawPoint(gh, i/5-gwinGetWidth(gh)/2, 95*sin(2*0.2*GFX_PI*i/180));
    }
}

void gui_loop(void){

}
