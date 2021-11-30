#ifndef LCD_H
#define LCD_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "chprintf.h"
#include "memstreams.h"
#include "evtimer.h"

#define _lcd_stream_data _base_sequential_stream_data

struct LcdStreamVMT {
  _base_sequential_stream_methods
};

typedef struct {
  const struct LcdStreamVMT *vmt;
  _lcd_stream_data
} LcdStream;

#ifdef __cplusplus
extern "C" {
#endif
  void lsObjectInit(LcdStream *msp);
#ifdef __cplusplus
}
#endif

void LCD_DATA_DIR_OUT(void);
void Lcd_Write(uint8_t data);
void Lcd_Write_Command(uint8_t cmd);
void Lcd_Write_Data(uint8_t chr);
void Lcd_Init(void);
void Lcd_Cursor(uint8_t column, uint8_t line);
void Lcd_Clear (void);

void Test_LCD1602(void);
 
#endif
