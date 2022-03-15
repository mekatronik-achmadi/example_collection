/**
 * @file lcd_draw.c
 * @brief Basic LCD Draw source
 *
 * @addtogroup LCD
 * @{
 */

#include <errno.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "esp_log.h"
#include "esp_console.h"

#include "fonts.h"
#include "lcd_draw.h"
#include "ssd1306i2c.h"

#include "logo.xbm"

extern ssd1306_t oled_dev;

/**
 * @brief Tag for LCD command
 *
 */
static const char *TAG = "cmd_oled";

/**
 * @brief Flag if image drawn forward or backward
 *
 */
static bool imgfwd = true;

/**
 * @brief LCD pixel buffer array
 *
 */
static uint8_t lcdbuff[DISPLAY_WIDTH * DISPLAY_HEIGHT / 8];

static void register_oled_img();
static void register_oled_flip();
static void register_oled_text();

/**
 * @brief register basic LCD commands
 *
 */
void register_oled(void){
    register_oled_img();
    register_oled_flip();
    register_oled_text();
}

/**
 * @brief LCD image test
 *
 */
void test_olcd_img(void){
    ssd1306_clear_screen(&oled_dev);
    ssd1306_clear_buffer(lcdbuff,0,sizeof(lcdbuff));

    ssd1306_load_xbm(&oled_dev, logo_bits, lcdbuff);
}

/**
 * @brief LCD flip test
 *
 */
void test_olcd_flip(void){
    ssd1306_set_scan_direction_fwd(&oled_dev, imgfwd);
    imgfwd = !imgfwd;
}

/**
 * @brief LCD text test
 *
 */
void test_olcd_text(void){
    ssd1306_clear_screen(&oled_dev);
    ssd1306_clear_buffer(lcdbuff,0,sizeof(lcdbuff));

    ssd1306_draw_string(&oled_dev,
                        lcdbuff,
                        font_builtin_fonts[FONT_FACE_GLCD5x7],
                        0, 0, "GLCD-5x7",
                        OLED_COLOR_WHITE,
                        OLED_COLOR_BLACK);

    ssd1306_draw_string(&oled_dev,
                        lcdbuff,
                        font_builtin_fonts[FONT_FACE_TERMINUS_6X12_ISO8859_1],
                        0, 10, "TERMINUS-6x12", // ymin = 0 + |7| + 3
                        OLED_COLOR_WHITE,
                        OLED_COLOR_BLACK);

    ssd1306_draw_string(&oled_dev,
                        lcdbuff,
                        font_builtin_fonts[FONT_FACE_TERMINUS_BOLD_8X14_ISO8859_1],
                        0, 25, "TERMINUSB-8x14", // ymin = 10 + |12| + 3
                        OLED_COLOR_WHITE,
                        OLED_COLOR_BLACK);

    ssd1306_draw_string(&oled_dev,
                        lcdbuff,
                        font_builtin_fonts[FONT_FACE_TERMINUS_BOLD_10X18_ISO8859_1],
                        0, 42, "TERMINUSB-10x18", // ymin = 25 + |14| + 3
                        OLED_COLOR_WHITE,
                        OLED_COLOR_BLACK);

    ssd1306_load_frame_buffer(&oled_dev,lcdbuff);
}

/**
 * @brief Basic LCD example routine
 *
 * @param pvParameters Task parameters
 */
static void ssd1306_task(void *pvParameters){
    printf("%s: Started user interface task\n", __FUNCTION__);
    vTaskDelay(1000 / portTICK_RATE_MS);


    if (ssd1306_load_xbm(&oled_dev, logo_bits, lcdbuff))
        goto error_loop;

    bool fwd = false;
    while (1) {
        vTaskDelay(1000 / portTICK_RATE_MS);
        printf("%s: still alive, flipping!\n", __FUNCTION__);
        ssd1306_set_scan_direction_fwd(&oled_dev, fwd);
        fwd = !fwd;
    }

error_loop:
    printf("%s: error while loading framebuffer into SSD1306\n", __func__);
    for(;;){
        vTaskDelay(1000 / portTICK_RATE_MS);
        printf("%s: error loop\n", __FUNCTION__);
    }
}

/**
 * @brief LCD loop start test
 *
 */
void test_olcd_loop(void){
    while (ssd1306_init(&oled_dev) != 0){
        printf("%s: failed to init SSD1306 lcd\n", __func__);
        vTaskDelay(1000 / portTICK_RATE_MS);
    }

    vTaskDelay(1000 / portTICK_RATE_MS);
    ssd1306_clear_screen(&oled_dev);
    ssd1306_clear_buffer(lcdbuff,0,sizeof(lcdbuff));
    xTaskCreate(ssd1306_task, "ssd1306_task", 2048, NULL, tskIDLE_PRIORITY, NULL);
}

/**
 * @brief LCD image command
 *
 * @param argc
 * @param argv
 * @return int
 */
static int oled_img(int argc, char **argv){
    test_olcd_img();
    ESP_LOGI(TAG, "Draw test OLED LCD");
    return 0;
}

/**
 * @brief Register LCD image command
 *
 */
static void register_oled_img(){
    const esp_console_cmd_t oled_img_cmd = {
        .command = "oled",
        .help = "Image OLED LCD Drawing",
        .hint = NULL,
        .func = &oled_img,
    };
    ESP_ERROR_CHECK( esp_console_cmd_register(&oled_img_cmd) );
}

/**
 * @brief LCD flip command
 *
 * @param argc
 * @param argv
 * @return int
 */
static int oled_flip(int argc, char **argv){
    test_olcd_flip();
    ESP_LOGI(TAG, "flipping OLED LCD");
    return 0;
}

/**
 * @brief Register LCD flip command
 *
 */
static void register_oled_flip(){
    const esp_console_cmd_t oled_flip_cmd = {
        .command = "flip",
        .help = "Flipping OLED LCD Drawing",
        .hint = NULL,
        .func = &oled_flip,
    };
    ESP_ERROR_CHECK( esp_console_cmd_register(&oled_flip_cmd) );
}

/**
 * @brief LCD text command
 *
 * @param argc
 * @param argv
 * @return int
 */
static int oled_text(int argc, char **argv){
    test_olcd_text();
    ESP_LOGI(TAG, "Text test OLED LCD");
    return 0;
}

/**
 * @brief Register LCD text command
 *
 */
static void register_oled_text(){
    const esp_console_cmd_t oled_text_cmd = {
        .command = "text",
        .help = "Text OLED LCD Drawing",
        .hint = NULL,
        .func = &oled_text,
    };
    ESP_ERROR_CHECK( esp_console_cmd_register(&oled_text_cmd) );
}

/**
 * @brief Demo text spaces
 * @details Show 15X3 font text occupy
 *
 */
void test_olcd_demo(void){
    char strBuff[LCD_BUFFER_LEN];

    ssd1306_clear_screen(&oled_dev);
    ssd1306_clear_buffer(lcdbuff,0,sizeof(lcdbuff));

    sprintf(strBuff, "0123456789ABCDEF");

    ssd1306_draw_string(&oled_dev,
                        lcdbuff,
                        font_builtin_fonts[FONT_FACE_TERMINUS_BOLD_8X14_ISO8859_1],
                        0, 4, strBuff,
                        OLED_COLOR_WHITE,
                        OLED_COLOR_BLACK);

    ssd1306_draw_string(&oled_dev,
                        lcdbuff,
                        font_builtin_fonts[FONT_FACE_TERMINUS_BOLD_8X14_ISO8859_1],
                        0, 19, strBuff, // ymin = 4 + |9| + |6|
                        OLED_COLOR_WHITE,
                        OLED_COLOR_BLACK);

    ssd1306_draw_string(&oled_dev,
                        lcdbuff,
                        font_builtin_fonts[FONT_FACE_TERMINUS_BOLD_8X14_ISO8859_1],
                        0, 33, strBuff, // ymin = 18 + |9| + |6|
                        OLED_COLOR_WHITE,
                        OLED_COLOR_BLACK);

    ssd1306_load_frame_buffer(&oled_dev,lcdbuff);
}

/** @} */
