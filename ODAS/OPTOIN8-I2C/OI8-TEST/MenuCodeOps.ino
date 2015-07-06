//////////////////////////////////////////////////////////////////////////////
// MenuCodeOps() - Run the OptoOut8-I2C card tests
//////////////////////////////////////////////////////////////////////////////

unsigned char readOptoIn8(void)
{
  int loopVal;
  unsigned int rval = 0;
  for (loopVal = 0; loopVal < 8; loopVal++)
  {
    rval |= mcpOI8.digitalRead(loopVal) & 0x1;
    rval <<= 1;
  }
  return rval >> 1;
}

//////////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////////

void testOI8board(void)
{
  int loopCnt;
  unsigned char digRdVal;
  int pass1Fail0;
  menuCard.setLED(0, HIGH);
  unsigned char readVal;
 do
  {
  int testPass = 1;
  int testBit = 0x1;
     for (int loopVal = 3; loopVal < 11; loopVal++)
    {
      digitalWrite(loopVal, LOW);
      readVal = readOptoIn8();
      if ((readVal & testBit) != testBit)
      {
        testPass = 0;
      }
      digitalWrite(loopVal, HIGH);
      readVal = readOptoIn8();
      if ((readVal & testBit) == testBit)
      {
        testPass = 0;
      }
      testBit <<= 1;
    }
    if (testPass)
    {
      passCount++;
    }
    else
    {
      failCount++;
    }
    delay(100);
    u8g.firstPage();
    do
    {
      setDisplayCursor(0, 0);
      u8g.print("OptoIn8 Test");
      setDisplayCursor(1, 0);
      u8g.print("Pass=");
      u8g.print(passCount);
      setDisplayCursor(2, 0);
      u8g.setColorIndex(1);  // default color
      u8g.print("Fail=");
      u8g.print(failCount);
      u8g.setColorIndex(1);  // default color
      setDisplayCursor(3, 0);
      u8g.print("Any to return");
    }
    while ( u8g.nextPage() );
  }
  while (menuCard.pollKeypad() == NONE);
  testCount = 0;
  passCount = 0;
  failCount = 0;
  menuCard.setLED(0, LOW);
  return;
}

//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//

void readEEPROM(void)
{
  char readBuff[97];
  readBuff[96] = 0;
  eeprom.begin();
  eep_vals myEep;
  menuCard.setLED(1, HIGH);
  u8g.firstPage();
  do
  {
    setDisplayCursor(0, 0);
    u8g.print("Reading EEPROM");
    eeprom.readBlock((const uint16_t) 0, (unsigned char*) readBuff, (const uint16_t) 96);

    setDisplayCursor(1, 0);
    for (int loopv = 0; loopv < 4; loopv++)
      u8g.print(readBuff[loopv]);
    setDisplayCursor(2, 0);
    for (int loopv = 32; loopv < 44; loopv++)
      u8g.print(readBuff[loopv]);
    setDisplayCursor(3, 0);
    for (int loopv = 64; loopv < 76; loopv++)
      u8g.print(readBuff[loopv]);
  }
  while ( u8g.nextPage() );
  while (menuCard.pollKeypad() == NONE);
  menuCard.setLED(1, LOW);
}

//////////////////////////////////////////////////////////////////////////////
// writeEEPROM()
//////////////////////////////////////////////////////////////////////////////

void writeEEPROM(void)
{
  char readBuff[97];
  readBuff[96] = 0;
  eeprom.begin();
  eep_vals myEep;
  menuCard.setLED(1, HIGH);
  u8g.firstPage();
  do
  {
    setDisplayCursor(0, 0);
    u8g.print("Writing EEPROM");
    myEep.signature[0] = 'O';
    myEep.signature[1] = 'D';
    myEep.signature[2] = 'A';
    myEep.signature[3] = 'S';
    myEep.fmt_version = 0x01;
    myEep.rsvd = 0;
    myEep.numatoms = 0x2;
    myEep.eeplen = 96;
    myEep.uuid[0] = '0';  // Serial number
    myEep.uuid[1] = '0';
    myEep.uuid[2] = '0';
    myEep.uuid[3] = '0';
    myEep.uuid[4] = '0';
    myEep.uuid[5] = '0';
    myEep.uuid[6] = '0';
    myEep.uuid[7] = '0';
    myEep.uuid[8] = '0';
    myEep.uuid[9] = '0';
    myEep.uuid[10] = '0';
    myEep.uuid[11] = '0';
    myEep.uuid[12] = '0';
    myEep.uuid[13] = '0';
    myEep.uuid[14] = '0';
    myEep.uuid[15] = '0';
    myEep.pid = 0x04;
    myEep.vslen = 32;
    myEep.pslen = 32;
    strcpy(myEep.vstr, "land.boards.com");
    strcpy(myEep.pstr, "OptoOut8-I2C");

    eeprom.writeBlock(0, (const uint8_t*) myEep.signature, 96);
    delay(10);

    eeprom.readBlock((const uint16_t) 0, (unsigned char*) readBuff, (const uint16_t) 96);

    setDisplayCursor(1, 0);
    for (int loopv = 0; loopv < 4; loopv++)
      u8g.print(readBuff[loopv]);
    setDisplayCursor(2, 0);
    for (int loopv = 32; loopv < 44; loopv++)
      u8g.print(readBuff[loopv]);
    setDisplayCursor(3, 0);
    for (int loopv = 64; loopv < 76; loopv++)
      u8g.print(readBuff[loopv]);
  }
  while ( u8g.nextPage() );
  while (menuCard.pollKeypad() == NONE);
  menuCard.setLED(1, LOW);
}

void testButtons(void)
{
  uint8_t keyState;
  u8g.firstPage();
  do
  {
    setDisplayCursor(0, 0);
    u8g.print(F("Button tests"));
    setDisplayCursor(1, 0);
    u8g.print(F("Press button"));
    setDisplayCursor(2, 0);
    u8g.print(F("Select=exit"));
  }
  while ( u8g.nextPage() );
  do
  {
    delay(100);
    keyState = menuCard.pollKeypad();
    switch (keyState)
    {
      case RIGHT:
        printString("Right button");
        break;
      case LEFT:
        printString("Left Button");
        break;
      case UP:
        printString("Up button");
        break;
      case DOWN:
        printString("Down button");
        break;
    }
  }
  while (keyState != SELECT);
}

void printString(char * myString)
{
  u8g.firstPage();
  do
  {
    setDisplayCursor(0, 0);
    u8g.print(myString);
  }
  while ( u8g.nextPage() );
}

void testLEDsFcn(void)
{
  u8g.firstPage();
  do
  {
    setDisplayCursor(0, 0);
    u8g.print(F("Running"));
    setDisplayCursor(1, 0);
    u8g.print(F("LED Tests"));
  }
  while ( u8g.nextPage() );
  menuCard.setLED(0, HIGH);
  delay(500);
  menuCard.setLED(0, LOW);
  menuCard.setLED(1, HIGH);
  delay(500);
  menuCard.setLED(1, LOW);
  menuCard.setLED(2, HIGH);
  delay(500);
  menuCard.setLED(2, LOW);
}

