#include "esp32/rom/ets_sys.h"
#include "driver/gpio.h"
#include "sdkconfig.h"

#include "fonts.h"
#include "ssd1306i2c.h"

#include "my_olcd.h"

#define BLINK_GPIO  2

void app_main(void){
    gpio_reset_pin(BLINK_GPIO);
    gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);

    my_oledInit();
    my_olcdtest_text();

    while(1){
        gpio_set_level(BLINK_GPIO, 0);
        ets_delay_us(500000);

        gpio_set_level(BLINK_GPIO, 1);
        ets_delay_us(500000);
    }
}
