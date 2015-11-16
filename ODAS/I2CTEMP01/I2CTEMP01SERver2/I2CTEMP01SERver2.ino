#include "Wire.h"
#define tcn75address 0x48 // with pins 5~7 set to GND, the device address is 0x48

void setup()
{
  Wire.begin();                      // wake up I2C bus 
  Serial.begin(115200);
}

float tcn75_getTemperature(int address)
{
  byte a, b;
  float temp=.0;
  Wire.beginTransmission(address);  // Start transmission
  Wire.write((byte)0);              // move your register pointer back to 00h
  Wire.endTransmission();           // Stop transmission
  Wire.requestFrom(address, 2);     // Send me the contents of your first two bytes
  a = Wire.read();                  // first received byte stored here
  b = Wire.read();                  // second received byte stored here
  temp=tcn75_convertTemp(a, b);     // convert received bytes into float value
  return(temp);
}

float tcn75_convertTemp(byte aa, byte bb)
{
  float temp;
  if (aa>127)            // check for below zero degrees
  {
    temp=((aa-128)*-1);
    if (bb==128)         // check for 0.5 fraction
    {
      temp-=0.5;
    }
  }
  else                   // it must be above zero degrees
  {
    temp=aa;
    if (bb==128)         // check for 0.5 fraction
    {
      temp+=0.5;
    }
  }
  return(temp);
}


void loop()
{
  Serial.print("Current temperature = ");
  Serial.println(tcn75_getTemperature(tcn75address));
  delay(2000);
}
