//id:lcd_serial_slave.h,lcd_serial
//13-8-2012,sidiknur@yahoo.com
//Atmega8,8MHz-internal
#ifndef LCD_SERIAL_SLAVE_H_INCLUDED
#define LCD_SERIAL_SLAVE_H_INCLUDED

#include "textlcd.h"
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

template<port_id_t pRS, uint8_t bRS,
          port_id_t pEN, uint8_t bEN,
          port_id_t pD4, uint8_t bD4,
          port_id_t pD5, uint8_t bD5,
          port_id_t pD6, uint8_t bD6,
          port_id_t pD7, uint8_t bD7,
          uint8_t COL_NUM>
class TextLCDSerialSlave : TextLCD<pRS,bRS,
                            pEN,bEN,pD4,bD4,pD5,bD5,
                            pD6,bD6,pD7,bD7,COL_NUM>,
                            Uart_8N1<BAUD_9600>
{
public:
    void Update(){
        uint8_t c;

        c = serial::GetChar();
        if(c == 254){
            c = serial::GetChar();
            if(c==LCDS_CMD_CLEAR_SCREEN)
                lcd::DisplayClear();
            else if(c==LCDS_CMD_HOME)
                lcd::GoHome();
            else if(c==LCDS_CMD_CURSOR_OFF)
                lcd::CursorOffBlinkOff();
            else if(c==LCDS_CMD_BLANK_DISPLAY){}
            else if((c & LCDS_CMD_SET_ADDRESS_DDRAM) == LCDS_CMD_SET_ADDRESS_DDRAM)
                lcd::Command(c);	//handle c as command
            else if((c & LCDS_CMD_SET_ADDRESS_CGRAM) == LCDS_CMD_SET_ADDRESS_CGRAM)
                lcd::Command(c);	//handle c as command
            else{}

        }
        else{
            //just send char to lcd
            lcd::PutChar(c);	//handle c as data
        }
    }
private:
    typedef TextLCD<pRS,bRS,pEN,bEN,pD4,bD4,pD5,bD5,pD6,bD6,pD7,bD7,COL_NUM> lcd;
    typedef Uart_8N1<> serial;
};

#endif // LCD_SERIAL_SLAVE_H_INCLUDED
