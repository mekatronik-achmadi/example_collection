#include "ta_led.h"

uint8_t cobavar = 200;

void tunda_us(unsigned int time){
    unsigned int i;

    for(i=0;i<time;i++){
    _delay_us(1);
    };
    return;
}

void tunda_ms(unsigned int time){
    unsigned int i;

    for(i=0;i<time;i++){
    _delay_ms(1);
    };
    return;
}

void ta_led_LEDInit(void){
    DDR_LED |= (1 << LED_1);
    PORT_LED |= (1 << LED_1);
}

void ta_led_LEDTest(void){
    PORT_LED ^= (1 << LED_1);
    tunda_ms(TUNDA);
}
