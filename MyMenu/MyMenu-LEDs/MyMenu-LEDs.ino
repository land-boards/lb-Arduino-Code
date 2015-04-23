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
  mcp.digitalWrite(2, LOW);
  mcp.digitalWrite(0, HIGH);

  delay(250);

  mcp.digitalWrite(0, LOW);
  mcp.digitalWrite(1, HIGH);

  delay(250);

  mcp.digitalWrite(1, LOW);
  mcp.digitalWrite(2, HIGH);
  delay(250);

}

