#include <ssd1306i2c.h>
#include <fonts.h>
#include <my_olcd.h>

#define BLINK_GPIO  GPIO_NUM_2

void setup(void){
  gpio_reset_pin(BLINK_GPIO);
  gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);
}

void loop(void){
    gpio_set_level(BLINK_GPIO, 0);
    ets_delay_us(500000);

    gpio_set_level(BLINK_GPIO, 1);
    ets_delay_us(500000);
}
