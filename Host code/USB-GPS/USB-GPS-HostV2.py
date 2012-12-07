# python code for interfacing to USB-GPS9 
# pretty basic stuff
# written by ladyada. MIT license

import serial
from time import sleep

BAUD = 9600
PORT = "/dev/ttyACM0"
TIMEOUT = 10

######## main

#ser = serial.Serial(0)
#print ser.portstr
#ser.close()

ser = serial.Serial(PORT, baudrate=BAUD, timeout=TIMEOUT)

BufLength = 0

while BufLength < 10000:
	data = ser.readline()
	BufLength += len(data)
	if len(data) > 0:
		print data,


ser.close()

