/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.org/license.html
 */

/**
 * @file    boards/addons/gdisp/board_ILI9341_spi.h
 * @brief   GDISP Graphic Driver subsystem board interface for the ILI9341 display.
 *
 * @note	This file contains a mix of hardware specific and operating system specific
 *			code. You will need to change it for your CPU and/or operating system.
 */

/*
 * Modification sources:
 * https://community.ugfx.io/topic/156-ili9341-spi-stm32f103/?do=findComment&comment=1197
 */

#ifndef _GDISP_LLD_BOARD_H
#define _GDISP_LLD_BOARD_H

#include "gfx.h"
#include "hal.h"

#define SPI_METHOD_IRQ		    1
#define SPI_METHOD_POLLING		2
#define SPI_METHOD              SPI_METHOD_POLLING

#define SPI_DRIVER (&SPID2)
#define SPI_PORT GPIOB
#define LCD_PORT GPIOB

#define LCD_MOSI	15
#define LCD_SCK     13
#define LCD_CS		12
#define LCD_DC		8
#define LCD_RES		9

#define LCD_DC_CMD	palSetPad(LCD_PORT, LCD_DC)
#define LCD_DC_DATA	palClearPad(LCD_PORT, LCD_DC)

#define LCD_CS_RES	palSetPad(LCD_PORT, LCD_CS)
#define LCD_CS_SET	palClearPad(LCD_PORT, LCD_CS)

// SPI setup ajust " SPI_BaudRatePrescaler_X" to set SPI speed.
// Peripherial Clock 42MHz SPI2 SPI3
// Peripherial Clock 84MHz SPI1                                SPI1        SPI2/3
#define SPI_BaudRatePrescaler_2         ((uint16_t)0x0000) //  42 MHz      21 MHZ
#define SPI_BaudRatePrescaler_4         ((uint16_t)0x0008) //  21 MHz      10.5 MHz
#define SPI_BaudRatePrescaler_8         ((uint16_t)0x0010) //  10.5 MHz    5.25 MHz
#define SPI_BaudRatePrescaler_16        ((uint16_t)0x0018) //  5.25 MHz    2.626 MHz
#define SPI_BaudRatePrescaler_32        ((uint16_t)0x0020) //  2.626 MHz   1.3125 MHz
#define SPI_BaudRatePrescaler_64        ((uint16_t)0x0028) //  1.3125 MHz  656.25 KHz
#define SPI_BaudRatePrescaler_128       ((uint16_t)0x0030) //  656.25 KHz  328.125 KHz
#define SPI_BaudRatePrescaler_256       ((uint16_t)0x0038) //  328.125 KHz 164.06 KHz

/**
 * SPI configuration structure.
 * Speed 12 MHz, CPHA=0, CPOL=0, 8bits frames, MSb transmitted first.
 * Soft slave select.
 */
static const SPIConfig spi_cfg = {
  NULL,
  LCD_PORT,
  LCD_CS, //SPI NSS
  SPI_BaudRatePrescaler_2
};

/**
 * @brief   Initialise the board for the display.
 *
 * @param[in] g			The GDisplay structure
 *
 * @note	Set the g->board member to whatever is appropriate. For multiple
 * 			displays this might be a pointer to the appropriate register set.
 *
 * @notapi
 */
static GFXINLINE void init_board(GDisplay *g) {

  // As we are not using multiple displays we set g->board to NULL as we don't use it.
  g->board = 0;

  // LED indicator
  palSetPadMode(GPIOC, 13, PAL_MODE_OUTPUT_PUSHPULL);
  palSetPad(GPIOC, 13);

  palSetPadMode(GPIOB, 15, PAL_MODE_STM32_ALTERNATE_PUSHPULL);
  palSetPadMode(GPIOB, 13, PAL_MODE_STM32_ALTERNATE_PUSHPULL);

  palSetPadMode(GPIOB, LCD_CS, PAL_MODE_OUTPUT_PUSHPULL);
  palSetPadMode(GPIOB, LCD_DC, PAL_MODE_OUTPUT_PUSHPULL);
  palSetPadMode(GPIOB, LCD_RES, PAL_MODE_OUTPUT_PUSHPULL);

  palSetPad(GPIOB, LCD_CS);
  palSetPad(GPIOB, LCD_RES);
  palClearPad(GPIOB,LCD_DC);

  spiStart(SPI_DRIVER, &spi_cfg);
  spiSelectI(SPI_DRIVER);
}

/**
 * @brief   After the initialisation.
 *
 * @param[in] g			The GDisplay structure
 *
 * @notapi
 */
static GFXINLINE void post_init_board(GDisplay *g) {
	(void) g;
}

/**
 * @brief   Set or clear the lcd reset pin.
 *
 * @param[in] g			The GDisplay structure
 * @param[in] state		TRUE = lcd in reset, FALSE = normal operation
 * 
 * @notapi
 */
static GFXINLINE void setpin_reset(GDisplay *g, bool_t state) {
	(void) g;

    if (state == TRUE) {
        palClearPad(LCD_PORT, LCD_RES);
    } else {
        palSetPad(LCD_PORT, LCD_RES);
    }
}

/**
 * @brief   Set the lcd back-light level.
 *
 * @param[in] g				The GDisplay structure
 * @param[in] percent		0 to 100%
 * 
 * @notapi
 */
static GFXINLINE void set_backlight(GDisplay *g, uint8_t percent) {
	(void) g;
	(void) percent;
}

/**
 * @brief   Take exclusive control of the bus
 *
 * @param[in] g				The GDisplay structure
 *
 * @notapi
 */
static GFXINLINE void acquire_bus(GDisplay *g) {
	(void) g;
    spiSelectI(SPI_DRIVER);
}

/**
 * @brief   Release exclusive control of the bus
 *
 * @param[in] g				The GDisplay structure
 *
 * @notapi
 */
static GFXINLINE void release_bus(GDisplay *g) {
	(void) g;
    spiUnselectI(SPI_DRIVER);
}

/**
 * @brief   Send data to the index register.
 *
 * @param[in] g				The GDisplay structure
 * @param[in] index			The index register to set
 *
 * @notapi
 */
static GFXINLINE void write_index(GDisplay *g, uint16_t index) {
    (void) g;

    palClearPad(LCD_PORT, LCD_DC);
#if SPI_METHOD == SPI_METHOD_IRQ
    spiSend(SPI_DRIVER, 1, &index);
#elif SPI_METHOD == SPI_METHOD_POLLING
    spiPolledExchange(SPI_DRIVER, index);
#endif
    palSetPad(LCD_PORT, LCD_DC);
}

/**
 * @brief   Send data to the lcd with DC control.
 *
 * @param[in] g				The GDisplay structure
 * @param[in] data			The data to send
 * 
 * @notapi
 */
static GFXINLINE void write_data(GDisplay *g, uint16_t data) {
	(void) g;

#if SPI_METHOD == SPI_METHOD_IRQ
    spiSend(SPI_DRIVER, 1, &data);
#elif SPI_METHOD == SPI_METHOD_POLLING
    spiPolledExchange(SPI_DRIVER, data);
#endif
}

/**
 * @brief   Set the bus in read mode
 *
 * @param[in] g				The GDisplay structure
 *
 * @notapi
 */
static GFXINLINE void setreadmode(GDisplay *g) {
	(void) g;
}

/**
 * @brief   Set the bus back into write mode
 *
 * @param[in] g				The GDisplay structure
 *
 * @notapi
 */
static GFXINLINE void setwritemode(GDisplay *g) {
	(void) g;
}

/**
 * @brief   Read data from the lcd.
 * @return	The data from the lcd
 *
 * @param[in] g				The GDisplay structure
 *
 * @notapi
 */
static GFXINLINE uint16_t read_data(GDisplay *g) {
	(void) g;
	return 0;
}

#endif /* _GDISP_LLD_BOARD_H */

