#include <Wire.h>
#include "Adafruit_MCP23017.h"

// Basic pin reading and pullup test for the MCP23017 I/O expander
// public domain!

// Connect pin #12 of the expander to Analog 5 (i2c clock)
// Connect pin #13 of the expander to Analog 4 (i2c data)
// Connect pins #15, 16 and 17 of the expander to ground (address selection)
// Connect pin #9 of the expander to 5V (power)
// Connect pin #10 of the expander to ground (common ground)
// Connect pin #18 through a ~10kohm resistor to 5V (reset pin, active low)

// Output #0 is on pin 21 so connect an LED or whatever from that to ground

Adafruit_MCP23017 mcp;
  
void setup() {  
  mcp0.begin(0);      // use default address 0
  mcp1.begin(1);      // use default address 0
  mcp2.begin(2);      // use default address 0
  mcp3.begin(3);      // use default address 0
  mcp4.begin(4);      // use default address 0
  mcp5.begin(5);      // use default address 0
  mcp6.begin(6);      // use default address 0
  mcp7.begin(7);      // use default address 0

  mcp0.pinMode(0, OUTPUT);
  mcp1.pinMode(1, OUTPUT);
  mcp2.pinMode(2, OUTPUT);
  mcp3.pinMode(3, OUTPUT);
  mcp4.pinMode(4, OUTPUT);
  mcp5.pinMode(5, OUTPUT);
  mcp6.pinMode(6, OUTPUT);
  mcp7.pinMode(7, OUTPUT);
}


// flip the pin #0 up and down

void loop() {
  delay(250);

  mcp0.digitalWrite(0, HIGH);
  mcp1.digitalWrite(1, LOW);
  mcp2.digitalWrite(2, LOW);
  mcp3.digitalWrite(3, LOW);
  mcp4.digitalWrite(4, LOW);
  mcp5.digitalWrite(5, LOW);
  mcp6.digitalWrite(6, LOW);
  mcp7.digitalWrite(7, LOW);

  delay(250);

  mcp0.digitalWrite(0, LOW);
  mcp1.digitalWrite(1, HIGH);
}
