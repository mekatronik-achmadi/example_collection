#ifndef ESP_SHELL_H
#define ESP_SHELL_H

#define CONFIG_ESP_CONSOLE_UART_NUM 0
#define UART_USE_PROMPT             1

void shell_Init(void);
int shell_Loop(void);

#endif
