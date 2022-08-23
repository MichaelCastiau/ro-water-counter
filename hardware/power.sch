EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 3 5
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
L Regulator_Switching:LM2594HVM-3.3 U1
U 1 1 6224290D
P 5100 3950
F 0 "U1" H 5100 4317 50  0000 C CNN
F 1 "LM2594HVM-3.3" H 5100 4226 50  0000 C CNN
F 2 "Package_SO:SOIC-8_3.9x4.9mm_P1.27mm" H 5300 3700 50  0001 L CIN
F 3 "http://www.ti.com/lit/ds/symlink/lm2594.pdf" H 5100 4050 50  0001 C CNN
	1    5100 3950
	1    0    0    -1  
$EndComp
Wire Wire Line
	4700 3850 3775 3850
$Comp
L power:+24V #PWR09
U 1 1 6223A400
P 3775 3450
F 0 "#PWR09" H 3775 3300 50  0001 C CNN
F 1 "+24V" H 3790 3623 50  0000 C CNN
F 2 "" H 3775 3450 50  0001 C CNN
F 3 "" H 3775 3450 50  0001 C CNN
	1    3775 3450
	1    0    0    -1  
$EndComp
Connection ~ 3775 3850
Wire Wire Line
	3775 4525 3775 4775
$Comp
L power:GND #PWR011
U 1 1 6223B3F8
P 7625 5150
F 0 "#PWR011" H 7625 4900 50  0001 C CNN
F 1 "GND" H 7630 4977 50  0000 C CNN
F 2 "" H 7625 5150 50  0001 C CNN
F 3 "" H 7625 5150 50  0001 C CNN
	1    7625 5150
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C5
U 1 1 6223C2A0
P 3775 4375
F 0 "C5" H 3893 4421 50  0000 L CNN
F 1 "68uF" H 3893 4330 50  0000 L CNN
F 2 "Capacitor_SMD:CP_Elec_5x5.4" H 3813 4225 50  0001 C CNN
F 3 "~" H 3775 4375 50  0001 C CNN
	1    3775 4375
	1    0    0    -1  
$EndComp
Wire Wire Line
	3775 3850 3775 4225
Wire Wire Line
	4700 3950 4325 3950
Wire Wire Line
	4325 3950 4325 4775
Wire Wire Line
	4325 4775 3775 4775
Wire Wire Line
	5300 4250 5300 4775
Wire Wire Line
	5300 4775 4325 4775
Connection ~ 4325 4775
$Comp
L Diode:1N5817 D3
U 1 1 6223DC12
P 5900 4375
F 0 "D3" V 5854 4455 50  0000 L CNN
F 1 "1N5817" V 5945 4455 50  0000 L CNN
F 2 "Diode_SMD:D_SOD-123" H 5900 4200 50  0001 C CNN
F 3 "http://www.vishay.com/docs/88525/1n5817.pdf" H 5900 4375 50  0001 C CNN
	1    5900 4375
	0    1    1    0   
$EndComp
Wire Wire Line
	5500 3950 5900 3950
Wire Wire Line
	5900 3950 5900 4225
Wire Wire Line
	5900 4525 5900 4775
Wire Wire Line
	5900 4775 5300 4775
Connection ~ 5300 4775
$Comp
L Device:L L1
U 1 1 6223EFA3
P 6275 3950
F 0 "L1" V 6100 3950 50  0000 C CNN
F 1 "100uH" V 6200 3950 50  0000 C CNN
F 2 "Inductor_SMD:L_1812_4532Metric" H 6275 3950 50  0001 C CNN
F 3 "~" H 6275 3950 50  0001 C CNN
	1    6275 3950
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6125 3950 5900 3950
Connection ~ 5900 3950
Wire Wire Line
	6425 3950 6625 3950
Wire Wire Line
	6625 3950 6625 3850
Wire Wire Line
	6625 3850 5500 3850
$Comp
L Device:CP C6
U 1 1 6223FE48
P 6625 4375
F 0 "C6" H 6743 4421 50  0000 L CNN
F 1 "120uF" H 6743 4330 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D5.0mm_P2.50mm" H 6663 4225 50  0001 C CNN
F 3 "~" H 6625 4375 50  0001 C CNN
	1    6625 4375
	1    0    0    -1  
$EndComp
Wire Wire Line
	6625 4525 6625 4775
Wire Wire Line
	6625 4775 5900 4775
Connection ~ 5900 4775
Wire Wire Line
	6625 4225 6625 3950
Connection ~ 6625 3950
Wire Wire Line
	7625 3950 7625 3725
$Comp
L power:+3.3V #PWR010
U 1 1 622410DB
P 7625 3450
F 0 "#PWR010" H 7625 3300 50  0001 C CNN
F 1 "+3.3V" H 7640 3623 50  0000 C CNN
F 2 "" H 7625 3450 50  0001 C CNN
F 3 "" H 7625 3450 50  0001 C CNN
	1    7625 3450
	1    0    0    -1  
$EndComp
Connection ~ 6625 4775
NoConn ~ 4900 4250
NoConn ~ 5000 4250
NoConn ~ 5100 4250
Wire Wire Line
	7625 4775 7625 5150
$Comp
L Connector:TestPoint TP?
U 1 1 622A62EF
P 7825 3725
AR Path="/62205316/622A62EF" Ref="TP?"  Part="1" 
AR Path="/622422B2/622A62EF" Ref="TP?"  Part="1" 
AR Path="/62D89C56/622A62EF" Ref="TP1"  Part="1" 
F 0 "TP1" H 8000 3775 50  0000 R CNN
F 1 "3.3V" H 8075 3875 50  0000 R CNN
F 2 "TestPoint:TestPoint_Pad_D1.5mm" H 8025 3725 50  0001 C CNN
F 3 "~" H 8025 3725 50  0001 C CNN
	1    7825 3725
	0    1    1    0   
$EndComp
Wire Wire Line
	7825 3725 7625 3725
Connection ~ 7625 3725
Wire Wire Line
	7625 3725 7625 3575
$Comp
L power:PWR_FLAG #FLG02
U 1 1 623559B1
P 3575 3850
F 0 "#FLG02" H 3575 3925 50  0001 C CNN
F 1 "PWR_FLAG" V 3575 3977 50  0000 L CNN
F 2 "" H 3575 3850 50  0001 C CNN
F 3 "~" H 3575 3850 50  0001 C CNN
	1    3575 3850
	0    -1   -1   0   
$EndComp
$Comp
L power:PWR_FLAG #FLG01
U 1 1 62356493
P 7850 3575
F 0 "#FLG01" H 7850 3650 50  0001 C CNN
F 1 "PWR_FLAG" V 7850 3703 50  0000 L CNN
F 2 "" H 7850 3575 50  0001 C CNN
F 3 "~" H 7850 3575 50  0001 C CNN
	1    7850 3575
	0    1    1    0   
$EndComp
$Comp
L power:PWR_FLAG #FLG03
U 1 1 62356DB9
P 7850 4775
F 0 "#FLG03" H 7850 4850 50  0001 C CNN
F 1 "PWR_FLAG" V 7850 4903 50  0000 L CNN
F 2 "" H 7850 4775 50  0001 C CNN
F 3 "~" H 7850 4775 50  0001 C CNN
	1    7850 4775
	0    1    1    0   
$EndComp
Wire Wire Line
	7850 4775 7625 4775
Connection ~ 7625 4775
Wire Wire Line
	7625 3575 7850 3575
Connection ~ 7625 3575
Wire Wire Line
	7625 3575 7625 3450
Wire Wire Line
	3575 3850 3775 3850
Wire Wire Line
	3775 3450 3775 3850
$Comp
L Connector:Barrel_Jack J3
U 1 1 62DFC84D
P 4450 1750
F 0 "J3" H 4507 2075 50  0000 C CNN
F 1 "Barrel_Jack" H 4507 1984 50  0000 C CNN
F 2 "Connector_BarrelJack:BarrelJack_Horizontal" H 4500 1710 50  0001 C CNN
F 3 "~" H 4500 1710 50  0001 C CNN
	1    4450 1750
	1    0    0    -1  
$EndComp
Wire Wire Line
	4750 1650 5200 1650
Wire Wire Line
	5200 1650 5200 1425
$Comp
L power:+24V #PWR07
U 1 1 62E0289B
P 5200 1350
F 0 "#PWR07" H 5200 1200 50  0001 C CNN
F 1 "+24V" H 5215 1523 50  0000 C CNN
F 2 "" H 5200 1350 50  0001 C CNN
F 3 "" H 5200 1350 50  0001 C CNN
	1    5200 1350
	1    0    0    -1  
$EndComp
Wire Wire Line
	4750 1850 5200 1850
$Comp
L power:GND #PWR08
U 1 1 62E03BC1
P 5200 2200
F 0 "#PWR08" H 5200 1950 50  0001 C CNN
F 1 "GND" H 5205 2027 50  0000 C CNN
F 2 "" H 5200 2200 50  0001 C CNN
F 3 "" H 5200 2200 50  0001 C CNN
	1    5200 2200
	1    0    0    -1  
$EndComp
Wire Wire Line
	5200 2200 5200 2075
$Comp
L Device:CP C4
U 1 1 62E05194
P 5525 1750
F 0 "C4" H 5643 1796 50  0000 L CNN
F 1 "22uF" H 5643 1705 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 5563 1600 50  0001 C CNN
F 3 "~" H 5525 1750 50  0001 C CNN
	1    5525 1750
	1    0    0    -1  
$EndComp
Wire Wire Line
	5525 1900 5525 2075
Wire Wire Line
	5525 2075 5200 2075
Connection ~ 5200 2075
Wire Wire Line
	5200 2075 5200 1850
Wire Wire Line
	5525 1600 5525 1425
Wire Wire Line
	5525 1425 5200 1425
Connection ~ 5200 1425
Wire Wire Line
	5200 1425 5200 1350
Wire Wire Line
	6625 3950 7625 3950
Wire Wire Line
	6625 4775 7625 4775
$EndSCHEMATC