void mcpWriteBit(uint8_t bitNum, uint8_t val)
{
  uint8_t chipNum = bitNum >> 4;
  uint8_t chNum = bitNum - (chipNum << 4);
  mcpWrite(chipNum, chNum, val);
}

void mcpPinModeBit(uint8_t bitNum, uint8_t val)
{
  uint8_t chipNum = bitNum >> 4;
  uint8_t chNum = bitNum - (chipNum << 4);
  mcpPinMode(chipNum, chNum, val);
}

void mcpPullUpBit(uint8_t bitNum, uint8_t val)
{
  uint8_t chipNum = bitNum >> 4;
  uint8_t chNum = bitNum - (chipNum << 4);
  mcpPullUp(chipNum, chNum, val);
}

uint8_t mcpReadBit(uint8_t bitNum)
{
  uint8_t chipNum = bitNum >> 4;
  uint8_t chNum = bitNum - (chipNum << 4);
  return(mcpRead(chipNum, chNum));
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

/* mcpPullUp(chipNum, chNum, val)
  Set the pull up for a channel.
  chipNum is from 0-7
  chNum is from 0-15
  val is HIGH to turn on pull up and LOW to turn off pullup
*/
void mcpPullUp(uint8_t chipNum, uint8_t chNum, uint8_t val)
{
  switch (chipNum)
  {
  case 0:
    mcp0.pullUp(chNum, val);
    break;
  case 1:
    mcp1.pullUp(chNum, val);
    break;
  case 2:
    mcp2.pullUp(chNum, val);
    break;
  case 3:
    mcp3.pullUp(chNum, val);
    break;
  case 4:
    mcp4.pullUp(chNum, val);
    break;
  case 5:
    mcp5.pullUp(chNum, val);
    break;
  case 6:
    mcp6.pullUp(chNum, val);
    break;
  case 7:
    mcp7.pullUp(chNum, val);
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

