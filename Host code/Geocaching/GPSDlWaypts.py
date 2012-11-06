# GPSDlWaypts.py
# Download waypoints to the GPS

import time
import serial
import string
import sys
 
# Configure the serial port to talk to the Arduino
connection = serial.Serial('/dev/ttyUSB1', 115200)
time.sleep(2)

connection.flushInput()

# read from the Arduino until receiving <DL> string
print "Waiting for start from Arduino"
data = connection.readline().strip('\n\r')
while data != "<DL>":
	data = connection.readline().strip('\n\r')
print "Received start from Arduino"

waypointNum = 0;

# open the file for reading
infile = open("geocaching.loc", "r") 

# if the line starts with <coord then pull out the numbers
# example: <coord lat="40.005717" lon="-79.598867"/>
# send the numbers to the arduino

line = infile.readline().strip('\n\r')
while line:
	line = infile.readline().strip('\n\r')
	if line[0:7] == "<coord ":
		startPos = string.find(line, '\"') + 1
		endPos = string.find(line, '\"', startPos+1)
		lat = float(line[startPos:endPos])
		startPos2 = string.find(line, '\"', endPos+1) + 1
		endPos2 = string.find(line, '\"', startPos2+1)
		lon = float(line[startPos2:endPos2])
		connection.write(str(waypointNum))
		connection.write("=" + str(round(lat,6)) + "," + str(round(lon,6)) + '\n')
		waypointNum = waypointNum + 1
		inChar = connection.read()
		if inChar != 'A':
			print "Ack missing?"

# Close opened file 
infile.close()

line = connection.readline()
print line,
while line[0:8] != "</SERIN>":
	line = connection.readline()
	print line,

print "Transfer completed"
