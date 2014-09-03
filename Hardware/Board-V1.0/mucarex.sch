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
LIBS:special
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
LIBS:mucarex
LIBS:mucarex-cache
EELAYER 27 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "MuCaREX V1.0 Multi Cartridge for Vectrex"
Date "21 aug 2014"
Rev "1"
Comp "P1X3L.NET"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L HM62256BLP-7 U3
U 1 1 52A5ACEB
P 2100 6550
F 0 "U3" H 1800 7450 50  0000 C CNN
F 1 "62256-80" H 2300 5700 50  0000 C CNN
F 2 "DIP28" H 2100 6550 30  0000 C CIN
F 3 "" H 2100 6550 60  0000 C CNN
	1    2100 6550
	1    0    0    -1  
$EndComp
$Comp
L AT49F040 U1
U 1 1 52A5B352
P 2100 1700
F 0 "U1" H 1750 2800 60  0000 C CNN
F 1 "LOROM" H 2350 700 60  0000 C CNN
F 2 "" H 2100 1700 60  0000 C CNN
F 3 "" H 2100 1700 60  0000 C CNN
	1    2100 1700
	1    0    0    -1  
$EndComp
$Comp
L CONN_10 P2
U 1 1 52A5B437
P 10150 4500
F 0 "P2" V 10100 4500 60  0000 C CNN
F 1 "PROG" V 10200 4500 60  0000 C CNN
F 2 "" H 10150 4500 60  0000 C CNN
F 3 "" H 10150 4500 60  0000 C CNN
	1    10150 4500
	1    0    0    -1  
$EndComp
$Comp
L LED D1
U 1 1 52A5B44B
P 10000 3300
F 0 "D1" H 10000 3400 50  0000 C CNN
F 1 "LED" H 10000 3200 50  0000 C CNN
F 2 "~" H 10000 3300 60  0000 C CNN
F 3 "~" H 10000 3300 60  0000 C CNN
	1    10000 3300
	1    0    0    -1  
$EndComp
$Comp
L R R1
U 1 1 52A5B45A
P 9550 3300
F 0 "R1" V 9630 3300 40  0000 C CNN
F 1 "75" V 9557 3301 40  0000 C CNN
F 2 "~" V 9480 3300 30  0000 C CNN
F 3 "~" H 9550 3300 30  0000 C CNN
	1    9550 3300
	0    1    1    0   
$EndComp
$Comp
L PWR_FLAG #FLG01
U 1 1 52A5B86E
P 9350 1050
F 0 "#FLG01" H 9350 1145 30  0001 C CNN
F 1 "PWR_FLAG" H 9350 1230 30  0000 C CNN
F 2 "" H 9350 1050 60  0000 C CNN
F 3 "" H 9350 1050 60  0000 C CNN
	1    9350 1050
	1    0    0    -1  
$EndComp
$Comp
L PWR_FLAG #FLG02
U 1 1 52A5B87D
P 9650 1050
F 0 "#FLG02" H 9650 1145 30  0001 C CNN
F 1 "PWR_FLAG" H 9650 1230 30  0000 C CNN
F 2 "" H 9650 1050 60  0000 C CNN
F 3 "" H 9650 1050 60  0000 C CNN
	1    9650 1050
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR03
U 1 1 52A5B894
P 9350 1250
F 0 "#PWR03" H 9350 1350 30  0001 C CNN
F 1 "VCC" H 9350 1350 30  0000 C CNN
F 2 "" H 9350 1250 60  0000 C CNN
F 3 "" H 9350 1250 60  0000 C CNN
	1    9350 1250
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR04
U 1 1 52A5B8AA
P 9650 1250
F 0 "#PWR04" H 9650 1250 30  0001 C CNN
F 1 "GND" H 9650 1180 30  0001 C CNN
F 2 "" H 9650 1250 60  0000 C CNN
F 3 "" H 9650 1250 60  0000 C CNN
	1    9650 1250
	1    0    0    -1  
$EndComp
$Comp
L CONN_18X2 P1
U 1 1 52A6F578
P 5300 6400
F 0 "P1" H 5300 7450 60  0000 C CNN
F 1 "VECTREX" V 5300 6400 50  0000 C CNN
F 2 "" H 5300 6400 60  0000 C CNN
F 3 "" H 5300 6400 60  0000 C CNN
	1    5300 6400
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR05
U 1 1 52A6F82E
P 5800 5900
F 0 "#PWR05" H 5800 5900 30  0001 C CNN
F 1 "GND" H 5800 5830 30  0001 C CNN
F 2 "" H 5800 5900 60  0000 C CNN
F 3 "" H 5800 5900 60  0000 C CNN
	1    5800 5900
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR06
U 1 1 52A6F842
P 6100 4550
F 0 "#PWR06" H 6100 4550 30  0001 C CNN
F 1 "GND" H 6100 4480 30  0001 C CNN
F 2 "" H 6100 4550 60  0000 C CNN
F 3 "" H 6100 4550 60  0000 C CNN
	1    6100 4550
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR07
U 1 1 52A6F869
P 4200 2900
F 0 "#PWR07" H 4200 2900 30  0001 C CNN
F 1 "GND" H 4200 2830 30  0001 C CNN
F 2 "" H 4200 2900 60  0000 C CNN
F 3 "" H 4200 2900 60  0000 C CNN
	1    4200 2900
	0    1    1    0   
$EndComp
$Comp
L GND #PWR08
U 1 1 52A6F890
P 7900 3650
F 0 "#PWR08" H 7900 3650 30  0001 C CNN
F 1 "GND" H 7900 3580 30  0001 C CNN
F 2 "" H 7900 3650 60  0000 C CNN
F 3 "" H 7900 3650 60  0000 C CNN
	1    7900 3650
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR09
U 1 1 52A6F8DD
P 2750 6650
F 0 "#PWR09" H 2750 6650 30  0001 C CNN
F 1 "GND" H 2750 6580 30  0001 C CNN
F 2 "" H 2750 6650 60  0000 C CNN
F 3 "" H 2750 6650 60  0000 C CNN
	1    2750 6650
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR010
U 1 1 52A6F8F9
P 9700 4150
F 0 "#PWR010" H 9700 4150 30  0001 C CNN
F 1 "GND" H 9700 4080 30  0001 C CNN
F 2 "" H 9700 4150 60  0000 C CNN
F 3 "" H 9700 4150 60  0000 C CNN
	1    9700 4150
	0    1    1    0   
$EndComp
$Comp
L GND #PWR011
U 1 1 52A6F924
P 9700 4950
F 0 "#PWR011" H 9700 4950 30  0001 C CNN
F 1 "GND" H 9700 4880 30  0001 C CNN
F 2 "" H 9700 4950 60  0000 C CNN
F 3 "" H 9700 4950 60  0000 C CNN
	1    9700 4950
	0    1    1    0   
$EndComp
NoConn ~ 9800 4550
NoConn ~ 9800 4650
NoConn ~ 9800 4750
$Comp
L VCC #PWR012
U 1 1 52A6FB56
P 4500 5900
F 0 "#PWR012" H 4500 6000 30  0001 C CNN
F 1 "VCC" H 4500 6000 30  0000 C CNN
F 2 "" H 4500 5900 60  0000 C CNN
F 3 "" H 4500 5900 60  0000 C CNN
	1    4500 5900
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR013
U 1 1 52A6FB75
P 4600 5900
F 0 "#PWR013" H 4600 6000 30  0001 C CNN
F 1 "VCC" H 4600 6000 30  0000 C CNN
F 2 "" H 4600 5900 60  0000 C CNN
F 3 "" H 4600 5900 60  0000 C CNN
	1    4600 5900
	1    0    0    -1  
$EndComp
Text GLabel 5400 6800 3    60   BiDi ~ 0
D0
$Comp
L GND #PWR014
U 1 1 52A6F80C
P 5750 6950
F 0 "#PWR014" H 5750 6950 30  0001 C CNN
F 1 "GND" H 5750 6880 30  0001 C CNN
F 2 "" H 5750 6950 60  0000 C CNN
F 3 "" H 5750 6950 60  0000 C CNN
	1    5750 6950
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR015
U 1 1 52A6FFCA
P 9300 3300
F 0 "#PWR015" H 9300 3400 30  0001 C CNN
F 1 "VCC" H 9300 3400 30  0000 C CNN
F 2 "" H 9300 3300 60  0000 C CNN
F 3 "" H 9300 3300 60  0000 C CNN
	1    9300 3300
	0    -1   -1   0   
$EndComp
Text GLabel 4350 3500 0    60   Input ~ 0
LED
Text GLabel 10200 3300 2    60   Output ~ 0
LED
Text GLabel 2800 700  2    60   BiDi ~ 0
D0
Text GLabel 3000 800  2    60   BiDi ~ 0
D1
Text GLabel 2800 900  2    60   BiDi ~ 0
D2
Text GLabel 3000 1000 2    60   BiDi ~ 0
D3
Text GLabel 2800 1100 2    60   BiDi ~ 0
D4
Text GLabel 3000 1200 2    60   BiDi ~ 0
D5
Text GLabel 2800 1300 2    60   BiDi ~ 0
D6
Text GLabel 3000 1400 2    60   BiDi ~ 0
D7
Text GLabel 2650 5800 2    60   BiDi ~ 0
D0
Text GLabel 2850 5900 2    60   BiDi ~ 0
D1
Text GLabel 2650 6000 2    60   BiDi ~ 0
D2
Text GLabel 2850 6100 2    60   BiDi ~ 0
D3
Text GLabel 2650 6200 2    60   BiDi ~ 0
D4
Text GLabel 2850 6300 2    60   BiDi ~ 0
D5
Text GLabel 2650 6400 2    60   BiDi ~ 0
D6
Text GLabel 2850 6500 2    60   BiDi ~ 0
D7
Text GLabel 1400 700  0    60   Input ~ 0
A0
Text GLabel 1200 800  0    60   Input ~ 0
A1
Text GLabel 1400 900  0    60   Input ~ 0
A2
Text GLabel 1200 1000 0    60   Input ~ 0
A3
Text GLabel 1400 1100 0    60   Input ~ 0
A4
Text GLabel 1200 1200 0    60   Input ~ 0
A5
Text GLabel 1400 1300 0    60   Input ~ 0
A6
Text GLabel 1200 1400 0    60   Input ~ 0
A7
Text GLabel 1400 1500 0    60   Input ~ 0
A8
Text GLabel 1200 1600 0    60   Input ~ 0
A9
Text GLabel 1400 1700 0    60   Input ~ 0
A10
Text GLabel 1200 1800 0    60   Input ~ 0
A11
Text GLabel 1550 5800 0    60   Input ~ 0
A0
Text GLabel 1350 5900 0    60   Input ~ 0
A1
Text GLabel 1550 6000 0    60   Input ~ 0
A2
Text GLabel 1350 6100 0    60   Input ~ 0
A3
Text GLabel 1550 6200 0    60   Input ~ 0
A4
Text GLabel 1350 6300 0    60   Input ~ 0
A5
Text GLabel 1550 6400 0    60   Input ~ 0
A6
Text GLabel 1350 6500 0    60   Input ~ 0
A7
Text GLabel 1550 6600 0    60   Input ~ 0
A8
Text GLabel 1350 6700 0    60   Input ~ 0
A9
Text GLabel 1550 6800 0    60   Input ~ 0
A10
Text GLabel 1350 6900 0    60   Input ~ 0
A11
Text GLabel 1550 7000 0    60   Input ~ 0
A12
Text GLabel 1350 7100 0    60   Input ~ 0
A13
$Comp
L AT49F040 U2
U 1 1 52A70891
P 2100 4100
F 0 "U2" H 1750 5200 60  0000 C CNN
F 1 "HIROM" H 2350 3150 60  0000 C CNN
F 2 "" H 2100 4100 60  0000 C CNN
F 3 "" H 2100 4100 60  0000 C CNN
	1    2100 4100
	1    0    0    -1  
$EndComp
Text GLabel 2800 3100 2    60   BiDi ~ 0
D0
Text GLabel 3000 3200 2    60   BiDi ~ 0
D1
Text GLabel 2800 3300 2    60   BiDi ~ 0
D2
Text GLabel 3000 3400 2    60   BiDi ~ 0
D3
Text GLabel 2800 3500 2    60   BiDi ~ 0
D4
Text GLabel 3000 3600 2    60   BiDi ~ 0
D5
Text GLabel 2800 3700 2    60   BiDi ~ 0
D6
Text GLabel 3000 3800 2    60   BiDi ~ 0
D7
Text GLabel 1400 3100 0    60   Input ~ 0
A0
Text GLabel 1200 3200 0    60   Input ~ 0
A1
Text GLabel 1400 3300 0    60   Input ~ 0
A2
Text GLabel 1200 3400 0    60   Input ~ 0
A3
Text GLabel 1400 3500 0    60   Input ~ 0
A4
Text GLabel 1200 3600 0    60   Input ~ 0
A5
Text GLabel 1400 3700 0    60   Input ~ 0
A6
Text GLabel 1200 3800 0    60   Input ~ 0
A7
Text GLabel 1400 3900 0    60   Input ~ 0
A8
Text GLabel 1200 4000 0    60   Input ~ 0
A9
Text GLabel 1400 4100 0    60   Input ~ 0
A10
Text GLabel 1200 4200 0    60   Input ~ 0
A11
$Comp
L XC9572XL-PC44 U4
U 1 1 52A6EFDB
P 6100 3100
F 0 "U4" H 7400 4150 70  0000 C CNN
F 1 "XC9572XL-PC44" H 6100 3100 60  0000 C CNN
F 2 "~" H 6100 3100 60  0000 C CNN
F 3 "~" H 6100 3100 60  0000 C CNN
	1    6100 3100
	1    0    0    -1  
$EndComp
Text GLabel 5500 7000 3    60   BiDi ~ 0
D1
Text GLabel 5600 6800 3    60   BiDi ~ 0
D2
Text GLabel 5700 5800 1    60   BiDi ~ 0
D3
Text GLabel 5600 6000 1    60   BiDi ~ 0
D4
Text GLabel 5500 5800 1    60   BiDi ~ 0
D5
Text GLabel 5400 6000 1    60   BiDi ~ 0
D6
Text GLabel 5300 5800 1    60   BiDi ~ 0
D7
Text GLabel 4350 2750 0    60   BiDi ~ 0
D7
Text GLabel 5300 7000 3    60   Input ~ 0
A0
Text GLabel 5200 6800 3    60   Input ~ 0
A1
Text GLabel 5100 7000 3    60   Input ~ 0
A2
Text GLabel 5000 6800 3    60   Input ~ 0
A3
Text GLabel 4900 7000 3    60   Input ~ 0
A4
Text GLabel 4800 6800 3    60   Input ~ 0
A5
Text GLabel 4700 7000 3    60   Input ~ 0
A6
Text GLabel 4600 6800 3    60   Input ~ 0
A7
Text GLabel 4700 5800 1    60   Input ~ 0
A8
Text GLabel 4800 6000 1    60   Input ~ 0
A9
Text GLabel 5100 5800 1    60   Input ~ 0
A10
Text GLabel 4900 5800 1    60   Input ~ 0
A11
Text GLabel 5900 7000 3    60   Input ~ 0
A12
Text GLabel 6000 6800 3    60   Input ~ 0
A13
Text GLabel 6100 7000 3    60   Input ~ 0
A14
Text GLabel 5200 6000 1    60   Input ~ 0
A15
Text GLabel 6200 6800 3    60   BiDi ~ 0
PB6
Text GLabel 5000 6000 1    60   Input ~ 0
OE
Text GLabel 5900 6000 1    60   Input ~ 0
RW
Text GLabel 6700 4450 3    60   Input ~ 0
A0
Text GLabel 5650 4450 3    60   Input ~ 0
A1
Text GLabel 5650 1850 1    60   Input ~ 0
A2
Text GLabel 5350 4450 3    60   Input ~ 0
A3
Text GLabel 6400 4450 3    60   Input ~ 0
A4
Text GLabel 6400 1850 1    60   Input ~ 0
A5
Text GLabel 7800 3200 2    60   Input ~ 0
A6
Text GLabel 4350 3050 0    60   Input ~ 0
A7
Text GLabel 7800 2450 2    60   Input ~ 0
A8
Text GLabel 6850 1850 1    60   Input ~ 0
A9
Text GLabel 6550 1850 1    60   Input ~ 0
A10
Text GLabel 7800 3350 2    60   Input ~ 0
A11
Text GLabel 5350 1850 1    60   Input ~ 0
A12
Text GLabel 6250 4450 3    60   Input ~ 0
A13
Text GLabel 4350 2450 0    60   Input ~ 0
A14
Text GLabel 4350 3200 0    60   Input ~ 0
A15
Text GLabel 5500 4450 3    60   BiDi ~ 0
PB6
Text GLabel 5500 1850 1    60   Input ~ 0
OE
Text GLabel 6250 1850 1    60   Input ~ 0
RW
Text GLabel 2850 6750 2    60   Input ~ 0
RW
Text GLabel 5800 1850 1    60   Input ~ 0
F1CE
Text GLabel 2800 2500 2    60   Input ~ 0
F1CE
Text GLabel 6100 1850 1    60   Input ~ 0
F2CE
Text GLabel 2800 4900 2    60   Input ~ 0
F2CE
Text GLabel 7800 3950 2    60   Input ~ 0
RA14
Text GLabel 1050 7200 0    60   Input ~ 0
RA14
Text GLabel 5950 4450 3    60   BiDi ~ 0
RCE
Text GLabel 2650 6900 2    60   BiDi ~ 0
RCE
Text GLabel 7800 2600 2    60   Input ~ 0
FA12
Text GLabel 4350 3350 0    60   Input ~ 0
FA13
Text GLabel 4350 2600 0    60   Input ~ 0
FA14
Text GLabel 6850 4450 3    60   Input ~ 0
FA15
Text GLabel 7800 3050 2    60   Input ~ 0
FA16
Text GLabel 5950 1850 1    60   Input ~ 0
FA17
Text GLabel 6550 4450 3    60   Input ~ 0
FA18
Text GLabel 4350 3950 0    60   BiDi ~ 0
TCK
Text GLabel 4350 3650 0    60   BiDi ~ 0
TDI
Text GLabel 7800 3800 2    60   BiDi ~ 0
TDO
Text GLabel 4350 3800 0    60   BiDi ~ 0
TMS
Text GLabel 9600 4050 0    60   BiDi ~ 0
TCK
Text GLabel 9550 4850 0    60   BiDi ~ 0
TDI
Text GLabel 9600 4250 0    60   BiDi ~ 0
TDO
Text GLabel 9600 4450 0    60   BiDi ~ 0
TMS
Text GLabel 1400 4300 0    60   Input ~ 0
FA12
Text GLabel 1400 1900 0    60   Input ~ 0
FA12
Text GLabel 1100 4400 0    60   Input ~ 0
FA13
Text GLabel 1100 2000 0    60   Input ~ 0
FA13
Text GLabel 1400 4500 0    60   Input ~ 0
FA14
Text GLabel 1400 2100 0    60   Input ~ 0
FA14
Text GLabel 1100 4600 0    60   Input ~ 0
FA15
Text GLabel 1100 2200 0    60   Input ~ 0
FA15
Text GLabel 1400 2300 0    60   Input ~ 0
FA16
Text GLabel 1400 4700 0    60   Input ~ 0
FA16
Text GLabel 1050 4800 0    60   Input ~ 0
FA17
Text GLabel 1100 2400 0    60   Input ~ 0
FA17
Text GLabel 1400 4900 0    60   Input ~ 0
FA18
Text GLabel 1400 2500 0    60   Input ~ 0
FA18
$Comp
L VCC #PWR016
U 1 1 52A85FC0
P 9450 2150
F 0 "#PWR016" H 9450 2250 30  0001 C CNN
F 1 "VCC" H 9450 2250 30  0000 C CNN
F 2 "" H 9450 2150 60  0000 C CNN
F 3 "" H 9450 2150 60  0000 C CNN
	1    9450 2150
	1    0    0    -1  
$EndComp
$Comp
L C C1
U 1 1 52A85FCF
P 9450 2350
F 0 "C1" H 9450 2450 40  0000 L CNN
F 1 "0.1uF" H 9456 2265 40  0000 L CNN
F 2 "~" H 9488 2200 30  0000 C CNN
F 3 "~" H 9450 2350 60  0000 C CNN
	1    9450 2350
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR017
U 1 1 52A85FDE
P 9450 2550
F 0 "#PWR017" H 9450 2550 30  0001 C CNN
F 1 "GND" H 9450 2480 30  0001 C CNN
F 2 "" H 9450 2550 60  0000 C CNN
F 3 "" H 9450 2550 60  0000 C CNN
	1    9450 2550
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR018
U 1 1 52A85FEB
P 9700 2150
F 0 "#PWR018" H 9700 2250 30  0001 C CNN
F 1 "VCC" H 9700 2250 30  0000 C CNN
F 2 "" H 9700 2150 60  0000 C CNN
F 3 "" H 9700 2150 60  0000 C CNN
	1    9700 2150
	1    0    0    -1  
$EndComp
$Comp
L C C2
U 1 1 52A85FF1
P 9700 2350
F 0 "C2" H 9700 2450 40  0000 L CNN
F 1 "0.1uF" H 9706 2265 40  0000 L CNN
F 2 "~" H 9738 2200 30  0000 C CNN
F 3 "~" H 9700 2350 60  0000 C CNN
	1    9700 2350
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR019
U 1 1 52A85FF7
P 9700 2550
F 0 "#PWR019" H 9700 2550 30  0001 C CNN
F 1 "GND" H 9700 2480 30  0001 C CNN
F 2 "" H 9700 2550 60  0000 C CNN
F 3 "" H 9700 2550 60  0000 C CNN
	1    9700 2550
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR020
U 1 1 52A85FFD
P 9950 2150
F 0 "#PWR020" H 9950 2250 30  0001 C CNN
F 1 "VCC" H 9950 2250 30  0000 C CNN
F 2 "" H 9950 2150 60  0000 C CNN
F 3 "" H 9950 2150 60  0000 C CNN
	1    9950 2150
	1    0    0    -1  
$EndComp
$Comp
L C C3
U 1 1 52A86003
P 9950 2350
F 0 "C3" H 9950 2450 40  0000 L CNN
F 1 "0.1uF" H 9956 2265 40  0000 L CNN
F 2 "~" H 9988 2200 30  0000 C CNN
F 3 "~" H 9950 2350 60  0000 C CNN
	1    9950 2350
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR021
U 1 1 52A86009
P 9950 2550
F 0 "#PWR021" H 9950 2550 30  0001 C CNN
F 1 "GND" H 9950 2480 30  0001 C CNN
F 2 "" H 9950 2550 60  0000 C CNN
F 3 "" H 9950 2550 60  0000 C CNN
	1    9950 2550
	1    0    0    -1  
$EndComp
$Comp
L C C4
U 1 1 52A86015
P 10200 2350
F 0 "C4" H 10200 2450 40  0000 L CNN
F 1 "0.1uF" H 10206 2265 40  0000 L CNN
F 2 "~" H 10238 2200 30  0000 C CNN
F 3 "~" H 10200 2350 60  0000 C CNN
	1    10200 2350
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR022
U 1 1 52A8601B
P 10200 2550
F 0 "#PWR022" H 10200 2550 30  0001 C CNN
F 1 "GND" H 10200 2480 30  0001 C CNN
F 2 "" H 10200 2550 60  0000 C CNN
F 3 "" H 10200 2550 60  0000 C CNN
	1    10200 2550
	1    0    0    -1  
$EndComp
Text GLabel 4500 7000 3    60   Input ~ 0
HALT
Text GLabel 6000 5800 1    60   Output ~ 0
CART
Text GLabel 6100 6000 1    60   Input ~ 0
MNI
Text GLabel 6200 5800 1    60   Input ~ 0
IRQ
$Comp
L VCC #PWR023
U 1 1 52AECC95
P 8100 6050
F 0 "#PWR023" H 8100 6150 30  0001 C CNN
F 1 "VCC" H 8100 6150 30  0000 C CNN
F 2 "" H 8100 6050 60  0000 C CNN
F 3 "" H 8100 6050 60  0000 C CNN
	1    8100 6050
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR024
U 1 1 52AECD02
P 8500 6550
F 0 "#PWR024" H 8500 6550 30  0001 C CNN
F 1 "GND" H 8500 6480 30  0001 C CNN
F 2 "" H 8500 6550 60  0000 C CNN
F 3 "" H 8500 6550 60  0000 C CNN
	1    8500 6550
	1    0    0    -1  
$EndComp
$Comp
L C C5
U 1 1 52AECD65
P 8100 6250
F 0 "C5" H 8100 6350 40  0000 L CNN
F 1 "4,7uF" H 8106 6165 40  0000 L CNN
F 2 "~" H 8138 6100 30  0000 C CNN
F 3 "~" H 8100 6250 60  0000 C CNN
	1    8100 6250
	1    0    0    -1  
$EndComp
$Comp
L SWITCH_INV J1
U 1 1 52AECE46
P 9700 5950
F 0 "J1" H 9500 6100 50  0000 C CNN
F 1 "VOLTAGE" H 9550 5800 50  0000 C CNN
F 2 "~" H 9700 5950 60  0000 C CNN
F 3 "~" H 9700 5950 60  0000 C CNN
	1    9700 5950
	-1   0    0    1   
$EndComp
$Comp
L VCC #PWR025
U 1 1 52AECE6E
P 9200 5700
F 0 "#PWR025" H 9200 5800 30  0001 C CNN
F 1 "VCC" H 9200 5800 30  0000 C CNN
F 2 "" H 9200 5700 60  0000 C CNN
F 3 "" H 9200 5700 60  0000 C CNN
	1    9200 5700
	1    0    0    -1  
$EndComp
Text GLabel 10200 5950 2    60   Output ~ 0
VCPLD
Text GLabel 5800 4450 3    60   Input ~ 0
VCPLD
Text GLabel 7800 3500 2    60   Input ~ 0
VCPLD
Text GLabel 6700 1850 1    60   Input ~ 0
VCPLD
Text GLabel 9300 4350 0    60   Input ~ 0
VCPLD
Wire Wire Line
	9650 1050 9650 1250
Wire Wire Line
	9350 1050 9350 1250
Wire Wire Line
	5700 6800 5700 6900
Wire Wire Line
	5800 6900 5800 6800
Wire Wire Line
	5800 5900 5800 6000
Wire Wire Line
	6100 4450 6100 4550
Wire Wire Line
	4350 2900 4200 2900
Wire Wire Line
	7800 3650 7900 3650
Wire Wire Line
	2650 6650 2750 6650
Wire Wire Line
	9800 4150 9700 4150
Wire Wire Line
	9800 4950 9700 4950
Wire Wire Line
	4500 6000 4500 5900
Wire Wire Line
	4600 6000 4600 5900
Wire Wire Line
	5700 6900 5800 6900
Wire Wire Line
	5750 6900 5750 6950
Connection ~ 5750 6900
Wire Wire Line
	2800 800  3000 800 
Wire Wire Line
	3000 1000 2800 1000
Wire Wire Line
	2800 1200 3000 1200
Wire Wire Line
	2800 1400 3000 1400
Wire Wire Line
	2650 5900 2850 5900
Wire Wire Line
	2650 6100 2850 6100
Wire Wire Line
	2650 6300 2850 6300
Wire Wire Line
	2650 6500 2850 6500
Wire Wire Line
	1200 1000 1400 1000
Wire Wire Line
	1200 1200 1400 1200
Wire Wire Line
	1200 1400 1400 1400
Wire Wire Line
	1200 1600 1400 1600
Wire Wire Line
	1200 1800 1400 1800
Wire Wire Line
	1350 5900 1550 5900
Wire Wire Line
	1350 6100 1550 6100
Wire Wire Line
	1350 6300 1550 6300
Wire Wire Line
	1350 6500 1550 6500
Wire Wire Line
	1350 6700 1550 6700
Wire Wire Line
	1350 6900 1550 6900
Wire Wire Line
	1350 7100 1550 7100
Wire Wire Line
	2800 3200 3000 3200
Wire Wire Line
	3000 3400 2800 3400
Wire Wire Line
	2800 3600 3000 3600
Wire Wire Line
	2800 3800 3000 3800
Wire Wire Line
	1200 3200 1400 3200
Wire Wire Line
	1200 3400 1400 3400
Wire Wire Line
	1200 3600 1400 3600
Wire Wire Line
	1200 3800 1400 3800
Wire Wire Line
	1200 4000 1400 4000
Wire Wire Line
	1200 4200 1400 4200
Wire Wire Line
	1200 800  1400 800 
Wire Wire Line
	5500 7000 5500 6800
Wire Wire Line
	5700 5800 5700 6000
Wire Wire Line
	5500 5800 5500 6000
Wire Wire Line
	5300 5800 5300 6000
Wire Wire Line
	5300 6800 5300 7000
Wire Wire Line
	5100 6800 5100 7000
Wire Wire Line
	4900 7000 4900 6800
Wire Wire Line
	4700 7000 4700 6800
Wire Wire Line
	4700 5800 4700 6000
Wire Wire Line
	5100 5800 5100 6000
Wire Wire Line
	4900 5800 4900 6000
Wire Wire Line
	5900 6800 5900 7000
Wire Wire Line
	6100 6800 6100 7000
Wire Wire Line
	2850 6750 2650 6750
Wire Wire Line
	1050 7200 1550 7200
Wire Wire Line
	9600 4050 9800 4050
Wire Wire Line
	9550 4850 9800 4850
Wire Wire Line
	9600 4250 9800 4250
Wire Wire Line
	9600 4450 9800 4450
Wire Wire Line
	1100 4400 1400 4400
Wire Wire Line
	1100 2000 1400 2000
Wire Wire Line
	1100 4600 1400 4600
Wire Wire Line
	1100 2200 1400 2200
Wire Wire Line
	1050 4800 1400 4800
Wire Wire Line
	1100 2400 1400 2400
Wire Wire Line
	4500 6800 4500 7000
Wire Wire Line
	6000 5800 6000 6000
Wire Wire Line
	6200 6000 6200 5800
Wire Wire Line
	8500 6350 8500 6550
Wire Wire Line
	8500 6450 8100 6450
Connection ~ 8500 6450
Wire Wire Line
	9300 4350 9800 4350
$Comp
L PWR_FLAG #FLG026
U 1 1 52AED3F8
P 9900 1050
F 0 "#FLG026" H 9900 1145 30  0001 C CNN
F 1 "PWR_FLAG" H 9900 1230 30  0000 C CNN
F 2 "" H 9900 1050 60  0000 C CNN
F 3 "" H 9900 1050 60  0000 C CNN
	1    9900 1050
	1    0    0    -1  
$EndComp
Wire Wire Line
	9900 1050 9900 1250
Text GLabel 9900 1250 3    60   Output ~ 0
VCPLD
Wire Wire Line
	9200 5700 9200 5850
Text Label 8900 6050 0    60   ~ 0
VREG
Wire Wire Line
	8900 6050 9200 6050
$Comp
L TS2950 U5
U 1 1 52FB6204
P 8500 6100
F 0 "U5" H 8300 6300 40  0000 C CNN
F 1 "TS2950" H 8500 6300 40  0000 L CNN
F 2 "TO-92" H 8500 6200 30  0000 C CIN
F 3 "~" H 8500 6100 60  0000 C CNN
	1    8500 6100
	1    0    0    -1  
$EndComp
Text GLabel 2800 2100 2    60   Input ~ 0
RW
Text GLabel 2800 4500 2    60   Input ~ 0
RW
Text GLabel 2800 2300 2    60   Input ~ 0
OE
Text GLabel 2800 4700 2    60   Input ~ 0
OE
Text GLabel 7800 2750 2    60   Input ~ 0
OE
Text GLabel 10200 2150 1    60   Input ~ 0
VCPLD
NoConn ~ 7800 2900
$Comp
L CONN_1 P3
U 1 1 53F58DA1
P 10100 950
F 0 "P3" H 10180 950 40  0000 L CNN
F 1 "CONN_1" H 10100 1005 30  0001 C CNN
F 2 "" H 10100 950 60  0000 C CNN
F 3 "" H 10100 950 60  0000 C CNN
	1    10100 950 
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR027
U 1 1 53F58DB0
P 10100 1100
F 0 "#PWR027" H 10100 1100 30  0001 C CNN
F 1 "GND" H 10100 1030 30  0001 C CNN
F 2 "" H 10100 1100 60  0000 C CNN
F 3 "" H 10100 1100 60  0000 C CNN
	1    10100 1100
	1    0    0    -1  
$EndComp
$Comp
L CONN_1 P4
U 1 1 53F58DCC
P 10250 950
F 0 "P4" H 10330 950 40  0000 L CNN
F 1 "CONN_1" H 10250 1005 30  0001 C CNN
F 2 "" H 10250 950 60  0000 C CNN
F 3 "" H 10250 950 60  0000 C CNN
	1    10250 950 
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR028
U 1 1 53F58DD2
P 10250 1100
F 0 "#PWR028" H 10250 1100 30  0001 C CNN
F 1 "GND" H 10250 1030 30  0001 C CNN
F 2 "" H 10250 1100 60  0000 C CNN
F 3 "" H 10250 1100 60  0000 C CNN
	1    10250 1100
	1    0    0    -1  
$EndComp
$EndSCHEMATC
