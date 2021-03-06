EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr User 7874 5906
encoding utf-8
Sheet 1 1
Title "STM32F103C8 Driver Motor"
Date "2022-04-09"
Rev "0.0"
Comp "Achmadi ST MT"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Device:R R-RST1
U 1 1 625189AE
P 850 1050
F 0 "R-RST1" H 920 1096 50  0001 L CNN
F 1 "10K" H 920 1050 50  0000 L CNN
F 2 "" V 780 1050 50  0001 C CNN
F 3 "~" H 850 1050 50  0001 C CNN
	1    850  1050
	1    0    0    -1  
$EndComp
$Comp
L power:VDD #PWR01
U 1 1 6251A7B6
P 850 800
F 0 "#PWR01" H 850 650 50  0001 C CNN
F 1 "VDD" H 865 973 50  0000 C CNN
F 2 "" H 850 800 50  0001 C CNN
F 3 "" H 850 800 50  0001 C CNN
	1    850  800 
	1    0    0    -1  
$EndComp
Wire Wire Line
	950  1200 850  1200
Wire Wire Line
	850  800  850  900 
$Comp
L power:VDD #PWR04
U 1 1 6251C627
P 1950 850
F 0 "#PWR04" H 1950 700 50  0001 C CNN
F 1 "VDD" H 1965 1023 50  0000 C CNN
F 2 "" H 1950 850 50  0001 C CNN
F 3 "" H 1950 850 50  0001 C CNN
	1    1950 850 
	1    0    0    -1  
$EndComp
Wire Wire Line
	1950 900  1950 1000
$Comp
L MCU_ST_STM32F1:STM32F103RCTx U1
U 1 1 62516B26
P 1650 2800
F 0 "U1" H 1650 911 50  0000 C CNN
F 1 "STM32F103RCTx" H 1650 820 50  0000 C CNN
F 2 "Package_QFP:LQFP-64_10x10mm_P0.5mm" H 1050 1100 50  0001 R CNN
F 3 "http://www.st.com/st-web-ui/static/active/en/resource/technical/document/datasheet/CD00191185.pdf" H 1650 2800 50  0001 C CNN
	1    1650 2800
	1    0    0    -1  
$EndComp
Wire Wire Line
	1450 1000 1450 900 
Wire Wire Line
	1450 900  1550 900 
Connection ~ 1950 900 
Wire Wire Line
	1550 1000 1550 900 
Connection ~ 1550 900 
Wire Wire Line
	1550 900  1650 900 
Wire Wire Line
	1650 1000 1650 900 
Connection ~ 1650 900 
Wire Wire Line
	1650 900  1750 900 
Wire Wire Line
	1750 1000 1750 900 
Connection ~ 1750 900 
Wire Wire Line
	1750 900  1850 900 
Wire Wire Line
	1850 1000 1850 900 
Connection ~ 1850 900 
Wire Wire Line
	1850 900  1950 900 
$Comp
L power:GND #PWR02
U 1 1 6251F37F
P 850 1400
F 0 "#PWR02" H 850 1150 50  0001 C CNN
F 1 "GND" H 855 1227 50  0000 C CNN
F 2 "" H 850 1400 50  0001 C CNN
F 3 "" H 850 1400 50  0001 C CNN
	1    850  1400
	1    0    0    -1  
$EndComp
Wire Wire Line
	950  1400 850  1400
$Comp
L power:GND #PWR03
U 1 1 625217E0
P 1850 4850
F 0 "#PWR03" H 1850 4600 50  0001 C CNN
F 1 "GND" H 1855 4677 50  0000 C CNN
F 2 "" H 1850 4850 50  0001 C CNN
F 3 "" H 1850 4850 50  0001 C CNN
	1    1850 4850
	1    0    0    -1  
$EndComp
Wire Wire Line
	1850 4600 1850 4650
Wire Wire Line
	1450 4600 1450 4650
Wire Wire Line
	1450 4650 1550 4650
Connection ~ 1850 4650
Wire Wire Line
	1850 4650 1850 4850
Wire Wire Line
	1750 4600 1750 4650
Connection ~ 1750 4650
Wire Wire Line
	1750 4650 1850 4650
Wire Wire Line
	1650 4600 1650 4650
Connection ~ 1650 4650
Wire Wire Line
	1650 4650 1750 4650
Wire Wire Line
	1550 4600 1550 4650
Connection ~ 1550 4650
Wire Wire Line
	1550 4650 1650 4650
$Comp
L Device:R R-LED1
U 1 1 62523DB1
P 2900 1050
F 0 "R-LED1" H 2970 1096 50  0001 L CNN
F 1 "10K" H 2970 1050 50  0000 L CNN
F 2 "" V 2830 1050 50  0001 C CNN
F 3 "~" H 2900 1050 50  0001 C CNN
	1    2900 1050
	1    0    0    -1  
$EndComp
$Comp
L power:VDD #PWR05
U 1 1 6252682D
P 2900 800
F 0 "#PWR05" H 2900 650 50  0001 C CNN
F 1 "VDD" H 2915 973 50  0000 C CNN
F 2 "" H 2900 800 50  0001 C CNN
F 3 "" H 2900 800 50  0001 C CNN
	1    2900 800 
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D1
U 1 1 6252831E
P 2650 1200
F 0 "D1" H 2643 1417 50  0000 C CNN
F 1 "LED" H 2643 1326 50  0000 C CNN
F 2 "" H 2650 1200 50  0001 C CNN
F 3 "~" H 2650 1200 50  0001 C CNN
	1    2650 1200
	1    0    0    -1  
$EndComp
Wire Wire Line
	2500 1200 2350 1200
Wire Wire Line
	2900 800  2900 900 
Wire Wire Line
	2900 1200 2800 1200
$Comp
L Regulator_Linear:AMS1117-3.3 U2
U 1 1 6252DDD8
P 4600 1300
F 0 "U2" H 4600 1542 50  0000 C CNN
F 1 "AMS1117-3.3" H 4600 1451 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-223-3_TabPin2" H 4600 1500 50  0001 C CNN
F 3 "http://www.advanced-monolithic.com/pdf/ds1117.pdf" H 4700 1050 50  0001 C CNN
	1    4600 1300
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x02_Male J-PWR1
U 1 1 6252F90C
P 3900 1300
F 0 "J-PWR1" H 4008 1389 50  0000 C CNN
F 1 "Conn_01x02_Male" H 4008 1390 50  0001 C CNN
F 2 "" H 3900 1300 50  0001 C CNN
F 3 "~" H 3900 1300 50  0001 C CNN
	1    3900 1300
	1    0    0    -1  
$EndComp
Wire Wire Line
	4300 1300 4250 1300
$Comp
L power:+12V #PWR07
U 1 1 62531082
P 4250 1050
F 0 "#PWR07" H 4250 900 50  0001 C CNN
F 1 "+12V" H 4265 1223 50  0000 C CNN
F 2 "" H 4250 1050 50  0001 C CNN
F 3 "" H 4250 1050 50  0001 C CNN
	1    4250 1050
	1    0    0    -1  
$EndComp
Wire Wire Line
	4250 1050 4250 1300
Connection ~ 4250 1300
Wire Wire Line
	4250 1300 4100 1300
$Comp
L Device:D D2
U 1 1 62536903
P 4350 1600
F 0 "D2" H 4350 1817 50  0000 C CNN
F 1 "D" H 4350 1726 50  0000 C CNN
F 2 "" H 4350 1600 50  0001 C CNN
F 3 "~" H 4350 1600 50  0001 C CNN
	1    4350 1600
	1    0    0    -1  
$EndComp
Wire Wire Line
	4500 1600 4600 1600
Wire Wire Line
	4100 1400 4100 1600
Wire Wire Line
	4100 1600 4200 1600
$Comp
L power:GNDPWR #PWR06
U 1 1 62538189
P 4100 1700
F 0 "#PWR06" H 4100 1500 50  0001 C CNN
F 1 "GNDPWR" H 4104 1546 50  0000 C CNN
F 2 "" H 4100 1650 50  0001 C CNN
F 3 "" H 4100 1650 50  0001 C CNN
	1    4100 1700
	1    0    0    -1  
$EndComp
Wire Wire Line
	4100 1600 4100 1700
Connection ~ 4100 1600
$Comp
L power:VDD #PWR09
U 1 1 62538F95
P 4950 1050
F 0 "#PWR09" H 4950 900 50  0001 C CNN
F 1 "VDD" H 4965 1223 50  0000 C CNN
F 2 "" H 4950 1050 50  0001 C CNN
F 3 "" H 4950 1050 50  0001 C CNN
	1    4950 1050
	1    0    0    -1  
$EndComp
Wire Wire Line
	4950 1050 4950 1300
Wire Wire Line
	4950 1300 4900 1300
$Comp
L power:GND #PWR08
U 1 1 62518847
P 4600 1700
F 0 "#PWR08" H 4600 1450 50  0001 C CNN
F 1 "GND" H 4605 1527 50  0000 C CNN
F 2 "" H 4600 1700 50  0001 C CNN
F 3 "" H 4600 1700 50  0001 C CNN
	1    4600 1700
	1    0    0    -1  
$EndComp
Wire Wire Line
	4600 1700 4600 1600
Connection ~ 4600 1600
Wire Wire Line
	2350 2400 2550 2400
Text Label 2550 2400 0    50   ~ 0
USB_DP
Wire Wire Line
	2350 2300 2550 2300
Text Label 2550 2300 0    50   ~ 0
USB_DM
Wire Wire Line
	3850 2850 4000 2850
$Comp
L power:VDD #PWR011
U 1 1 62542D43
P 4000 2850
F 0 "#PWR011" H 4000 2700 50  0001 C CNN
F 1 "VDD" H 4015 3023 50  0000 C CNN
F 2 "" H 4000 2850 50  0001 C CNN
F 3 "" H 4000 2850 50  0001 C CNN
	1    4000 2850
	1    0    0    -1  
$EndComp
Text Label 4000 3050 0    50   ~ 0
USB_DM
Text Label 4000 2950 0    50   ~ 0
USB_DP
Wire Wire Line
	3850 3050 4000 3050
Wire Wire Line
	3850 2950 4000 2950
Connection ~ 3450 2950
Wire Wire Line
	3450 2850 3450 2950
$Comp
L Device:R R-USB1
U 1 1 6254010D
P 3700 2850
F 0 "R-USB1" V 3493 2850 50  0001 C CNN
F 1 "10K" V 3585 2850 50  0000 C CNN
F 2 "" V 3630 2850 50  0001 C CNN
F 3 "~" H 3700 2850 50  0001 C CNN
	1    3700 2850
	0    1    1    0   
$EndComp
$Comp
L Device:R R-USB3
U 1 1 6253F649
P 3700 3050
F 0 "R-USB3" V 3493 3050 50  0001 C CNN
F 1 "68" V 3585 3050 50  0000 C CNN
F 2 "" V 3630 3050 50  0001 C CNN
F 3 "~" H 3700 3050 50  0001 C CNN
	1    3700 3050
	0    1    1    0   
$EndComp
$Comp
L Device:R R-USB2
U 1 1 6253D156
P 3700 2950
F 0 "R-USB2" V 3493 2950 50  0001 C CNN
F 1 "68" V 3585 2950 50  0000 C CNN
F 2 "" V 3630 2950 50  0001 C CNN
F 3 "~" H 3700 2950 50  0001 C CNN
	1    3700 2950
	0    1    1    0   
$EndComp
Wire Wire Line
	3400 2950 3450 2950
Wire Wire Line
	3100 3350 3100 3400
Wire Wire Line
	3000 3350 3000 3400
Wire Wire Line
	2350 2000 2550 2000
Text Label 2550 2000 0    50   ~ 0
MOTOR_PWM
Wire Wire Line
	2350 1900 2550 1900
Text Label 2550 1900 0    50   ~ 0
MOTOR_DIR
$Comp
L Device:R R-OPTO1
U 1 1 62562298
P 5550 1150
F 0 "R-OPTO1" H 5620 1196 50  0001 L CNN
F 1 "330" H 5620 1150 50  0000 L CNN
F 2 "" V 5480 1150 50  0001 C CNN
F 3 "~" H 5550 1150 50  0001 C CNN
	1    5550 1150
	1    0    0    -1  
$EndComp
$Comp
L power:VDD #PWR012
U 1 1 6256CE63
P 5550 950
F 0 "#PWR012" H 5550 800 50  0001 C CNN
F 1 "VDD" H 5565 1123 50  0000 C CNN
F 2 "" H 5550 950 50  0001 C CNN
F 3 "" H 5550 950 50  0001 C CNN
	1    5550 950 
	1    0    0    -1  
$EndComp
Wire Wire Line
	5650 1300 5550 1300
Wire Wire Line
	5550 950  5550 1000
Wire Wire Line
	5650 1500 5550 1500
Text Label 5550 1500 2    50   ~ 0
MOTOR_PWM
Text Label 6400 1400 0    50   ~ 0
DRIVER_A
Connection ~ 6300 1400
Wire Wire Line
	6300 1400 6400 1400
Wire Wire Line
	6250 1500 6300 1500
$Comp
L power:GNDPWR #PWR015
U 1 1 62581CDB
P 6300 1500
F 0 "#PWR015" H 6300 1300 50  0001 C CNN
F 1 "GNDPWR" H 6304 1346 50  0000 C CNN
F 2 "" H 6300 1450 50  0001 C CNN
F 3 "" H 6300 1450 50  0001 C CNN
	1    6300 1500
	1    0    0    -1  
$EndComp
Wire Wire Line
	6300 1400 6300 1300
Wire Wire Line
	6250 1400 6300 1400
Wire Wire Line
	6300 950  6300 1000
$Comp
L power:+12V #PWR014
U 1 1 6257D6B6
P 6300 950
F 0 "#PWR014" H 6300 800 50  0001 C CNN
F 1 "+12V" H 6315 1123 50  0000 C CNN
F 2 "" H 6300 950 50  0001 C CNN
F 3 "" H 6300 950 50  0001 C CNN
	1    6300 950 
	1    0    0    -1  
$EndComp
$Comp
L Device:R R-OPHI1
U 1 1 6257C1D6
P 6300 1150
F 0 "R-OPHI1" H 6370 1196 50  0001 L CNN
F 1 "10K" H 6370 1150 50  0000 L CNN
F 2 "" V 6230 1150 50  0001 C CNN
F 3 "~" H 6300 1150 50  0001 C CNN
	1    6300 1150
	1    0    0    -1  
$EndComp
$Comp
L Isolator:4N35 U3
U 1 1 62560EE9
P 5950 1400
F 0 "U3" H 5950 1725 50  0000 C CNN
F 1 "4N35" H 5950 1634 50  0000 C CNN
F 2 "Package_DIP:DIP-6_W7.62mm" H 5750 1200 50  0001 L CIN
F 3 "https://www.vishay.com/docs/81181/4n35.pdf" H 5950 1400 50  0001 L CNN
	1    5950 1400
	1    0    0    -1  
$EndComp
$Comp
L Device:R R-OPTO2
U 1 1 6258D2B2
P 5550 2150
F 0 "R-OPTO2" H 5620 2196 50  0001 L CNN
F 1 "330" H 5620 2150 50  0000 L CNN
F 2 "" V 5480 2150 50  0001 C CNN
F 3 "~" H 5550 2150 50  0001 C CNN
	1    5550 2150
	1    0    0    -1  
$EndComp
$Comp
L power:VDD #PWR013
U 1 1 6258D430
P 5550 1950
F 0 "#PWR013" H 5550 1800 50  0001 C CNN
F 1 "VDD" H 5565 2123 50  0000 C CNN
F 2 "" H 5550 1950 50  0001 C CNN
F 3 "" H 5550 1950 50  0001 C CNN
	1    5550 1950
	1    0    0    -1  
$EndComp
Wire Wire Line
	5650 2300 5550 2300
Wire Wire Line
	5550 1950 5550 2000
Wire Wire Line
	5650 2500 5550 2500
Text Label 5550 2500 2    50   ~ 0
MOTOR_DIR
Text Label 6400 2400 0    50   ~ 0
DRIVER_B
Connection ~ 6300 2400
Wire Wire Line
	6300 2400 6400 2400
Wire Wire Line
	6250 2500 6300 2500
$Comp
L power:GNDPWR #PWR017
U 1 1 6258D442
P 6300 2500
F 0 "#PWR017" H 6300 2300 50  0001 C CNN
F 1 "GNDPWR" H 6304 2346 50  0000 C CNN
F 2 "" H 6300 2450 50  0001 C CNN
F 3 "" H 6300 2450 50  0001 C CNN
	1    6300 2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	6300 2400 6300 2300
Wire Wire Line
	6250 2400 6300 2400
Wire Wire Line
	6300 1950 6300 2000
$Comp
L power:+12V #PWR016
U 1 1 6258D44F
P 6300 1950
F 0 "#PWR016" H 6300 1800 50  0001 C CNN
F 1 "+12V" H 6315 2123 50  0000 C CNN
F 2 "" H 6300 1950 50  0001 C CNN
F 3 "" H 6300 1950 50  0001 C CNN
	1    6300 1950
	1    0    0    -1  
$EndComp
$Comp
L Device:R R-OPHI2
U 1 1 6258D459
P 6300 2150
F 0 "R-OPHI2" H 6370 2196 50  0001 L CNN
F 1 "10K" H 6370 2150 50  0000 L CNN
F 2 "" V 6230 2150 50  0001 C CNN
F 3 "~" H 6300 2150 50  0001 C CNN
	1    6300 2150
	1    0    0    -1  
$EndComp
$Comp
L Isolator:4N35 U4
U 1 1 6258D463
P 5950 2400
F 0 "U4" H 5950 2725 50  0000 C CNN
F 1 "4N35" H 5950 2634 50  0000 C CNN
F 2 "Package_DIP:DIP-6_W7.62mm" H 5750 2200 50  0001 L CIN
F 3 "https://www.vishay.com/docs/81181/4n35.pdf" H 5950 2400 50  0001 L CNN
	1    5950 2400
	1    0    0    -1  
$EndComp
Wire Wire Line
	3400 3050 3550 3050
Wire Wire Line
	3450 2950 3550 2950
Wire Wire Line
	3550 2850 3450 2850
$Comp
L power:GNDPWR #PWR019
U 1 1 625C1C55
P 6000 3950
F 0 "#PWR019" H 6000 3750 50  0001 C CNN
F 1 "GNDPWR" H 6004 3796 50  0000 C CNN
F 2 "" H 6000 3900 50  0001 C CNN
F 3 "" H 6000 3900 50  0001 C CNN
	1    6000 3950
	1    0    0    -1  
$EndComp
Connection ~ 6000 2950
Wire Wire Line
	5500 2950 6000 2950
Wire Wire Line
	6500 2950 6000 2950
$Comp
L power:+12V #PWR018
U 1 1 625BBFF1
P 6000 2950
F 0 "#PWR018" H 6000 2800 50  0001 C CNN
F 1 "+12V" H 6015 3123 50  0000 C CNN
F 2 "" H 6000 2950 50  0001 C CNN
F 3 "" H 6000 2950 50  0001 C CNN
	1    6000 2950
	1    0    0    -1  
$EndComp
$Comp
L Transistor_FET:IRF540N Q4
U 1 1 625B917C
P 6600 3750
F 0 "Q4" H 6805 3796 50  0000 L CNN
F 1 "IRF540N" H 6805 3705 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-220-3_Vertical" H 6850 3675 50  0001 L CIN
F 3 "http://www.irf.com/product-info/datasheets/data/irf540n.pdf" H 6600 3750 50  0001 L CNN
	1    6600 3750
	-1   0    0    -1  
$EndComp
$Comp
L Transistor_FET:IRF540N Q2
U 1 1 625B7ED2
P 5400 3750
F 0 "Q2" H 5604 3796 50  0000 L CNN
F 1 "IRF540N" H 5604 3705 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-220-3_Vertical" H 5650 3675 50  0001 L CIN
F 3 "http://www.irf.com/product-info/datasheets/data/irf540n.pdf" H 5400 3750 50  0001 L CNN
	1    5400 3750
	1    0    0    -1  
$EndComp
$Comp
L Transistor_FET:IRF540N Q3
U 1 1 625B3A4E
P 6600 3150
F 0 "Q3" H 6805 3196 50  0000 L CNN
F 1 "IRF540N" H 6805 3105 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-220-3_Vertical" H 6850 3075 50  0001 L CIN
F 3 "http://www.irf.com/product-info/datasheets/data/irf540n.pdf" H 6600 3150 50  0001 L CNN
	1    6600 3150
	-1   0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x02_Female J-MOTOR1
U 1 1 625AC89A
P 5950 3250
F 0 "J-MOTOR1" V 5842 3298 50  0000 L CNN
F 1 "Conn_01x02_Female" V 5887 3298 50  0001 L CNN
F 2 "" H 5950 3250 50  0001 C CNN
F 3 "~" H 5950 3250 50  0001 C CNN
	1    5950 3250
	0    -1   -1   0   
$EndComp
$Comp
L Transistor_FET:IRF540N Q1
U 1 1 625AB817
P 5400 3150
F 0 "Q1" H 5604 3196 50  0000 L CNN
F 1 "IRF540N" H 5604 3105 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-220-3_Vertical" H 5650 3075 50  0001 L CIN
F 3 "http://www.irf.com/product-info/datasheets/data/irf540n.pdf" H 5400 3150 50  0001 L CNN
	1    5400 3150
	1    0    0    -1  
$EndComp
$Comp
L Connector:USB_B_Micro J-DATA1
U 1 1 6251ADFD
P 3100 2950
F 0 "J-DATA1" H 3157 3417 50  0000 C CNN
F 1 "USB_B_Micro" H 3157 3326 50  0000 C CNN
F 2 "" H 3250 2900 50  0001 C CNN
F 3 "~" H 3250 2900 50  0001 C CNN
	1    3100 2950
	1    0    0    -1  
$EndComp
Wire Wire Line
	6500 3350 6500 3450
Wire Wire Line
	6050 3450 6500 3450
Connection ~ 6500 3450
Wire Wire Line
	6500 3450 6500 3550
Wire Wire Line
	5950 3450 5500 3450
Wire Wire Line
	5500 3450 5500 3350
Wire Wire Line
	5500 3550 5500 3450
Connection ~ 5500 3450
Wire Wire Line
	5500 3950 6000 3950
Wire Wire Line
	6500 3950 6000 3950
Connection ~ 6000 3950
Wire Wire Line
	6800 3150 6900 3150
Wire Wire Line
	6800 3750 6900 3750
Text Label 6900 3150 0    50   ~ 0
DRIVER_A
Text Label 6900 3750 0    50   ~ 0
DRIVER_B
Wire Wire Line
	5200 3150 5100 3150
Wire Wire Line
	5200 3750 5100 3750
Text Label 5100 3150 2    50   ~ 0
DRIVER_B
Text Label 5100 3750 2    50   ~ 0
DRIVER_A
$Comp
L power:GND #PWR010
U 1 1 62539837
P 3000 3400
F 0 "#PWR010" H 3000 3150 50  0001 C CNN
F 1 "GND" H 3005 3227 50  0000 C CNN
F 2 "" H 3000 3400 50  0001 C CNN
F 3 "" H 3000 3400 50  0001 C CNN
	1    3000 3400
	1    0    0    -1  
$EndComp
Wire Wire Line
	3100 3400 3000 3400
Connection ~ 3000 3400
Wire Wire Line
	1950 850  1950 900 
$EndSCHEMATC
