CC = xtensa-lx106-elf-gcc
CFLAGS = -I. -mlongcalls
LDLIBS = -nostdlib -Wl,--start-group -lmain -lnet80211 -lwpa -llwip -lpp -lphy -lc -Wl,--end-group -lgcc -ldriver
LDFLAGS = -Teagle.app.v6.ld
INITBIN = /opt/esp-open-sdk/ESP8266_NONOS_SDK-2.1.0-18-g61248df/bin/esp_init_data_default.bin
BLANKBIN = /opt/esp-open-sdk/ESP8266_NONOS_SDK-2.1.0-18-g61248df/bin/blank.bin

all: blinky-0x00000.bin

blinky-0x00000.bin: blinky
	esptool elf2image $^

blinky: blinky.o

blinky.o: blinky.c

flash: blinky-0x00000.bin
	sudo esptool -p /dev/ttyUSB0 erase_flash
	sudo esptool -p /dev/ttyUSB0 write_flash 0x3e000 $(BLANKBIN) 0x3fc000 $(INITBIN) 0x3fe000 $(BLANKBIN)
	sudo esptool -p /dev/ttyUSB0 write_flash 0x00000 blinky-0x00000.bin 0x10000 blinky-0x10000.bin
clean:
	rm -f blinky blinky.o blinky-0x00000.bin blinky-0x10000.bin
