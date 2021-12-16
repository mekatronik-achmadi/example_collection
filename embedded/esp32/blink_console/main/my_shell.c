#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "sdkconfig.h"
#include "esp_system.h"
#include "esp_console.h"
#include "esp_log.h"
#include "esp_vfs_dev.h"
#include "esp_err.h"
#include "driver/uart.h"
#include "driver/gpio.h"
#include "linenoise/linenoise.h"
#include "argtable3/argtable3.h"

#include "my_cmd.h"
#include "myconfig.h"

#if UART_USE_PROMPT
const char* prompt = "esp32> ";
#else
const char* prompt = "";
#endif

static void consoleInit(void){
    fflush(stdout);
    fsync(fileno(stdout));
    setvbuf(stdin, NULL,_IONBF, 0);

    esp_vfs_dev_uart_port_set_rx_line_endings(CONFIG_ESP_CONSOLE_UART_NUM, ESP_LINE_ENDINGS_CR);
    esp_vfs_dev_uart_port_set_tx_line_endings(CONFIG_ESP_CONSOLE_UART_NUM, ESP_LINE_ENDINGS_CRLF);

    const uart_config_t uartConf = {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .source_clk = UART_SCLK_REF_TICK,
    };

    uart_driver_install(CONFIG_ESP_CONSOLE_UART_NUM, 256, 0, 0, NULL, 0);
    uart_param_config(CONFIG_ESP_CONSOLE_UART_NUM, &uartConf);
    esp_vfs_dev_uart_use_driver(CONFIG_ESP_CONSOLE_UART_NUM);

    const esp_console_config_t consoleConf = {
        .max_cmdline_args = 8,
        .max_cmdline_length = 256,
    };

    esp_console_init(&consoleConf);

    linenoiseAllowEmpty(true);
    linenoiseHistorySetMaxLen(100);
}

void shellInit(void){
    consoleInit();
    esp_console_register_help_command();

    registerCommands();

    printf("System Configured\n");

     printf("\n"
           "This is an example of ESP-IDF console component.\n"
           "Type 'help' to get the list of commands.\n");

    int probe_status = linenoiseProbe();
    if (probe_status) { /* zero indicates success */
        printf("\n"
               "Your terminal program does not support escape sequences.\n"
               "Line editing and history features are disabled.\n");
        linenoiseSetDumbMode(1);
    }
}

int shellLoop(void){
    char* line = linenoise(prompt);
    if(line==NULL){
        return 1;
    }

    if(strlen(line)>0){
        linenoiseHistoryAdd(line);
    }

    int ret;
    esp_err_t err = esp_console_run(line, &ret);

    if (err == ESP_ERR_NOT_FOUND) {
        printf("Unrecognized command\n");
    } else if (err == ESP_ERR_INVALID_ARG) {
        // command was empty
    } else if (err == ESP_OK && ret != ESP_OK) {
        printf("Command returned non-zero error code: 0x%x (%s)\n", ret, esp_err_to_name(ret));
    } else if (err != ESP_OK) {
        printf("Internal error: %s\n", esp_err_to_name(err));
    }

    /* linenoise allocates line buffer on the heap, so need to free it */
    linenoiseFree(line);
    return 0;
}
