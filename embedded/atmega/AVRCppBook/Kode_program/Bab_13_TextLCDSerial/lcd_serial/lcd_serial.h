//id:lcd_serial.h,lcd_serial
//13-8-2012,sidiknur@yahoo.com
//Atmega8,8MHz-internal
#ifndef LCD_SERIAL_H_INCLUDED
#define LCD_SERIAL_H_INCLUDED

#include <util/delay.h>
#include "uart.h"

//milford instruction list
#define	LCDS_CMD_CLEAR_SCREEN			0x01
#define LCDS_CMD_DISPLAY_LEFT			0x18
#define LCDS_CMD_DISPLAY_RIGHT			0x1c
#define LCDS_CMD_HOME					0x00
#define LCDS_CMD_CURSOR_LEFT			0x10
#define LCDS_CMD_CURSOR_RIGHT			0x14
#define LCDS_CMD_UNDERLINE_CURSOR_ON	0x0e
#define LCDS_CMD_CURSOR_BLINK			0x0d
#define LCDS_CMD_CURSOR_OFF				0x0c
#define LCDS_CMD_BLANK_DISPLAY			0x08
#define LCDS_CMD_RESTORE_DISPLAY		0x0c
#define LCDS_CMD_SET_ADDRESS_DDRAM		0x80
#define LCDS_CMD_SET_ADDRESS_CGRAM		0x40

template<uint8_t row_num, uint8_t col_num>
class LcdSerial : Uart_8N1<>
{
public:
    LcdSerial(){
        _delay_ms(20); //wait LCD module to init
    }

    void PutChar(uint8_t ch){
        lcd::PutChar(ch);
    }
    void PutStr(const char* str){
        while(*str){
            lcd::PutChar(*str++);
        }
    }
    void GotoXY(uint8_t row, uint8_t col){
        row--;
        col--;
        set_address_ddram((row%2? (row>>1)*col_num+0x40 :
                           (row>>1)*col_num )+ col);
    }

    void ClrScr(void){
        command(LCDS_CMD_CLEAR_SCREEN);
    }

    void Home(void){
        command(LCDS_CMD_HOME);
    }

     void CursorOff(void){
        command(LCDS_CMD_CURSOR_OFF);
    }

    void BlankDisplay(void){
        command(LCDS_CMD_BLANK_DISPLAY);
    }

private:
    typedef Uart_8N1<> lcd;
    void command(uint8_t cmd){
        lcd::PutChar(254);
        lcd::PutChar(cmd);
        if(cmd==LCDS_CMD_CLEAR_SCREEN || cmd==LCDS_CMD_HOME)
            _delay_ms(10);
    }

    void set_address_ddram(uint8_t addr){
        command(LCDS_CMD_SET_ADDRESS_DDRAM + addr);
    }

    void set_address_cgram(uint8_t addr){
        command(LCDS_CMD_SET_ADDRESS_CGRAM + addr);
    }
};

#endif // LCD_SERIAL_H_INCLUDED
