#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "ch.h"
#include "hal.h"
#include "gfx.h"

#include "chprintf.h"
#include "stdint.h"

#include "sensor.h"
#include "data.h"

extern adcsample_t dV;

extern SerialUSBDriver SDU1;

/**
 * @brief   data point array for display.
 */
point vdata[N_DATA];

/**
 * @brief   set data array to zero.
 *
 */
static void dataZeroing(void){
    uint16_t i;

    for(i=0;i<N_DATA;i++){
       vdata[i].x = i;
       vdata[i].y = 0;
    }
}

/**
 * @brief   set data shifting by 1.
 * @pre     @p LEFT_TO_RIGHT must defined.
 *
 */
static void dataShifting(void){
    uint16_t i;

#if LEFT_TO_RIGHT
    for(i=0;i<N_DATA-1;i++){
        vdata[i].y = vdata[i+1].y;
    }
#else
    for(i=N_DATA-1;i>0;i--){
        vdata[i].y = vdata[i-1].y;
    }
#endif
}

#if UPDATE_DATA_AUTO
static THD_WORKING_AREA(waData, 256);
static THD_FUNCTION(thdData, arg) {

    (void)arg;

    chRegSetThreadName("data update");
    while (true) {
        dataUpdate();
        chThdSleepMilliseconds(100);
    }
}
#endif

void dataInit(void){
    dataZeroing();

#if UPDATE_DATA_AUTO
    chThdCreateStatic(waData, sizeof(waData), NORMALPRIO, thdData, NULL);
#endif
}

void dataUpdate(void){
    dataShifting();

#if LEFT_TO_RIGHT
    vdata[N_DATA-1].y = DATA_SCALE * senTemp;
#else
    vdata[0].y = DATA_SCALE * dV;
#endif

    chprintf((BaseSequentialStream *)&SDU1, "%i\r\n",dV);
}
