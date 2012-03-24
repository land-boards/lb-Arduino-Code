import time
import serial
 
# Configure the serial port
connection = serial.Serial('/dev/ttyUSB0', 9600)
while 1:
	data = connection.readline().strip('\n')
	print data
	time.sleep(1)

