//////////////////////////////////////////////////////////////////////////////
// Interrupt is called once a millisecond, looks for any new GPS data, and stores it
//////////////////////////////////////////////////////////////////////////////

SIGNAL(TIMER0_COMPA_vect) {
  char c = GPS.read();
  // if you want to debug, this is a good time to do it!
  if (GPSECHO)
    if (c) UDR0 = c;  
  // writing direct to UDR0 is much much faster than Serial.print 
  // but only one character can be written at a time. 
}

//////////////////////////////////////////////////////////////////////////////
// 
//////////////////////////////////////////////////////////////////////////////

void useInterrupt(boolean v) {
  if (v) {
    // Timer0 is already used for millis() - we'll just interrupt somewhere
    // in the middle and call the "Compare A" function above
    OCR0A = 0xAF;
    TIMSK0 |= _BV(OCIE0A);
    usingInterrupt = true;
  } 
  else {
    // do not call the interrupt function COMPA anymore
    TIMSK0 &= ~_BV(OCIE0A);
    usingInterrupt = false;
  }
}

//////////////////////////////////////////////////////////////////////////////
// 
//////////////////////////////////////////////////////////////////////////////

void GPSInit(void)
{
  // 9600 NMEA is the default baud rate for Adafruit MTK GPS's- some use 4800
  GPS.begin(9600);

  // uncomment this line to turn on RMC (recommended minimum) and GGA (fix data) including altitude
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  // uncomment this line to turn on only the "minimum recommended" data
  //GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCONLY);
  // For parsing data, we don't suggest using anything but either RMC only or RMC+GGA since
  // the parser doesn't care about other sentences at this time

  // Set the update rate
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);   // 1 Hz update rate
  // For the parsing code to work nicely and have time to sort thru the data, and
  // print it out we don't suggest using anything higher than 1 Hz

  // the nice thing about this code is you can have a timer0 interrupt go off
  // every 1 millisecond, and read data from the GPS for you. that makes the
  // loop code a heck of a lot easier!
  useInterrupt(true);
  return;
}

//////////////////////////////////////////////////////////////////////////////
// 
//////////////////////////////////////////////////////////////////////////////

void readGPS(void)
{
    // in case you are not using the interrupt above, you'll
  // need to 'hand query' the GPS, not suggested :(
  if (! usingInterrupt) {
    // read data from the GPS in the 'main loop'
    char c = GPS.read();
    // if you want to debug, this is a good time to do it!
    if (GPSECHO)
      if (c) UDR0 = c;
    // writing direct to UDR0 is much much faster than Serial.print 
    // but only one character can be written at a time. 
  }

  // if a sentence is received, we can check the checksum, parse it...
  if (GPS.newNMEAreceived()) {
    // a tricky thing here is if we print the NMEA sentence, or data
    // we end up not listening and catching other sentences! 
    // so be very wary if using OUTPUT_ALLDATA and trytng to print out data
    //Serial.println(GPS.lastNMEA());   // this also sets the newNMEAreceived() flag to false

    if (!GPS.parse(GPS.lastNMEA()))   // this also sets the newNMEAreceived() flag to false
      return;  // we can fail to parse a sentence in which case we should just wait for another
  }

  // approximately every 2 seconds or so, print out the current stats
  if (millis() - timer > 2000) { 
    timer = millis(); // reset the timer
#ifdef SERIAL_OUT
    Serial.print("\nTime: ");
    Serial.print(GPS.hour, DEC); 
    Serial.print(':');
    Serial.print(GPS.minute, DEC); 
    Serial.print(':');
    Serial.print(GPS.seconds, DEC); 
    Serial.print('.');
    Serial.println(GPS.milliseconds);
    Serial.print("Date: ");
    Serial.print(GPS.day, DEC); 
    Serial.print('/');
    Serial.print(GPS.month, DEC); 
    Serial.print("/20");
    Serial.println(GPS.year, DEC);
#endif
    setCursorTFT(1,0);
    tft.print(GPS.hour, DEC);
    tft.print(":");
    if (GPS.seconds<10)
      tft.print("0");
    tft.print(GPS.minute, DEC);
    tft.print(":");
    if (GPS.seconds<10)
      tft.print("0");
    tft.print(GPS.seconds, DEC); 
    tft.print(" ");
    tft.print(GPS.month, DEC);
    tft.print("/");
    tft.print(GPS.day, DEC);
    tft.print("/20");
    tft.print(GPS.year, DEC);
    tft.print("   ");

#ifdef SERIAL_OUT
    Serial.print("Fix: "); 
    Serial.print(GPS.fix);
    Serial.print(" quality: "); 
    Serial.println(GPS.fixquality); 
#endif
    if (GPS.fix) 
    {
#ifdef SERIAL_OUT
      Serial.print("Location: ");
      Serial.print(GPS.latitude, 4); 
      Serial.print(GPS.lat);
      Serial.print(", "); 
      Serial.print(GPS.longitude, 4); 
      Serial.println(GPS.lon);
#endif
      setCursorTFT(2,0);
      tft.print("Lat ");
      tft.print(GPS.latitude, 4);
      tft.print(GPS.lat);
      setCursorTFT(3,0);
      tft.print("Lon ");
      tft.print(GPS.longitude, 4);
      tft.print(GPS.lon);
#ifdef SERIAL_OUT
      Serial.print("Speed (knots): "); 
      Serial.println(GPS.speed);
      Serial.print("Angle: "); 
      Serial.println(GPS.angle);
      Serial.print("Altitude: "); 
      Serial.println(GPS.altitude);
      Serial.print("Satellites: "); 
      Serial.println(GPS.satellites);
#endif
    }
    else
    {
      setCursorTFT(2,0);
      tft.print("Acquiring a fix     ");      
      clearLine(3);
    }
  }
}

//////////////////////////////////////////////////////////////////////////////
// 
//////////////////////////////////////////////////////////////////////////////

void GPSClock(void)
{
      // in case you are not using the interrupt above, you'll
  // need to 'hand query' the GPS, not suggested :(
  if (! usingInterrupt) {
    // read data from the GPS in the 'main loop'
    char c = GPS.read();
    // if you want to debug, this is a good time to do it!
    if (GPSECHO)
      if (c) UDR0 = c;
    // writing direct to UDR0 is much much faster than Serial.print 
    // but only one character can be written at a time. 
  }

  // if a sentence is received, we can check the checksum, parse it...
  if (GPS.newNMEAreceived()) {
    // a tricky thing here is if we print the NMEA sentence, or data
    // we end up not listening and catching other sentences! 
    // so be very wary if using OUTPUT_ALLDATA and trytng to print out data
    //Serial.println(GPS.lastNMEA());   // this also sets the newNMEAreceived() flag to false

    if (!GPS.parse(GPS.lastNMEA()))   // this also sets the newNMEAreceived() flag to false
      return;  // we can fail to parse a sentence in which case we should just wait for another
  }

  // approximately every 1 seconds or so, print out the current stats
  if (millis() - timer >= 800) 
  { 
    timer = millis(); // reset the timer
    setCursorTFT(1,0);
    tft.print(GPS.hour, DEC);
    tft.print(":");
    tft.print(GPS.minute, DEC);
    tft.print(":");
    if (GPS.seconds<10)
      tft.print("0");
    tft.print(GPS.seconds, DEC); 
    tft.print(" ");
    tft.print(GPS.month, DEC);
    tft.print("/");
    tft.print(GPS.day, DEC);
    tft.print("/20");
    tft.print(GPS.year, DEC);
    tft.print("  ");

    if (!GPS.fix) 
    {
      setCursorTFT(2,0);
      tft.print("Acquiring a fix     ");
      clearLine(3);
    }
    else
      clearLine(2);
  }

}


void quietReadGPS(void)
{
 int intLat, intLon;
    // in case you are not using the interrupt above, you'll
  // need to 'hand query' the GPS, not suggested :(
  if (! usingInterrupt) {
    // read data from the GPS in the 'main loop'
    char c = GPS.read();
    // if you want to debug, this is a good time to do it!
    if (GPSECHO)
      if (c) UDR0 = c;
    // writing direct to UDR0 is much much faster than Serial.print 
    // but only one character can be written at a time. 
  }

  // if a sentence is received, we can check the checksum, parse it...
  if (GPS.newNMEAreceived()) {
    // a tricky thing here is if we print the NMEA sentence, or data
    // we end up not listening and catching other sentences! 
    // so be very wary if using OUTPUT_ALLDATA and trytng to print out data
    //Serial.println(GPS.lastNMEA());   // this also sets the newNMEAreceived() flag to false

    if (!GPS.parse(GPS.lastNMEA()))   // this also sets the newNMEAreceived() flag to false
      return;  // we can fail to parse a sentence in which case we should just wait for another
  }

  // approximately every 2 seconds or so, print out the current stats
  if (millis() - timer > 2000) { 
    timer = millis(); // reset the timer
  }
       fLat2 = GPS.latitude/100.0;
        intLat = (int) fLat2;
        fLat2 = fLat2 - (float) intLat;
        fLat2 *= 10.0/6.0;
        fLat2 += (float) intLat;
        fLon2 = -GPS.longitude/100.0;
        intLon = (int) fLon2;
        fLon2 = fLon2 - (float) intLon;
        fLon2 *= 10.0/6.0;
        fLon2 += (float) intLon;
}

