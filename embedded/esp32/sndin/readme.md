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
	+ [Setup](#setup)
	+ [Build](#build)
- [PlatformIO](#platformio)
	+ [Setup](#setup-1)
	+ [Home](#home-server)
	+ [Build](#build-1)
- [PlatformIO VSCode](#platformio-vscode)
	+ [Setup](#setup-2)
	+ [Home](#home-page)
- [Serial Plotter](#serial-plotter)
	+ [Qt Serial Plot](#qt-serial-plot)
	+ [Arduplot](#arduplot)
	+ [Python Serial Plot](#python-serial-plot)

**note:** The recommended platform is PlatformIO as it easier because everything downloaded from their server and available on both Windows or GNU/Linux.

## Wiring

**note:** SPH0645 still untested

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

**note:** This command is for ArchLinux or its derivative.

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

**note:** You just need to do this once to generate **sdkconfig** file.

```sh
make defconfig
```

#### generate compile commands for clangd

**note:** You just need to do this once

```sh
bear -- make app
```

#### reflash bootloader and partition table

**note:** You just need to do this once for each development kit.
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

**note:** The user codebase is similar to IDF version with some changes.
The difference only in framework installation source.

### Setup

#### environment

```sh
cd $HOME
virtualenv platformio --system-site-packages

source $HOME/platformio/bin/activate
mkdir -p $HOME/.platformio/
pip install platformio

deactivate
cd -
```

#### install USB permission

**note:** This is may necessary for GNU/Linux system.

```sh
UDEV=https://raw.githubusercontent.com/platformio/platformio-core/develop/platformio/assets/system/99-platformio-udev.rules
curl -fsSL $UDEV | sudo tee /etc/udev/rules.d/99-platformio-udev.rules
sudo udevadm control --reload-rules
sudo udevadm trigger
```

#### install framework

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

**note:** You just need to do this once

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

## PlatformIO VSCode

**note:** This part if you prefer using Visual Studio Code.
If you using Vim or other programming editor, you may follow previous step and skip this part.

### Setup

First, install Visual Studio Code:

- Windows: [Download](https://code.visualstudio.com/download/)
- ArchLinux/Manjaro: [AUR](https://aur.archlinux.org/packages/visual-studio-code-bin)
- Debian/Ubuntu: [Download](https://code.visualstudio.com/download/)

Then install this extension: [PlatformIO](https://marketplace.visualstudio.com/items?itemName=platformio.platformio-ide)

You may install from command line using command:

```sh
code --install-extension platformio.platformio-ide
code --install-extension ms-vscode.vscode-serial-monitor
```

Or from VSCode Quick Open (Ctrl+P):

```
ext install platformio.platformio-ide
ext install ms-vscode.vscode-serial-monitor
```

**tips:**

You may need to disable/remove Clangd, if you prefer Microsoft's C/C++ extension:

```sh
code --uninstall-extension llvm-vs-code-extensions.vscode-clangd
```

### Home Page

Open PlatformIO Project Tasks, from VSCode Quick Open (Ctrl+P):

```
View: Show PlatformIO
```

Then on **Quick Access** -> **PIO Home**, click **Open**

Next, to open project, click **Pick a Folder** on Project Tasks.

Then, from Project Tasks, you can build and upload your project.

To access Serial Port, from VSCode Quick Open (Ctrl+P):

```
View: Toggle Serial Monitor
```

## Serial Plotter

They are several Serial Plotter available for Windows and GNU/Linux

**note:** make sure you have device access as mentioned before.

### Qt Serial Plot

A Qt5/QWT based serial plot. 

Visit [Project Page](https://github.com/hyOzd/serialplot).

Installation:

- ArchLinux/Manjaro: [AUR](https://aur.archlinux.org/packages/serialplot-hg)
- Debian/Ubuntu: [AppImage](https://serialplot.ozderya.net/downloads/serialplot-0.12.0-x86_64.AppImage)
- Windows: [Setup x86](https://serialplot.ozderya.net/downloads/serialplot-0.12.0-win32-setup.exe)

### Arduplot

A clone of Arduino Plotter without Arduino IDE and come as a Python package.

Visit [Project Page](https://github.com/yhur/arduplot).

Installing inside in an environment on GNU/Linux or MSYS2 (Windows):

```sh
cd $HOME
virtualenv arduplot --system-site-packages

source $HOME/arduplot/bin/activate
pip install arduplot

deactivate
cd -
```

then to use:

```sh
source $HOME/arduplot/bin/activate
arduplot -p /dev/ttyUSB0 -b 115200
```

### Python Serial Plot

This in example of serial plotting using Matplotlib and PySerial.

First, install required modules. For ArchLinux/Manjaro:

```sh
sudo pacman -S python-matplotlib python-pyserial
```

The Python script is [here](https://github.com/mekatronik-achmadi/example_collection/tree/master/embedded/esp32/sndin/serialgraph)

Download and run using command (assumed you have device access):

```sh
python serialgraph.py /dev/ttyUSB0
```
