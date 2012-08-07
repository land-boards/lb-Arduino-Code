#!/usr/bin/env python
# http://docs.python.org/library/csv.html

import csv 
from sys import argv

fileToRead = ""
fileToWrite = ""

if len(argv) == 1:
	fileToRead = "eggs.csv"
	fileToWrite = "egga_out.csv"
elif len(argv) == 2:
	fileToRead = argv[1]
	fileToWrite = fileToRead[:-4] + "_out.csv"
elif len(argv) >= 3:
	fileToRead = argv[1]
	fileToWrite = argv[2]

if fileToRead[-4:] != ".csv":
	print "Input file must end in .csv"
	exit()

if fileToWrite[-4:] != ".csv":
	print "Output file must end in .csv"
	exit()

spamReader = csv.reader(open(fileToRead, 'rb'), delimiter=',', quotechar='"')

spamWriter = csv.writer(open(fileToWrite, 'wb'), delimiter=',', quotechar='"')

for inRow in spamReader:
	outRow=[]
	if inRow[0] != None:
		outRow.append(inRow[2])
		outRow.append(inRow[1])
		spamWriter.writerow(outRow)

