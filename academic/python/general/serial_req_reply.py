#!/usr/bin/python

import serial
import time
import sys
import io

ser = serial.Serial()
ser.baudrate = 9600
ser.port = '/dev/ttyACM0'
ser.timeout = 1
ser.open()

ser_io = io.TextIOWrapper(io.BufferedRWPair(ser, ser))

if ser.isOpen():
	print('Open: %s' % str(ser.port)) 
	
	while 1:
		ser_io.write("AT\n")
		ser_io.flush()
		ser_recev = ser_io.readline()
		if len(ser_recev) > 0:
			print(ser_recev)
			break
		time.sleep(0.1)
	
	#while 1:
		#ser.write(bytearray(b'AT\n\r'))
		#recev = ser.readline()
		#if len(recev) > 0:
			#print(recev)
			#break
		#time.sleep(1)
	
	ser.close()
	exit

else:
	ser.close()
	exit
