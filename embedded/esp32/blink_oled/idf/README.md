# ESP32 IDF Example

This particular example show minimum example of ESP32 using ESP-IDF framework compiled directly on GCC Xtensa.

## Contents
- [Framework Installation](#framework-installation)

## Framework Installation

This installation guidance currently limited only to ArchLinux operating system or its derivatives such as Manjaro.

First install GCC Xtensa specificly for ESP32 from AUR here:
https://aur.archlinux.org/packages/xtensa-esp32-elf-gcc-bin/

**NOTES:** You should changes all **python2-** dependencies to **python-** in its PKGBUILD recipe.

Next, install ESP-IDF (tested only in version 4.3) using my own PKGBUILD here:
https://github.com/mekatronik-achmadi/archmate/tree/master/packages/pkgbuild/esp32-idf/

Last, install Python modules for KConfig and PyParsing.
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
