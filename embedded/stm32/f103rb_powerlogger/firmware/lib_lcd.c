#include "ch.h"
#include "hal.h"
#include "lib_lcd.h"

LcdStream myLCD;

static msg_t put(void *ip, uint8_t chr) {
    (void)ip;
    Lcd_Write_Data(chr);
    return RDY_OK;
}

static const struct LcdStreamVMT vmt = {NULL, NULL, put, NULL};
void lsObjectInit(LcdStream *msp) {
    msp->vmt = &vmt;
}

void Lcd_Pin_Dir(void){
    palSetPadMode(LCD_PORT_CRTL,LCD_PIN_RS,LCD_PORT_MODE);
    palSetPadMode(LCD_PORT_CRTL,LCD_PIN_RW,LCD_PORT_MODE);
    palSetPadMode(LCD_PORT_CRTL,LCD_PIN_EN,LCD_PORT_MODE);
    palSetPadMode(LCD_PORT_DATA,LCD_PIN_D4,LCD_PORT_MODE);
    palSetPadMode(LCD_PORT_DATA,LCD_PIN_D5,LCD_PORT_MODE);
    palSetPadMode(LCD_PORT_DATA,LCD_PIN_D6,LCD_PORT_MODE);
    palSetPadMode(LCD_PORT_DATA,LCD_PIN_D7,LCD_PORT_MODE);
    palClearPad(LCD_PORT_CRTL,LCD_PIN_RW);
}

void Lcd_Write_Data(uint8_t chr){
    palWritePort(LCD_PORT_DATA,(chr & 0xf0));
    palSetPad(LCD_PORT_CRTL,LCD_PIN_RS);
    palSetPad(LCD_PORT_CRTL,LCD_PIN_EN);
    chThdSleepMicroseconds(40);
    palClearPad(LCD_PORT_CRTL,LCD_PIN_EN);
    palClearPad(LCD_PORT_CRTL,LCD_PIN_RS);
    chThdSleepMicroseconds(40);

    palWritePort(LCD_PORT_DATA,((chr & 0x0f)<<4));
    palSetPad(LCD_PORT_CRTL,LCD_PIN_RS);
    palSetPad(LCD_PORT_CRTL,LCD_PIN_EN);
    chThdSleepMicroseconds(40);
    palClearPad(LCD_PORT_CRTL,LCD_PIN_EN);
    palClearPad(LCD_PORT_CRTL,LCD_PIN_RS);
    chThdSleepMicroseconds(40);
}

void Lcd_Write_Command(uint8_t cmd){
    palWritePort(LCD_PORT_DATA,(cmd & 0xf0));
    palSetPad(LCD_PORT_CRTL,LCD_PIN_EN);
    chThdSleepMicroseconds(40);
    palClearPad(LCD_PORT_CRTL,LCD_PIN_EN);
    chThdSleepMicroseconds(40);

    palWritePort(LCD_PORT_DATA,((cmd & 0x0f)<<4));
    palSetPad(LCD_PORT_CRTL,LCD_PIN_EN);
    chThdSleepMicroseconds(40);
    palClearPad(LCD_PORT_CRTL,LCD_PIN_EN);
    chThdSleepMicroseconds(40);
}

void Lcd_Cursor(uint8_t column, uint8_t line){
    uint8_t position = LCD_2X16_DDRAM_ADDR;
    if (line > 0)
    {
    position |= LCD_2X16_NEXT_LINE;
    }
    Lcd_Write_Command(position | column);
}

void Lcd_Init(void){
    lsObjectInit(&myLCD);
    Lcd_Pin_Dir();

    chThdSleepMilliseconds(500);
    palWritePort(LCD_PORT_CRTL,0x00);
    palWritePort(LCD_PORT_DATA,0x00);

    palSetPad(LCD_PORT_DATA,LCD_PIN_D5);
    palSetPad(LCD_PORT_CRTL,LCD_PIN_EN);
    chThdSleepMilliseconds(40);
    palClearPad(LCD_PORT_CRTL,LCD_PIN_EN);
    chThdSleepMilliseconds(40);

    Lcd_Write_Command(0x28);
    chThdSleepMicroseconds(40);
    Lcd_Write_Command(0x0c);
    chThdSleepMicroseconds(40);
}

void Lcd_Clear (void){
    Lcd_Write_Command(0x01);
    chThdSleepMicroseconds(40);
}

void Lcd_Example(){
    Lcd_Clear();
    Lcd_Cursor(0,0);
    chprintf((BaseSequentialStream *)&myLCD,"A-LCD");
    Lcd_Cursor(0,1);
    chprintf((BaseSequentialStream *)&myLCD,"Works");
}
