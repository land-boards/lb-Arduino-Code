//////////////////////////////////////////////////////////////////////////////
// OneWLOps() - Run the 1 Wire Interface
//////////////////////////////////////////////////////////////////////////////

void steepTemps(void)
{
  uint8_t key;
  clearDisplay();
  tft.print(F("** Steep Temps **"));
  do
  {
    readNext1Wire();
    if (sensorNumber > 0)
    {
      tft.setTextSize(3);
      setDisplayCursor(sensorNumber+4,0);
      if (temps1Wire[sensorNumber-1] < 150.0)
        tft.setTextColor(ST7735_BLACK,ST7735_WHITE);
      else if (temps1Wire[sensorNumber-1] > 165.0)
        tft.setTextColor(ST7735_BLACK,ST7735_RED);
      else
        tft.setTextColor(ST7735_GREEN,ST7735_WHITE);
      tft.print(temps1Wire[sensorNumber-1]);
      tft.print(F(" "));
      tft.setTextSize(1);
    }
    myOneWireLogger.delayAvailable(250);
    key = myOneWireLogger.pollKeypad();
  }
  while (key == NONE);
  tft.fillScreen(ST7735_BLACK);
}

//////////////////////////////////////////////////////////////////////////////
// OneWLOps() - Run the 1 Wire Interface
//////////////////////////////////////////////////////////////////////////////

void boilTemps(void)
{
  uint8_t key;
  clearDisplay();
  tft.print(F("** Boil Temps **"));
  do
  {
    readNext1Wire();
    if (sensorNumber > 0)
    {
      tft.setTextSize(3);
      setDisplayCursor(sensorNumber+4,0);
//      tft.print(F("                "));
//      setDisplayCursor(sensorNumber,0);
//      tft.print(F("S"));
//      tft.print(sensorNumber);
//      tft.print(F("-"));
//      tft.print(sensorAddr, HEX);
//      tft.print(F(" "));
      if (temps1Wire[sensorNumber-1] < 200.0)
        tft.setTextColor(ST7735_BLACK,ST7735_WHITE);
      else
        tft.setTextColor(ST7735_RED,ST7735_BLACK);
      tft.print(temps1Wire[sensorNumber-1]);
      tft.print(F(" "));
      tft.setTextSize(1);
    }
    myOneWireLogger.delayAvailable(250);
    key = myOneWireLogger.pollKeypad();
  }
  while (key == NONE);
  tft.fillScreen(ST7735_BLACK);
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

void InitLimits(void)
{
  uint8_t i;
  uint8_t addr[8];

  if ( !ds.search(addr)) 
  {
    ds.reset_search();
    delay(250);
    firstRun=0;
    sensorNumber=0;
    return;
  }

  firstRun=0;

  setDisplayCursor(2,0);
  for( i = 0; i < 8; i++) 
  {
    tft.print(addr[7-i], HEX);
    tft.print(" ");
  }
  if (OneWire::crc8(addr, 7) != addr[7]) 
  {
    return;
  }
  
  ds.reset();
  ds.select(addr);
  ds.write(0x4e,1);         // Write scratchpad 
  ds.write(0x70,1);         // Temp limit high
  ds.write(0x01,1);         // Temp limit low
  ds.write(0x7f,1);         // Config reg - 12 bits conversions
  delay(800);
  setDisplayCursor(3,0);
  tft.print("Wrote scratchpad");
  delay(250);

  ds.reset();
  ds.select(addr);
  ds.write(0x48,1);         // store scratchpad into eeprom
  delay(200);
  setDisplayCursor(4,0);
  tft.print("Wrote EEPROM");
  delay(500);

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
  delay(300);               // 
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

  fahrenheit = ((((float)raw) * 1.8)/16.0) + 32.0;
  temps1Wire[sensorNumber] = fahrenheit;
  sensorAddr = addr[7];
  sensorNumber++;
}

