// DIGIO128_Loopback code
// Tests port-to-port loopback
// Reports any failures

#include "LandBoards_MCP23017.h"

LandBoards_MCP23017 mcp0;
LandBoards_MCP23017 mcp1;
LandBoards_MCP23017 mcp2;
LandBoards_MCP23017 mcp3;
LandBoards_MCP23017 mcp4;
LandBoards_MCP23017 mcp5;
LandBoards_MCP23017 mcp6;
LandBoards_MCP23017 mcp7;

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
#if defined(ARDUINO_ARCH_AVR)
  TWBR = 12;          // go to 400 KHz I2C speed mode
#elif defined(ARDUINO_ARCH_STM32F1)
  Wire.setClock(400000);  // 400KHz speed
#else
  #error “This library only supports boards with an AVR or SAM processor.”
#endif

  uint8_t chip;
  uint8_t port;

  for (chip = 0; chip < 8; chip++)
  {
    for (port = 0; port < 16; port++)
    {
      mcpPinMode(chip, port, INPUT);
    }
  }
}

// flip the pin #0 up and down

void loop()
{
  if (loopBackTest() == 0)
    Serial.println("Loopback Test PASS");
  else
    Serial.println("Loopback Test FAILED");
}

uint8_t loopBackTest(void)
{
  uint8_t chip;
  uint8_t port;
  uint8_t pass0fail1 = 0;
  for (chip = 0; chip < 8; chip += 2)
  {
    for (port = 0; port < 16; port++)
    {
      mcpPinMode(chip, port, OUTPUT);
      mcpPinMode(chip + 1, 15 - port,INPUT);
      
      delay(2);
      mcpWrite(chip, port, HIGH);
      delay(2);
      if (mcpRead(chip + 1, 15 - port) != HIGH)
      {
        Serial.print("Error on chip ");
        Serial.print(chip);
        Serial.print(" and port ");
        Serial.print(port);
        Serial.println(" Expected High");
        pass0fail1 = 1;
      }
      mcpWrite(chip, port, LOW);
      delay(2);
      if (mcpRead(chip + 1, 15 - port) != LOW)
      {
        Serial.print("Error on chip ");
        Serial.print(chip);
        Serial.print(" and port ");
        Serial.print(port);
        Serial.println(" Expected LOW");
        pass0fail1 = 1;
      }
      mcpPinMode(chip, port, INPUT);
      delay(2);
    }
    return pass0fail1;
  }
}

/* mcpWrite(chipNum, chNum, val)
  Write a value to a pin.
  chipNum is from 0-7
  chNum is from 0-15
  val is LOW or HIGH
*/
void mcpWrite(uint8_t chipNum, uint8_t chNum, uint8_t val)
{
  switch (chipNum)
  {
    case 0:
      mcp0.digitalWrite(chNum, val);
      break;
    case 1:
      mcp1.digitalWrite(chNum, val);
      break;
    case 2:
      mcp2.digitalWrite(chNum, val);
      break;
    case 3:
      mcp3.digitalWrite(chNum, val);
      break;
    case 4:
      mcp4.digitalWrite(chNum, val);
      break;
    case 5:
      mcp5.digitalWrite(chNum, val);
      break;
    case 6:
      mcp6.digitalWrite(chNum, val);
      break;
    case 7:
      mcp7.digitalWrite(chNum, val);
      break;
  }
}

/* mcpPinMode(chipNum, chNum, val)
  Set the pin to be an input or output.
  chipNum is from 0-7
  chNum is from 0-15
  val is INPUT or OUTPUT
*/
void mcpPinMode(uint8_t chipNum, uint8_t chNum, uint8_t val)
{
  switch (chipNum)
  {
    case 0:
      mcp0.pinMode(chNum, val);
      break;
    case 1:
      mcp1.pinMode(chNum, val);
      break;
    case 2:
      mcp2.pinMode(chNum, val);
      break;
    case 3:
      mcp3.pinMode(chNum, val);
      break;
    case 4:
      mcp4.pinMode(chNum, val);
      break;
    case 5:
      mcp5.pinMode(chNum, val);
      break;
    case 6:
      mcp6.pinMode(chNum, val);
      break;
    case 7:
      mcp7.pinMode(chNum, val);
      break;
  }
}

/* mcpRead(chipNum, chNum)
  Reads a channel.
  chipNum is from 0-7
  chNum is from 0-15
  Returns the value of the pin
*/
uint8_t mcpRead(uint8_t chipNum, uint8_t chNum)
{
  switch (chipNum)
  {
    case 0:
      return(mcp0.digitalRead(chNum));
      break;
    case 1:
      return(mcp1.digitalRead(chNum));
      break;
    case 2:
      return(mcp2.digitalRead(chNum));
      break;
    case 3:
      return(mcp3.digitalRead(chNum));
      break;
    case 4:
      return(mcp4.digitalRead(chNum));
      break;
    case 5:
      return(mcp5.digitalRead(chNum));
      break;
    case 6:
      return(mcp6.digitalRead(chNum));
      break;
    case 7:
      return(mcp7.digitalRead(chNum));
      break;
  }
}
