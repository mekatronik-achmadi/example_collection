/**
 * @file keypad.c
 * @brief Keypad driver code
 *
 * @addtogroup GPIO
 * @{
 */

#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "driver/gpio.h"

#include "keypad.h"
#include "input.h"

/**
 * @brief First column
 *
 */
#define IN_0    25

/**
 * @brief Second column
 *
 */
#define IN_1    26

/**
 * @brief Third column
 *
 */
#define IN_2    27

/**
 * @brief Column as input GPIO
 *
 */
#define KEY_IN_PIN_SEL      ((1ULL<<IN_0) | \
                            (1ULL<<IN_1)  | \
                            (1ULL<<IN_2))

/**
 * @brief First row
 *
 */
#define OUT_0   18

/**
 * @brief Second row
 *
 */
#define OUT_1   19

/**
 * @brief Third row
 *
 */
#define OUT_2   16

/**
 * @brief Fourth row
 *
 */
#define OUT_3   17

/**
 * @brief Row as output GPIO
 *
 */
#define KEY_OUT_PIN_SEL     ((1ULL<<OUT_0) | \
                            (1ULL<<OUT_1)  | \
                            (1ULL<<OUT_2)  | \
                            (1ULL<<OUT_3))

/**
 * @brief Lock flag to avoid bouncing/double entry
 *
 */
static bool keyLock = false;

/**
 * @brief Set all row output to low
 *
 */
static void keygpioLow(void){
    gpio_set_level(OUT_0, 0);
    gpio_set_level(OUT_1, 0);
    gpio_set_level(OUT_2, 0);
    gpio_set_level(OUT_3, 0);
}

/**
 * @brief Keyboard scanning routine
 *
 */
static void keygpioScan(void){
    bool noInput = true;

    keygpioLow();
    gpio_set_level(OUT_0, 1);
    if(gpio_get_level(IN_0)==1){
        noInput = false;
        if(!keyLock) key_Inputs('1');
    }
    if(gpio_get_level(IN_1)==1){
        noInput = false;
        if(!keyLock) key_Inputs('2');
    }
    if(gpio_get_level(IN_2)==1){
        noInput = false;
        if(!keyLock) key_Inputs('3');
    }

    keygpioLow();
    gpio_set_level(OUT_1, 1);
    if(gpio_get_level(IN_0)==1){
        noInput = false;
        if(!keyLock) key_Inputs('4');
    }
    if(gpio_get_level(IN_1)==1){
        noInput = false;
        if(!keyLock) key_Inputs('5');
    }
    if(gpio_get_level(IN_2)==1){
        noInput = false;
        if(!keyLock) key_Inputs('6');
    }

    keygpioLow();
    gpio_set_level(OUT_2, 1);
    if(gpio_get_level(IN_0)==1){
        noInput = false;
        if(!keyLock) key_Inputs('7');
    }
    if(gpio_get_level(IN_1)==1){
        noInput = false;
        if(!keyLock) key_Inputs('8');
    }
    if(gpio_get_level(IN_2)==1){
        noInput = false;
        if(!keyLock) key_Inputs('9');
    }

    keygpioLow();
    gpio_set_level(OUT_3, 1);
    if(gpio_get_level(IN_0)==1){
        noInput = false;
        if(!keyLock) key_Inputs('*');
    }
    if(gpio_get_level(IN_1)==1){
        noInput = false;
        if(!keyLock) key_Inputs('0');
    }
    if(gpio_get_level(IN_2)==1){
        noInput = false;
        if(!keyLock) key_Inputs('#');
    }

    if(!noInput){
        keyLock = true;
    }
    else {
        keyLock = false;
    }
}

/**
 * @brief Initiate keypad GPIO
 *
 */
static void keygpioInit(void){
    gpio_config_t io_conf;

    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = KEY_OUT_PIN_SEL;
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    io_conf.pull_up_en = GPIO_PULLUP_DISABLE;
    gpio_config(&io_conf);

    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pin_bit_mask = KEY_IN_PIN_SEL;
    io_conf.pull_down_en = GPIO_PULLDOWN_ENABLE;
    io_conf.pull_up_en = GPIO_PULLUP_DISABLE;
    gpio_config(&io_conf);
}

/**
 * @brief Keypad scanning loop task
 *
 * @param pvParameter
 */
static void keypadTask(void *pvParameter){
    keygpioLow();

    while (1) {
        keygpioScan();
        vTaskDelay(KEYPAD_DELAY / portTICK_PERIOD_MS);
    }
}

/**
 * @brief Initiate Keypad driver
 *
 */
void keypadInit(void){
    keygpioInit();
    xTaskCreate(&keypadTask, "keypad_task", 2048, NULL, 4, NULL);
}

/** @} */