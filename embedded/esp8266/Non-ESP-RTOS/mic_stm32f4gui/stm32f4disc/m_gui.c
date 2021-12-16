/**
 * @file   m_gui.c
 * @brief  GUI handler code
 *
 * @addtogroup M_GUI
 * @{
 */

#include "m_gui.h"

point vdata[N_DISPDATA];
char txt0[16];

/**
 * @brief   data array zero function.
 */
void m_data_zero(void){
    u_int16_t i;

    for(i=0;i<N_DISPDATA;i++){
       vdata[i].x = i;
       vdata[i].y = 0;
    }
}

/**
 * @brief   data array shift function.
 */
void m_data_shift(void){
    u_int16_t i;

    #if LEFT_TO_RIGHT
        for(i=0;i<N_DISPDATA-1;i++){
            vdata[i].y = vdata[i+1].y;
        }
    #else
        for(i=N_DISPDATA-1;i>0;i--){
            vdata[i].y = vdata[i-1].y;
        }
    #endif
}

/**
 * @brief   prepare data display.
 */
void m_data_disp(void){
    uint16_t val;

    m_data_shift();
    val = rand() % 100;
#if LEFT_TO_RIGHT
   vdata[N_DISPDATA-1].y = val;
#else
   vdata[0].y = val;
#endif
}

/**
 * @brief   prepare data display.
 */
void m_data_set(uint16_t val){
    m_data_shift();
#if LEFT_TO_RIGHT
   vdata[N_DISPDATA-1].y = val;
#else
   vdata[0].y = val;
#endif
}


/**
 * @brief   overall graph object variable.
 */
static GGraphObject g;

/**
 * @brief   line graph object variable.
 */
static GGraphStyle GraphLine = {
    { GGRAPH_POINT_DOT, 10, White },          // Point
    { GGRAPH_LINE_SOLID, 10, White },          // Line
    { GGRAPH_LINE_SOLID, 0, Gray },        // X axis
    { GGRAPH_LINE_SOLID, 0, Gray },        // Y axis
    { GGRAPH_LINE_DOT, 5, Gray, 50 },      // X grid
    { GGRAPH_LINE_DOT, 5, Gray, 50 },     // Y grid
    GWIN_GRAPH_STYLE_POSITIVE_AXIS_ARROWS   // Flags
};

/*===========================================================================*/
/* GRAPH DRAW                                                                */
/*===========================================================================*/

/**
 * @brief   graph window variable.
 */
GHandle gh;

/**
 * @brief   console window variable.
 */
GHandle gc;

/**
 * @brief   gui loop routine
 */
static void m_gui_routine(void){
    gwinGraphStartSet(gh);
    gwinGraphDrawAxis(gh);

#if DRAW_RAND
    m_data_disp();
#endif
    gwinGraphDrawPoints(gh, vdata, sizeof(vdata)/sizeof(vdata[0]));
    gwinPrintf(gc, txt0);

    gfxSleepMilliseconds(25);

    gwinClear(gh);
    gwinClear(gc);
}

static THD_WORKING_AREA(waDraw, 256);
/**
 * @brief   Main Draw routine.
 */
static THD_FUNCTION(thdDraw, arg) {

    font_t	    gfont;

    (void)arg;
    chRegSetThreadName("drawgraph");

    gfont = gdispOpenFont("UI2");
    gwinSetDefaultFont(gfont);

    {
      GWindowInit wi;
      gwinClearInit(&wi);

      wi.show = true;

      wi.x = 0;
      wi.y = 0;
      wi.width = gdispGetWidth();
      wi.height = 7*(gdispGetHeight()/8);
      gh = gwinGraphCreate(&g, &wi);

      wi.x = 0;
      wi.y = 7*(gdispGetHeight()/8);
      wi.width = gdispGetWidth();
      wi.height = gdispGetHeight()/8;

      gc = gwinConsoleCreate(0, &wi);

    }

  gwinGraphSetOrigin(gh, 0, 0);
  gwinGraphSetStyle(gh, &GraphLine);

  gwinClear(gh);
  gwinGraphStartSet(gh);
  gwinGraphDrawAxis(gh);

  gwinClear(gc);

  while (1) {
     m_gui_routine();
  }
}

/**
 * @brief   gui start function.
 */
void m_gui_start(void){
    gdispSetOrientation(GDISP_ROTATE_270);
    m_data_zero();
    chsnprintf(txt0,16,"no data");
    chThdCreateStatic(waDraw, sizeof(waDraw),	NORMALPRIO, thdDraw, NULL);

    gfxSleepMilliseconds(500);
}
/** @} */
