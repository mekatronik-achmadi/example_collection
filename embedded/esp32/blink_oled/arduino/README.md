# ESP32 Arduino Example

This particular example show minimum example of ESP32 using Arduino framework, which actually employ ESP-IDF and GGC-Xtensa under the hood.
For that reason, the source written in same C-API with ESP-IDF despite in regular INO file.

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

This example tested using Arduino IDE 1.8.16 on Arch-Linux 5.10-LTS.
It should be reproducible in other operating system such as Windows.

First, install required ESP32 library.
Open *File*  -> *Preferences*.
Then open Additional Board Manager URLs dialog and add URL below:

```
https://dl.espressif.com/dl/package_esp32_index.json
```

![images](images/arduino_board.png?raw=true)

Next, open *Tools* -> *Board* -> *Board Manager*.

![images](images/board_manager.png?raw=true)

On Search Filter, type ESP32, choose latest version, then press *Install* button.

![images](images/esp32_install.png?raw=true)

Wait until finished and done.

### OLED LCD Library

**I'M STUCK HERE**

## Source Download

All your need is just **blink_oled.ino** file.
You can download as single file from **blink_oled** folder.

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