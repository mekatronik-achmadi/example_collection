#ifndef _CONSOLE_
#define _CONSOLE_

#define SHELL_WA_SIZE   THD_WORKING_AREA_SIZE(2048)
#define TEST_WA_SIZE    THD_WORKING_AREA_SIZE(256)

void consoleInit(void);
void consoleLoop(void);

#endif