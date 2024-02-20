# ESP32-based Sound Input Testing

## Acknowledge

This work are based on:
- [ESP32 Sound Spectrum](https://github.com/pedrominatel/esp32-projects/blob/master/demo/sound_spectrum/main/i2s_spectrum_example_main.c)
- [Adafruit Guide](https://learn.adafruit.com/adafruit-i2s-mems-microphone-breakout)

## Contents

This folder contains:

- [Wiring](#wiring)
- [ESP IDF](#idf)
- [PlatformIO](#platformio)

## Wiring

| INMP441 | SPH0645 | ESP32 | DEVKIT |
|:-------:|:-------:|:-----:|:------:|
| L/R     | SEL     | GND   | GND    |
| WS      | LRCL    | IO13  | D13    |
| SD      | DOUT    | IO23  | D23    |
| SCK     | BCLK    | IO14  | D14    |
| GND     | GND     | GND   | GND    |
| VDD     | 3V      | VDD   | 3V3    |

## IDF

This source tree based on XTensa's GCC for ESP32, ESP-IDF, and ESP-DSP.
Information described here on works only for Arch-Linux or its derivative.

### Device Access

Run these command to gain device access without sudo:

```sh
sudo groupadd -fr lock
sudo groupadd -fr uucp

sudo gpasswd -a $USER lock
sudo gpasswd -a $USER uucp
```

Then reboot.

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

Coming Soon
