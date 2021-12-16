# Parameters for compiling
ARDMK_VENDOR	= archlinux-arduino
ARDUINO_DIR     = /usr/share/arduino
TARGET          = output
ARDUINO_LIBS    =  
AVR_TOOLS_DIR	=  

#CFLAGS        += 
#CXXFLAGS      += 
#ASFLAGS       += 
#LDFLAGS       += -u vfprintf -lprintf_flt -u vfscanf -lscanf_flt

BOARD_TAG	= mega
BOARD_SUB	= atmega2560
# If you found problem on compile, you can uncomment and change MCU and F_CPU
# To know what MCU you can use check board.txt on end of this file
#MCU		= atmega2560
#F_CPU		= 16000000
MONITOR_PORT = /dev/ttyACM0

# Avrdude command for programming
#sudo avrdude -v -p m2560 -c wiring -P /dev/ttyACM0 -D -U flash:w:output.hex:i
#sudo avrdude -v -p m328p -c arduino -P /dev/ttyACM0 -D -U flash:w:output.hex:i

# Arduino makefile
include /usr/share/arduino/Arduino.mk

# Bellow you found MCU values extracted from board.txt file. Added just to reference
# MCU data is the info after .menu.cpu.
# Example: #atmegang.menu.cpu.atmega168.build.mcu=atmega168 => MCU = atmega168
#
#atmegang.build.mcu=atmegang
#atmegang.menu.cpu.atmega168.build.mcu=atmega168
#atmegang.menu.cpu.atmega8.build.mcu=atmega8
#bt.menu.cpu.atmega328.build.mcu=atmega328p
#bt.menu.cpu.atmega168.build.mcu=atmega168
#diecimila.menu.cpu.atmega328.build.mcu=atmega328p
#diecimila.menu.cpu.atmega168.build.mcu=atmega168
#esplora.build.mcu=atmega32u4
#ethernet.build.mcu=atmega328p
#fio.build.mcu=atmega328p
#leonardo.build.mcu=atmega32u4
#lilypad.menu.cpu.atmega328.build.mcu=atmega328p
#lilypad.menu.cpu.atmega168.build.mcu=atmega168
#LilyPadUSB.build.mcu=atmega32u4
#megaADK.build.mcu=atmega2560
#mega.menu.cpu.atmega2560.build.mcu=atmega2560
#mega.menu.cpu.atmega1280.build.mcu=atmega1280
#megaADK.build.mcu=atmega2560
#micro.build.mcu=atmega32u4
#mini.menu.cpu.atmega328.build.mcu=atmega328p
#mini.menu.cpu.atmega168.build.mcu=atmega168
#nano.menu.cpu.atmega328.build.mcu=atmega328p
#nano.menu.cpu.atmega168.build.mcu=atmega168
#pro.menu.cpu.16MHzatmega328.build.mcu=atmega328p
#pro.menu.cpu.8MHzatmega328.build.mcu=atmega328p
#pro.menu.cpu.16MHzatmega168.build.mcu=atmega168
#pro.menu.cpu.8MHzatmega168.build.mcu=atmega168
#robotControl.build.mcu=atmega32u4
#robotMotor.build.mcu=atmega32u4
#uno.build.mcu=atmega328p
#yun.build.mcu=atmega32u4
