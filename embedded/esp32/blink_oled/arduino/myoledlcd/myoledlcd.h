#ifndef MY_OLED_LCD_H
#define MY_OLED_LCD_H

#ifdef __cplusplus
extern "C" {
#endif

#include <errno.h>
#include <ctype.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <errno.h>

#include <driver/i2c.h>
#include <driver/gpio.h>

/************************** Font Part ************************/

#define DEFAULT_FONT FONT_FACE_GLCD5x7

typedef enum
{
    FONT_FACE_GLCD5x7 = 0,
    FONT_FACE_BITOCRA_4X7,
    FONT_FACE_TERMINUS_6X12_ISO8859_1,
    FONT_FACE_TERMINUS_8X14_ISO8859_1,
    FONT_FACE_TERMINUS_BOLD_8X14_ISO8859_1,
    FONT_FACE_TERMINUS_10X18_ISO8859_1,
    FONT_FACE_TERMINUS_BOLD_10X18_ISO8859_1,
    FONT_FACE_TERMINUS_12X24_ISO8859_1,
    FONT_FACE_TERMINUS_BOLD_12X24_ISO8859_1,
} font_face_t;

typedef struct _font_char_desc
{
    uint8_t width;   ///< Character width in pixel
    uint16_t offset; ///< Offset of this character in bitmap
} font_char_desc_t;

typedef struct _font_info
{
    uint8_t height;                           ///< Character height in pixel, all characters have same height
    uint8_t c;                                ///< Simulation of "C" width in TrueType term, the space between adjacent characters
    char char_start;                          ///< First character
    char char_end;                            ///< Last character
    const font_char_desc_t *char_descriptors; ///< descriptor for each character
    const uint8_t *bitmap;                    ///< Character bitmap
} font_info_t;

inline const font_char_desc_t *font_get_char_desc(const font_info_t *fnt, char c)
{
    return c < fnt->char_start || c > fnt->char_end
        ? NULL
        : fnt->char_descriptors + c - fnt->char_start;
}

uint16_t font_measure_string(const font_info_t *fnt, const char *s);

/************************** SSD1306/SH1106 Part ************************/

#define SSD1306_I2C_ADDR    (0x3C)
#define SCL_PIN				GPIO_NUM_22
#define SDA_PIN 			GPIO_NUM_21
#define DISPLAY_WIDTH		128
#define DISPLAY_HEIGHT		64

/* SSD1306 commands */
#define SSD1306_SET_MEM_ADDR_MODE    (0x20)

#define SSD1306_SET_COL_ADDR         (0x21)
#define SSD1306_SET_PAGE_ADDR        (0x22)
#define SSD1306_SET_DISP_START_LINE  (0x40)
#define SSD1306_SET_CONTRAST         (0x81)
#define SSD1306_SET_SEGMENT_REMAP0   (0xA0)
#define SSD1306_SET_SEGMENT_REMAP1   (0xA1)
#define SSD1306_SET_ENTIRE_DISP_ON   (0xA5)
#define SSD1306_SET_ENTIRE_DISP_OFF  (0xA4)
#define SSD1306_SET_INVERSION_OFF    (0xA6)
#define SSD1306_SET_INVERSION_ON     (0xA7)

#define SSD1306_SET_MUX_RATIO        (0xA8)
#define SSD1306_MUX_RATIO_MASK       (0x3F)
#define SSD1306_SET_DISPLAY_OFF      (0xAE)
#define SSD1306_SET_DISPLAY_ON       (0xAF)
#define SSD1306_SET_SCAN_DIR_FWD     (0xC0)
#define SSD1306_SET_SCAN_DIR_BWD     (0xC8)
#define SSD1306_SET_DISPLAY_OFFSET   (0xD3)
#define SSD1306_SET_OSC_FREQ         (0xD5)
#define SSD1306_SET_PRE_CHRG_PER     (0xD9)

#define SSD1306_SET_COM_PINS_HW_CFG  (0xDA)
#define SSD1306_COM_PINS_HW_CFG_MASK (0x32)
#define SSD1306_SEQ_COM_PINS_CFG     (0x02)
#define SSD1306_ALT_COM_PINS_CFG     (0x12)
#define SSD1306_COM_LR_REMAP_OFF     (0x02)
#define SSD1306_COM_LR_REMAP_ON      (0x22)

#define SSD1306_SET_DESEL_LVL        (0xDB)
#define SSD1306_SET_NOP              (0xE3)

#define SSD1306_SET_CHARGE_PUMP      (0x8D)
#define SSD1306_CHARGE_PUMP_EN       (0x14)
#define SSD1306_CHARGE_PUMP_DIS      (0x10)

#define SSD1306_SCROLL_HOR_LEFT      (0x27)
#define SSD1306_SCROLL_HOR_RIGHT     (0x26)
#define SSD1306_SCROLL_HOR_VER_LEFT  (0x2A)
#define SSD1306_SCROLL_HOR_VER_RIGHT (0x29)
#define SSD1306_SCROLL_ENABLE        (0x2F)
#define SSD1306_SCROLL_DISABLE       (0x2E)

#define SH1106_SET_CHARGE_PUMP       (0xAD)
#define SH1106_CHARGE_PUMP_EN        (0x8B)
#define SH1106_CHARGE_PUMP_DIS       (0x8A)
#define SH1106_CHARGE_PUMP_VALUE     (0x30)

#define SH1106_SET_PAGE_ADDRESS      (0xB0)
#define SH1106_SET_LOW_COL_ADDR      (0x00)
#define SH1106_SET_HIGH_COL_ADDR     (0x10)

typedef enum{
    SH1106_VOLTAGE_74 = 0, // 7.4 Volt
    SH1106_VOLTAGE_80,     // 8.0 Volt
    SH1106_VOLTAGE_84,     // 8.4 Volt
    SH1106_VOLTAGE_90      // 9.0 Volt
} sh1106_voltage_t;

typedef enum{
    SSD1306_SCREEN = 0,
    SH1106_SCREEN
} ssd1306_screen_t;

typedef struct{
    i2c_port_t i2c_port;
    uint8_t i2c_addr;
    ssd1306_screen_t screen;
    uint8_t width;
    uint8_t height;
} ssd1306_t;

typedef enum{
    SSD1306_ADDR_MODE_HORIZONTAL = 0,
    SSD1306_ADDR_MODE_VERTICAL,
    SSD1306_ADDR_MODE_PAGE
} ssd1306_mem_addr_mode_t;

typedef enum{
    OLED_COLOR_TRANSPARENT = -1, //!< Transparent (not drawing)
    OLED_COLOR_BLACK = 0,        //!< Black (pixel off)
    OLED_COLOR_WHITE = 1,        //!< White (or blue, yellow, pixel on)
    OLED_COLOR_INVERT = 2,       //!< Invert pixel (XOR)
} ssd1306_color_t;

typedef enum{
    FRAME_5 = 0,
    FRAME_64,
    FRAME_128,
    FRAME_256,
    FRAME_3,
    FRAME_4,
    FRAME_25,
    FRAME_2

} ssd1306_scroll_t;

#define ssd1306_clear_buffer memset

int ssd1306_command(const ssd1306_t *dev, uint8_t cmd);
int ssd1306_init(const ssd1306_t *dev);
int ssd1306_clear_screen(const ssd1306_t *dev);
int ssd1306_load_xbm(const ssd1306_t *dev, uint8_t *xbm, uint8_t *fb);
int ssd1306_load_frame_buffer(const ssd1306_t *dev, uint8_t buf[]);
int ssd1306_display_on(const ssd1306_t *dev, bool on);
int ssd1306_set_display_start_line(const ssd1306_t *dev, uint8_t start);
int ssd1306_set_display_offset(const ssd1306_t *dev, uint8_t offset);
int ssd1306_set_mem_addr_mode(const ssd1306_t *dev, ssd1306_mem_addr_mode_t mode);
int ssd1306_set_segment_remapping_enabled(const ssd1306_t *dev, bool on);
int ssd1306_set_scan_direction_fwd(const ssd1306_t *dev, bool fwd);
int ssd1306_set_com_pin_hw_config(const ssd1306_t *dev, uint8_t config);
int ssd1306_set_contrast(const ssd1306_t *dev, uint8_t contrast);
int ssd1306_set_inversion(const ssd1306_t *dev, bool on);
int ssd1306_set_osc_freq(const ssd1306_t *dev, uint8_t osc_freq);
int ssd1306_set_mux_ratio(const ssd1306_t *dev, uint8_t ratio);
int ssd1306_set_column_addr(const ssd1306_t *dev, uint8_t start, uint8_t stop);
int ssd1306_set_page_addr(const ssd1306_t *dev, uint8_t start, uint8_t stop);
int ssd1306_set_precharge_period(const ssd1306_t *dev, uint8_t prchrg);
int ssd1306_set_deseltct_lvl(const ssd1306_t *dev, uint8_t lvl);
int ssd1306_set_whole_display_lighting(const ssd1306_t *dev, bool light);
int ssd1306_draw_pixel(const ssd1306_t *dev, uint8_t *fb, int8_t x, int8_t y, ssd1306_color_t color);
int ssd1306_draw_line(const ssd1306_t *dev, uint8_t *fb, int16_t x0, int16_t y0, int16_t x1, int16_t y1, ssd1306_color_t color);
int ssd1306_draw_hline(const ssd1306_t *dev, uint8_t *fb, int8_t x, int8_t y, uint8_t w, ssd1306_color_t color);
int ssd1306_draw_vline(const ssd1306_t *dev, uint8_t *fb, int8_t x, int8_t y, uint8_t h, ssd1306_color_t color);
int ssd1306_draw_rectangle(const ssd1306_t *dev, uint8_t *fb, int8_t x, int8_t y, uint8_t w, uint8_t h, ssd1306_color_t color);
int ssd1306_fill_rectangle(const ssd1306_t *dev, uint8_t *fb, int8_t x, int8_t y, uint8_t w, uint8_t h, ssd1306_color_t color);
int ssd1306_draw_circle(const ssd1306_t *dev, uint8_t *fb, int8_t x0, int8_t y0, uint8_t r, ssd1306_color_t color);
int ssd1306_fill_circle(const ssd1306_t *dev, uint8_t *fb, int8_t x0, int8_t y0, uint8_t r, ssd1306_color_t color);
int ssd1306_draw_triangle(const ssd1306_t *dev, uint8_t *fb, int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, ssd1306_color_t color);
int ssd1306_fill_triangle(const ssd1306_t *dev, uint8_t *fb, int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, ssd1306_color_t color);
int ssd1306_draw_char(const ssd1306_t *dev, uint8_t *fb, const font_info_t *font, uint8_t x, uint8_t y, char c, ssd1306_color_t foreground, ssd1306_color_t background);
int ssd1306_draw_string(const ssd1306_t *dev, uint8_t *fb, const font_info_t *font, uint8_t x, uint8_t y, const char *str, ssd1306_color_t foreground, ssd1306_color_t background);
int ssd1306_stop_scroll(const ssd1306_t *dev);
int ssd1306_start_scroll_hori(const ssd1306_t *dev, bool way, uint8_t start, uint8_t stop, ssd1306_scroll_t frame);
int ssd1306_start_scroll_hori_vert(const ssd1306_t *dev, bool way, uint8_t start, uint8_t stop, uint8_t dy, ssd1306_scroll_t frame);
int ssd1306_set_charge_pump_enabled(const ssd1306_t *dev, bool enabled);
int sh1106_set_charge_pump_voltage(const ssd1306_t *dev, sh1106_voltage_t select);
void my_oledInit(void);

/************************** Text Drawing Part ************************/

void my_olcdtest_text(void);

#ifdef __cplusplus
}
#endif

#endif
