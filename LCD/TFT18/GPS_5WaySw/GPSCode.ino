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
  initGPSVals();
  // 9600 NMEA is the default baud rate for Adafruit MTK GPS's- some use 4800
  GPS.begin(9600);

  // uncomment this line to turn on RMC (recommended minimum) and GGA (fix data) including altitude
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  // uncomment this line to turn on only the "minimum recommended" data
  //GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCONLY);
  // For parsing data, we don't suggest using anything but either RMC only or RMC+GGA since
  // the parser doesn't care about other sentences at this time

  // Set the update rate
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);  // 1 Hz update rate
  //GPS.sendCommand(PMTK_SET_NMEA_UPDATE_5HZ);    // 5 Hz update rate
  //GPS.sendCommand(PMTK_SET_NMEA_UPDATE_10HZ);  // 10 Hz update rate
  // For the parsing code to work nicely and have time to sort thru the data, and
  // print it out we don't suggest using anything higher than 1 Hz

  // the nice thing about this code is you can have a timer0 interrupt go off
  // every 1 millisecond, and read data from the GPS for you. that makes the
  // loop code a heck of a lot easier!
  useInterrupt(true);
#ifdef DBG_TFT
  debugMsg(F("GPS initialized"));
  delay(250);
#endif
  return;
}

//////////////////////////////////////////////////////////////////////////////
// 
//////////////////////////////////////////////////////////////////////////////

void initGPSVals(void)
{
  myGPSStore.hour = 0;
  myGPSStore.minute = 0;
  myGPSStore.seconds = 0;
  myGPSStore.year = 0;
  myGPSStore.month = 0;
  myGPSStore.day = 0;
  myGPSStore.latitude = 0,0;
  myGPSStore.longitude = 0,0;
  myGPSStore.altitude = 0,0;
  myGPSStore.speed = 0,0;
  myGPSStore.angle = 0,0;
  myGPSStore.fix = 0;
}

//////////////////////////////////////////////////////////////////////////////
// 
//////////////////////////////////////////////////////////////////////////////

void storeGPSVals(void)
{
  myGPSStore.hour = GPS.hour;
  myGPSStore.minute = GPS.minute;
  myGPSStore.seconds = GPS.seconds;
  myGPSStore.year = GPS.year;
  myGPSStore.month = GPS.month;
  myGPSStore.day = GPS.day;
  myGPSStore.latitude = GPS.latitude;
  myGPSStore.longitude = GPS.longitude;
  myGPSStore.altitude = GPS.altitude;
  myGPSStore.speed = GPS.speed;
  myGPSStore.angle = GPS.angle;
  myGPSStore.fix = GPS.fix;
}

//////////////////////////////////////////////////////////////////////////////
// 
//////////////////////////////////////////////////////////////////////////////

void readGPS(void)
{
  int keyState;
  myGPSStore.hour = 0;
  myGPSStore.minute = 0;
  myGPSStore.seconds = 0;
  myGPSStore.year = 0;
  myGPSStore.month = 0;
  myGPSStore.day = 0;
  myGPSStore.latitude = 0.0;
  myGPSStore.longitude = 0.0;
  myGPSStore.geoidheight = 0;
  myGPSStore.altitude = 0.0;
  myGPSStore.satellites = 0;
  myGPSStore.speed = 0.0;
  myGPSStore.angle = 0.0;
  
  do
  {
#ifdef DBG_TFT
    if (GPS.fix)
      debugMsg(F("fix = 1"));
    else
      debugMsg(F("fix = 0"));
#endif
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
    if (GPS.newNMEAreceived()) 
    {
      GPS.parse(GPS.lastNMEA());
    }

    // approximately every second or so, print out the current stats
    // HH:MM:SS_MM/DD/YYYY
    // 0123456789012345678
    if ((GPS.fix) && (millis() - timer > 900))
    {
      timer = millis(); // reset the timer
      setCursorTFT(2,0);
      if (myGPSStore.hour != GPS.hour)
      {
        if (GPS.hour<10)
          tft.print(F("0"));
        tft.print(GPS.hour, DEC);
      }
      if (myGPSStore.minute != GPS.minute)
      {
        setCursorTFT(2,2);
        tft.print(F(":"));
        if (GPS.minute<10)
          tft.print(F("0"));
        tft.print(GPS.minute, DEC);
      }
      if (myGPSStore.seconds != GPS.seconds)
      {
        setCursorTFT(2,5);
        tft.print(F(":"));
        if (GPS.seconds<10)
          tft.print(F("0"));
        tft.print(GPS.seconds, DEC); 
        tft.print(F(" "));
      }
      if (myGPSStore.month != GPS.month)
      {
        setCursorTFT(2,9);
        if (GPS.month<10)
          tft.print(F("0"));
        tft.print(GPS.month, DEC);
        tft.print(F("/"));
      }
      if (myGPSStore.day != GPS.day)
      {
        setCursorTFT(2,12);
        if (GPS.day<10)
          tft.print("0");
        tft.print(GPS.day, DEC);
      }
      if (myGPSStore.year != GPS.year)
      {
        setCursorTFT(2,14);
        tft.print(F("/20"));
        if (GPS.year<10)
          tft.print("0");
        tft.print(GPS.year, DEC);
      }

      if (myGPSStore.latitude != GPS.latitude)
      {
        setCursorTFT(3,0);
        tft.print(F("Lat "));
        tft.print(GPS.latitude, 4);
        tft.print(GPS.lat);
      }
      if (myGPSStore.longitude != GPS.longitude)
      {
        setCursorTFT(4,0);
        tft.print(F("Lon "));
        tft.print(GPS.longitude, 4);
        tft.print(GPS.lon);
      }
      if (myGPSStore.speed != GPS.speed)
      {
        setCursorTFT(5,0);
        tft.print(F("Speed (knots): "));
        tft.print(GPS.speed);
      }
      if (myGPSStore.angle != GPS.angle)
      {
        setCursorTFT(6,0);
        tft.print(F("Angle: ")); 
        tft.println(GPS.angle);
      }
      if (myGPSStore.altitude != GPS.altitude)
      {
        setCursorTFT(7,0);
        tft.print(F("Altitude: "));
        tft.print(GPS.altitude);
      }
      if (myGPSStore.satellites != GPS.satellites)
      {
        setCursorTFT(8,0);
        tft.print(F("Satellites: "));
        tft.print(GPS.satellites);
      }
      storeGPSVals();

    }
    else if (!GPS.fix)
    {
      clearLine(1);
      tft.print(F("Acquiring a fix"));      
      clearLine(2);
      tft.print(F("Satellites: "));
      tft.print(GPS.satellites);
      clearLine(3);
      clearLine(4);
      clearLine(5);
      clearLine(6);
      clearLine(7);
      clearLine(8);
    }
    keyState = mySwitch.checkKeypad();
  }
  while(keyState == NOKEY);
}

//////////////////////////////////////////////////////////////////////////////
// 
//////////////////////////////////////////////////////////////////////////////

void GPSClock(void)
{
  int keyState;
  tft.fillRect(0,10,128,70,ST7735_BLACK);
  while (mySwitch.checkKeypad() != NOKEY);
  do
  {
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
      //#ifdef DBG_TFT
      //  debugMsg("no nmea received");
      //#endif
      // a tricky thing here is if we print the NMEA sentence, or data
      // we end up not listening and catching other sentences! 
      // so be very wary if using OUTPUT_ALLDATA and trytng to print out data
      //Serial.println(GPS.lastNMEA());   // this also sets the newNMEAreceived() flag to false

      if (!GPS.parse(GPS.lastNMEA()))   // this also sets the newNMEAreceived() flag to false
        return;  // we can fail to parse a sentence in which case we should just wait for another
    }
    //#ifdef DBG_TFT
    //else
    //  debugMsg("nmea was received");
    //#endif

    if (!GPS.fix) 
    {
      clearLine(1);
      tft.print(F("Acquiring a fix"));
      mySwitch.delayPressed(10);
    }
    else
    {
      clearLine(1);
      clearLine(2);
      // approximately every 2 seconds or so, print out the current stats
      if (millis() - timer >= 800) 
      { 
        timer = millis(); // reset the timer
        tft.setTextSize(2);
        setCursorTFT(3,0);
        if (GPS.hour<10)
          tft.print("0");
        tft.print(GPS.hour, DEC);
        tft.print(":");
        if (GPS.minute<10)
          tft.print("0");
        tft.print(GPS.minute, DEC);
        tft.print(":");
        if (GPS.seconds<10)
          tft.print("0");
        tft.print(GPS.seconds, DEC); 
        setCursorTFT(6,0);
        if (GPS.month<10)
          tft.print("0");
        tft.print(GPS.month, DEC);
        tft.print("/");
        if (GPS.day<10)
          tft.print("0");
        tft.print(GPS.day, DEC);
        tft.print("/20");
        tft.print(GPS.year, DEC);
        tft.print("  ");
        tft.setTextSize(1);
      }
    }
    keyState = mySwitch.checkKeypad();
  }
  while(keyState == NOKEY);
  while(keyState != NOKEY)
    {
      keyState = mySwitch.checkKeypad();
    delay(5);
    }
}

//////////////////////////////////////////////////////////////////////////////
// 
//////////////////////////////////////////////////////////////////////////////

int quietReadGPS(void)
{
  int intLat, intLon;
  if (! usingInterrupt) {
    char c = GPS.read();
    if (GPSECHO)
      if (c) UDR0 = c;
  }

  if (GPS.newNMEAreceived()) 
  {
    if (!GPS.parse(GPS.lastNMEA()))   // this also sets the newNMEAreceived() flag to false
      return -1;  // we can fail to parse a sentence in which case we should just wait for another
  }
  else
    return -2;

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
  return 0;
}

//////////////////////////////////////////////////////////////////////////////////////
// bearing and distance calculations from gerard's coobro geo code base
//////////////////////////////////////////////////////////////////////////////////////

int calc_bearing(float flat1, float flon1, float flat2, float flon2)
{
  float calc;
  float bear_calc; 

  float x = 69.1 * (flat2 - flat1);
  float y = 69.1 * (flon2 - flon1) * cos(flat1/57.3);

  calc=atan2(y,x);
  bear_calc= degrees(calc);

  if(bear_calc<=1)
  {
    bear_calc=360+bear_calc;
  }
  return bear_calc;
} 

//////////////////////////////////////////////////////////////////////////////////////
// unsigned long calc_dist(float flat1, float flon1, float flat2, float flon2)
//////////////////////////////////////////////////////////////////////////////////////

unsigned long calc_dist(float flat1, float flon1, float flat2, float flon2)
{
  float dist_calc=0;
  float dist_calc2=0;
  float diflat=0;
  float diflon=0;

  diflat=radians(flat2-flat1);
  flat1=radians(flat1);
  flat2=radians(flat2);
  diflon=radians((flon2)-(flon1));

  dist_calc = (sin(diflat/2.0)*sin(diflat/2.0));
  dist_calc2= cos(flat1);
  dist_calc2*=cos(flat2);
  dist_calc2*=sin(diflon/2.0);
  dist_calc2*=sin(diflon/2.0);
  dist_calc +=dist_calc2;

  dist_calc=(2*atan2(sqrt(dist_calc),sqrt(1.0-dist_calc)));

  dist_calc*=6371000.0; //Converting to meters
  return dist_calc;
}

