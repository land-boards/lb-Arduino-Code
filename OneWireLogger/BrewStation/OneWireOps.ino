//////////////////////////////////////////////////////////////////////////////
// do1Wire() - Run the 1 Wire Interface
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
  uint8_t present = 0;
  uint8_t type_s;
  uint8_t data[12];
  uint8_t addr[8];

  if ( !ds.search(addr)) 
  {
#ifdef SERIAL_OUT
    Serial.println("");
#endif
    ds.reset_search();
    delay(250);
    firstRun=0;
    sensorNumber=0;
    return(-1);
  }

  firstRun=0;

#ifdef SERIAL_OUT
  for( i = 0; i < 8; i++) 
  {
    Serial.print(addr[i], HEX);
  }
  Serial.print(",");
#endif
  if (OneWire::crc8(addr, 7) != addr[7]) 
  {
#ifdef SERIAL_OUT
    Serial.println("CRC is not valid!");
#endif
    return(-2);
  }

  // the first ROM byte indicates which chip
  switch (addr[0]) {
  case 0x10:
    type_s = 1;
    break;
  case 0x28:
    type_s = 0;
    break;
  case 0x22:
    type_s = 0;
    break;
  default:
#ifdef SERIAL_OUT
    Serial.println("Device is not a DS18x20 family device.");
#endif
    return(0);
  } 

  ds.reset();
  ds.select(addr);
  ds.write(0x44,1);         // start conversion, with parasite power on at the end

  delay(750);               // maybe 750ms is enough, maybe not
  // we might do a ds.depower() here, but the reset will take care of it.

  present = ds.reset();
  ds.select(addr);    
  ds.write(0xBE);         // Read Scratchpad

  for ( i = 0; i < 9; i++) 
  {           // we need 9 bytes
    data[i] = ds.read();
  }
  // convert the data to actual temperature

  unsigned int raw = (data[1] << 8) | data[0];
  if (type_s) 
  {
    raw = raw << 3; // 9 bit resolution default
    if (data[7] == 0x10) {
      // count remain gives full 12 bit resolution
      raw = (raw & 0xFFF0) + 12 - data[6];
    }
  } 
  else 
  {
    byte cfg = (data[4] & 0x60);
    if (cfg == 0x00) raw = raw << 3;  // 9 bit resolution, 93.75 ms
    else if (cfg == 0x20) raw = raw << 2; // 10 bit res, 187.5 ms
    else if (cfg == 0x40) raw = raw << 1; // 11 bit res, 375 ms
    // default is 12 bit resolution, 750 ms conversion time
  }
  fahrenheit = ((float)raw / 16.0) * 1.8 + 32.0;
#ifdef SERIAL_OUT
  Serial.print(fahrenheit);
  Serial.print(",");
#endif
  temps1Wire[sensorNumber] = fahrenheit;
  sensorAddr = addr[7];
  sensorNumber++;
}


