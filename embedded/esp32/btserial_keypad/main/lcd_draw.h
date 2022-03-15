/**
 * @file lcd_draw.h
 * @brief Basic LCD Draw header
 *
 * @addtogroup LCD
 * @{
 */

#ifndef LCD_DRAW_H
#define LCD_DRAW_H

#define LCD_LINE_NUMS   3
#define LCD_LINE1_LEN   16
#define LCD_LINE2_LEN   2*LCD_LINE1_LEN
#define LCD_LINE3_LEN   3*LCD_LINE1_LEN
#define LCD_BUFFER_LEN  LCD_LINE1_LEN+1

void test_olcd_img(void);
void test_olcd_flip(void);
void test_olcd_text(void);
void test_olcd_loop(void);
void test_olcd_demo(void);
void register_oled(void);

#endif // LCD_DRAW_H

/** @} */