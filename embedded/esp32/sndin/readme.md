# ESP32-based Sound Input Testing

## Acknowledge

This work are based on:
- [ESP32 Sound Spectrum](https://github.com/pedrominatel/esp32-projects/blob/master/demo/sound_spectrum/main/i2s_spectrum_example_main.c)
- [Adafruit Guide](https://learn.adafruit.com/adafruit-i2s-mems-microphone-breakout)

## Contents

This folder contains:

- [Wiring](#wiring)
- [Device Access](#device-access)
- [ESP IDF](#idf)
- [PlatformIO](#platformio)

**NOTES:** The recommended platform is PlatformIO as it easier because everything downloaded from their server and available on both Windows or GNU/Linux.

## Wiring

**NOTES:** SPH0645 still untested

| INMP441 | SPH0645 | ESP32 | DEVKIT |
|:-------:|:-------:|:-----:|:------:|
| L/R     | SEL     | GND   | GND    |
| WS      | LRCL    | IO13  | D13    |
| SD      | DOUT    | IO23  | D23    |
| SCK     | BCLK    | IO14  | D14    |
| GND     | GND     | GND   | GND    |
| VDD     | 3V      | VDD   | 3V3    |

## Device Access

Run these command to gain device access without sudo:

```sh
sudo groupadd -fr lock
sudo groupadd -fr uucp

sudo gpasswd -a $USER lock
sudo gpasswd -a $USER uucp
```

**NOTES:** This command is for ArchLinux or its derivative.

Then reboot.

## IDF

This source tree based on XTensa's GCC for ESP32 and ESP-IDF from Espressif.
Information described here on works only for Arch-Linux or its derivative.

### Setup

Install following Arch Linux Packages:

- Python 3.9: [AUR](https://aur.archlinux.org/packages/python39/)
- XTensa GCC (remove all python2-*): [AUR](https://aur.archlinux.org/packages/xtensa-esp32-elf-gcc-bin/)
- ESP-IDF: [PKGBUILD](https://github.com/mekatronik-achmadi/archmate/tree/main/pkgbuilds/optional/esp32-idf/)
- ESP-DSP: [PKGBUILD](https://github.com/mekatronik-achmadi/archmate/tree/main/pkgbuilds/optional/esp32-dsp/)

Then setup Python environment:

```sh
cd $HOME
virtualenv --python=/usr/bin/python3.9 esp-python --system-site-packages

source $HOME/esp-python/bin/activate
pip install kconfiglib future cryptography pyserial pyparsing==2.2.0
deactivate

cd -
```

run these command script to use virtual environment

```sh
source esp32env.sh
```

### Build

#### generate default sdkconfig

**NOTES:** You just need to do this once to generate **sdkconfig** file.

```sh
make defconfig
```

#### generate compile commands for clangd

**NOTES:** You just need to do this once

```sh
bear -- make app
```

#### reflash bootloader and partition table

**NOTES:** You just need to do this once each development kit.
But you should repeat this step after flashing firmware using Arduino or PlatformIO.

Connect USB and run commands:

```sh
make erase_flash
make bootloader-flash
make partition_table-flash
```

#### compile app and flashing

compile command:

```sh
make app
```

if successfully compiled, flash to chip using command:

```sh
make app-flash
```

## PlatformIO

This source tree based on XTensa's GCC for ESP32 and ESP-IDF from PlatformIO server.
Information described here tested on ArchLinux but should work Windows using Python or MSYS2.

**NOTES:** The user codebase is similar to IDF version with some changes.
The difference only in framework installation source.

### Setup

#### environment

```sh
cd $HOME
virtualenv platformio --system-site-packages

source $HOME/platformio/bin/activate
mkdir -p $HOME/.platformio/
pip install platformio

UDEV=https://raw.githubusercontent.com/platformio/platformio-core/develop/platformio/assets/system/99-platformio-udev.rules
curl -fsSL $UDEV | sudo tee /etc/udev/rules.d/99-platformio-udev.rules
sudo udevadm control --reload-rules
sudo udevadm trigger

deactivate
cd -
```

### install framework

```sh
source $HOME/platformio/bin/activate
pio project init -b esp32dev -O 'framework=espidf'
```

### Home Server

```sh
source $HOME/platformio/bin/activate
pio home --no-open &
xdg-open http://localhost:8008/ &
```

### Build

#### generate compile commands for clangd

**NOTES:** You just need to do this once

```sh
source $HOME/platformio/bin/activate
export MAKEFLAGS=-j$(nproc)

make compiledb
```

#### compile app and flashing

compile command:

```sh
make all
```

if successfully compiled, flash to chip using command:

```sh
make upload
```
