# ESP32 IDF Example

This particular example show minimum example of ESP32 using ESP-IDF framework compiled directly on GCC Xtensa.

## Contents
- [Minimum Hardware](#minimum-hardware)
- [Framework Installation](#framework-installation)
- [Source Download](#source-download)

## Minimum Hardware

This example use NodeMCU ESP32 with OLED LCD SH1106 connected to GPIO as I2C.
Programmer done through its TTL-USB chip connected to UART0 as default.

Here GPIO List:

| I/O | Func |
|:---:|:----:|
| IO2 | LED |
|IO22 | LCD_SCL |
|IO21 | LCD_SDA |

![images](board.jpg?raw=true)


## Framework Installation

This installation guidance currently limited only to ArchLinux operating system or its derivatives such as Manjaro.

First install GCC Xtensa specificly for ESP32 from AUR here:
https://aur.archlinux.org/packages/xtensa-esp32-elf-gcc-bin/

**NOTES:** You should changes all **python2-** dependencies to **python-** in its PKGBUILD recipe.

Next, install ESP-IDF (tested only in version 4.3) using my own PKGBUILD here:
https://github.com/mekatronik-achmadi/archmate/tree/master/packages/pkgbuild/esp32-idf/

Last, install Python modules for KConfig and PyParsing (version 2.2.0 or before).
I recommend install as user installation (not system wide).

For example you can use commands like this:

```sh
cd $HOME
virtualenv esp-python --system-site-packages

source $HOME/esp-python/bin/activate
pip install --no-deps kconfiglib
pip install --no-deps pyparsing==2.2.0
deactivate
```

## Source Download

Files you need download required source files and structure folder like this:

```
+-- idf
|   +-- Makefile
|   +-- sdkconfig
|   +-- main
|        +-- component.mk
|        +-- blink_oled.c
```

## Compilation

To build the firmware binary, first open terminal on the **idf** folder's path.
Then activate the Python environment using commands:

```sh
export IDF_PATH=/opt/esp-idf
source $HOME/esp-python/bin/activate
```

Then generate the default configuration using comand:

```sh
make defconfig
```