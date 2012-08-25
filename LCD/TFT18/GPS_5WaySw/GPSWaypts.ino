
void goWays(void)
{
  int keyState;
  float distCalc; 
  tft.fillRect(0,10,128,70,ST7735_BLACK);
  tft.drawCircle(64,110,45,ST7735_WHITE);
  setCursorTFT(1,0);
  tft.print(F("Going to waypoint"));
  delay(1000);
  setCursorTFT(1,18);
  tft.print(currentWayPoint, DEC);
  setCursorTFT(2,0);
  tft.print(F("Bearing ="));
  setCursorTFT(3,0);
  tft.print(F("Distance ="));
  setCursorTFT(4,0);
  tft.print(F("Direction ="));
  setCursorTFT(5,0);
  tft.print(F("Satellites ="));
  quietReadGPS();
  setCursorTFT(2,10);
  tft.print("         ");
  setCursorTFT(2,10);
  bearing = calc_bearing(fLat2,fLon2,myStoreVals.lats[currentWayPoint],myStoreVals.lons[currentWayPoint]);
  tft.print(bearing);
  lastLat = fLat2;
  setCursorTFT(3,11);
  tft.print("        ");
  setCursorTFT(3,11);
  tft.print(calc_dist(fLat2,fLon2,myStoreVals.lats[currentWayPoint],myStoreVals.lons[currentWayPoint]));
  lastLon = fLon2;
  setCursorTFT(4,12);
  tft.print(GPS.angle-bearing);
  lastAngle = GPS.angle;
  lastBearing = bearing;
  setCursorTFT(5,13);
  tft.print(GPS.satellites);
  lastSats = GPS.satellites;
  do
  {
    quietReadGPS();
    distCalc = calc_dist(fLat2,fLon2,myStoreVals.lats[currentWayPoint],myStoreVals.lons[currentWayPoint]);
    bearing = calc_bearing(fLat2,fLon2,myStoreVals.lats[currentWayPoint],myStoreVals.lons[currentWayPoint]);
    if ((fLat2 != lastLat) || (fLon2 != lastLon))
    {
      setCursorTFT(2,10);
      tft.print("           ");
      setCursorTFT(2,10);
      tft.print(bearing);
      setCursorTFT(3,11);
      tft.print("          ");
      setCursorTFT(3,11);
      tft.print(distCalc);
      lastLat = fLat2;
      lastLon = fLon2;
    }
    if ((GPS.angle != lastAngle) || (bearing != lastBearing))
    {
      setCursorTFT(4,12);
      tft.print("         ");
      setCursorTFT(4,12);
      tft.print(GPS.angle-bearing);
      drawVector(GPS.angle-bearing);
      lastAngle = GPS.angle;
      lastBearing = bearing;
    }
    if (lastSats != GPS.satellites)
    {
      setCursorTFT(5,13);
      tft.print(GPS.satellites);
      tft.print("  ");
    }

    keyState = mySwitch.checkKeypad();
  }
  while(keyState == NOKEY);
  tft.fillRect(0,10,128,150,ST7735_BLACK);
  while (mySwitch.checkKeypad() != NOKEY);
}
//////////////////////////////////////////////////////////////////////////////
// parseRxBuffer - save waypoints - rxBuffer[]
// Order is ww=aa.aaaa,ooo.ooo
// ww is the way point number
// aa.aaaa is the latitude
// 000.000 is the longitude
//////////////////////////////////////////////////////////////////////////////

int parseRxBuffer(void)
{
  int lineOffset;
  int floatStringOffset;
  char floatBuff[10];
  int wayPointNum;
  float latF, longF;
  if (rxBuffer[1] == '=')  //waypoints from 0-9
  {
    wayPointNum = rxBuffer[0] - '0';
    lineOffset = 2;
  }
  else if (rxBuffer[2] == '=')  // waypoints from 10-19
  {
    wayPointNum = ((rxBuffer[0] - '0') * 10);
    wayPointNum += (rxBuffer[1] - '0');
    lineOffset = 3;
  }
  else
    return(-1);
  floatStringOffset = 0;
  while (rxBuffer[lineOffset] != ',')
  {
    floatBuff[floatStringOffset++] = rxBuffer[lineOffset++];
  }
  floatBuff[floatStringOffset] = 0;
  latF=atof(floatBuff);
  lineOffset++;
  floatStringOffset = 0;
  while (rxBuffer[lineOffset] != 0)
  {
    floatBuff[floatStringOffset++] = rxBuffer[lineOffset++];
  }
  floatBuff[floatStringOffset] = 0;
  longF=atof(floatBuff);
  if ((wayPointNum >= 0) && (wayPointNum <= 19)) 
    setFArray(wayPointNum,latF,longF);
  else
    return(-2);
  return(0);
}

//////////////////////////////////////////////////////////////////////////////
// Set the lat long values in the buffer to the Geocache values
//////////////////////////////////////////////////////////////////////////////

void setFArray(int wayPointNum, float latF, float longF)
{
  myStoreVals.lats[wayPointNum] = latF;
  myStoreVals.lons[wayPointNum] = longF;
}

//////////////////////////////////////////////////////////////////////////////
// 
//////////////////////////////////////////////////////////////////////////////

void dlWays(void)
{
  int rxCount = 0;
  int charIn;
  int errorCode;
  while (Serial.available())   
    // flush the serial read port
    charIn = Serial.read();
  Serial.println("<DL>");    // signals host that it's time to load waypoints
  if (Serial.available())
  {
    charIn = Serial.read();
    if (charIn == '\n')
    {
      tft.print(".");
      rxBuffer[rxCount] = 0;
      errorCode = parseRxBuffer();
      if (errorCode == -1)
      {
        clearLine(2);
        tft.print("Error: Missing equal");
      }
      else if (errorCode == -2)
      {
        clearLine(2);
        tft.print("Error: Bad waypt num");
      } 
      rxCount = 0;
      Serial.write('A');
      if ((rxBuffer[0] == '1') && (rxBuffer[1]=='9'))
      {
        clearLine(3);
        tft.print("Download Completed  ");
        EEPROM_writeAnything(0, myStoreVals);
        Serial.println("</SERIN>");    // signals host that it's time to load waypoints
        delay(2000);  // 2 second message
      }
    }
    else
    {
      rxBuffer[rxCount++] = charIn;
    }
  }
  Serial.println("</DL>");    // signals host that it's time to load waypoints
  clearLine(2);
  tft.print("Download Terminated ");
  delay(2000);  // 2 second message
}

//////////////////////////////////////////////////////////////////////////////
// setWay() - Set the waypoints
//////////////////////////////////////////////////////////////////////////////

void setWay(void)
{
  tft.fillRect(0,10,128,70,ST7735_BLACK);
  setCursorTFT(1,0);
  tft.setTextColor(ST7735_WHITE,ST7735_BLUE);
  tft.print("Set active Waypoint");
  tft.setTextColor(ST7735_WHITE,ST7735_BLACK);
  setCursorTFT(2,0);
  tft.print(F("Up/Down to change"));
  setCursorTFT(3,0);
  tft.print(F("Select to save"));
  setCursorTFT(5,0);
  tft.print(F("Waypoint = "));
  setCursorTFT(5,11);
  tft.print(currentWayPoint, DEC);
  int keyState;
  do
  {
    int keyState = mySwitch.checkKeypad();
    switch(keyState)
    {
    case SELECT:
      myStoreVals.myCurrentWayPoint = currentWayPoint;
      EEPROM_writeAnything(0, myStoreVals);
      return;
    case UP:
      if (currentWayPoint < 19)
        currentWayPoint++;
      else
        currentWayPoint = 0;
      delay(250);
      setCursorTFT(5,11);
      tft.print("  ");
      setCursorTFT(5,11);
      tft.print(currentWayPoint, DEC);
      break;
    case DOWN:
      if (currentWayPoint > 0)
        currentWayPoint--;
      else
        currentWayPoint = 19;
      setCursorTFT(5,11);
      tft.print("  ");
      setCursorTFT(5,11);
      tft.print(currentWayPoint, DEC);
      delay(250);
      break;
    }
  }
  while(1);
  delay(2000);
}

//////////////////////////////////////////////////////////////////////////////
// 
//////////////////////////////////////////////////////////////////////////////

void shWays(void)
{
  tft.fillRect(0,10,128,70,ST7735_BLACK);
  tft.fillScreen(ST7735_BLACK);
  setCursorTFT(0,0);
  tft.setTextColor(ST7735_WHITE,ST7735_BLUE);
  tft.print(F("Showing waypoints"));
  tft.setTextColor(ST7735_WHITE,ST7735_BLACK);
  for (int row = 0; row < 15; row++)
  {
    setCursorTFT(row+1,0);
    tft.print(row);
    tft.print(",");
    tft.print(myStoreVals.lats[row],4);
    tft.print(",");
    tft.print(myStoreVals.lons[row],4);
  }
  while(mySwitch.checkKeypad() == NOKEY)
    delay(50);
  while(mySwitch.checkKeypad() != NOKEY)
    delay(50);

  tft.fillRect(0,10,128,150,ST7735_BLACK);
}


