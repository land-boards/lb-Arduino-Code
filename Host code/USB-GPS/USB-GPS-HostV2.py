# python code for interfacing to USB-GPS9 
# pretty basic stuff
# written by ladyada. MIT license

import serial
from time import sleep

BAUD = 9600
PORT = "/dev/ttyACM0"
TIMEOUT = 1

######## main

import time
import serial

ser = serial.Serial(PORT, baudrate=BAUD)

while 1:
  data = ser.readline().strip('\n\r')
  print data
#  time.sleep(0.1)
