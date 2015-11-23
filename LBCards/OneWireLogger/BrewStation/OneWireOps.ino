//////////////////////////////////////////////////////////////////////////////
// do1Wire() - Run the 1 Wire Interface
//////////////////////////////////////////////////////////////////////////////

void do1Wire(void)
{
  uint8_t key;
  clearDisplay();
  tft.print(F("**** Thermometer ****"));
  do
  {
    readNext1Wire();
    if (sensorNumber > 0)
    {
      tft.setTextSize(3);
      setDisplayCursor(5+sensorNumber,0);
      tft.print(temps1Wire[sensorNumber-1]);
      tft.print(F("F "));
      tft.setTextSize(1);
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
  delay(750);               // maybe 750ms is enough, maybe not
  // we might do a ds.depower() here, but the reset will take care of it.

  ds.reset();
  ds.select(addr);    
  ds.write(0xBE);         // Read Scratchpad

  for ( i = 0; i < 9; i++) 
  {           // we need 9 bytes
    data[i] = ds.read();
  }

// debug by dumping the address array
//  setDisplayCursor(3+sensorNumber,0);
//  for ( i = 0; i < 8; i++) 
//  {           // we need 9 bytes
//    tft.print(addr[7-i],HEX);
//    tft.print(" ");
//  }
  
  // convert the data to actual temperature
  int raw = (data[1] << 8) | data[0];
  if ((addr[0] == 0x28) || (addr[0] == 0x22))
    fahrenheit = ((((float)raw) * 1.8)/16.0) + 32.0;
  else if (addr[0] == 0x10)
    fahrenheit = ((((float)raw) * 1.8)/2.0) + 32.0;
  else
    fahrenheit = -99.9;
  temps1Wire[sensorNumber] = fahrenheit;
  sensorAddr = addr[7];
  sensorNumber++;
}

