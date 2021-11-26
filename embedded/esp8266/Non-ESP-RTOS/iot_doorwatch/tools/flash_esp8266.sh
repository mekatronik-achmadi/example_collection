#!/bin/bash

WORKDIR=$(pwd)/../firmware/
UNIX_OS=$(lsb_release -i | cut -f2)
SERTERM=minicom

if [ $UNIX_OS == "Arch" ];then
	ESP_SDK_BIN=/opt/esp-open-sdk/sdk/bin/
	ROOTING=sudo
	ESPTOOL=esptool
	ESPPORT=/dev/ttyUSB0
	
elif [ $UNIX_OS = "Ubuntu" ];then
	echo "Ubuntu not supported yet"
	exit
elif [ $UNIX_OS = "Debian" ];then
	echo "Debian not supported yet"
	exit
elif [ $UNIX_OS = "MacOS" ];then
	echo "MacOS not supported yet"
	exit	
fi

BLANK_1_ADDR=0x3e000
INIT_2_ADDR=0x3fc000
BLANK_2_ADDR=0x3fe000

FW_FILE_1_ADDR=0x00000
FW_FILE_2_ADDR=0x10000

INITBIN=${ESP_SDK_BIN}/esp_init_data_default.bin
BLANKBIN=${ESP_SDK_BIN}/blank.bin

FW_FILE_1=${WORKDIR}/${FW_FILE_1_ADDR}.bin
FW_FILE_2=${WORKDIR}/${FW_FILE_2_ADDR}.bin

make clean
make all
if [ $? -eq 0 ];then
	${ROOTING} ${ESPTOOL} --port ${ESPPORT} erase_flash
	${ROOTING} ${ESPTOOL} --port ${ESPPORT} write_flash ${BLANK_1_ADDR} ${BLANKBIN} ${INIT_2_ADDR} ${INITBIN} ${BLANK_2_ADDR} ${BLANKBIN}
	${ROOTING} ${ESPTOOL} --port ${ESPPORT} write_flash ${FW_FILE_1_ADDR} ${FW_FILE_1} ${FW_FILE_2_ADDR} ${FW_FILE_2}
	${ROOTING} ${SERTERM} -b 9600 -D ${ESPPORT}
fi
