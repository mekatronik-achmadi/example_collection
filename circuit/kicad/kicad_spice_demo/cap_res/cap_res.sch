EESchema Schematic File Version 2
LIBS:pspice
EELAYER 25 0
EELAYER END
$Descr User 7874 5906
encoding utf-8
Sheet 1 1
Title "Signal Transient example"
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L VSOURCE V1
U 1 1 5B7AF2D6
P 1600 2700
F 0 "V1" H 1600 2600 50  0000 C CNN
F 1 "dc 0v ac 1v" H 1600 2800 50  0000 C CNN
F 2 "" H 1600 2700 50  0001 C CNN
F 3 "" H 1600 2700 50  0001 C CNN
	1    1600 2700
	1    0    0    -1  
$EndComp
$Comp
L C C1
U 1 1 5B7AF35E
P 2850 2250
F 0 "C1" V 2950 2400 50  0000 C CNN
F 1 "1u" V 2950 2100 50  0000 C CNN
F 2 "" H 2850 2250 50  0001 C CNN
F 3 "" H 2850 2250 50  0001 C CNN
	1    2850 2250
	1    0    0    -1  
$EndComp
$Comp
L C C2
U 1 1 5B7AF3CF
P 4000 2250
F 0 "C2" V 4100 2400 50  0000 C CNN
F 1 "100n" V 4100 2100 50  0000 C CNN
F 2 "" H 4000 2250 50  0001 C CNN
F 3 "" H 4000 2250 50  0001 C CNN
	1    4000 2250
	1    0    0    -1  
$EndComp
$Comp
L R R1
U 1 1 5B7AF440
P 2300 1800
F 0 "R1" V 2380 1800 50  0000 C CNN
F 1 "10k" V 2300 1800 50  0000 C CNN
F 2 "" H 2300 1800 50  0001 C CNN
F 3 "" H 2300 1800 50  0001 C CNN
	1    2300 1800
	0    1    1    0   
$EndComp
$Comp
L R R2
U 1 1 5B7AF49B
P 3550 1800
F 0 "R2" V 3630 1800 50  0000 C CNN
F 1 "1k" V 3550 1800 50  0000 C CNN
F 2 "" H 3550 1800 50  0001 C CNN
F 3 "" H 3550 1800 50  0001 C CNN
	1    3550 1800
	0    1    1    0   
$EndComp
$Comp
L 0 #GND01
U 1 1 5B7AF697
P 1600 3550
F 0 "#GND01" H 1600 3450 50  0001 C CNN
F 1 "0" H 1600 3480 50  0000 C CNN
F 2 "" H 1600 3550 50  0001 C CNN
F 3 "" H 1600 3550 50  0001 C CNN
	1    1600 3550
	1    0    0    -1  
$EndComp
$Comp
L 0 #GND02
U 1 1 5B7AF6C9
P 2850 2650
F 0 "#GND02" H 2850 2550 50  0001 C CNN
F 1 "0" H 2850 2580 50  0000 C CNN
F 2 "" H 2850 2650 50  0001 C CNN
F 3 "" H 2850 2650 50  0001 C CNN
	1    2850 2650
	1    0    0    -1  
$EndComp
$Comp
L 0 #GND03
U 1 1 5B7AF6FB
P 4000 2650
F 0 "#GND03" H 4000 2550 50  0001 C CNN
F 1 "0" H 4000 2580 50  0000 C CNN
F 2 "" H 4000 2650 50  0001 C CNN
F 3 "" H 4000 2650 50  0001 C CNN
	1    4000 2650
	1    0    0    -1  
$EndComp
Text GLabel 1600 1500 0    60   Input ~ 0
v_0
Text GLabel 4000 1500 0    60   Input ~ 0
v_2
Text GLabel 2850 1500 0    60   Input ~ 0
v_1
Connection ~ 1600 1800
Wire Wire Line
	2050 1800 1600 1800
Wire Wire Line
	1600 1500 1600 2000
Connection ~ 4000 1800
Wire Wire Line
	1600 3550 1600 3400
Wire Wire Line
	2850 2500 2850 2650
Wire Wire Line
	4000 2500 4000 2650
Connection ~ 2850 1800
Wire Wire Line
	2850 1500 2850 2000
Wire Wire Line
	4000 1500 4000 2000
Wire Wire Line
	3800 1800 4000 1800
Wire Wire Line
	2550 1800 3300 1800
Text Notes 4600 2950 0    60   ~ 0
+PSPICE\n\n** vsource options **\n* dc 0v ac 1v\n* pulse (0 5 1u 1u 1u 1 1)\n\n** choose analysis **\n* .op\n* .dc v_0 1V 10V .01V\n* .dc temp -40 100 1\n* .ac dec 10 1 100k\n* .tran .1ns 100ns\n* .tran 1u 100m\n\n.control\nrun\nplot v(v_0), v(v_1), v(v_2)\n* plot phase(v(v_2)), mag(v(v_2)), abs(v(v_2)), db(v(v_2))\n.endc\n
$EndSCHEMATC
