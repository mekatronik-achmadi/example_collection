#ifndef BLINK_H
#define BLINK_H

#define BLINK_LED   16
#define BLINK_GPIO  (1ULL << BLINK_LED)
#define BLINK_DELAY 100

void nvs_Init(void);
void led_Init(void);

#endif
