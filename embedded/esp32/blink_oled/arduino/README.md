# ESP32 Arduino Example

This particular example show minimum example of ESP32 using Arduino framework, which actually employ ESP-IDF and GGC-Xtensa under the hood.
For that reason, the source written in same C-API as ESP-IDF (not C++) despite in regular INO file.

## Contents
- [Minimum Hardware](#minimum-hardware)
- [Framework Installation](#framework-installation)
    + [OLED LCD Library](#oled-lcd-library)
- [Source Download](#source-download)
- [Compilation and Flashing](#compilation-and-flashing)

## Minimum Hardware

This example use NodeMCU ESP32 with OLED LCD SH1106 connected to GPIO as I2C.
Programmer done through its TTL-USB chip connected to UART0 as default.

Here GPIO List:

| I/O | Func |
|:---:|:----:|
| IO2 | LED |
|IO22 | LCD_SCL |
|IO21 | LCD_SDA |

![images](images/board.jpg?raw=true)

## Framework Installation

This example tested using **Arduino IDE 1.8.16** on **Arch-Linux 5.10-LTS**.
It should be reproducible in other operating system such as Windows.

First, install required ESP32 board library.
Open *File*  -> *Preferences*.
Then open Additional Board Manager URLs dialog and add URL below:

```
https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_dev_index.json
```

![images](images/arduino_board.png?raw=true)

Next, open *Tools* -> *Board* -> *Board Manager*.

![images](images/board_manager.png?raw=true)

On Search Filter, type ESP32, choose **2.0.0** version (as it based on ESP-IDF 4.4), then press *Install* button.

![images](images/esp32_install.png?raw=true)

Wait until finished and done.

### OLED LCD Library

You need to install the prepared OLED LCD Library in **myoledlcd**  folder.

Easiest way to do is download the folder in zip format.
Here you download using Downgit URL: [Download myoledlcd](https://minhaskamal.github.io/DownGit/#/home?url=https://github.com/mekatronik-achmadi/example_collection/tree/master/embedded/esp32/blink_oled/arduino/myoledlcd)

Then you can import library as zip using *Sketch* -> *Include Library* -> *Add .ZIP Library*

![images](images/add_zip_lib.png?raw=true)

## Source Download

For minimum example, you can find it in *File* -> *Examples* -> *Examples from Custom Libraries*.
Choose **text_drawing**.

![images](images/example.png?raw=true)

If you cant find the example (you should find it if the library already installed), you can copy and paste code below:

```c
#include <myoledlcd.h>

#define BLINK_GPIO  GPIO_NUM_2

void setup(void){
  gpio_reset_pin(BLINK_GPIO);
  gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);
  my_oledInit();
  my_olcdtest_text();
}

void loop(void){
    gpio_set_level(BLINK_GPIO, 0);
    ets_delay_us(500000);

    gpio_set_level(BLINK_GPIO, 1);
    ets_delay_us(500000);
}
```

## Compilation and Flashing

Before continue, make sure you choose correct board for Arduino's target.

Next, open *Tools* -> *Board* -> *ESP32 Arduino* -> *ESP32 Dev Module*.

The board setting should became looks like this:

 ![images](images/esp32_board.png?raw=true)
 
 To compile, click *Sketch* -> *Verify/Compile*
 
 To Upload, click *Sketch* -> *Upload*
 
**NOTES:** Make sure the **Port** (either **/dev/ttyUSBx** in Linux or **COMx** in Windows) is correct.
 
 **NOTES:** As some NodeMCU board had problem with RTS/CTS logic, you may need to hold down Flash or IO0 button to enter flashing mode when the **esptool.py** try to reset the board.
 
**NOTES:**  Arduino will override the board's bootloader and partition table automatically when flashing. No need to do it manually.

**NOTES:** Arduino's bootloader both checking RTS/CTS and IO15 logic state to start the app. You may need to power-on reset the NodeMCU board. No need to worry this workaround if you use custom ESP32 board without RTS/CTS.