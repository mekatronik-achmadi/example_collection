EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr User 7874 5906
encoding utf-8
Sheet 1 1
Title "OLED Keypad BT-SPP"
Date "2022-03-14"
Rev ""
Comp "ITS"
Comment1 "drafted by Achmadi ST MT"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L RF_Module:ESP32-WROOM-32 U1
U 1 1 622F3415
P 3150 2400
F 0 "U1" H 3150 3981 50  0000 C CNN
F 1 "ESP32-WROOM-32" H 3150 3890 50  0000 C CNN
F 2 "RF_Module:ESP32-WROOM-32" H 3150 900 50  0001 C CNN
F 3 "https://www.espressif.com/sites/default/files/documentation/esp32-wroom-32_datasheet_en.pdf" H 2850 2450 50  0001 C CNN
	1    3150 2400
	1    0    0    -1  
$EndComp
$Comp
L Device:R R-NRST1
U 1 1 622F41B9
P 2450 1050
F 0 "R-NRST1" H 2520 1096 50  0001 L CNN
F 1 "10K" H 2520 1050 50  0000 L CNN
F 2 "" V 2380 1050 50  0001 C CNN
F 3 "~" H 2450 1050 50  0001 C CNN
	1    2450 1050
	1    0    0    -1  
$EndComp
$Comp
L power:VDD #PWR01
U 1 1 622F5504
P 2450 800
F 0 "#PWR01" H 2450 650 50  0001 C CNN
F 1 "VDD" H 2465 973 50  0000 C CNN
F 2 "" H 2450 800 50  0001 C CNN
F 3 "" H 2450 800 50  0001 C CNN
	1    2450 800 
	1    0    0    -1  
$EndComp
Wire Wire Line
	2550 1200 2450 1200
Wire Wire Line
	2450 1200 2300 1200
Connection ~ 2450 1200
Wire Wire Line
	2450 800  2450 900 
$Comp
L power:VDD #PWR02
U 1 1 622F6957
P 3150 900
F 0 "#PWR02" H 3150 750 50  0001 C CNN
F 1 "VDD" H 3165 1073 50  0000 C CNN
F 2 "" H 3150 900 50  0001 C CNN
F 3 "" H 3150 900 50  0001 C CNN
	1    3150 900 
	1    0    0    -1  
$EndComp
Wire Wire Line
	3150 900  3150 1000
$Comp
L power:GND #PWR03
U 1 1 622F7E83
P 3150 3850
F 0 "#PWR03" H 3150 3600 50  0001 C CNN
F 1 "GND" H 3155 3677 50  0000 C CNN
F 2 "" H 3150 3850 50  0001 C CNN
F 3 "" H 3150 3850 50  0001 C CNN
	1    3150 3850
	1    0    0    -1  
$EndComp
Wire Wire Line
	3150 3800 3150 3850
$Comp
L Device:R R-FLASH1
U 1 1 622F9BE7
P 3850 1050
F 0 "R-FLASH1" H 3920 1096 50  0001 L CNN
F 1 "10K" H 3920 1050 50  0000 L CNN
F 2 "" V 3780 1050 50  0001 C CNN
F 3 "~" H 3850 1050 50  0001 C CNN
	1    3850 1050
	1    0    0    -1  
$EndComp
$Comp
L power:VDD #PWR04
U 1 1 622FA1DF
P 3850 800
F 0 "#PWR04" H 3850 650 50  0001 C CNN
F 1 "VDD" H 3865 973 50  0000 C CNN
F 2 "" H 3850 800 50  0001 C CNN
F 3 "" H 3850 800 50  0001 C CNN
	1    3850 800 
	1    0    0    -1  
$EndComp
Wire Wire Line
	3750 1200 3850 1200
Wire Wire Line
	3850 1200 4100 1200
Connection ~ 3850 1200
Wire Wire Line
	3850 800  3850 900 
Text Label 4100 1200 0    50   ~ 0
FLASH
Wire Wire Line
	3750 1300 4100 1300
Wire Wire Line
	3750 1500 4100 1500
Text Label 4100 1300 0    50   ~ 0
TXD
Text Label 4100 1500 0    50   ~ 0
RXD
$Comp
L Connector:Conn_01x04_Female J-SSD13061
U 1 1 62309E22
P 2050 4300
F 0 "J-SSD13061" H 2078 4230 50  0000 L CNN
F 1 "Conn_01x04_Female" H 2078 4185 50  0001 L CNN
F 2 "" H 2050 4300 50  0001 C CNN
F 3 "~" H 2050 4300 50  0001 C CNN
	1    2050 4300
	1    0    0    -1  
$EndComp
$Comp
L Device:R R-OLED2
U 1 1 62311794
P 1450 3900
F 0 "R-OLED2" H 1520 3946 50  0001 L CNN
F 1 "10K" H 1520 3900 50  0000 L CNN
F 2 "" V 1380 3900 50  0001 C CNN
F 3 "~" H 1450 3900 50  0001 C CNN
	1    1450 3900
	1    0    0    -1  
$EndComp
$Comp
L Device:R R-OLED1
U 1 1 6231344B
P 1350 3900
F 0 "R-OLED1" H 1420 3946 50  0001 L CNN
F 1 "10K" H 1420 3900 50  0000 L CNN
F 2 "" V 1280 3900 50  0001 C CNN
F 3 "~" H 1350 3900 50  0001 C CNN
	1    1350 3900
	1    0    0    -1  
$EndComp
$Comp
L power:VDD #PWR05
U 1 1 6231395C
P 1400 3700
F 0 "#PWR05" H 1400 3550 50  0001 C CNN
F 1 "VDD" H 1415 3873 50  0000 C CNN
F 2 "" H 1400 3700 50  0001 C CNN
F 3 "" H 1400 3700 50  0001 C CNN
	1    1400 3700
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR06
U 1 1 6231803D
P 1650 4200
F 0 "#PWR06" H 1650 3950 50  0001 C CNN
F 1 "GND" H 1655 4027 50  0000 C CNN
F 2 "" H 1650 4200 50  0001 C CNN
F 3 "" H 1650 4200 50  0001 C CNN
	1    1650 4200
	1    0    0    -1  
$EndComp
Wire Wire Line
	1450 4050 1450 4400
Wire Wire Line
	1450 4400 1850 4400
Wire Wire Line
	1350 4050 1350 4500
Wire Wire Line
	1350 4500 1850 4500
Wire Wire Line
	1450 4400 1150 4400
Connection ~ 1450 4400
Wire Wire Line
	1350 4500 1150 4500
Connection ~ 1350 4500
Wire Wire Line
	1850 4200 1650 4200
Wire Wire Line
	1850 4300 1750 4300
Wire Wire Line
	1750 4300 1750 3750
Wire Wire Line
	1750 3750 1450 3750
Wire Wire Line
	1400 3700 1450 3700
Wire Wire Line
	1450 3700 1450 3750
Connection ~ 1450 3750
Wire Wire Line
	1400 3700 1350 3700
Wire Wire Line
	1350 3700 1350 3750
Connection ~ 1400 3700
Text Label 1150 4400 2    50   ~ 0
OLED_SCL
Text Label 1150 4500 2    50   ~ 0
OLED_SDA
Text Label 1150 1800 2    50   ~ 0
FLASH
Text Label 1150 1700 2    50   ~ 0
NRST
Text Label 1150 1600 2    50   ~ 0
TXD
Text Label 1150 1500 2    50   ~ 0
RXD
$Comp
L power:GND #PWR0102
U 1 1 623080B7
P 1150 1900
F 0 "#PWR0102" H 1150 1650 50  0001 C CNN
F 1 "GND" H 1155 1727 50  0000 C CNN
F 2 "" H 1150 1900 50  0001 C CNN
F 3 "" H 1150 1900 50  0001 C CNN
	1    1150 1900
	1    0    0    -1  
$EndComp
$Comp
L power:VDD #PWR0101
U 1 1 62307AD4
P 1150 1400
F 0 "#PWR0101" H 1150 1250 50  0001 C CNN
F 1 "VDD" H 1165 1573 50  0000 C CNN
F 2 "" H 1150 1400 50  0001 C CNN
F 3 "" H 1150 1400 50  0001 C CNN
	1    1150 1400
	1    0    0    -1  
$EndComp
Wire Wire Line
	1350 1900 1150 1900
Wire Wire Line
	1350 1800 1150 1800
Wire Wire Line
	1350 1700 1150 1700
Wire Wire Line
	1350 1600 1150 1600
Wire Wire Line
	1350 1500 1150 1500
Wire Wire Line
	1350 1400 1150 1400
$Comp
L Connector:Conn_01x06_Male J-PROG1
U 1 1 622FEA6A
P 1550 1600
F 0 "J-PROG1" H 1522 1528 50  0000 R CNN
F 1 "Conn_01x06_Male" H 1658 1890 50  0001 C CNN
F 2 "" H 1550 1600 50  0001 C CNN
F 3 "~" H 1550 1600 50  0001 C CNN
	1    1550 1600
	-1   0    0    -1  
$EndComp
Text Label 2300 1200 2    50   ~ 0
NRST
Wire Wire Line
	3750 2600 4100 2600
Wire Wire Line
	3750 2700 4100 2700
Text Label 4100 2600 0    50   ~ 0
OLED_SDA
Text Label 4100 2700 0    50   ~ 0
OLED_SCL
Wire Wire Line
	3750 1400 4100 1400
Text Label 4100 1400 0    50   ~ 0
LED
$Comp
L Device:R R-LED1
U 1 1 6233C872
P 4700 1200
F 0 "R-LED1" H 4770 1246 50  0001 L CNN
F 1 "330" H 4770 1200 50  0000 L CNN
F 2 "" V 4630 1200 50  0001 C CNN
F 3 "~" H 4700 1200 50  0001 C CNN
	1    4700 1200
	1    0    0    -1  
$EndComp
$Comp
L power:VDD #PWR07
U 1 1 6233DE45
P 4700 1000
F 0 "#PWR07" H 4700 850 50  0001 C CNN
F 1 "VDD" H 4715 1173 50  0000 C CNN
F 2 "" H 4700 1000 50  0001 C CNN
F 3 "" H 4700 1000 50  0001 C CNN
	1    4700 1000
	1    0    0    -1  
$EndComp
Wire Wire Line
	4700 1000 4700 1050
$Comp
L Device:LED D-LED1
U 1 1 62340D9B
P 4700 1550
F 0 "D-LED1" V 4739 1432 50  0001 R CNN
F 1 "LED" V 4693 1432 50  0000 R CNN
F 2 "" H 4700 1550 50  0001 C CNN
F 3 "~" H 4700 1550 50  0001 C CNN
	1    4700 1550
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4700 1350 4700 1400
Wire Wire Line
	4700 1700 4700 1850
Text Label 4700 1850 0    50   ~ 0
LED
$Comp
L Connector:Conn_01x07_Male J-Keypad1
U 1 1 62304F9E
P 4950 2750
F 0 "J-Keypad1" H 5058 3139 50  0000 C CNN
F 1 "Conn_01x07_Male" H 5058 3140 50  0001 C CNN
F 2 "" H 4950 2750 50  0001 C CNN
F 3 "~" H 4950 2750 50  0001 C CNN
	1    4950 2750
	1    0    0    -1  
$EndComp
Wire Wire Line
	5150 2850 5400 2850
Wire Wire Line
	5150 2950 5400 2950
Wire Wire Line
	5150 3050 5400 3050
Text Label 5400 2850 0    50   ~ 0
IN_0
Text Label 5400 2950 0    50   ~ 0
IN_1
Text Label 5400 3050 0    50   ~ 0
IN_2
Wire Wire Line
	5150 2450 5400 2450
Wire Wire Line
	5150 2550 5400 2550
Wire Wire Line
	5150 2650 5400 2650
Wire Wire Line
	5150 2750 5400 2750
Text Label 5400 2450 0    50   ~ 0
OUT_0
Text Label 5400 2550 0    50   ~ 0
OUT_1
Text Label 5400 2650 0    50   ~ 0
OUT_2
Text Label 5400 2750 0    50   ~ 0
OUT_3
Wire Wire Line
	3750 2900 4100 2900
Wire Wire Line
	3750 3000 4100 3000
Wire Wire Line
	3750 3100 4100 3100
Text Label 4100 2900 0    50   ~ 0
IN_0
Text Label 4100 3000 0    50   ~ 0
IN_1
Text Label 4100 3100 0    50   ~ 0
IN_2
Wire Wire Line
	3750 2400 4100 2400
Wire Wire Line
	3750 2500 4100 2500
Text Label 4100 2400 0    50   ~ 0
OUT_0
Text Label 4100 2500 0    50   ~ 0
OUT_1
Wire Wire Line
	3750 2200 4100 2200
Text Label 4100 2200 0    50   ~ 0
OUT_2
Wire Wire Line
	3750 2300 4100 2300
Text Label 4100 2300 0    50   ~ 0
OUT_3
$EndSCHEMATC
