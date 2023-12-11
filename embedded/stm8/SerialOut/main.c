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

static void Clk_Init(void){
    CLK_DeInit();

    CLK_HSECmd(DISABLE);
    CLK_LSICmd(DISABLE);
    CLK_HSICmd(ENABLE);
    while(CLK_GetFlagStatus(CLK_FLAG_HSIRDY) == FALSE);

    CLK_ClockSwitchCmd(ENABLE);
    CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);
    CLK_SYSCLKConfig(CLK_PRESCALER_CPUDIV1);
    CLK_ClockSwitchConfig(CLK_SWITCHMODE_AUTO, CLK_SOURCE_HSI,
    DISABLE, CLK_CURRENTCLOCKSTATE_ENABLE);

    CLK_PeripheralClockConfig(CLK_PERIPHERAL_SPI, DISABLE);
    CLK_PeripheralClockConfig(CLK_PERIPHERAL_I2C, DISABLE);
    CLK_PeripheralClockConfig(CLK_PERIPHERAL_ADC, DISABLE);
    CLK_PeripheralClockConfig(CLK_PERIPHERAL_AWU, DISABLE);
    CLK_PeripheralClockConfig(CLK_PERIPHERAL_UART1, ENABLE);
    CLK_PeripheralClockConfig(CLK_PERIPHERAL_TIMER1, DISABLE);
    CLK_PeripheralClockConfig(CLK_PERIPHERAL_TIMER2, DISABLE);
    CLK_PeripheralClockConfig(CLK_PERIPHERAL_TIMER4, DISABLE);
}

static void PAL_Init(void){
    GPIO_DeInit(GPIOD);
    GPIO_Init(GPIOD, GPIO_PIN_5, GPIO_MODE_OUT_PP_HIGH_FAST);
    GPIO_Init(GPIOD, GPIO_PIN_6, GPIO_MODE_IN_PU_NO_IT);
    GPIO_Init(LED_GPIO_PORT, (GPIO_Pin_TypeDef) LED_GPIO_PINS, GPIO_MODE_OUT_PP_LOW_FAST);
}

static void Serial_Init(void){
    UART1_DeInit();
    UART1_Init((uint32_t)9600,
                UART1_WORDLENGTH_8D,
                UART1_STOPBITS_1,
                UART1_PARITY_NO,
                UART1_SYNCMODE_CLOCK_DISABLE,
                UART1_MODE_TXRX_ENABLE);

    UART1_ITConfig(UART1_IT_RXNE_OR, ENABLE);

    UART1_Cmd(ENABLE);
}

int main(void)
{
    Clk_Init();
    PAL_Init();
    Serial_Init();

    enableInterrupts();

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
