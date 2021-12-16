EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:pspice
EELAYER 25 0
EELAYER END
$Descr User 7874 5906
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L VSOURCE V2
U 1 1 5B80B5F7
P 4200 3150
F 0 "V2" H 4200 3050 50  0000 C CNN
F 1 "5" H 4200 3250 50  0000 C CNN
F 2 "" H 4200 3150 50  0001 C CNN
F 3 "" H 4200 3150 50  0001 C CNN
	1    4200 3150
	1    0    0    -1  
$EndComp
$Comp
L VSOURCE V3
U 1 1 5B80B75D
P 5150 3150
F 0 "V3" H 5150 3050 50  0000 C CNN
F 1 "-5" H 5150 3250 50  0000 C CNN
F 2 "" H 5150 3150 50  0001 C CNN
F 3 "" H 5150 3150 50  0001 C CNN
	1    5150 3150
	1    0    0    -1  
$EndComp
$Comp
L 0 #GND01
U 1 1 5B80B7EF
P 4650 4000
F 0 "#GND01" H 4650 3900 50  0001 C CNN
F 1 "0" H 4650 3930 50  0000 C CNN
F 2 "" H 4650 4000 50  0001 C CNN
F 3 "" H 4650 4000 50  0001 C CNN
	1    4650 4000
	1    0    0    -1  
$EndComp
Text GLabel 4050 2300 0    60   Input ~ 0
v_p
Text GLabel 5000 2300 0    60   Input ~ 0
v_m
Text Notes 5800 3750 0    60   ~ 0
+PSPICE\n\n* .ac dec 10 100 1000k\n.tran 100u 10m\n* .dc V1 -0.5 0.5 0.1\n\n* dc 0V ac 1V\n* sin(0 1m 500)\n\n.control\nset color0=rgb:f/f/f\nset color1=rgb:0/0/0\n\nrun\nplot v(v_in), v(v_amp), v(v_off), v(v_out)\n.endc
Text Notes 5750 2200 0    60   ~ 0
-PSPICE\n\n.include lm358.mod
$Comp
L 0 #GND02
U 1 1 5B80B513
P 1800 4050
F 0 "#GND02" H 1800 3950 50  0001 C CNN
F 1 "0" H 1800 3980 50  0000 C CNN
F 2 "" H 1800 4050 50  0001 C CNN
F 3 "" H 1800 4050 50  0001 C CNN
	1    1800 4050
	1    0    0    -1  
$EndComp
Text GLabel 1100 2450 0    60   Input ~ 0
v_in
$Comp
L VSOURCE V1
U 1 1 5B80B42C
P 1250 3250
F 0 "V1" H 1250 3150 50  0000 C CNN
F 1 "sin(0 1m 500)" H 1250 3350 50  0000 C CNN
F 2 "" H 1250 3250 50  0001 C CNN
F 3 "" H 1250 3250 50  0001 C CNN
	1    1250 3250
	1    0    0    -1  
$EndComp
$Comp
L VSOURCE V4
U 1 1 5B80E01F
P 2400 3250
F 0 "V4" H 2400 3150 50  0000 C CNN
F 1 "18mV" H 2400 3350 50  0000 C CNN
F 2 "" H 2400 3250 50  0001 C CNN
F 3 "" H 2400 3250 50  0001 C CNN
	1    2400 3250
	1    0    0    -1  
$EndComp
Text GLabel 2250 2400 0    60   Input ~ 0
v_off
$Comp
L LF356 U1
U 1 1 5B80E46C
P 3150 1500
F 0 "U1" H 3150 1750 50  0000 L CNN
F 1 "LM358" H 3150 1650 50  0000 L CNN
F 2 "" H 3200 1550 50  0001 C CNN
F 3 "" H 3300 1650 50  0001 C CNN
	1    3150 1500
	1    0    0    1   
$EndComp
$Comp
L R R4
U 1 1 5B80E5EC
P 3200 1050
F 0 "R4" V 3280 1050 50  0000 C CNN
F 1 "5k" V 3200 1050 50  0000 C CNN
F 2 "" V 3130 1050 50  0001 C CNN
F 3 "" H 3200 1050 50  0001 C CNN
	1    3200 1050
	0    1    1    0   
$EndComp
$Comp
L R R1
U 1 1 5B80E7A1
P 2200 1050
F 0 "R1" V 2280 1050 50  0000 C CNN
F 1 "1k" V 2200 1050 50  0000 C CNN
F 2 "" V 2130 1050 50  0001 C CNN
F 3 "" H 2200 1050 50  0001 C CNN
	1    2200 1050
	0    1    1    0   
$EndComp
Text GLabel 2850 1200 0    60   Input ~ 0
v_m
Text GLabel 2850 2150 0    60   Input ~ 0
v_p
Text GLabel 3500 900  0    60   Input ~ 0
v_amp
Text GLabel 2150 1600 0    60   Input ~ 0
v_in
$Comp
L 0 #GND03
U 1 1 5B81640B
P 1950 1150
F 0 "#GND03" H 1950 1050 50  0001 C CNN
F 1 "0" H 1950 1080 50  0000 C CNN
F 2 "" H 1950 1150 50  0001 C CNN
F 3 "" H 1950 1150 50  0001 C CNN
	1    1950 1150
	1    0    0    -1  
$EndComp
$Comp
L LF356 U2
U 1 1 5B81649A
P 4800 1400
F 0 "U2" H 4800 1650 50  0000 L CNN
F 1 "LM358" H 4800 1550 50  0000 L CNN
F 2 "" H 4850 1450 50  0001 C CNN
F 3 "" H 4950 1550 50  0001 C CNN
	1    4800 1400
	1    0    0    1   
$EndComp
$Comp
L R R2
U 1 1 5B816708
P 4300 950
F 0 "R2" V 4380 950 50  0000 C CNN
F 1 "5k" V 4300 950 50  0000 C CNN
F 2 "" V 4230 950 50  0001 C CNN
F 3 "" H 4300 950 50  0001 C CNN
	1    4300 950 
	0    1    1    0   
$EndComp
$Comp
L R R3
U 1 1 5B81686F
P 4850 950
F 0 "R3" V 4930 950 50  0000 C CNN
F 1 "5k" V 4850 950 50  0000 C CNN
F 2 "" V 4780 950 50  0001 C CNN
F 3 "" H 4850 950 50  0001 C CNN
	1    4850 950 
	0    1    1    0   
$EndComp
Text GLabel 5600 950  0    60   Input ~ 0
v_out
Text GLabel 4600 750  0    60   Input ~ 0
v_m
Wire Wire Line
	4200 3850 5150 3850
Wire Wire Line
	4650 4000 4650 3850
Connection ~ 4650 3850
Wire Wire Line
	4050 2300 4200 2300
Wire Wire Line
	4200 2300 4200 2450
Wire Wire Line
	5000 2300 5150 2300
Wire Wire Line
	5150 2300 5150 2450
Wire Wire Line
	1250 2450 1250 2550
Wire Wire Line
	1100 2450 1250 2450
Wire Wire Line
	2250 2400 2400 2400
Wire Wire Line
	2400 2400 2400 2550
Wire Wire Line
	1250 3950 2400 3950
Wire Wire Line
	1800 3950 1800 4050
Connection ~ 1800 3950
Wire Wire Line
	3350 1050 3550 1050
Wire Wire Line
	3550 900  3550 1500
Wire Wire Line
	3450 1500 4500 1500
Wire Wire Line
	2150 1600 2850 1600
Wire Wire Line
	2850 2150 4700 2150
Wire Wire Line
	3050 2150 3050 1800
Wire Wire Line
	4450 950  4450 1300
Wire Wire Line
	4450 1300 4500 1300
Wire Wire Line
	4000 950  4150 950 
Wire Wire Line
	4700 950  4450 950 
Wire Wire Line
	5000 950  5150 950 
Wire Wire Line
	5150 950  5150 1400
Wire Wire Line
	5100 1400 5700 1400
Wire Wire Line
	5700 1400 5700 950 
Wire Wire Line
	5700 950  5600 950 
Connection ~ 5150 1400
Wire Wire Line
	4600 750  4700 750 
Wire Wire Line
	4700 750  4700 1100
Wire Wire Line
	3500 900  3550 900 
Connection ~ 3550 1050
Connection ~ 3550 1500
Wire Wire Line
	4700 2150 4700 1700
Connection ~ 3050 2150
Wire Wire Line
	3050 1050 2350 1050
Wire Wire Line
	2500 1050 2500 1400
Wire Wire Line
	2500 1400 2850 1400
Connection ~ 2500 1050
Wire Wire Line
	2850 1200 3050 1200
Wire Wire Line
	2050 1050 1950 1050
Wire Wire Line
	1950 1050 1950 1150
Text GLabel 4000 950  0    60   Input ~ 0
v_off
$EndSCHEMATC
