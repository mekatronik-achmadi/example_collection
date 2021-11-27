#ifndef LIB_LCD_H
#define LIB_LCD_H

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdlib.h>
#include <math.h>

#include "ch.h"
#include "hal.h"

#include "shell.h"
#include "chprintf.h"
#include "memstreams.h"
#include "evtimer.h"

#define _lcd_stream_data _base_sequential_stream_data

#define LCD_PIN_RS 0
#define LCD_PIN_RW 1
#define LCD_PIN_EN 2
#define LCD_PORT_CRTL GPIOC

#define LCD_PIN_D4 4
#define LCD_PIN_D5 5
#define LCD_PIN_D6 6
#define LCD_PIN_D7 7
#define LCD_PORT_DATA GPIOC

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

 void Lcd_Clear (void);
 void Lcd_Cursor(uint8_t column, uint8_t line);
 void Lcd_Example(void);
 void Lcd_Init(void);

#endif // LIB_LCD_H
