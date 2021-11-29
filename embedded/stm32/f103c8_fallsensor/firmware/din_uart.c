/*
              DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE

 Copyright (C) 2018 Achmadi S.T.

 Everyone is permitted to copy and distribute verbatim or modified
 copies of this license document, and changing it is allowed as long
 as the name is changed.

            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
   TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION

  0. You just DO WHAT THE FUCK YOU WANT TO.
 */

/**
 * @file    din_uart.c
 * @brief   UART-1 starting code.
 *
 * @addtogroup Communication
 * @{
 */

#include "din_uart.h"

/**
 * @brief   UART-1 starting function.
 */
void d_uart_start(void){
    palSetPadMode(GPIOA,9,PAL_MODE_STM32_ALTERNATE_PUSHPULL); //TX
    palSetPadMode(GPIOA,10,PAL_MODE_INPUT); //RX
    sdStart(&SD1,NULL);
}

/**
 * @brief   UART-1 info message function.
 */
void d_uart_info(void){
#if UART_INFO

    chprintf((BaseSequentialStream *)&SD1, "Kernel:       %s\r\n", CH_KERNEL_VERSION);

#ifdef PORT_COMPILER_NAME
    chprintf((BaseSequentialStream *)&SD1, "Compiler:     %s\r\n", PORT_COMPILER_NAME);
#endif

    chprintf((BaseSequentialStream *)&SD1, "Architecture: %s\r\n", PORT_ARCHITECTURE_NAME);

#ifdef PORT_CORE_VARIANT_NAME
    chprintf((BaseSequentialStream *)&SD1, "Core Variant: %s\r\n", PORT_CORE_VARIANT_NAME);
#endif

#ifdef PORT_INFO
    chprintf((BaseSequentialStream *)&SD1, "Port Info:    %s\r\n", PORT_INFO);
#endif

#ifdef PLATFORM_NAME
chprintf((BaseSequentialStream *)&SD1, "Platform:     %s\r\n", PLATFORM_NAME);
#endif

#ifdef BOARD_NAME
    chprintf((BaseSequentialStream *)&SD1, "Board:        %s\r\n", BOARD_NAME);
#endif

#ifdef __DATE__
    #ifdef __TIME__
        chprintf((BaseSequentialStream *)&SD1, "Build time:   %s%s%s\r\n", __DATE__, " - ", __TIME__);
    #endif
#endif

#endif

    chprintf((BaseSequentialStream *)&SD1, "Firmware written by: Achmadi S.T. \r\n", BOARD_NAME);
}
/** @} */
