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
L C Cin1
U 1 1 5B7FFBA1
P 1700 1950
F 0 "Cin1" H 1725 2050 50  0000 L CNN
F 1 "10u" H 1725 1850 50  0000 L CNN
F 2 "" H 1738 1800 50  0001 C CNN
F 3 "" H 1700 1950 50  0001 C CNN
	1    1700 1950
	0    1    1    0   
$EndComp
$Comp
L BC549 Q1
U 1 1 5B7FFBF2
P 2500 1950
F 0 "Q1" H 2700 2025 50  0000 L CNN
F 1 "npn_bc549c" H 2700 1950 50  0000 L CNN
F 2 "TO_SOT_Packages_THT:TO-92_Molded_Narrow" H 2700 1875 50  0001 L CIN
F 3 "" H 2500 1950 50  0001 L CNN
	1    2500 1950
	1    0    0    -1  
$EndComp
$Comp
L R R2
U 1 1 5B7FFC68
P 2100 2200
F 0 "R2" V 2180 2200 50  0000 C CNN
F 1 "10k" V 2100 2200 50  0000 C CNN
F 2 "" V 2030 2200 50  0001 C CNN
F 3 "" H 2100 2200 50  0001 C CNN
	1    2100 2200
	1    0    0    -1  
$EndComp
$Comp
L R R1
U 1 1 5B7FFCDA
P 2100 1650
F 0 "R1" V 2180 1650 50  0000 C CNN
F 1 "68k" V 2100 1650 50  0000 C CNN
F 2 "" V 2030 1650 50  0001 C CNN
F 3 "" H 2100 1650 50  0001 C CNN
	1    2100 1650
	1    0    0    -1  
$EndComp
$Comp
L R R3
U 1 1 5B7FFD55
P 2600 1350
F 0 "R3" V 2680 1350 50  0000 C CNN
F 1 "10k" V 2600 1350 50  0000 C CNN
F 2 "" V 2530 1350 50  0001 C CNN
F 3 "" H 2600 1350 50  0001 C CNN
	1    2600 1350
	1    0    0    -1  
$EndComp
$Comp
L C Cout1
U 1 1 5B7FFDCB
P 3050 1600
F 0 "Cout1" H 3075 1700 50  0000 L CNN
F 1 "10u" H 3075 1500 50  0000 L CNN
F 2 "" H 3088 1450 50  0001 C CNN
F 3 "" H 3050 1600 50  0001 C CNN
	1    3050 1600
	0    1    1    0   
$EndComp
$Comp
L R Rload1
U 1 1 5B7FFE42
P 3450 2000
F 0 "Rload1" V 3530 2000 50  0000 C CNN
F 1 "100k" V 3450 2000 50  0000 C CNN
F 2 "" V 3380 2000 50  0001 C CNN
F 3 "" H 3450 2000 50  0001 C CNN
	1    3450 2000
	1    0    0    -1  
$EndComp
$Comp
L 0 #GND01
U 1 1 5B7FFEF6
P 2600 2550
F 0 "#GND01" H 2600 2450 50  0001 C CNN
F 1 "0" H 2600 2480 50  0000 C CNN
F 2 "" H 2600 2550 50  0001 C CNN
F 3 "" H 2600 2550 50  0001 C CNN
	1    2600 2550
	1    0    0    -1  
$EndComp
Wire Wire Line
	2100 2350 3450 2350
Wire Wire Line
	3450 2350 3450 2150
Wire Wire Line
	2600 2150 2600 2550
Connection ~ 2600 2350
Wire Wire Line
	1850 1950 2300 1950
Wire Wire Line
	2100 1800 2100 2050
Connection ~ 2100 1950
Wire Wire Line
	2600 1500 2600 1750
Wire Wire Line
	2900 1600 2600 1600
Connection ~ 2600 1600
Wire Wire Line
	3200 1600 3850 1600
Wire Wire Line
	3450 1600 3450 1850
Wire Wire Line
	2600 1200 2600 1050
Wire Wire Line
	2100 1500 2100 1350
Wire Wire Line
	1150 1950 1550 1950
Connection ~ 3450 1600
Text GLabel 1900 1350 0    60   Input ~ 0
vcc
Text GLabel 2350 1050 0    60   Input ~ 0
vcc
Wire Wire Line
	2600 1050 2350 1050
Wire Wire Line
	2100 1350 1900 1350
Text GLabel 1150 1950 0    60   Input ~ 0
v_in
Text GLabel 3700 1350 0    60   Input ~ 0
v_out
Wire Wire Line
	3850 1600 3850 1350
Wire Wire Line
	3850 1350 3700 1350
$Comp
L VSOURCE V_AC1
U 1 1 5B800688
P 2750 3750
F 0 "V_AC1" H 2750 3650 50  0000 C CNN
F 1 "sin(0 1m 500)" H 2750 3850 50  0000 C CNN
F 2 "" H 2750 3750 50  0001 C CNN
F 3 "" H 2750 3750 50  0001 C CNN
	1    2750 3750
	1    0    0    -1  
$EndComp
$Comp
L VSOURCE V_DC1
U 1 1 5B8007DD
P 1750 3800
F 0 "V_DC1" H 1750 3700 50  0000 C CNN
F 1 "dc 5V" H 1750 3900 50  0000 C CNN
F 2 "" H 1750 3800 50  0001 C CNN
F 3 "" H 1750 3800 50  0001 C CNN
	1    1750 3800
	1    0    0    -1  
$EndComp
$Comp
L 0 #GND02
U 1 1 5B800866
P 2300 4600
F 0 "#GND02" H 2300 4500 50  0001 C CNN
F 1 "0" H 2300 4530 50  0000 C CNN
F 2 "" H 2300 4600 50  0001 C CNN
F 3 "" H 2300 4600 50  0001 C CNN
	1    2300 4600
	1    0    0    -1  
$EndComp
Wire Wire Line
	1750 4500 2750 4500
Wire Wire Line
	2750 4500 2750 4450
Wire Wire Line
	2300 4600 2300 4500
Connection ~ 2300 4500
Text GLabel 2650 3000 0    60   Input ~ 0
v_in
Wire Wire Line
	2650 3000 2750 3000
Wire Wire Line
	2750 3000 2750 3050
Text GLabel 1650 3000 0    60   Input ~ 0
vcc
Wire Wire Line
	1650 3000 1750 3000
Wire Wire Line
	1750 3000 1750 3100
Text Notes 4200 3000 0    60   ~ 0
+PSPICE\n\n.model npn_bc549c npn ( IS=7.59E-15 VAF=73.4 BF=480\n+ IKF=0.0962 NE=1.2665\n+ ISE=3.278E-15 IKR=0.03 ISC=2.00E-13\n+ NC=1.2 NR=1 BR=5 RC=0.25 CJC=6.33E-12\n+ FC=0.5 MJC=0.33 VJC=0.65 CJE=1.25E-11\n+ MJE=0.55 VJE=0.65 TF=4.26E-10\n+ ITF=0.6 VTF=3 XTF=20 RB=100\n+ IRB=0.0001 RBM=10 RE=0.5 TR=1.50E-07)\n\n* .ac dec 10 10 1000k\n.tran 100u 10m\n\n* dc 0V ac 1V\n* sin(0 1m 500)
$EndSCHEMATC