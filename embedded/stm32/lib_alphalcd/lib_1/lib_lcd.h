#ifndef LIB_LCD_H
#define LIB_LCD_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "chprintf.h"
#include "memstreams.h"
#include "evtimer.h"
#include "chstreams.h"
#include "pal_lld.h"

#define _lcd_stream_data _base_sequential_stream_data

#define LCD_PIN_RS 10
#define LCD_PIN_RW 11
#define LCD_PIN_EN 12
#define LCD_PORT_CRTL GPIOC

#define LCD_PIN_D4 4
#define LCD_PIN_D5 5
#define LCD_PIN_D6 6
#define LCD_PIN_D7 7
#define LCD_PORT_DATA GPIOB

#define LCD_PORT_MODE PAL_MODE_OUTPUT_PUSHPULL

#define LCD_2X16_CGRAM_ADDR 0x40
#define LCD_2X16_DDRAM_ADDR 0x80
#define LCD_2X16_NEXT_LINE  0x40

struct LcdStreamVMT {
    _base_sequential_stream_methods
};

typedef struct {
    const struct LcdStreamVMT *vmt;
    _base_sequential_stream_data
} LcdStream;

#ifdef __cplusplus
extern "C" {
#endif
void lsObjectInit(LcdStream *msp);
#ifdef __cplusplus
}
#endif

void Lcd_Pin_Dir(void);
void Lcd_Write_Command(uint8_t cmd);
void Lcd_Write_Data(uint8_t chr);
void Lcd_Init(void);
void Lcd_Cursor(uint8_t column, uint8_t line);
void Lcd_Clear (void);
void Test_Lcd(void);

#endif // LIB_LCD_H
