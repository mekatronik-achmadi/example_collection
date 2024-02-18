#include <esp_system.h>
#include <esp_console.h>
#include <esp_vfs_dev.h>
#include <esp_err.h>

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include "driver/uart.h"
#include "driver/gpio.h"

#include <linenoise/linenoise.h>
#include <argtable3/argtable3.h>

#include "shell.h"

#define CONFIG_ESP_CONSOLE_UART_NUM 0
#define UART_USE_PROMPT             1

//////////////////////////// Commands ///////////////////////

static int reboot_cb(int argc, char *argv[]){
    printf("Rebooting\n");
    esp_restart();
}

static void reboot_reg(void){
    const esp_console_cmd_t cmd = {
        .command = "reboot",
        .help = "Reboot the chip",
        .hint = NULL,
        .func = &reboot_cb
    };
    esp_console_cmd_register(&cmd);
}

static int serialTest_cb(int argc, char *argv[]){
    printf("ESP32 Console Shell\n");
    return 0;
}

static void serialTest_reg(void){
    const esp_console_cmd_t cmd = {
        .command = "test",
        .help = "Testing Console",
        .hint = NULL,
        .func = &serialTest_cb
    };
    esp_console_cmd_register(&cmd);
}

static void register_Commands(void){
    reboot_reg();
    serialTest_reg();
}

/////////////////////////// SHELL //////////////////

#if UART_USE_PROMPT
const char *prompt = "esp> ";
#else
const char *prompt = "";
#endif

static void console_Init(void){
    fflush(stdout);
    fsync(fileno(stdout));
    setvbuf(stdin,NULL,_IONBF,0);

    esp_vfs_dev_uart_set_rx_line_endings(ESP_LINE_ENDINGS_CR);
    esp_vfs_dev_uart_set_tx_line_endings(ESP_LINE_ENDINGS_CRLF);

    uart_config_t uart_Conf = {
        .baud_rate = CONFIG_ESP_CONSOLE_UART_BAUDRATE,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1
    };

    uart_param_config(CONFIG_ESP_CONSOLE_UART_NUM,&uart_Conf);
    uart_driver_install(CONFIG_ESP_CONSOLE_UART_NUM,
            256,
            0,
            0,
            NULL,
            0);
    esp_vfs_dev_uart_use_driver(CONFIG_ESP_CONSOLE_UART_NUM);

    esp_console_config_t console_Conf = {
        .max_cmdline_args = 8,
        .max_cmdline_length = 256
    };
    esp_console_init(&console_Conf);

    //linenoiseAllowEmpty(true);
}

void shell_Init(void){
    console_Init();

    esp_console_register_help_command();
    register_Commands();

    printf("\n"
           "This is console shell.\n"
           "Run in dumb mode without line editing nor history.\n"
           "Type 'help' to get the list of commands.\n"
           "\n");

    linenoiseSetDumbMode(1);
}

int shell_Loop(void){
    char *line = linenoise(prompt);

    if(line==NULL) return 1;
    if(strlen(line)==0) return 0;

    int ret;
    esp_err_t err = esp_console_run(line,&ret);

    if(err==ESP_ERR_NOT_FOUND)
        printf("Command Unknown\n");

    else if(err==ESP_ERR_INVALID_ARG) ;

    else if((err==ESP_OK) && (ret!=ESP_OK))
        printf("Non-Zero return: 0x%x (%s)\n",
                ret,
                esp_err_to_name(ret));

    else if(err!=ESP_OK)
        printf("Internal Error: %s\n", esp_err_to_name(err));

    linenoiseFree(line);

    return 0;
}

