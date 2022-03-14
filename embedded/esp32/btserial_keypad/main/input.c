#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

#include "esp_log.h"
#include "esp_console.h"

#include "ssd1306i2c.h"
#include "input.h"

extern ssd1306_t oled_dev;

static uint8_t lcdbuff[DISPLAY_WIDTH * DISPLAY_HEIGHT / 8];

static void register_lcdClear(void);

static void registerInputs(void){
    register_lcdClear();
}

static int input_lcdClear(int argc, char **argv){
    ssd1306_clear_screen(&oled_dev);
    ssd1306_clear_buffer(lcdbuff,0,sizeof(lcdbuff));
    ssd1306_load_frame_buffer(&oled_dev,lcdbuff);

    return 0;
}

static void register_lcdClear(void)
{
    const esp_console_cmd_t cmd = {
        .command = "lcdclr",
        .help = "Clear LCD",
        .hint = NULL,
        .func = &input_lcdClear,
    };
    esp_console_cmd_register(&cmd);
}

void start_Inputs(void){
    registerInputs();
}

void bt_log_char(uint8_t* spp_data_ind){
    static char strBuffer[32];

    sprintf(strBuffer, "%s", spp_data_ind);
    strBuffer[strcspn(strBuffer, "\r\n")] = 0; /* remove 0d (CR) and 0a (LF) */

    printf("%s\r\n",strBuffer);
    if(strcmp(strBuffer, "OK")==0){
        printf("OK\r\n");
    }else {
        printf("NOT OK\r\n");
    }
}
