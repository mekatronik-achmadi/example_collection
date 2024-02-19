# ESP8266 Sound Input Testing

## Acknowledge

This work is based on:

- [ESP8266 I2S Mic]()
- [Adafruit Guide](https://learn.adafruit.com/adafruit-i2s-mems-microphone-breakout)

## Contents

- [Wiring](#wiring)
- [ESP RTOS](#rtos)
- [PlatformIO](#platformio)

## Wiring

| INMP441 | SPH0645 | ESP8266 | NODEMCU |
|:-------:|:-------:|:-------:|:-------:|
| L/R | SEL | GND | GND |
| WS | LRCL | GPIO14 | D5 |
| SD | DOUT | GPIO12 | D6 |
| SCK | BCLK | GPIO13 | D7 |
| GND | GND | GND | GND |
| VDD | 3V | VDD | VDD |


