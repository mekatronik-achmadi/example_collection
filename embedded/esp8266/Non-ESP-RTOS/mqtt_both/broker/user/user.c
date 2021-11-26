#include "osapi.h"
#include "ets_sys.h"
#include "gpio.h"
#include "os_type.h"

#include "mem.h"
#include "ip_addr.h"
#include "espconn.h"
#include "user_interface.h"

#include "drv_gpio16.h"
#include "drv_uart.h"
#include "wifi_sta.h"
#include "mqtt_broker.h"

LOCAL os_timer_t blink_timer;
LOCAL uint8 blink_led;

LOCAL void ICACHE_FLASH_ATTR blink_timer_cb(void *prv){
    if(blink_led==1) { gpio16_output_set(1); blink_led = 0;}
    else{ gpio16_output_set(0); blink_led = 1;}
}

LOCAL void ICACHE_FLASH_ATTR print_info(void){
    os_printf("[INFO]-------------------------------------------\r\n");
    os_printf("[INFO] Compiled at %s %s\r\n",__DATE__,__TIME__);
    os_printf("[INFO] SDK: %s\r\n",system_get_sdk_version());
    os_printf("[INFO] Chip ID: %08X\r\n",system_get_chip_id());
    os_printf("[INFO] CPU Freq: %d MHz \r\n",system_get_cpu_freq());
    os_printf("[INFO] Memory:\r\n"); system_print_meminfo();
    os_printf("-------------------------------------------\r\n");
    os_printf("\r\n");
}

void ICACHE_FLASH_ATTR user_init(){
    gpio_init();
    uart_init(SERIALBAUD,SERIALBAUD);
    uart_rx_intr_enable(UART0);
    print_info();

    user_wifi_station_init();
    
    gpio16_output_conf();
    os_timer_setfn(&blink_timer,(os_timer_func_t*)blink_timer_cb,NULL);
    os_timer_arm(&blink_timer, 500, 1);
}
