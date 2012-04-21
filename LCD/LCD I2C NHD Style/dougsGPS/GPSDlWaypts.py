# GPSDlWaypts.py
# Download waypoints to the GPS

import time
import serial
 
# Configure the serial port to talk to the Arduino
connection = serial.Serial('/dev/ttyACM0', 9600)

# read from the Arduino until receiving <DL> string
data = connection.readline().strip('\n')
#while data <> "<DL>"
	data = connection.readline().strip('\n')

# open the file for reading
fo = open("geocaching.loc", "r") 
line = fo.readline()
while line:
	line = of.readline()
	#if the line starts with <coord then pull out the numbers
	# example: <coord lat="40.005717" lon="-79.598867"/>
	#send the numbers to the arduino
	
# Close opened file 
fo.close()
