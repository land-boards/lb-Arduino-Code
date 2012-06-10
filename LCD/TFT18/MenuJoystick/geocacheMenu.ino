////////////////////////////////////////////////////////////
// geocacheMenu() - 
////////////////////////////////////////////////////////////

const char * menuHeader = "** Doug's GPS v003 **";
const char * monGPSLocn = "Monitor GPS Loc'n";
const char * monGPSClk  = "Monitor Clock";
const char * downldWays = "Download Waypoints";
const char * goToWaypts = "Go to Waypoint";
const char * setActWays = "Set Active Waypnt";
const char * showWaypts = "Show Waypoints";

void geocacheMenu(void)
{
  int pressedKey = checkKeypad();
  switch (menuState)
  {
  case MENU0:
    tft.fillScreen(ST7735_BLACK);
    setCursorTFT(0,0);
    tft.print(menuHeader);
    setCursorTFT(1,0);
    tft.setTextColor(ST7735_WHITE,ST7735_BLUE);
    tft.print(monGPSLocn);
    setCursorTFT(2,0);
    tft.setTextColor(ST7735_WHITE,ST7735_BLACK);
    tft.print(monGPSClk);
    setCursorTFT(3,0);
    tft.print(downldWays);
    setCursorTFT(4,0);
    tft.print(goToWaypts);
    setCursorTFT(5,0);
    tft.print(setActWays);
    setCursorTFT(6,0);
    tft.print(showWaypts);
    menuState = MENU0B;
    break;
  case MENU0B:
    if (pressedKey != NOKEY)
    {
      if ((pressedKey == SELECT) || (pressedKey == RIGHT))
      {
        clearLine(2);
        clearLine(3);
        clearLine(4);
        clearLine(5);
        clearLine(6);
        menuState = MENU0C;
      }
      else if (pressedKey == DOWN)
        menuState = MENU1;
    }
    break;
  case MENU0C:
    if (pressedKey != NOKEY)
      menuState = MENU0;
    readGPS();
    break;
  case MENU1:
    tft.fillScreen(ST7735_BLACK);
    setCursorTFT(0,0);
    tft.print(menuHeader);
    setCursorTFT(1,0);
    tft.print(monGPSLocn);
    setCursorTFT(2,0);
    tft.setTextColor(ST7735_WHITE,ST7735_BLUE);
    tft.print(monGPSClk);
    tft.setTextColor(ST7735_WHITE,ST7735_BLACK);
    setCursorTFT(3,0);
    tft.print(downldWays);
    setCursorTFT(4,0);
    tft.print(goToWaypts);
    setCursorTFT(5,0);
    tft.print(setActWays);
    setCursorTFT(6,0);
    tft.print(showWaypts);
    menuState = MENU1B;
    break;
  case MENU1B:
    if (pressedKey != NOKEY)
    {
      if ((pressedKey == SELECT) || (pressedKey == RIGHT))
      {
        clearLine(1);
        clearLine(2);
        clearLine(3);
        clearLine(4);
        clearLine(5);
        clearLine(6);
        menuState = MENU1C;
      }
      else if (pressedKey == UP)
        menuState = MENU0;
      else if (pressedKey == DOWN)
        menuState = MENU2;
    }
    break;
  case MENU1C:
    if (pressedKey != NOKEY)
    {
      tft.fillScreen(ST7735_BLACK);
      menuState = MENU1;
    }
    GPSClock();
    break;
  case MENU2:
    tft.fillScreen(ST7735_BLACK);
    setCursorTFT(0,0);
    tft.print(menuHeader);
    setCursorTFT(1,0);
    tft.print(monGPSLocn);
    setCursorTFT(2,0);
    tft.print(monGPSClk);
    setCursorTFT(3,0);
    tft.setTextColor(ST7735_WHITE,ST7735_BLUE);
    tft.print(downldWays);
    tft.setTextColor(ST7735_WHITE,ST7735_BLACK);
    setCursorTFT(4,0);
    tft.print(goToWaypts);
    setCursorTFT(5,0);
    tft.print(setActWays);
    setCursorTFT(6,0);
    tft.print(showWaypts);
    menuState = MENU2B;
    break;
  case MENU2B:
    {
      int charIn;
      if (pressedKey != NOKEY)
      {
      if ((pressedKey == SELECT) || (pressedKey == RIGHT))
        {
          rxCount = 0;
          clearLine(2);
          clearLine(3);
          clearLine(4);
          clearLine(5);
          clearLine(6);
          clearLine(1);
          tft.print("Downloading WAYPNTS ");
          setCursorTFT(2,0);
          menuState = MENU2C;
          while (Serial.available())    // flush the serial read port
            charIn = Serial.read();
          Serial.println("<DL>");    // signals host that it's time to load waypoints
        }
        else if (pressedKey == UP)
          menuState = MENU1;
        else if (pressedKey == DOWN)
          menuState = MENU3;
      }
    }
    break;
  case MENU2C:
    {
      int charIn;
      int errorCode;
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
            menuState = MENU2;
          }
        }
        else
        {
          rxBuffer[rxCount++] = charIn;
        }
      }
      if (pressedKey == UP)
      {
        Serial.println("</DL>");    // signals host that it's time to load waypoints
        clearLine(2);
        tft.print("Download Terminated ");
        delay(2000);  // 2 second message
        menuState = MENU2;
      }
    }
    break;
  case MENU3:
    tft.fillScreen(ST7735_BLACK);
    setCursorTFT(0,0);
    tft.print(menuHeader);
    setCursorTFT(1,0);
    tft.print(monGPSLocn);
    setCursorTFT(2,0);
    tft.print(monGPSClk);
    setCursorTFT(3,0);
    tft.print(downldWays);
    setCursorTFT(4,0);
    tft.setTextColor(ST7735_WHITE,ST7735_BLUE);
    tft.print(goToWaypts);
    tft.setTextColor(ST7735_WHITE,ST7735_BLACK);
    setCursorTFT(5,0);
    tft.print(setActWays);
    setCursorTFT(6,0);
    tft.print(showWaypts);
    menuState = MENU3B;
    break;
  case MENU3B:
    if (pressedKey != NOKEY)
    {
      if ((pressedKey == SELECT) || (pressedKey == RIGHT))
      {
        quietReadGPS();
        delay(500);
        menuState = MENU3C;
      }
      else if (pressedKey == UP)
        menuState = MENU2;
      else if (pressedKey == DOWN)
        menuState = MENU4;
    }
    break;
  case MENU3C:
    tft.fillScreen(ST7735_BLACK);
    setCursorTFT(0,0);
    tft.print(menuHeader);
    setCursorTFT(1,0);
    tft.print("Going to Waypoint   ");
    setCursorTFT(1,18);
    tft.print(currentWayPoint, DEC);
    setCursorTFT(2,0);
    tft.print("Bearing =");
    setCursorTFT(3,0);
    tft.print("Distance =");
    setCursorTFT(4,0);
    tft.print("Direction =");
    setCursorTFT(5,0);
    tft.print("Satellites =");
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
    menuState = MENU3D;
    break;
  case MENU3D:
    {
      if (pressedKey != NOKEY)
      {
        menuState = MENU3;
        break;
      }
      if (quietReadGPS() != 0)
      {
        break;
      }
      float distCalc = calc_dist(fLat2,fLon2,myStoreVals.lats[currentWayPoint],myStoreVals.lons[currentWayPoint]);
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
        lastAngle = GPS.angle;
        lastBearing = bearing;
      }
      if (lastSats != GPS.satellites)
      {
        setCursorTFT(5,13);
        tft.print(GPS.satellites);
        tft.print("  ");
      }
    }
    break;
  case MENU4:
    tft.fillScreen(ST7735_BLACK);
    setCursorTFT(0,0);
    tft.print(menuHeader);
    setCursorTFT(1,0);
    tft.print(monGPSLocn);
    setCursorTFT(2,0);
    tft.print(monGPSClk);
    setCursorTFT(3,0);
    tft.print(downldWays);
    setCursorTFT(4,0);
    tft.print(goToWaypts);
    setCursorTFT(5,0);
    tft.setTextColor(ST7735_WHITE,ST7735_BLUE);
    tft.print(setActWays);
    tft.setTextColor(ST7735_WHITE,ST7735_BLACK);
    setCursorTFT(6,0);
    tft.print(showWaypts);
    menuState = MENU4B;
    break;
  case MENU4B:
    if (pressedKey != NOKEY)
    {
      if ((pressedKey == SELECT) || (pressedKey == RIGHT))
      {
        tft.fillScreen(ST7735_BLACK);
        setCursorTFT(0,0);
        tft.print("Select WayPoint     ");
        setCursorTFT(2,0);
        tft.print(currentWayPoint, DEC);
        menuState = MENU4C;
      }
      else if (pressedKey == UP)
      {
        menuState = MENU3;
      }
      else if (pressedKey == DOWN)
      {
        menuState = MENU5;
      }
    }
    break;
  case MENU4C:
    {
      if (pressedKey != NOKEY)
      {
        switch(pressedKey)
        {
        case SELECT:
          myStoreVals.myCurrentWayPoint = currentWayPoint;
          EEPROM_writeAnything(0, myStoreVals);
          menuState = MENU4;
          break;
        case UP:
          if (currentWayPoint < 9)
            currentWayPoint++;
          break;
        case DOWN:
          if (currentWayPoint > 0)
            currentWayPoint--;
          break;
        }
        clearLine(2);
        tft.print(currentWayPoint, DEC);
      }
    }
    break;
  case MENU5:
    tft.fillScreen(ST7735_BLACK);
    setCursorTFT(0,0);
    tft.print(menuHeader);
    setCursorTFT(1,0);
    tft.print(monGPSLocn);
    setCursorTFT(2,0);
    tft.print(monGPSClk);
    setCursorTFT(3,0);
    tft.print(downldWays);
    setCursorTFT(4,0);
    tft.print(goToWaypts);
    setCursorTFT(5,0);
    tft.print(setActWays);
    setCursorTFT(6,0);
    tft.setTextColor(ST7735_WHITE,ST7735_BLUE);
    tft.print(showWaypts);
    tft.setTextColor(ST7735_WHITE,ST7735_BLACK);
    menuState = MENU5B;
    break;
  case MENU5B:
    if (pressedKey != NOKEY)
    {
      if ((pressedKey == SELECT) || (pressedKey == RIGHT))
      {
        tft.fillScreen(ST7735_BLACK);
        setCursorTFT(0,0);
        tft.print("WayPoints           ");
        for (int row = 1; row < 16; row++)
        {
          setCursorTFT(row,0);
          tft.print(row);
          tft.print(",");
          tft.print(myStoreVals.lats[row-1],4);
          tft.print(",");
          tft.print(myStoreVals.lons[row-1],4);
        }
        menuState = MENU5C;
      }
      else if (pressedKey == UP)
      {
        menuState = MENU4;
      }
    }
    break;
  case MENU5C:
    {
      if (pressedKey != NOKEY)
      {
        switch(pressedKey)
        {
        case SELECT:
        case UP:
          tft.fillScreen(ST7735_BLACK);
          menuState = MENU5;
          break;
        }
      }
      break;
    }
  }
}


