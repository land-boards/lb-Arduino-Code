void geocacheMenu(void)
{
  int pressedKey = checkIR();
  switch (menuState)
  {
  case MENU0:
    lcd.setCursor(0,0);
    lcd.print("** Doug's GPS v01 **");
    lcd.setCursor(1,0);
    lcd.print("> Monitor GPS Loc'n ");
    lcd.setCursor(2,0);
    lcd.print("Monitor Clock       ");
    lcd.setCursor(3,0);
    lcd.print("Download  Waypoints ");
    menuState = MENU0B;
    break;
  case MENU0B:
    if (pressedKey != NOKEY)
    {
      if (pressedKey == PAUSE)
      {
        clearLine(2);
        clearLine(3);
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
    lcd.setCursor(1,0);
    lcd.print("> Monitor Clock     ");
    lcd.setCursor(2,0);
    lcd.print("Download  Waypoints ");
    lcd.setCursor(3,0);
    lcd.print("Go to Waypoint      ");
    menuState = MENU1B;
    break;
  case MENU1B:
    if (pressedKey != NOKEY)
    {
      if (pressedKey == PAUSE)
      {
        clearLine(2);
        clearLine(3);
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
    lcd.setCursor(1,0);
    lcd.print("Monitor Clock       ");
    lcd.setCursor(2,0);
    lcd.print("> Download Waypoints");
    lcd.setCursor(3,0);
    lcd.print("Go to Waypoint      ");
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
          lcd.setCursor(1,0);
          lcd.print("Downloading WAYPNTS ");
          lcd.setCursor(2,0);
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
          lcd.print(".");
          rxBuffer[rxCount] = 0;
          errorCode = parseRxBuffer();
          if (errorCode == -1)
          {
            lcd.setCursor(2,0);
            lcd.print("Error: Missing equal");
          }
          else if (errorCode == -2)
          {
            lcd.setCursor(2,0);
            lcd.print("Error: Bad waypt num");
          } 
          rxCount = 0;
          Serial.write('A');
          if ((rxBuffer[0] == '1') && (rxBuffer[1]=='9'))
          {
            lcd.setCursor(3,0);
            lcd.print("Download Completed  ");
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
        lcd.setCursor(2,0);
        lcd.print("Download Terminated ");
        delay(2000);  // 2 second message
        menuState = MENU2;
      }
    }
    break;
  case MENU3:
    lcd.setCursor(0,0);
    lcd.print("** Doug's GPS v01 **");
    lcd.setCursor(1,0);
    lcd.print("Monitor Clock       ");
    lcd.setCursor(2,0);
    lcd.print("Download  Waypoints ");
    lcd.setCursor(3,0);
    lcd.print("> Go to Waypoint    ");
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
    lcd.setCursor(1,0);
    lcd.print("Going to Waypoint   ");
    lcd.setCursor(1,18);
    lcd.print(currentWayPoint, DEC);
    clearLine(2);
    lcd.print("Bearing =           ");
    clearLine(3);
    lcd.print("Distance =          ");
    menuState = MENU3D;
    delay(500);
    break;
  case MENU3D:
    quietReadGPS();
    lcd.setCursor(0,0);
    lcd.print("** Doug's GPS v01 **");
    lcd.setCursor(2,11);
    lcd.print("         ");
    lcd.setCursor(2,11);
    lcd.print(calc_bearing(myStoreVals.lats[currentWayPoint],myStoreVals.lons[currentWayPoint],fLat2,fLon2));
    lcd.setCursor(3,12);
    lcd.print("        ");
    lcd.setCursor(3,12);
    lcd.print(calc_dist(myStoreVals.lats[currentWayPoint],myStoreVals.lons[currentWayPoint],fLat2,fLon2));
    if (pressedKey != NOKEY)
      menuState = MENU3;
    break;
  case MENU4:
    lcd.setCursor(1,0);
    lcd.print("Download  Waypoints ");
    lcd.setCursor(2,0);
    lcd.print("Go to Waypoint      ");
    lcd.setCursor(3,0);
    lcd.print("> Set Active Waypnt ");
    menuState = MENU4B;
    break;
  case MENU4B:
    if (pressedKey != NOKEY)
    {
      if (pressedKey == PAUSE)
      {
        lcd.setCursor(1,0);
        lcd.print("Select WayPoint     ");
        clearLine(2);
        clearLine(3);
        lcd.setCursor(2,0);
        lcd.print(currentWayPoint, DEC);
        menuState = MENU4C;
      }
      else if (pressedKey == LEFT)
      {
        menuState = MENU3;
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
        lcd.setCursor(2,0);
        lcd.print(currentWayPoint, DEC);
      }
    }
  }
}
