#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

#include "esp_log.h"
#include "esp_console.h"

#include "ssd1306i2c.h"
#include "input.h"

extern ssd1306_t oled_dev;

char inputBuffer[102];

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

static void input_log_char(char* strbuff ){
    uint16_t datLen;

    printf("%s\r\n",strbuff);

    datLen = strlen(strbuff);
    printf("len %i\r\n",datLen);
}

static void input_lcd_string(char* strbuff){
    ssd1306_clear_buffer(lcdbuff,0,sizeof(lcdbuff));

    if(strlen(strbuff)<=20)
        ssd1306_draw_string(&oled_dev,
                            lcdbuff,
                            font_builtin_fonts[FONT_FACE_TERMINUS_6X12_ISO8859_1],
                            0, 4, strbuff,
                            OLED_COLOR_WHITE,
                            OLED_COLOR_BLACK);

    ssd1306_load_frame_buffer(&oled_dev,lcdbuff);
}

void start_Inputs(void){
    registerInputs();
}

void bt_Inputs(uint8_t *spp_data_ind){
    char strBuffer[18];
    uint16_t chkLen;

    if(strlen(inputBuffer)==0){
        ssd1306_clear_screen(&oled_dev);
        ssd1306_clear_buffer(lcdbuff,0,sizeof(lcdbuff));
    }

    sprintf(strBuffer, "%s", spp_data_ind);
    strBuffer[strcspn(strBuffer, "\r\n")] = 0;  /* remove 0d (CR) and 0a (LF) */

    input_log_char(strBuffer);

    if(strcmp(strBuffer, "lcdclr")==0){
        ssd1306_clear_screen(&oled_dev);
        memset(inputBuffer, 0, sizeof(inputBuffer));
        ssd1306_clear_buffer(lcdbuff,0,sizeof(lcdbuff));
    }else {
        chkLen = strlen(inputBuffer) + strlen(strBuffer);
        if(chkLen <= 100){
            strcat(inputBuffer,strBuffer);
            input_lcd_string(inputBuffer);
            printf("%s\r\n",inputBuffer);
        }
        else {
            ssd1306_clear_screen(&oled_dev);
            memset(inputBuffer, 0, sizeof(inputBuffer));
            ssd1306_clear_buffer(lcdbuff,0,sizeof(lcdbuff));
        }
    }
}
