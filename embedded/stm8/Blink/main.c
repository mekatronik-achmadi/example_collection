#include <stdint.h>

#include "stm8s.h"

#define LED_GPIO_PORT   (GPIOA)
#define LED_GPIO_PINS   (GPIO_PIN_3)

void Delay(uint16_t nCount);

int main(void)
{
    GPIO_Init(LED_GPIO_PORT, (GPIO_Pin_TypeDef) LED_GPIO_PINS, GPIO_MODE_OUT_PP_LOW_FAST);

    while (1) {
        GPIO_WriteReverse(LED_GPIO_PORT, (GPIO_Pin_TypeDef)LED_GPIO_PINS);
        Delay(0x8FFF);
    }
}

void Delay(uint16_t nCount){
    while (nCount !=0) {
        nCount--;
    }
}

#ifdef USE_FULL_ASSERT

void assert_failed(uint8_t* file, uint32_t line){
    (void) file;
    (void) line;

    while(1){}
}

#endif
