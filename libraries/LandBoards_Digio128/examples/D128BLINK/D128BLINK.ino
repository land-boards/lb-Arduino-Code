// DIGIO-16 Example code
// Make all 128 lines outputs
// Blink each line, one at a time

#include <Wire.h>
#include "Adafruit_MCP23017.h"

Adafruit_MCP23017 mcp0;
Adafruit_MCP23017 mcp1;
Adafruit_MCP23017 mcp2;
Adafruit_MCP23017 mcp3;
Adafruit_MCP23017 mcp4;
Adafruit_MCP23017 mcp5;
Adafruit_MCP23017 mcp6;
Adafruit_MCP23017 mcp7;

// Set all of the ports up to be inputs

void setup() 
{
  Serial.begin(9600);
  mcp0.begin(0);      // use default address 0
  mcp1.begin(1);      // use default address 0
  mcp2.begin(2);      // use default address 0
  mcp3.begin(3);      // use default address 0
  mcp4.begin(4);      // use default address 0
  mcp5.begin(5);      // use default address 0
  mcp6.begin(6);      // use default address 0
  mcp7.begin(7);      // use default address 0
  TWBR = 12;    // go to 400 KHz I2C speed mode

  uint8_t pinNum;
  
  for (pinNum = 0; pinNum < 128; pinNum++)
    mcpPinModeBit(pinNum, INPUT);
}

// flip the last pin up and down

void loop() 
{
  uint8_t valRead; 
  toggleDiffChannel();
  mcpPinModeBit(15,INPUT);
  mcpPinModeBit(0,OUTPUT);
  Serial.println("Setting Bit0 low");
  mcpWriteBit(0,LOW);
  delay(200);
  Serial.print("Reading back Bit15, value = ");
  valRead = mcpReadBit(15);
  Serial.println(valRead);
  delay(200);
  Serial.println("Setting Bit0 HIGH");
  mcpWriteBit(0,HIGH);
  delay(200);
  Serial.print("Reading back Bit15, value = ");
  valRead = mcpReadBit(15);
  Serial.println(valRead);
  delay(200);
//  blinkFailLed();
}

#define TXC13A 8  //J1
#define TXC13B 4
#define TXC11A 7  // J2
#define TXC11B 12
#define TXC19A 1  // J3
#define TXC19B 14
#define TXC21A 0  // J4
#define TXC21B 15
#define TXC22A 19 // J5
#define TXC22B 20
#define TXC20A 26 // J6
#define TXC20B 21
#define TXC07A 27 // J7
#define TXC07B 28
#define TXC02A 22 // J8
#define TXC02B 24
#define TXC01A 23 // J9
#define TXC01B 25
#define TXC06A 11 // J10
#define TXC06B 3
#define TXC05A 13 // J11
#define TXC05B 2
#define TXC14A 5  // J12
#define TXC14B 10
#define TXC12A 6  // J13
#define TXC12B 9

uint8_t pwmTable[] = {TXC13A,TXC13B,TXC11A,TXC11B,TXC19A,TXC19B,TXC21A,TXC21B,TXC22A,TXC22B,TXC20A,TXC20B,TXC07A,TXC07B,TXC02A,TXC02B,TXC01A,TXC01B,TXC06A,TXC06B,TXC05A,TXC05B,TXC14A,TXC14B,TXC12A,TXC12B};

// Set a differential channel to a value

void setDiffOut(uint8_t chNum, uint8_t aOrBFlag,  uint8_t value)
{
//  Serial.println("Got to setDiffOut");
  uint8_t tableEntry = (chNum << 1 ) + aOrBFlag;
//  Serial.print("tableEntry=");
//  Serial.println(tableEntry);
  mcpPinModeBit(pwmTable[tableEntry],OUTPUT);
  mcpWriteBit(pwmTable[tableEntry],value);
//  Serial.print("pwmTable=");
//  Serial.println(pwmTable[tableEntry]);
}

// test setting a differential channel value

void toggleDiffChannel(void)
{
  while (1)
  {
  Serial.println("Got to toggleDiffChannel");
  setDiffOut(0,0,HIGH);
  delay(100);
  setDiffOut(0,0,LOW);
  delay(100);
  }
}

void blinkFailLed(void)
{
  uint8_t chip;
  uint8_t port;

  chip = 0;
  port = 0;
  mcpPinMode(chip, port, OUTPUT);
  mcpWriteBit(127, HIGH);
  delay(500);
  mcpWriteBit(127, LOW);
  delay(500);
  mcpPinMode(chip, port, OUTPUT);
}


