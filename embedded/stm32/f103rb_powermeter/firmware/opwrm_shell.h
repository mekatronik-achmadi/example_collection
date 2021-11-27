#ifndef OPWRM_SHELL
#define OPWRM_SHELL

#define SHELL_WA_SIZE   THD_WA_SIZE(2048)
#define TEST_WA_SIZE    THD_WA_SIZE(256)

void Serial_Setup(void);
void Shell_Setup(void);

#endif