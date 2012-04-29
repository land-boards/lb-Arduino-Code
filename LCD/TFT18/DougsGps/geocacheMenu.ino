void geocacheMenu(void)
{
  int pressedKey = checkIR();
  switch (menuState)
  {
  case MENU0:
    setCursorTFT(0,0);
    tft.print("** Doug's GPS v002 **");
    setCursorTFT(1,0);
    tft.print("> Monitor GPS Loc'n ");
    setCursorTFT(2,0);
    tft.print("Monitor Clock       ");
    setCursorTFT(3,0);
    tft.print("Download  Waypoints ");
    setCursorTFT(4,0);
    tft.print("Go to Waypoint      ");
    setCursorTFT(5,0);
    tft.print("Set Active Waypnt   ");
    setCursorTFT(6,0);
    tft.print("Show Waypoints      ");
    menuState = MENU0B;
    break;
  case MENU0B:
    if (pressedKey != NOKEY)
    {
      if (pressedKey == PAUSE)
      {
        clearLine(2);
        clearLine(3);
        clearLine(4);
        clearLine(5);
        clearLine(6);
        menuState = MENU0C;
      }
      else if (pressedKey == RIGHT)
        menuState = MENU1;
    }
    break;
  case MENU0C:
    if (pressedKey != NOKEY)
      menuState = MENU0;
    readGPS();
    break;
  case MENU1:
    setCursorTFT(0,0);
    tft.print("** Doug's GPS v01 **");
    setCursorTFT(1,0);
    tft.print("Monitor GPS Loc'n   ");
    setCursorTFT(2,0);
    tft.print("> Monitor Clock     ");
    setCursorTFT(3,0);
    tft.print("Download  Waypoints ");
    setCursorTFT(4,0);
    tft.print("Go to Waypoint      ");
    setCursorTFT(5,0);
    tft.print("Set Active Waypnt   ");
    setCursorTFT(6,0);
    tft.print("Show Waypoints      ");
    menuState = MENU1B;
    break;
  case MENU1B:
    if (pressedKey != NOKEY)
    {
      if (pressedKey == PAUSE)
      {
        clearLine(2);
        clearLine(3);
        clearLine(4);
        clearLine(5);
        clearLine(6);
        menuState = MENU1C;
      }
      else if (pressedKey == LEFT)
        menuState = MENU0;
      else if (pressedKey == RIGHT)
        menuState = MENU2;
    }
    break;
  case MENU1C:
    if (pressedKey != NOKEY)
      menuState = MENU1;
    GPSClock();
    break;
  case MENU2:
    setCursorTFT(0,0);
    tft.print("** Doug's GPS v01 **");
    setCursorTFT(1,0);
    tft.print("Monitor GPS Loc'n   ");
    setCursorTFT(2,0);
    tft.print("Monitor Clock       ");
    setCursorTFT(3,0);
    tft.print("> Download  Waypnts ");
    setCursorTFT(4,0);
    tft.print("Go to Waypoint      ");
    setCursorTFT(5,0);
    tft.print("Set Active Waypnt   ");
    setCursorTFT(6,0);
    tft.print("Show Waypoints      ");
    menuState = MENU2B;
    break;
  case MENU2B:
    {
      int charIn;
      if (pressedKey != NOKEY)
      {
        if (pressedKey == PAUSE)
        {
          rxCount = 0;
          clearLine(2);
          clearLine(3);
          clearLine(4);
          clearLine(5);
          clearLine(6);
          setCursorTFT(1,0);
          tft.print("Downloading WAYPNTS ");
          setCursorTFT(2,0);
          menuState = MENU2C;
          while (Serial.available())    // flush the serial read port
            charIn = Serial.read();
          Serial.println("<DL>");    // signals host that it's time to load waypoints
        }
        else if (pressedKey == LEFT)
          menuState = MENU1;
        else if (pressedKey == RIGHT)
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
            setCursorTFT(2,0);
            tft.print("Error: Missing equal");
          }
          else if (errorCode == -2)
          {
            setCursorTFT(2,0);
            tft.print("Error: Bad waypt num");
          } 
          rxCount = 0;
          Serial.write('A');
          if ((rxBuffer[0] == '1') && (rxBuffer[1]=='9'))
          {
            setCursorTFT(3,0);
            tft.print("Download Completed  ");
            dumpFArray();
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
      if (pressedKey == LEFT)
      {
        Serial.println("</DL>");    // signals host that it's time to load waypoints
        setCursorTFT(2,0);
        tft.print("Download Terminated ");
        delay(2000);  // 2 second message
        menuState = MENU2;
      }
    }
    break;
  case MENU3:
    setCursorTFT(0,0);
    tft.print("** Doug's GPS v01 **");
    setCursorTFT(1,0);
    tft.print("Monitor GPS Loc'n   ");
    setCursorTFT(2,0);
    tft.print("Monitor Clock       ");
    setCursorTFT(3,0);
    tft.print("Download  Waypoints ");
    setCursorTFT(4,0);
    tft.print("> Go to Waypoint    ");
    setCursorTFT(5,0);
    tft.print("Set Active Waypnt   ");
    setCursorTFT(6,0);
    tft.print("Show Waypoints      ");
    menuState = MENU3B;
    break;
  case MENU3B:
    if (pressedKey != NOKEY)
    {
      if (pressedKey == PAUSE)
      {
        quietReadGPS();
        delay(500);
        menuState = MENU3C;
      }
      else if (pressedKey == LEFT)
        menuState = MENU2;
      else if (pressedKey == RIGHT)
        menuState = MENU4;
    }
    break;
  case MENU3C:
    setCursorTFT(1,0);
    tft.print("Going to Waypoint   ");
    setCursorTFT(1,18);
    tft.print(currentWayPoint, DEC);
    clearLine(2);
    tft.print("Bearing =           ");
    clearLine(3);
    tft.print("Distance =          ");
    clearLine(4);
    clearLine(5);
    menuState = MENU3D;
    delay(500);
    break;
  case MENU3D:
    quietReadGPS();
    setCursorTFT(0,0);
    tft.print("** Doug's GPS v01 **");
    setCursorTFT(2,11);
    tft.print("         ");
    setCursorTFT(2,11);
    tft.print(calc_bearing(myStoreVals.lats[currentWayPoint],myStoreVals.lons[currentWayPoint],fLat2,fLon2));
    setCursorTFT(3,12);
    tft.print("        ");
    setCursorTFT(3,12);
    tft.print(calc_dist(myStoreVals.lats[currentWayPoint],myStoreVals.lons[currentWayPoint],fLat2,fLon2));
    if (pressedKey != NOKEY)
      menuState = MENU3;
    break;
  case MENU4:
    setCursorTFT(0,0);
    tft.print("** Doug's GPS v01 **");
    setCursorTFT(1,0);
    tft.print("Monitor GPS Loc'n   ");
    setCursorTFT(2,0);
    tft.print("Monitor Clock       ");
    setCursorTFT(3,0);
    tft.print("Download  Waypoints ");
    setCursorTFT(4,0);
    tft.print("Go to Waypoint      ");
    setCursorTFT(5,0);
    tft.print("> Set Active Waypnt ");
    setCursorTFT(6,0);
    tft.print("Show Waypoints      ");
    menuState = MENU4B;
    break;
  case MENU4B:
    if (pressedKey != NOKEY)
    {
      if (pressedKey == PAUSE)
      {
        setCursorTFT(1,0);
        tft.print("Select WayPoint     ");
        clearLine(2);
        clearLine(3);
        clearLine(4);
        clearLine(5);
        clearLine(6);
        setCursorTFT(2,0);
        tft.print(currentWayPoint, DEC);
        menuState = MENU4C;
      }
      else if (pressedKey == LEFT)
      {
        menuState = MENU3;
      }
      else if (pressedKey == RIGHT)
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
        case PAUSE:
          menuState = MENU4;
          myStoreVals.myCurrentWayPoint = currentWayPoint;
          EEPROM_writeAnything(0, myStoreVals);
          break;
        case PLUS:
          if (currentWayPoint < 9)
            currentWayPoint++;
          break;
        case MINUS:
          if (currentWayPoint > 0)
            currentWayPoint--;
          break;
        case ZEROKEY:
          currentWayPoint = 0;
          break;
        case ONEKEY:
          currentWayPoint = 1;
          break;
        case TWOKEY:
          currentWayPoint = 2;
          break;
        case THREEKEY:
          currentWayPoint = 3;
          break;
        case FOURKEY:
          currentWayPoint = 4;
          break;
        case FIVEKEY:
          currentWayPoint = 5;
          break;
        case SIXKEY:
          currentWayPoint = 6;
          break;
        case SEVENKEY:
          currentWayPoint = 7;
          break;
        case EIGHTKEY:
          currentWayPoint = 8;
          break;
        case NINEKEY:
          currentWayPoint = 9;
          break;
        }
        clearLine(2);
        setCursorTFT(2,0);
        tft.print(currentWayPoint, DEC);
      }
    }
  case MENU5:
    setCursorTFT(0,0);
    tft.print("** Doug's GPS v01 **");
    setCursorTFT(1,0);
    tft.print("Monitor GPS Loc'n   ");
    setCursorTFT(2,0);
    tft.print("Monitor Clock       ");
    setCursorTFT(3,0);
    tft.print("Download  Waypoints ");
    setCursorTFT(4,0);
    tft.print("Go to Waypoint      ");
    setCursorTFT(5,0);
    tft.print("Set Active Waypoint ");
    setCursorTFT(6,0);
    tft.print("> Show Waypoints    ");
    menuState = MENU5B;
    break;
  case MENU5B:
    if (pressedKey != NOKEY)
    {
      if (pressedKey == PAUSE)
      {
        setCursorTFT(0,0);
        tft.print("WayPoints           ");
        for (int row = 1; row < 16; row++)
        {
          clearLine(row);
          tft.print(row);
          tft.print(",");
          tft.print(myStoreVals.lats[row-1],4);
          tft.print(",");
          tft.print(myStoreVals.lons[row-1],4);
        }
        menuState = MENU5C;
      }
      else if (pressedKey == LEFT)
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
        case PAUSE:
        case LEFT:
          for (int row = 0; row < 16; row++)
            clearLine(row);
          menuState = MENU5;
          break;
        }
      }
    }
  }
}
