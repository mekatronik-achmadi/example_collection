#!/bin/bash

# run in sudo

while true
do 
	read sdata
	echo $sdata > /dev/ttyUSB0
	echo -e "\r" > /dev/ttyUSB0
done
