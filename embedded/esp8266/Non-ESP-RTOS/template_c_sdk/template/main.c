#include "ets_sys.h"
#include "osapi.h"
#include "os_type.h"
#include "user_config.h"

void ICACHE_FLASH_ATTR user_init(){
    uart_div_modify(0, UART_CLK_FREQ / 9600);
    os_printf("\nESP8266 says hello\n\n");
}
