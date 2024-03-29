#include <stdint.h>

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
#include "i2smic.h"

//////////////////////////////// Commands //////////////////////////

extern uint8_t mic_TaskRun;

static int micTask_cb(int argc, char *argv[]){
    if(mic_TaskRun) mic_TaskRun = 0;
    else mic_TaskRun = 1;

    return 0;
}

static void micTask_reg(void){
    const esp_console_cmd_t cmd = {
        .command = "mic",
        .help = "Run Mic Task",
        .hint = NULL,
        .func = &micTask_cb
    };
    esp_console_cmd_register(&cmd);

}

static int micMax_cb(int argc, char *argv[]){
    uint16_t max = mic_Max();
    printf("Max: %i\n",max);

    return 0;
}

static void micMax_reg(void){
    const esp_console_cmd_t cmd = {
        .command = "max",
        .help = "Get Max Mic",
        .hint = NULL,
        .func = &micMax_cb
    };
    esp_console_cmd_register(&cmd);

}

static int micGet_cb(int argc, char *argv[]){
    printf("Bytes: %i\n",(uint16_t)mic_Get());
    return 0;
}

static void micGet_reg(void){
    const esp_console_cmd_t cmd = {
        .command = "get",
        .help = "Get One Shot Mic",
        .hint = NULL,
        .func = &micGet_cb
    };
    esp_console_cmd_register(&cmd);
}

static int reboot_cb(int argc, char *argv[]){
    printf("Rebooting\n");
    esp_restart();
}

static void reboot_reg(void){
    const esp_console_cmd_t cmd = {
        .command = "reboot",
        .help = "Rebooting Chip",
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
        .help = "Test the Console",
        .hint = NULL,
        .func = &serialTest_cb
    };
    esp_console_cmd_register(&cmd);
}

static void register_Commands(void){
    micTask_reg();
    micMax_reg();
    micGet_reg();
    reboot_reg();
    serialTest_reg();
}

////////////////////////////// SHELL  ///////////////////////////////

#if UART_USE_PROMPT
const char *prompt = "esp> ";
#else
const char *prompt = "";
#endif

static void console_Init(void){
    fflush(stdout);
    fsync(fileno(stdout));
    setvbuf(stdin,NULL,_IONBF,0);

    esp_vfs_dev_uart_port_set_rx_line_endings(CONFIG_ESP_CONSOLE_UART_NUM,
            ESP_LINE_ENDINGS_CR);
    esp_vfs_dev_uart_port_set_tx_line_endings(CONFIG_ESP_CONSOLE_UART_NUM,
            ESP_LINE_ENDINGS_CRLF);

    const uart_config_t uart_Conf = {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .source_clk = UART_SCLK_REF_TICK
    };

    uart_driver_install(CONFIG_ESP_CONSOLE_UART_NUM,
            256,
            0,
            0,
            NULL,
            0);

    uart_param_config(CONFIG_ESP_CONSOLE_UART_NUM,&uart_Conf);
    esp_vfs_dev_uart_use_driver(CONFIG_ESP_CONSOLE_UART_NUM);

    const esp_console_config_t console_Conf = {
        .max_cmdline_args = 8,
        .max_cmdline_length = 256
    };
    esp_console_init(&console_Conf);

    linenoiseAllowEmpty(true);
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

