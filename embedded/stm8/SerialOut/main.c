#include <stdint.h>
#include <stdio.h>

#include "stm8s.h"

#define LED_GPIO_PORT   (GPIOA)
#define LED_GPIO_PINS   (GPIO_PIN_3)

void Delay(uint32_t nCount){
    while (nCount !=0) {
        nCount--;
    }
}

int putchar(int c){
    UART1_SendData8(c);
    while (UART1_GetFlagStatus(UART1_FLAG_TXE)==RESET);
    return (c);
}

int getchar(void){
    int c = 0;
    while (UART1_GetFlagStatus(UART1_FLAG_RXNE)==RESET);
    c = UART1_ReceiveData8();
    return c;
}

static void Serial_Init(void){
    CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);

    UART1_DeInit();
    UART1_Init((uint32_t)9600,
                UART1_WORDLENGTH_8D,
                UART1_STOPBITS_1,
                UART1_PARITY_NO,
                UART1_SYNCMODE_CLOCK_DISABLE,
                UART1_MODE_TXRX_ENABLE);
}

int main(void)
{
    GPIO_Init(LED_GPIO_PORT, (GPIO_Pin_TypeDef) LED_GPIO_PINS, GPIO_MODE_OUT_PP_LOW_FAST);

    Serial_Init();

    printf("Serial Print OK\r\n");

    while (1) {
        GPIO_WriteReverse(LED_GPIO_PORT, (GPIO_Pin_TypeDef)LED_GPIO_PINS);
        Delay(0xAFFFF);
    }
}



#ifdef USE_FULL_ASSERT

void assert_failed(uint8_t* file, uint32_t line){
    (void) file;
    (void) line;

    while(1){}
}

#endif
