/**
 * @file   m_gui.h
 * @brief  GUI handler header
 *
 * @addtogroup M_GUI
 * @{
 */

#ifndef M_GUI_H
#define M_GUI_H

#include "ch.h"
#include "hal.h"
#include "gfx.h"

#include "chprintf.h"
#include "shell.h"

#include "math.h"
#include "stdlib.h"
#include "stdio.h"

#include "m_gui.h"
#include "m_shell.h"

#define DRAW_RAND FALSE

#define DATASIZE 256
#define N_DISPDATA 320
#define LEFT_TO_RIGHT TRUE
#define GRAPH_SCALE 0.0

void m_gui_start(void);
void m_gui_empty(void);
void m_gui_sine(void);
void m_data_set(uint16_t val);

#endif // M_GUI_H
/** @} */
