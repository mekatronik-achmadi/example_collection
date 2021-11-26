#!/bin/bash
#
# ESP8266 C SDK project creation template
# Copyright (C) 2016 Sven Gregori
#
# Sets up a basic project structure to use the ESP8266 native C SDK on either
# command line or Eclipse (well, it gives instructions for that, not really
# setting up anything for that).
#
# Usage: ./mkproject.sh /path/to/project/destination
#
# Note, the script requires $ESP_SDK_ROOT environment variable to be set to
# the esp-open-sdk toolchain main directory!
#

export ESP_SDK_ROOT=/opt/esp-open-sdk
export PATH=$ESP_SDK_ROOT/xtensa-lx106-elf/bin:$PATH

SCRIPT_PATH=$(readlink -f $0)
SCRIPT_DIR=$(dirname $SCRIPT_PATH)
TEMPLATE_DIR="${SCRIPT_DIR}/template/"

if [ $# -lt 1 ] ; then
    echo "usage: $0 /path/to/project"
    exit 1
fi

TARGET="$1"

if [ -e $TARGET ] ; then
    echo "Target dir '$TARGET' already exists, not gonna touch that."
    exit 1
fi

mkdir -p ${TARGET}/user
touch ${TARGET}/user/user_config.h
sed s/{ESP_SDK_ROOT}/$(echo $ESP_SDK_ROOT | sed 's/[\/&]/\\&/g')/g ${TEMPLATE_DIR}/Makefile > ${TARGET}/Makefile
cp ${TEMPLATE_DIR}/main.c ${TARGET}/user

echo "Project created successfully at $TARGET"
