#!/bin/bash

# run in sudo

stty -F /dev/ttyUSB0 cs8 38400 -cstopb -parenb ignbrk -brkint -icrnl -imaxbel -opost -onlcr -isig -icanon -iexten -echo -echoe -echok 
