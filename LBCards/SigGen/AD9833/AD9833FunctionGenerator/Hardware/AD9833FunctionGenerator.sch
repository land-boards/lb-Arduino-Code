EESchema Schematic File Version 4
LIBS:AD9833FunctionGenerator-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 3
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
L AD9833FunctionGenerator-rescue:Conn_01x07 J_AD9833
U 1 1 5B8B29C3
P 4050 2000
F 0 "J_AD9833" H 3850 2650 50  0000 C CNN
F 1 "Conn_01x07" H 3900 2550 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x07_P2.54mm_Vertical" H 4050 2000 50  0001 C CNN
F 3 "" H 4050 2000 50  0001 C CNN
	1    4050 2000
	1    0    0    -1  
$EndComp
Text Label 2400 1650 0    50   ~ 0
GND
Wire Wire Line
	9800 3750 9800 3550
Text Label 9800 3550 2    50   ~ 0
5V
$Comp
L Device:CP C1
U 1 1 5B8B3473
P 1200 3050
F 0 "C1" H 1225 3150 50  0000 L CNN
F 1 "220nF" H 1225 2950 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 1238 2900 50  0001 C CNN
F 3 "" H 1200 3050 50  0001 C CNN
	1    1200 3050
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C2
U 1 1 5B8B34AC
P 2300 3050
F 0 "C2" H 2325 3150 50  0000 L CNN
F 1 "100nF" H 2325 2950 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 2338 2900 50  0001 C CNN
F 3 "" H 2300 3050 50  0001 C CNN
	1    2300 3050
	1    0    0    -1  
$EndComp
Wire Wire Line
	1200 2700 1200 2900
Wire Wire Line
	2000 2700 2300 2700
Wire Wire Line
	2300 2700 2300 2900
Wire Wire Line
	1700 3000 1700 3300
Wire Wire Line
	1200 3200 1200 3300
Wire Wire Line
	1200 3300 1700 3300
Connection ~ 1700 3300
Wire Wire Line
	2300 3300 2300 3200
Text Label 2550 1350 2    50   ~ 0
+12V
Connection ~ 2300 2700
Text Label 2600 2700 2    50   ~ 0
5V
Wire Wire Line
	10400 5250 10600 5250
Wire Wire Line
	10400 5150 10600 5150
Text Label 10600 5250 2    50   ~ 0
SCL
Text Label 10600 5150 2    50   ~ 0
SDA
Wire Wire Line
	9900 5750 9900 5850
Text Label 9900 6050 2    50   ~ 0
GND
Wire Wire Line
	9400 5150 8950 5150
Text Label 8950 5150 0    50   ~ 0
DDS_CS
Wire Wire Line
	9400 5250 8950 5250
Text Label 8950 5250 0    50   ~ 0
MOSI
Wire Wire Line
	9400 5450 8950 5450
Text Label 8950 5450 0    50   ~ 0
SCK
Wire Wire Line
	3850 1800 3400 1800
Wire Wire Line
	3850 1900 3400 1900
Wire Wire Line
	3850 2000 3400 2000
Wire Wire Line
	3850 2100 3400 2100
Wire Wire Line
	3850 2200 3400 2200
Wire Wire Line
	3850 2300 3400 2300
Text Notes 4150 2350 0    63   ~ 0
REF\nVCC\nGND\nDAT\nCLK\nFNC\nOUT
NoConn ~ 3850 1700
Text Label 3400 1800 0    50   ~ 0
5V
Text Label 3400 1900 0    50   ~ 0
GND
Text Label 3400 2000 0    50   ~ 0
MOSI
Text Label 3400 2100 0    50   ~ 0
SCK
Text Label 3400 2200 0    50   ~ 0
DDS_CS
Text Label 3400 2300 0    50   ~ 0
DDS_SIG
Wire Wire Line
	1200 2700 1400 2700
Wire Wire Line
	1700 3300 2300 3300
Wire Wire Line
	2300 2700 2600 2700
$Comp
L Regulator_Linear:LM7805_TO220 U1
U 1 1 5BA958E1
P 1700 2700
F 0 "U1" H 1700 2939 50  0000 C CNN
F 1 "LM7805_TO220" H 1700 2850 50  0000 C CNN
F 2 "Package_TO_SOT_THT:TO-220-3_Vertical" H 1700 2925 50  0001 C CIN
F 3 "http://www.fairchildsemi.com/ds/LM/LM7805.pdf" H 1700 2650 50  0001 C CNN
F 4 "926-LM7805CT/NOPB" H -1300 1200 50  0001 C CNN "MouserPartNo"
	1    1700 2700
	1    0    0    -1  
$EndComp
Wire Wire Line
	10400 4850 10800 4850
Wire Wire Line
	10400 4750 10800 4750
Text Label 5250 5700 2    50   ~ 0
5V
Text Label 5250 6700 2    50   ~ 0
GND
Text Label 5750 6000 2    50   ~ 0
FREQHI
Text Label 10800 4750 2    50   ~ 0
FREQHI
Text Label 10800 4850 2    50   ~ 0
FREQLO
Wire Wire Line
	9400 4350 8950 4350
Text Label 8950 4350 0    50   ~ 0
WAVEBTN
Wire Wire Line
	9400 4450 8950 4450
Text Label 8950 4450 0    50   ~ 0
MODEBTN
Text Label 4050 5400 2    50   ~ 0
GND
Text Label 4050 4350 2    50   ~ 0
5V
Wire Wire Line
	4200 4600 4450 4600
Text Label 4450 4600 2    50   ~ 0
VEL1
Wire Wire Line
	10400 5350 10625 5350
Text Label 10625 5350 2    50   ~ 0
VEL1
$Comp
L Device:R R_VEL1
U 1 1 5BB29D66
P 4050 5050
F 0 "R_VEL1" H 4250 5000 50  0000 C CNN
F 1 "100R" H 4300 5100 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 3980 5050 50  0001 C CNN
F 3 "~" H 4050 5050 50  0001 C CNN
	1    4050 5050
	-1   0    0    1   
$EndComp
Text Label 2550 1950 2    50   ~ 0
-12V
Text Label 5200 1850 0    50   ~ 0
DDS_SIG
$Comp
L power:PWR_FLAG #FLG0101
U 1 1 5BB589B5
P 2600 1350
F 0 "#FLG0101" H 2600 1425 50  0001 C CNN
F 1 "PWR_FLAG" V 2600 1500 50  0001 L CNN
F 2 "" H 2600 1350 50  0001 C CNN
F 3 "~" H 2600 1350 50  0001 C CNN
	1    2600 1350
	0    1    1    0   
$EndComp
$Comp
L power:PWR_FLAG #FLG0102
U 1 1 5BB5C39F
P 2600 1650
F 0 "#FLG0102" H 2600 1725 50  0001 C CNN
F 1 "PWR_FLAG" V 2600 1800 50  0001 L CNN
F 2 "" H 2600 1650 50  0001 C CNN
F 3 "~" H 2600 1650 50  0001 C CNN
	1    2600 1650
	0    1    1    0   
$EndComp
Wire Wire Line
	1900 1350 2100 1350
$Comp
L power:PWR_FLAG #FLG0103
U 1 1 5BB669DD
P 2600 1950
F 0 "#FLG0103" H 2600 2025 50  0001 C CNN
F 1 "PWR_FLAG" V 2600 2100 50  0001 L CNN
F 2 "" H 2600 1950 50  0001 C CNN
F 3 "~" H 2600 1950 50  0001 C CNN
	1    2600 1950
	0    1    1    0   
$EndComp
Wire Wire Line
	1200 2700 900  2700
Connection ~ 1200 2700
Text Label 900  2700 0    50   ~ 0
+12V
$Comp
L Connector_Generic:Conn_01x02 J_OUT1
U 1 1 5BB86F40
P 10700 2050
F 0 "J_OUT1" H 10550 2200 50  0000 L CNN
F 1 "Conn_01x02" H 10780 1951 50  0001 L CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x02_P2.54mm_Vertical" H 10700 2050 50  0001 C CNN
F 3 "~" H 10700 2050 50  0001 C CNN
	1    10700 2050
	1    0    0    -1  
$EndComp
Wire Wire Line
	10500 2150 10350 2150
Text Label 10350 2800 2    50   ~ 0
GND
Wire Wire Line
	1650 1650 1650 1550
Wire Wire Line
	1650 1550 1400 1550
Wire Wire Line
	1650 1650 1650 1750
Connection ~ 1650 1650
$Comp
L Connector_Generic:Conn_02x05_Odd_Even J_PWR1
U 1 1 5BBA34EF
P 1100 1650
F 0 "J_PWR1" H 1150 2067 50  0000 C CNN
F 1 "Conn_02x05_Odd_Even" H 1150 1976 50  0001 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_2x05_P2.54mm_Vertical" H 1100 1650 50  0001 C CNN
F 3 "~" H 1100 1650 50  0001 C CNN
	1    1100 1650
	1    0    0    -1  
$EndComp
Wire Wire Line
	9400 4650 8950 4650
Text Label 8950 4650 0    50   ~ 0
RANGEBTN
Wire Wire Line
	6500 1850 5200 1850
$Comp
L Potentiometer_Digital:MCP42050 U_POT1
U 1 1 5BB5DA86
P 7000 2150
F 0 "U_POT1" H 6600 2800 50  0000 C CNN
F 1 "MCP42050" H 6600 2700 50  0000 C CNN
F 2 "Package_SO:SOIC-14_3.9x8.7mm_P1.27mm" H 7000 2250 50  0001 C CNN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/11195c.pdf" H 7000 2250 50  0001 C CNN
F 4 "579-MCP42050-I/SL" H 1150 -2950 50  0001 C CNN "MouserPartNo"
	1    7000 2150
	-1   0    0    -1  
$EndComp
Wire Wire Line
	7500 1850 7700 1850
Text Label 7700 1850 2    50   ~ 0
SCK
Wire Wire Line
	7500 1950 7700 1950
Text Label 7700 1950 2    50   ~ 0
MOSI
NoConn ~ 7500 2050
Wire Wire Line
	7500 2150 7750 2150
Text Label 7750 2150 2    50   ~ 0
POT_CS
Wire Wire Line
	9400 5050 8950 5050
Text Label 8950 5050 0    50   ~ 0
POT_CS
Wire Wire Line
	7500 2350 7600 2350
Wire Wire Line
	7500 2450 7600 2450
Wire Wire Line
	7000 1650 7000 1450
Text Label 7000 1300 2    50   ~ 0
5V
Wire Wire Line
	7000 2650 7000 2800
Text Label 7000 2800 2    50   ~ 0
GND
Wire Wire Line
	7600 2450 7600 2350
Connection ~ 7600 2350
Wire Wire Line
	7600 2350 7750 2350
Text Label 7750 2350 2    50   ~ 0
5V
Wire Wire Line
	5200 1950 6500 1950
Wire Wire Line
	10350 2150 10350 2800
Wire Wire Line
	10150 2050 10500 2050
$Comp
L Device:R_POT_Dual_Separate RV_FREQ1
U 2 1 5BF20191
P 5250 6000
F 0 "RV_FREQ1" H 5100 5950 50  0000 R CNN
F 1 "B10K" H 5050 6050 50  0000 R CNN
F 2 "PTH901:PTH901" H 5250 6000 50  0001 C CNN
F 3 "~" H 5250 6000 50  0001 C CNN
F 4 "652-PTH901-030S-103B" H 0   -1050 50  0001 C CNN "MouserPartNo"
	2    5250 6000
	1    0    0    1   
$EndComp
$Comp
L MCU_Module:Arduino_Nano_v3.x A1
U 1 1 5BBCCF3E
P 9900 4750
F 0 "A1" H 9150 5900 50  0000 C CNN
F 1 "Arduino_Nano_v3.x" H 9200 5800 50  0000 C CNN
F 2 "Module:Arduino_Nano" H 10050 3800 50  0001 L CNN
F 3 "http://www.mouser.com/pdfdocs/Gravitech_Arduino_Nano3_0.pdf" H 9900 3750 50  0001 C CNN
	1    9900 4750
	1    0    0    -1  
$EndComp
Wire Wire Line
	10000 3750 10000 3550
Text Label 10000 3550 3    50   ~ 0
AREF
Wire Wire Line
	10400 4550 10650 4550
Text Label 10650 4550 2    50   ~ 0
AREF
Wire Wire Line
	10000 5750 10000 5850
Wire Wire Line
	10000 5850 9900 5850
Connection ~ 9900 5850
Wire Wire Line
	9900 5850 9900 6050
NoConn ~ 9400 4150
NoConn ~ 9400 4250
NoConn ~ 9400 4550
NoConn ~ 9400 4750
NoConn ~ 9400 4850
NoConn ~ 9400 4950
NoConn ~ 9400 5350
NoConn ~ 10400 4950
NoConn ~ 10400 5450
NoConn ~ 10400 4250
NoConn ~ 10400 4150
NoConn ~ 10100 3750
Text Label 5200 1950 0    50   ~ 0
DDS_REDUX
Wire Wire Line
	4050 5200 4050 5400
$Sheet
S 1350 4500 1400 1600
U 5C156641
F0 "AuxiliaryBoard" 50
F1 "AuxiliaryBoard.sch" 50
F2 "5V" I R 2750 5100 50 
F3 "GND" I R 2750 5550 50 
F4 "RANGEBTN" I L 1350 4700 50 
F5 "MODEBTN" I L 1350 5000 50 
F6 "WAVEBTN" I L 1350 5300 50 
F7 "SCL" I L 1350 5900 50 
F8 "SDA" I L 1350 5600 50 
$EndSheet
$Sheet
S 9100 1450 1050 1100
U 5BBD761F
F0 "OutputSection" 50
F1 "OutputSection.sch" 50
F2 "SIGIN" I L 9100 2050 50 
F3 "+12V" I L 9100 1550 50 
F4 "-12V" I L 9100 1650 50 
F5 "SIGOUT" I R 10150 2050 50 
F6 "GND" I L 9100 2450 50 
F7 "OFFSETADJUST" I L 9100 1850 50 
$EndSheet
Text Label 1700 3600 2    50   ~ 0
GND
Wire Wire Line
	1700 3300 1700 3600
Wire Wire Line
	9100 2450 8850 2450
Wire Wire Line
	8850 2450 8850 2800
Text Label 8850 2800 2    50   ~ 0
GND
Wire Wire Line
	9100 1550 8950 1550
Wire Wire Line
	8950 1550 8950 1300
Text Label 8950 1300 2    50   ~ 0
+12V
Wire Wire Line
	9100 1650 8700 1650
Wire Wire Line
	8700 1650 8700 1300
Text Label 8700 1300 2    50   ~ 0
-12V
Wire Notes Line
	3200 1000 3200 2800
Wire Notes Line
	4500 2800 4500 1000
Wire Notes Line
	4500 1000 3200 1000
Wire Notes Line
	10900 3100 10900 1000
Wire Notes Line
	10900 1000 8400 1000
Wire Notes Line
	8400 1000 8400 3100
Wire Notes Line
	8400 3100 10900 3100
Wire Notes Line
	700  1000 700  3700
Wire Notes Line
	2900 1000 700  1000
Text Notes 3200 950  0    50   ~ 0
DDS Signal Generation
Text Notes 8400 950  0    50   ~ 0
Output Amplifier Section
Text Notes 700  950  0    50   ~ 0
Power Supply Section
Wire Notes Line
	8700 3400 10900 3400
Wire Notes Line
	10900 3400 10900 6200
Wire Notes Line
	10900 6200 8700 6200
Wire Notes Line
	8700 6200 8700 3400
Wire Wire Line
	4050 4750 4050 4900
Wire Wire Line
	4050 4350 4050 4450
Text Notes 1050 4150 0    50   ~ 0
Peripheral Controls section
Wire Wire Line
	1350 5300 900  5300
Text Label 900  5300 0    50   ~ 0
WAVEBTN
Wire Wire Line
	1350 5000 900  5000
Text Label 900  5000 0    50   ~ 0
MODEBTN
Wire Wire Line
	1350 4700 900  4700
Text Label 900  4700 0    50   ~ 0
RANGEBTN
Wire Wire Line
	1350 5600 1150 5600
Text Label 1150 5600 0    50   ~ 0
SDA
Wire Wire Line
	1350 5900 1150 5900
Text Label 1150 5900 0    50   ~ 0
SCL
Text Label 3050 6100 2    50   ~ 0
GND
Wire Wire Line
	3050 5550 3050 6100
Wire Wire Line
	2750 5550 3050 5550
Wire Wire Line
	2750 5100 3050 5100
Wire Wire Line
	3050 5100 3050 4500
Text Label 3050 4500 2    50   ~ 0
5V
Wire Wire Line
	8500 2050 9100 2050
Text Label 8500 2050 0    50   ~ 0
DDS_REDUX
Wire Notes Line
	3200 2800 4500 2800
Wire Notes Line
	4800 1000 7900 1000
Wire Notes Line
	7900 1000 7900 3100
Wire Notes Line
	7900 3100 4800 3100
Wire Notes Line
	4800 3100 4800 1000
Text Notes 5600 950  0    50   ~ 0
Signal Compensation
Text Notes 8700 3350 0    50   ~ 0
Micocontroller
$Comp
L Device:C C_POTBP1
U 1 1 5BC0F1E8
P 6100 1450
F 0 "C_POTBP1" V 5851 1450 50  0000 C CNN
F 1 "100nF" V 5940 1450 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 6138 1300 50  0001 C CNN
F 3 "~" H 6100 1450 50  0001 C CNN
	1    6100 1450
	0    1    1    0   
$EndComp
Wire Wire Line
	6250 1450 7000 1450
Connection ~ 7000 1450
Wire Wire Line
	7000 1450 7000 1300
Wire Wire Line
	5950 1450 5000 1450
Text Label 5000 2800 0    50   ~ 0
GND
Wire Wire Line
	6500 2450 6300 2450
Wire Wire Line
	6500 2350 5200 2350
$Comp
L Device:R ROFF1
U 1 1 5BC66CD0
P 6150 2250
F 0 "ROFF1" V 6050 2250 50  0000 C CNN
F 1 "1K" V 6150 2250 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 6080 2250 50  0001 C CNN
F 3 "~" H 6150 2250 50  0001 C CNN
	1    6150 2250
	0    1    1    0   
$EndComp
Wire Wire Line
	6300 2250 6500 2250
$Comp
L Device:R ROFF2
U 1 1 5BC6A9D4
P 6150 2450
F 0 "ROFF2" V 6250 2450 50  0000 C CNN
F 1 "1K" V 6150 2450 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 6080 2450 50  0001 C CNN
F 3 "~" H 6150 2450 50  0001 C CNN
	1    6150 2450
	0    1    1    0   
$EndComp
Wire Wire Line
	6000 2250 5750 2250
Wire Wire Line
	5750 2250 5750 2150
Text Label 5750 2150 3    50   ~ 0
5V
Wire Wire Line
	6000 2450 5750 2450
Wire Wire Line
	5750 2450 5750 2625
Text Label 5750 2625 1    50   ~ 0
GND
Text Label 5200 2350 0    50   ~ 0
OFFSETADJUST
Wire Wire Line
	9100 1850 8500 1850
Text Label 8500 1850 0    50   ~ 0
OFFSETADJUST
Wire Wire Line
	5000 1450 5000 2800
Text Label 5900 2200 1    50   ~ 0
GND
Wire Wire Line
	5900 2050 5900 2200
Wire Wire Line
	5900 2050 6500 2050
$Comp
L Switch:SW_DPDT_x2 SW_PWR1
U 1 1 5BCEE1CD
P 1700 1450
F 0 "SW_PWR1" H 1700 1643 50  0000 C CNN
F 1 "SW_DPDT_x2" H 1700 1644 50  0001 C CNN
F 2 "ALPS_SPUN191600:ALPS_SPUN191600" H 1700 1450 50  0001 C CNN
F 3 "" H 1700 1450 50  0001 C CNN
	1    1700 1450
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_DPDT_x2 SW_PWR1
U 2 1 5BCEE23F
P 1700 1850
F 0 "SW_PWR1" H 1700 2100 50  0000 C CNN
F 1 "SW_DPDT_x2" H 1700 2200 50  0001 C CNN
F 2 "ALPS_SPUN191600:ALPS_SPUN191600" H 1700 1850 50  0001 C CNN
F 3 "" H 1700 1850 50  0001 C CNN
	2    1700 1850
	1    0    0    1   
$EndComp
NoConn ~ 900  1450
NoConn ~ 900  1850
Wire Wire Line
	1400 1450 1500 1450
Wire Wire Line
	1400 1850 1500 1850
NoConn ~ 1900 1550
NoConn ~ 1900 1750
Wire Wire Line
	1400 1750 1650 1750
Wire Wire Line
	1900 1950 2100 1950
Wire Wire Line
	1650 1650 2100 1650
Wire Wire Line
	1400 1650 1650 1650
$Comp
L Device:R_POT_Dual_Separate RV_TIME1
U 1 1 5BC6763B
P 4050 4600
F 0 "RV_TIME1" H 3980 4600 50  0000 R CNN
F 1 "R_POT_Dual_Separate" H 3980 4555 50  0001 R CNN
F 2 "PTH901:PTH901" H 4050 4600 50  0001 C CNN
F 3 "~" H 4050 4600 50  0001 C CNN
	1    4050 4600
	1    0    0    -1  
$EndComp
$Comp
L Device:R_POT_Dual_Separate RV_TIME1
U 2 1 5BC676BC
P 4050 5900
F 0 "RV_TIME1" H 3980 5900 50  0000 R CNN
F 1 "R_POT_Dual_Separate" H 3980 5855 50  0001 R CNN
F 2 "PTH901:PTH901" H 4050 5900 50  0001 C CNN
F 3 "~" H 4050 5900 50  0001 C CNN
	2    4050 5900
	1    0    0    -1  
$EndComp
Text Label 4050 6700 2    50   ~ 0
GND
Text Label 4050 5650 2    50   ~ 0
5V
Wire Wire Line
	4200 5900 4550 5900
Text Label 4550 5900 2    50   ~ 0
PHASE1
$Comp
L Device:R R_PHASE1
U 1 1 5BC7BDA5
P 4050 6350
F 0 "R_PHASE1" H 4300 6300 50  0000 C CNN
F 1 "100R" H 4300 6400 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 3980 6350 50  0001 C CNN
F 3 "~" H 4050 6350 50  0001 C CNN
	1    4050 6350
	-1   0    0    1   
$EndComp
Wire Wire Line
	4050 6500 4050 6700
Wire Wire Line
	4050 6050 4050 6200
Wire Wire Line
	4050 5650 4050 5750
Wire Wire Line
	10400 5050 10750 5050
Text Label 10750 5050 2    50   ~ 0
PHASE1
Text Label 5250 4400 2    50   ~ 0
5V
Text Label 5250 5400 2    50   ~ 0
GND
Text Label 5750 4800 2    50   ~ 0
FREQLO
$Comp
L Device:R_POT_Dual_Separate RV_FREQ1
U 1 1 5BCABCEC
P 5250 4800
F 0 "RV_FREQ1" H 5100 4750 50  0000 R CNN
F 1 "B10K" H 5000 4850 50  0000 R CNN
F 2 "PTH901:PTH901" H 5250 4800 50  0001 C CNN
F 3 "~" H 5250 4800 50  0001 C CNN
F 4 "652-PTH901-030S-103B" H 1500 -2250 50  0001 C CNN "MouserPartNo"
	1    5250 4800
	1    0    0    1   
$EndComp
Wire Wire Line
	5250 4400 5250 4650
Wire Wire Line
	5750 4800 5400 4800
Wire Wire Line
	5250 4950 5250 5400
Wire Wire Line
	5250 5700 5250 5850
Wire Wire Line
	5400 6000 5750 6000
Wire Wire Line
	5250 6150 5250 6700
Wire Notes Line
	6000 6800 700  6800
Wire Notes Line
	2900 1000 2900 3700
Wire Notes Line
	700  3700 2900 3700
Wire Notes Line
	700  6800 700  4000
Wire Notes Line
	700  4000 6000 4000
Wire Notes Line
	6000 4000 6000 6800
NoConn ~ 900  1550
NoConn ~ 900  1650
NoConn ~ 900  1750
$Comp
L Device:C CPWRBP2
U 1 1 5BCBBC9B
P 2100 1800
F 0 "CPWRBP2" H 2215 1845 50  0000 L CNN
F 1 "100nF" H 2215 1756 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 2138 1650 50  0001 C CNN
F 3 "~" H 2100 1800 50  0001 C CNN
	1    2100 1800
	1    0    0    -1  
$EndComp
Connection ~ 2100 1650
Wire Wire Line
	2100 1650 2600 1650
Connection ~ 2100 1950
Wire Wire Line
	2100 1950 2600 1950
$Comp
L Device:C CPWRBP1
U 1 1 5BCBBCF7
P 2100 1500
F 0 "CPWRBP1" H 2215 1545 50  0000 L CNN
F 1 "100nF" H 2215 1456 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 2138 1350 50  0001 C CNN
F 3 "~" H 2100 1500 50  0001 C CNN
	1    2100 1500
	1    0    0    -1  
$EndComp
Connection ~ 2100 1350
Wire Wire Line
	2100 1350 2600 1350
$EndSCHEMATC
