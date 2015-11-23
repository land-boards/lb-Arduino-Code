//////////////////////////////////////////////////////////////////////////////
// OneWLOps() - Run the 1 Wire Interface
//////////////////////////////////////////////////////////////////////////////

void do1Wire(void)
{
  uint8_t key;
  clearDisplay();
  tft.print(F("Do 1 Wire"));
  do
  {
    readNext1Wire();
    if (sensorNumber > 0)
    {
      setDisplayCursor(sensorNumber,0);
      tft.print(F("                "));
      setDisplayCursor(sensorNumber,0);
      tft.print(F("S"));
      tft.print(sensorNumber);
      tft.print(F("-"));
      tft.print(sensorAddr, HEX);
      tft.print(F(" "));
      tft.print(temps1Wire[sensorNumber-1]);
      tft.print(F("F   "));
    }
    myOneWireLogger.delayAvailable(250);
    key = myOneWireLogger.pollKeypad();
  }
  while (key == NONE);
  tft.fillScreen(ST7735_BLACK);
}

//////////////////////////////////////////////////////////////////////////////
// do1WCSV() - Run the 1 Wire Interface and output results over Serial as CSV
//////////////////////////////////////////////////////////////////////////////

void do1WCSV(void)
{
  uint8_t key;
  clearDisplay();
  tft.print(F("Do 1 Wire"));
  do
  {
    readNext1Wire();
    if (sensorNumber > 0)
    {
      uint8_t timeStat = VIEW_YEAR;
      setRTCTime = RTC.now();
      currYear = setRTCTime.year();
      currMonth = setRTCTime.month();
      currDay = setRTCTime.day();
      currHour = setRTCTime.hour();
      currMin = setRTCTime.minute();
      currSec = setRTCTime.second();
      setDisplayCursor(sensorNumber,0);
      tft.print(F("                    "));
      setDisplayCursor(sensorNumber,0);
      tft.print(currHour);
//      tft.print(F(":"));
      tft.print(currMin);
//      tft.print(F(":"));
      tft.print(currSec);
      tft.print(F(","));
      tft.print(F("S"));
      tft.print(sensorNumber);
      tft.print(F("-"));
      tft.print(sensorAddr, HEX);
      tft.print(F(" "));
      tft.print(temps1Wire[sensorNumber-1]);
      tft.print(F("F   "));
//      if (temps1Wire[sensorNumber-1] < 150.0)
//      {
//        tft.setTextColor(ST7735_BLACK,ST7735_WHITE);
//        tft.fillRect(0,80,128,64,ST7735_WHITE);
//      }
//      else if (temps1Wire[sensorNumber-1] < 165.0)
//      {
//        tft.setTextColor(ST7735_WHITE,ST7735_BLUE);
//        tft.fillRect(0,80,128,64,ST7735_BLUE);
//      }
//      else
//      {
//        tft.setTextColor(ST7735_WHITE,ST7735_RED);
//        tft.fillRect(0,80,128,64,ST7735_RED);
//      }
//      setDisplayCursor(sensorNumber+8,0);
//	  tft.setTextSize(3);
//      tft.print(temps1Wire[sensorNumber-1]);
      tft.setTextSize(1);
      tft.setTextColor(ST7735_WHITE,ST7735_BLACK);
      if (sensorNumber == 1)
        Serial.print("\n");
      Serial.print(currHour);
      Serial.print(":");
      Serial.print(currMin);
      Serial.print(":");
      Serial.print(currSec);
      Serial.print(",");
      Serial.print(sensorNumber);
      Serial.print(",");
      Serial.print(sensorAddr, HEX);
      Serial.print(",");
      Serial.print(temps1Wire[sensorNumber-1]);
      Serial.print(",");
//      Serial.print("\n");
    }
    myOneWireLogger.delayAvailable(250);
    key = myOneWireLogger.pollKeypad();
  }
  while (key == NONE);
  tft.fillScreen(ST7735_BLACK);
}

//////////////////////////////////////////////////////////////////////////////
// OneWire DS18S20, DS18B20, DS1822 Temperature Example
//
// http://www.pjrc.com/teensy/td_libs_OneWire.html
//
// The DallasTemperature library can do all this work for you!
// http://milesburton.com/Dallas_Temperature_Control_Library
//////////////////////////////////////////////////////////////////////////////

char readNext1Wire(void)
{
  uint8_t i;
  uint8_t data[12];
  uint8_t addr[8];

  if ( !ds.search(addr)) 
  {
    ds.reset_search();
    delay(250);
    firstRun=0;
    sensorNumber=0;
    return(-1);
  }

  firstRun=0;

  if (OneWire::crc8(addr, 7) != addr[7]) 
  {
    return(-2);
  }

  ds.reset();
  ds.select(addr);
  ds.write(0x44,1);         // start conversion, with parasite power on at the end
  delay(750);               // 
  // we might do a ds.depower() here, but the reset will take care of it.

  ds.reset();
  ds.select(addr);    
  ds.write(0xBE);         // Read Scratchpad command

  for ( i = 0; i < 9; i++) 
  {           // we need 9 bytes
    data[i] = ds.read();
  }
  // convert the data to actual temperature
  int raw = (data[1] << 8) | data[0];
  if ((addr[0] == 0x28) || (addr[0] == 0x22))
    fahrenheit = ((((float)raw) * 1.8)/16.0) + 32.0;
  else if (addr[0] == 0x10)
    fahrenheit = ((((float)raw) * 1.8)/2.0) + 32.0;
  else
    fahrenheit = -99.9;  temps1Wire[sensorNumber] = fahrenheit;
  sensorAddr = addr[7];
  sensorNumber++;
}

