/**
 * @file   m_shell.h
 * @brief  Communication Shell handler header
 *
 * @addtogroup M_USB
 * @{
 */
#ifndef M_SHELL_H
#define M_SHELL_H

#include "ch.h"
#include "hal.h"
#include "gfx.h"

#include "chprintf.h"
#include "shell.h"

#include "math.h"
#include "stdlib.h"
#include "stdio.h"

#include "usbcfg.h"

/**
 * @brief   shell thread size.
 */
#define SHELL_WA_SIZE   THD_WORKING_AREA_SIZE(2048)
/**
 * @brief   test routine size.
 */
#define TEST_WA_SIZE    THD_WORKING_AREA_SIZE(256)

void m_shell_start(void);
void m_shell_term(void);

#endif // M_SHELL_H
/** @} */
