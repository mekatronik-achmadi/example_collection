#include "ets_sys.h"
#include "osapi.h"
#include "gpio.h"
#include "driver/gpio16.h"
#include "os_type.h"
#include "user_config.h"

#define SERIALBAUD 9600

static os_timer_t blinky_timer;
static void blinky_timer_handler(void *prv);
static uint8_t led_on = 0;

static os_timer_t serial_timer;
static void serial_timer_handler(void *prv);

void ICACHE_FLASH_ATTR user_init(){
	uart_init(SERIALBAUD, SERIALBAUD);
	os_printf("\nSDK version:%s\n", system_get_sdk_version());
	os_printf("Serial Jalan OK\n");

	gpio_init();
	gpio_output_set(0, 0, (1 << 2), 0);
	gpio16_output_conf();

	os_timer_setfn(&blinky_timer, (os_timer_func_t *)blinky_timer_handler, NULL);
  	os_timer_arm(&blinky_timer, 500, 1);

  	os_timer_setfn(&serial_timer, (os_timer_func_t *)serial_timer_handler, NULL);
  	os_timer_arm(&serial_timer, 1000, 1);
}


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

void serial_timer_handler(void *prv){
  	os_printf("Test Serial per detik\n");
}
