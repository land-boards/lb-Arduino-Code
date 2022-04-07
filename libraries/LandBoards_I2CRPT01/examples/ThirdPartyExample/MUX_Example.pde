/**********************************************************
 * MUX_Example.pde ----- Sample sketch for the 4 Channel I2C Multiplexer
 * 
 * A sample sketch that shows the basic functions of the 4 Channel I2C 
 * Multiplexer.  The below sketch uses 4 Lipo Fuel Gauges connected to the
 * multiplexer.
 *
 * 2011, DSS Circuits, Inc.  http://www.dsscircuits.com
 * 
 **********************************************************/
#include "Wire.h"

#define FG          0x36  //Lipo Fuel Gauge Address
#define MUX         0x70  //Multiplexer Address

void setup()
{
  Wire.begin();
  Serial.begin(115200);
  mux(0);  //select Lipo Fuel Gauge on channel 0
  initializeFG(FG);
  mux(1);  //select Lipo Fuel Gauge on channel 0
  initializeFG(FG);
  mux(2);  //select Lipo Fuel Gauge on channel 0
  initializeFG(FG);
  mux(3);  //select Lipo Fuel Gauge on channel 0
  initializeFG(FG);
  mux(0xFF);  //disable all channels. This is not required
}

void loop()
{
  mux(0);
  readFG(FG);
  mux(1);
  readFG(FG);
  mux(2);
  readFG(FG);
  mux(3);
  readFG(FG);
  mux(0xFF);
  delay(500);
}


/********************************************************
* When selecting a channel bit2 of the control register
* must be set to a logic 1 to enable channel selection.
* If bit2 is a logic zero then all channels will be disabled.
* If 0xFF is the selected channel it will disable all channels.
********************************************************/
void mux(byte channel)
{
  byte controlRegister = 0x04;  
  controlRegister |= channel;
  Wire.beginTransmission(MUX);
  if (channel == 0xFF){Wire.send(0x00);} //deselect all channels
  else {Wire.send(controlRegister);}     //set to selected channel
  Wire.endTransmission();
}

void initializeFG(uint8_t address)
{
  Serial.println("Initiating Quick Start");
  Wire.beginTransmission(FG);
  Wire.send(0x06);
  Wire.send(0x40);
  Wire.send(0x00);
  Wire.endTransmission();  
}

void readFG(int _fg)
{
  unsigned int byte1 = 0;
  unsigned int byte2 = 0;
  unsigned int comb = 0;
  Wire.beginTransmission(_fg);
  Wire.send(0x04);
  Wire.endTransmission();
  Wire.requestFrom(_fg,2);
  byte1 = Wire.receive();
  byte2 = Wire.receive();
  Serial.print("SOC REGISTER = ");
  Serial.print(byte1,HEX);
  Serial.println(byte2,HEX); 
  comb = ((byte1 << 8));
  comb |= (byte2);
  Serial.print("SOC percent = ");
  Serial.print(map(comb,0x0000,0x6400,0,10000)/100.0,2);
  Serial.println("%");
  delay(500);
}
  
