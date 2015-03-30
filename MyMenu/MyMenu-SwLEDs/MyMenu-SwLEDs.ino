#include <Wire.h>
#include <Adafruit_MCP23008.h>

Adafruit_MCP23008 mcp;
  
void setup() {  
  mcp.begin();      // use default address 0

  mcp.pinMode(0, OUTPUT);
  mcp.pinMode(1, OUTPUT);
  mcp.pinMode(2, OUTPUT);
  mcp.pinMode(3, INPUT);
  mcp.pinMode(4, INPUT);
  mcp.pinMode(5, INPUT);
  mcp.pinMode(6, INPUT);
  mcp.pinMode(7, INPUT);
}

void loop() {
  int a, b, c, d, e;
  a = !mcp.digitalRead(3);
  delay(10);
  b = !mcp.digitalRead(4);
  delay(10);
  c = !mcp.digitalRead(5);
  delay(10);
  d = !mcp.digitalRead(6);
  delay(10);
  e = !mcp.digitalRead(7);
  delay(10);
  mcp.digitalWrite(0, a|d|e);
  delay(10);
  mcp.digitalWrite(1, b|e);
  delay(10);
  mcp.digitalWrite(2, c|d);
  delay(10);
}

