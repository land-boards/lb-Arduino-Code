#include <OneWire.h>
#include <Arduino.h>

// OneWire DS18S20, DS18B20, DS1822 Temperature Example
//
// http://www.pjrc.com/teensy/td_libs_OneWire.html
//
// The DallasTemperature library can do all this work for you!
// http://milesburton.com/Dallas_Temperature_Control_Library

OneWire  ds(6);  // on pin 

void read1Wire(void) 
{
  byte i;
  byte present = 0;
  byte type_s;
  byte data[12];
  byte addr[8];
  float celsius, fahrenheit;

  //  setCursorTFT(1,0);
  if ( !ds.search(addr)) {
    //    tft.println("No more addresses.");
    ds.reset_search();
    delay(250);
    sensNum = 0;
    return;
  }

  //  setCursorTFT(2,0);
  //  tft.print("ROM =");
  //  for( i = 0; i < 8; i++) {
  //    Serial.write(' ');
  //    tft.print(addr[i], HEX);
  //  }

  if (OneWire::crc8(addr, 7) != addr[7]) {
    //    tft.println("CRC is not valid!");
    return;
  }
  //  tft.println();

  setCursorTFT(sensNum*3+1,0);
  // the first ROM byte indicates which chip
  switch (addr[0]) {
  case 0x10:
    tft.println("Chip = DS18S20");  // or old DS1820
    type_s = 1;
    break;
  case 0x28:
    tft.println("Chip = DS18B20");
    type_s = 0;
    break;
  case 0x22:
    tft.println("Chip = DS1822");
    type_s = 0;
    break;
  default:
    //    tft.println("Device is not a DS18x20 family device.");
    return;
  } 

  ds.reset();
  ds.select(addr);
  ds.write(0x44,1);         // start conversion, with parasite power on at the end

  delay(1000);     // maybe 750ms is enough, maybe not
  // we might do a ds.depower() here, but the reset will take care of it.

  present = ds.reset();
  ds.select(addr);    
  ds.write(0xBE);         // Read Scratchpad

  //  setCursorTFT(4,0);
  //  tft.print("  Data = ");
  //  tft.print(present,HEX);
  //  tft.print(" ");
  for ( i = 0; i < 9; i++) {           // we need 9 bytes
    data[i] = ds.read();
    //    tft.print(data[i], HEX);
    //    tft.print(" ");
  }
  //  setCursorTFT(5,0);
  //  tft.print(" CRC=");
  //  tft.print(OneWire::crc8(data, 8), HEX);
  //  tft.println();

  // convert the data to actual temperature

  unsigned int raw = (data[1] << 8) | data[0];
  if (type_s) 
  {
    raw = raw << 3; // 9 bit resolution default
    if (data[7] == 0x10) 
    {
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
  celsius = (float)raw / 16.0;
  fahrenheit = celsius * 1.8 + 32.0;
  setCursorTFT(sensNum*3+2,0);
  tft.print("Temp = ");
  tft.print(celsius);
  tft.print("C");
  setCursorTFT(sensNum*3+3,0);
  tft.print(fahrenheit);
  tft.println(" F");
  sensNum++;
}



