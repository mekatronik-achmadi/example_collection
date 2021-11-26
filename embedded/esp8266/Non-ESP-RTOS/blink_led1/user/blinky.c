#include "ets_sys.h"
#include "osapi.h"
#include "gpio.h"
#include "driver/gpio16.h"
#include "os_type.h"
#include "user_config.h"

#include "blinky.h"

os_timer_t blinky_timer;
static uint8_t led_on = 0;

void blinky_timer_handler(void *prv){
  	if (led_on==1) {
  		gpio_output_set(0, (1 << 2), 0, 0);
    		gpio16_output_set(1);
    		led_on=0;
  	}
  	else {
    		gpio_output_set((1 << 2), 0, 0, 0);
    		gpio16_output_set(0);
    		led_on=1;
  	}
}


