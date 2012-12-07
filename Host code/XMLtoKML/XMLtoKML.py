# XMLtoKML.py
# Converts a waypoint XML file to a KML file

import time
import string
import sys
#import serial

# open the file for reading
infile = open("LOCUS_DataLogger.xml", "r")

# open the file for writing
outfile = open("LOCUS_DataLogger.kml","w")

line = infile.readline().strip('\n\r')
if line != '<?xml version="1.0"?>':
  print "First line didn't match what was expected"
  print 'Expected: <?xml version="1.0"?>'
  print 'Got: ',line
  sys.exit
  
line = infile.readline().strip('\n\r')
if line != '<dataset2 xmlns="xsdbooks">':
  print "Second line didn't match what was expected"
  print 'Expected: <dataset2 xmlns="xsdbooks">'
  print 'Got: ',line
  sys.exit

outfile.write('<?xml version="1.0" encoding="UTF-8"?>\n')
outfile.write('  <kml xmlns="http://www.opengis.net/kml/2.2">\n')
outfile.write('   <Document>\n')
outfile.write('     <name>GPS Path</name>\n')
outfile.write('     <description>Path parsed from GPS data.</description>\n')
outfile.write('     <Style id="yellowLineGreenPoly">\n')
outfile.write('       <LineStyle>\n')
outfile.write('         <color>7f00ffff</color>\n')
outfile.write('         <width>4</width> \n')
outfile.write('       </LineStyle> \n')
outfile.write('       <PolyStyle> \n')
outfile.write('         <color>7f00ff00</color> \n')
outfile.write('       </PolyStyle> \n')
outfile.write('     </Style> \n')
outfile.write('     <Placemark> \n')
outfile.write('       <name>Begin</name> \n')
outfile.write('       <description>Start GPD Data</description> \n')
outfile.write('       <styleUrl>#yellowLineGreenPoly</styleUrl> \n')
outfile.write('       <LineString> \n')
outfile.write('         <extrude>1</extrude> \n')
outfile.write('         <tessellate>1</tessellate> \n')
outfile.write('         <altitudeMode>absolute</altitudeMode> \n')
outfile.write('         <coordinates>')
  
line = infile.readline().strip('\n\r')
while line:
# Input file format
#    <Count Data="1">
#    <UTC>2012-11-05,21:43:05</UTC>
#    <FixType>3D-fix</FixType>
#    <Lat>39.936371</Lat>
#    <Lon>-79.665398</Lon>
#    <HGT>315</HGT>
#  </Count>

  if line[0:14] != "  <Count Data=":
    print "Expected: <Count Data="
    print 'Got:', line
    sys.exit(0)
  line = infile.readline().strip('\n\r')
  if line[0:9] != "    <UTC>":
    print "Expected:     <UTC>"
    sys.exit(0)
  line = infile.readline().strip('\n\r')
  if line[0:29] != "    <FixType>3D-fix</FixType>":
    print 'Got a line without a 3D fix on it'
    sys.exit(0)
  else:
    print 'Got a fix'
  # Latitude
  line = infile.readline().strip('\n\r')
  if line[0:9] != "    <Lat>":
    print 'Expected:     <Lat>'
    print 'Got:',line
    sys.exit(0)
  startPos = 9
  endPos = string.find(line, '<', startPos+1)
  lat = float(line[startPos:endPos])
#  print 'lat:', lat
  # Longitude
  line = infile.readline().strip('\n\r')
  if line[0:9] != "    <Lon>":
    print 'Expected:     <Lon>'
    print 'Got:',line
    sys.exit(0)
  startPos = 9
  endPos = string.find(line, '<', startPos+1)
  lon = float(line[startPos:endPos])
#  print 'lon:', lon
  # Height above sea leval
  line = infile.readline().strip('\n\r')
  if line[0:9] != "    <HGT>":
    print 'Expected:     <HGT>'
    print 'Got:',line
    sys.exit(0)
  startPos = 9
  endPos = string.find(line, '<', startPos+1)
  height = float(line[startPos:endPos])
#  print 'height:', height
  # end count
  line = infile.readline().strip('\n\r')
  if line[0:10] != "  </Count>":
    print 'Expected:  </Count>'
    print 'Got:',line
    sys.exit(0)
  print lon,
  print ',',lat,
  print ',',height
  outfile.write(str(lon))
  outfile.write(',')
  outfile.write(str(lat))
  outfile.write(',')
  outfile.write(str(height))
  outfile.write('\n')
  line = infile.readline().strip('\n\r')
  if line[0:14] != "  <Count Data=":
    break;
# output file format
outfile.write('</coordinates>\n')
outfile.write('       </LineString>\n')
outfile.write('     </Placemark>\n')
outfile.write('   </Document>\n')
outfile.write(' </kml>\n')

# Close opened files
infile.close()
outfile.close()

