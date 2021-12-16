/*
    ChibiOS - Copyright (C) 2006..2015 Giovanni Di Sirio

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#ifndef _BOARD_H_
#define _BOARD_H_

/*
 * Setup for the Olimex STM32-P103 proto board.
 */

/*
 * Board identifier.
 */
#define BOARD_BASIC
#define BOARD_NAME              "BASIC"

/*
 * Board frequencies.
 */
#define STM32_LSECLK            32768
#define STM32_HSECLK            8000000

/*
 * MCU type, supported types are defined in ./os/hal/platforms/hal_lld.h.
 */
#define STM32F10X_HD

#define GPIOE_TFT_RST			1
#define GPIOD_TFT_LIGHT			13

/*
 * IO pins assignments.
 */
#define VAL_GPIOACRL            0x88888888
#define VAL_GPIOACRH            0x88888888
#define VAL_GPIOAODR            0xFFFFFFFF

#define VAL_GPIOBCRL            0x88888888
#define VAL_GPIOBCRH            0x88888888
#define VAL_GPIOBODR            0xFFFFFFFF

#define VAL_GPIOCCRL            0x88888888
#define VAL_GPIOCCRH            0x88888888
#define VAL_GPIOCODR            0xFFFFFFFF

#define VAL_GPIODCRL            0x88888888
#define VAL_GPIODCRH            0x88888888
#define VAL_GPIODODR            0xFFFFFFFF

#define VAL_GPIOECRL            0x88888888
#define VAL_GPIOECRH            0x88888888
#define VAL_GPIOEODR            0xFFFFFFFF

#define VAL_GPIOFCRL            0x88888888
#define VAL_GPIOFCRH            0x88888888
#define VAL_GPIOFODR            0xFFFFFFFF

#define VAL_GPIOGCRL            0x88888888
#define VAL_GPIOGCRH            0x88888888
#define VAL_GPIOGODR            0xFFFFFFFF

/*
 * USB bus activation macro, required by the USB driver.
 */
#define usb_lld_connect_bus(usbp) palClearPad(GPIOC, GPIOC_USB_DISC)

/*
 * USB bus de-activation macro, required by the USB driver.
 */
#define usb_lld_disconnect_bus(usbp) palSetPad(GPIOC, GPIOC_USB_DISC)

#if !defined(_FROM_ASM_)
#ifdef __cplusplus
extern "C" {
#endif
  void boardInit(void);
#ifdef __cplusplus
}
#endif
#endif /* _FROM_ASM_ */

#endif /* _BOARD_H_ */
