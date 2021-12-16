#include "gfx.h"
#include "math.h"

#include "grafik.h"

// Graph styling
static GGraphStyle GraphStyle = {
    { GGRAPH_POINT_DOT, 0, Blue },          // Point
    { GGRAPH_LINE_NONE, 2, Gray },          // Line
    { GGRAPH_LINE_SOLID, 0, White },        // X axis
    { GGRAPH_LINE_SOLID, 0, White },        // Y axis
    { GGRAPH_LINE_DASH, 5, Gray, 50 },      // X grid
    { GGRAPH_LINE_DOT, 7, Yellow, 50 },     // Y grid
    GWIN_GRAPH_STYLE_POSITIVE_AXIS_ARROWS   // Flags
};

// Window handler
static GHandle gh;

void draw_axisplanes(void){
	// Create the graph window
    {
        GWindowInit wi;
        gwinClearInit(&wi);
        wi.show = TRUE;
        wi.x = wi.y = 0;
        wi.width = gdispGetWidth();
        wi.height = gdispGetHeight();
        gh = gwinGraphCreate(0, &wi);
    }
    
    // Set the graph origin and style
    gwinGraphSetOrigin(gh, gwinGetWidth(gh)/2, gwinGetHeight(gh)/2);
    gwinGraphSetStyle(gh, &GraphStyle);
    gwinGraphDrawAxis(gh);
}

void draw_example(void){
    uint16_t    i;
    
    // Clear screen
    gwinClear(gh);
    
    // Set the graph origin and style
    gwinGraphSetOrigin(gh, gwinGetWidth(gh)/2, gwinGetHeight(gh)/2);
    gwinGraphSetStyle(gh, &GraphStyle);
    gwinGraphDrawAxis(gh);
    
    // Modify the style
    gwinGraphStartSet(gh);
    GraphStyle.point.color = Blue;
    gwinGraphSetStyle(gh, &GraphStyle);
    
    // Draw a sine wave
    for(i = 0; i < gwinGetWidth(gh); i++) {
        gwinGraphDrawPoint(gh, i-gwinGetWidth(gh)/2, 80*sin(2*2*GFX_PI*i/180));
    }

    // Modify the style
    gwinGraphStartSet(gh);
    GraphStyle.point.color = Green;
    gwinGraphSetStyle(gh, &GraphStyle);

    // Draw a different sine wave
    for(i = 0; i < gwinGetWidth(gh)*5; i++) {
        gwinGraphDrawPoint(gh, i/5-gwinGetWidth(gh)/2, 95*sin(2*0.2*GFX_PI*i/180));
    }    
}
