#ifndef TA_LCD_H
#define TA_LCD_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "ch.h"
#include "hal.h"
#include "chprintf.h"
#include "memstreams.h"
#include "chstreams.h"

#define _lcd_stream_data _base_sequential_stream_data

#define LCD_PIN_RS 0
#define LCD_PIN_EN 1
#define LCD_PORT_CRTL GPIOE

#define LCD_PIN_D4 4
#define LCD_PIN_D5 5
#define LCD_PIN_D6 6
#define LCD_PIN_D7 7
#define LCD_PORT_DATA GPIOE

#define LCD_PORT_MODE PAL_MODE_OUTPUT_PUSHPULL

#define  TLCD_MAXX            16  // max x-Position (0...15)
#define  TLCD_MAXY             4  // max y-Position (0...1)

#define  LCD_DDRAM              7

#define LCD_LINE0_DDRAMADDR		0x00
#define LCD_LINE1_DDRAMADDR		0x40
#define LCD_LINE2_DDRAMADDR		0x10
#define LCD_LINE3_DDRAMADDR		0x50


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
void Lcd_Example (void);


#endif // LIB_LCD_H
