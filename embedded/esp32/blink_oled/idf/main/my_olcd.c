/**
 * @file my_olcd.c
 * @brief Basic LCD Draw source
 *
 * @addtogroup LCD
 * @{
 */

#include "fonts.h"
#include "ssd1306i2c.h"

extern ssd1306_t oled_dev;

/**
 * @brief LCD pixel buffer array
 *
 */
uint8_t lcdbuff[DISPLAY_WIDTH * DISPLAY_HEIGHT / 8];

/**
 * @brief Test text drawing
 *
 */
void my_olcdtest_text(void){
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

/** @} */
