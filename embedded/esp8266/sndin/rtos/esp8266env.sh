#!/bin/bash

# make defconfig
# make erase_flash
# make bootloader-flash
# make partition_table-flash

# make app
# make app-flash

export IDF_PATH=/opt/esp8266-rtos
export PATH="$IDF_PATH/tools:$PATH"
export MAKEFLAGS="-j$(nproc)"
export GNUMAKEFLAGS="-j$(nproc)"
source $HOME/esp-python/bin/activate

