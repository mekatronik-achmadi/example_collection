CC = xtensa-lx106-elf-gcc
CFLAGS = -I. -mlongcalls
LDLIBS = -nostdlib -Wl,--start-group -lmain -lnet80211 -lwpa -llwip -lpp -lphy -lc -Wl,--end-group -lgcc -ldriver
LDFLAGS = -Teagle.app.v6.ld
INITBIN = /opt/esp-open-sdk/ESP8266_NONOS_SDK-2.1.0-18-g61248df/bin/esp_init_data_default.bin
BLANKBIN = /opt/esp-open-sdk/ESP8266_NONOS_SDK-2.1.0-18-g61248df/bin/blank.bin

all: main_user-0x00000.bin

main_user-0x00000.bin: main_user
	esptool elf2image $^

main_user: main_user.o

main_user.o: main_user.c

flash: main_user-0x00000.bin
	sudo esptool -p /dev/ttyUSB0 erase_flash
	sudo esptool -p /dev/ttyUSB0 write_flash 0x3e000 $(BLANKBIN) 0x3fc000 $(INITBIN) 0x3fe000 $(BLANKBIN)
	sudo esptool -p /dev/ttyUSB0 write_flash 0x00000 main_user-0x00000.bin 0x10000 main_user-0x10000.bin
clean:
	rm -f main_user main_user.o main_user-0x00000.bin main_user-0x10000.bin
