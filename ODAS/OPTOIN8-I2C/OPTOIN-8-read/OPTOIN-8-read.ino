#include <Wire.h>
#include "Adafruit_MCP23008.h"

Adafruit_MCP23008 mcp;

void setup()
{  
  Serial.begin(57600);
  mcp.begin();      // use default address 0

  pinMode(8, OUTPUT);
  digitalWrite(8, LOW);
  mcp.pinMode(0, INPUT);
  mcp.pinMode(1, INPUT);
  mcp.pinMode(2, INPUT);
  mcp.pinMode(3, INPUT);
  mcp.pinMode(4, INPUT);
  mcp.pinMode(5, INPUT);
  mcp.pinMode(6, INPUT);
  mcp.pinMode(7, INPUT);
  mcp.pullUp(0, HIGH);  // turn on a 100K pullup internally
  mcp.pullUp(1, HIGH);  // turn on a 100K pullup internally
  mcp.pullUp(2, HIGH);  // turn on a 100K pullup internally
  mcp.pullUp(3, HIGH);  // turn on a 100K pullup internally
  mcp.pullUp(4, HIGH);  // turn on a 100K pullup internally
  mcp.pullUp(5, HIGH);  // turn on a 100K pullup internally
  mcp.pullUp(6, HIGH);  // turn on a 100K pullup internally
  mcp.pullUp(7, HIGH);  // turn on a 100K pullup internally
}

void loop() {
  // The LED will 'echo' the button
  digitalWrite(8, LOW);
//  delay(1);
  Serial.print("Wrote LOW, read back  ");
  Serial.println(mcp.digitalRead(7));
  digitalWrite(8, HIGH);
//  delay(1);
  Serial.print("Wrote HIGH, read back ");
  Serial.println(mcp.digitalRead(7));
}

