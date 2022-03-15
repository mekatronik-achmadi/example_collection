/**
 * @file input.c
 * @brief Input handler code
 *
 * @addtogroup Input
 * @{
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

#include "esp_log.h"
#include "esp_console.h"

#include "ssd1306i2c.h"
#include "input.h"

extern ssd1306_t oled_dev;

/**
 * @brief Input Buffer
 *
 */
char inputBuffer[MAX_INPUT_LEN];

/**
 * @brief LCD Buffer
 *
 */
static uint8_t lcdbuff[DISPLAY_WIDTH * DISPLAY_HEIGHT / 8];

/**
 * @brief Register LCD Clear command
 *
 */
static void register_lcdClear(void);

/**
 * @brief Register Input commands
 *
 */
static void registerInputs(void){
    register_lcdClear();
}

/**
 * @brief LCD Clear command
 *
 * @param argc
 * @param argv
 * @return int
 */
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

/**
 * @brief Show Bluetooth received string
 *
 * @param strbuff
 */
static void input_log_char(char* strbuff ){
    uint16_t datLen;

    printf("%s\r\n",strbuff);

    datLen = strlen(strbuff);
    printf("len %i\r\n",datLen);
}

/**
 * @brief Display string each line on LCD
 *
 * @param[in] strbuff String Buffer
 */
static void input_lcd_string(char* strbuff){
    char subline_1[LCD_BUFFER_LEN];
    char subline_2[LCD_BUFFER_LEN];
    char subline_3[LCD_BUFFER_LEN];

    ssd1306_clear_buffer(lcdbuff,0,sizeof(lcdbuff));

    if(strlen(strbuff)<=LCD_LINE1_LEN)
        ssd1306_draw_string(&oled_dev,
                            lcdbuff,
                            font_builtin_fonts[FONT_FACE_TERMINUS_BOLD_8X14_ISO8859_1],
                            0, 4, strbuff,
                            OLED_COLOR_WHITE,
                            OLED_COLOR_BLACK);

    else if(strlen(strbuff)>LCD_LINE1_LEN && strlen(strbuff)<=LCD_LINE2_LEN){

        strncpy(subline_1, &strbuff[0], LCD_LINE1_LEN);
        subline_1[LCD_LINE1_LEN]='\0';
        ssd1306_draw_string(&oled_dev,
                            lcdbuff,
                            font_builtin_fonts[FONT_FACE_TERMINUS_BOLD_8X14_ISO8859_1],
                            0, 4, subline_1,
                            OLED_COLOR_WHITE,
                            OLED_COLOR_BLACK);

        strncpy(subline_2, &strbuff[LCD_LINE1_LEN], strlen(strbuff)-LCD_LINE1_LEN);
        subline_2[strlen(strbuff)-LCD_LINE1_LEN] = '\0';
        ssd1306_draw_string(&oled_dev,
                            lcdbuff,
                            font_builtin_fonts[FONT_FACE_TERMINUS_BOLD_8X14_ISO8859_1],
                            0, 19, subline_2,
                            OLED_COLOR_WHITE,
                            OLED_COLOR_BLACK);

    }
    else if(strlen(strbuff)>LCD_LINE2_LEN && strlen(strbuff)<=LCD_LINE3_LEN){

        strncpy(subline_1, &strbuff[0], LCD_LINE1_LEN);
        subline_1[LCD_LINE1_LEN]='\0';
        ssd1306_draw_string(&oled_dev,
                            lcdbuff,
                            font_builtin_fonts[FONT_FACE_TERMINUS_BOLD_8X14_ISO8859_1],
                            0, 4, subline_1,
                            OLED_COLOR_WHITE,
                            OLED_COLOR_BLACK);

        strncpy(subline_2, &strbuff[LCD_LINE1_LEN], LCD_LINE1_LEN);
        subline_2[LCD_LINE1_LEN] = '\0';
        ssd1306_draw_string(&oled_dev,
                            lcdbuff,
                            font_builtin_fonts[FONT_FACE_TERMINUS_BOLD_8X14_ISO8859_1],
                            0, 19, subline_2,
                            OLED_COLOR_WHITE,
                            OLED_COLOR_BLACK);

        strncpy(subline_3, &strbuff[LCD_LINE2_LEN], strlen(strbuff)-LCD_LINE2_LEN);
        subline_3[strlen(strbuff)-LCD_LINE2_LEN] = '\0';
        ssd1306_draw_string(&oled_dev,
                            lcdbuff,
                            font_builtin_fonts[FONT_FACE_TERMINUS_BOLD_8X14_ISO8859_1],
                            0, 33, subline_3,
                            OLED_COLOR_WHITE,
                            OLED_COLOR_BLACK);

    }

    ssd1306_load_frame_buffer(&oled_dev,lcdbuff);
}

/**
 * @brief Initiate Input functions
 *
 */
void inputsInit(void){
    registerInputs();
}

/**
 * @brief Handle Bluetooth Serial inputs
 *
 * @param spp_data_ind Bluetooth SPP data received structure
 */
void bt_Inputs(uint8_t *spp_data_ind){
    char strBuffer[LCD_BUFFER_LEN];
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
        if(chkLen <= MAX_INPUT_LEN){
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

/**
 * @brief Handle keypad inputs
 *
 * @param keynum Number assigned from keypad routine
 */
void key_Inputs(char keynum){
    char chrBuffer[2];
    uint16_t chkLen;

    if(strlen(inputBuffer)==0){
        ssd1306_clear_screen(&oled_dev);
        ssd1306_clear_buffer(lcdbuff,0,sizeof(lcdbuff));
    }

    sprintf(chrBuffer, "%c", keynum); /* convert single char to string */

    printf("key= %s\r\n",chrBuffer);

    chkLen = strlen(inputBuffer) + strlen(chrBuffer);
    if(chkLen <= MAX_INPUT_LEN){
        strcat(inputBuffer,chrBuffer);
        input_lcd_string(inputBuffer);
        printf("%s\r\n",inputBuffer);
    }
    else {
        ssd1306_clear_screen(&oled_dev);
        memset(inputBuffer, 0, sizeof(inputBuffer));
        ssd1306_clear_buffer(lcdbuff,0,sizeof(lcdbuff));
    }
}

/** @} */