
#ifndef _BOARD_H_
#define _BOARD_H_

/*
 * Setup for the Olimex STM32-P103 proto board.
 */

/*
 * Board identifier.
 */
#define BOARD_OPWRM
#define BOARD_NAME              "OPWRM"

/*
 * Board frequencies.
 */
#define STM32_LSECLK            32768
#define STM32_HSECLK            8000000

/*
 * MCU type, supported types are defined in ./os/hal/platforms/hal_lld.h.
 */
#define STM32F10X_MD

#define VAL_GPIOACRL            0
#define VAL_GPIOACRH            0
#define VAL_GPIOAODR            0

#define VAL_GPIOBCRL            0
#define VAL_GPIOBCRH            0
#define VAL_GPIOBODR            0

#define VAL_GPIOCCRL            0
#define VAL_GPIOCCRH            0
#define VAL_GPIOCODR            0

#define VAL_GPIODCRL            0
#define VAL_GPIODCRH            0
#define VAL_GPIODODR            0

#define VAL_GPIOECRL            0
#define VAL_GPIOECRH            0
#define VAL_GPIOEODR            0

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
