/////////////////////////////////////////////////////////////////////////////
// MenuCodeOps() - Run the OptoOut8-I2C card tests
//////////////////////////////////////////////////////////////////////////////

void testOO8board(void)
{
  mux.setI2CChannel(SEL_OLED);
  u8g.firstPage();
  do
  {
    setDisplayCursor(0, 0);
    u8g.print("Digo16 Test");
    setDisplayCursor(2, 0);
    u8g.print("Hold any key");
    setDisplayCursor(3, 1);
    u8g.print(" to stop");
  }
  while ( u8g.nextPage() );

  do
  {
    mux.setI2CChannel(SEL_DIGIO16);
    uint8_t chip;
    uint8_t port;

    for (port = 0; port < 16; port++)
    {
      mcp0.digitalWrite(port, HIGH);
      delay(250);
      mcp0.digitalWrite(port, LOW);
      //      delay(250);
    }
    mux.setI2CChannel(SEL_OLED);
  }
  while (menuCard.pollKeypad() == NONE);

}

//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//

void readEEPROM(void)
{
//  eep_vals myEep;
  char readBuff[97];
  readBuff[96] = 0;
  mux.setI2CChannel(SEL_DIGIO16);
  eeprom.begin();
  eeprom.readBlock((const uint16_t) 0, (unsigned char*) readBuff, (const uint16_t) 96);
  mux.setI2CChannel(SEL_OLED);
  menuCard.setLED(1, HIGH);
  u8g.firstPage();
  do
  {
    setDisplayCursor(0, 0);
    u8g.print("Read EEPROM");
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
  menuCard.setLED(2, LOW);
}

//////////////////////////////////////////////////////////////////////////////
// writeEEPROM()
//////////////////////////////////////////////////////////////////////////////

void writeEEPROM(void)
{
  eep_vals myEep;
  char readBuff[97];
  readBuff[96] = 0;
  myEep.signature[0] = 'O';
  myEep.signature[1] = 'D';
  myEep.signature[2] = 'A';
  myEep.signature[3] = 'S';
  myEep.fmt_version = 0x01;
  myEep.rsvd = 0;
  myEep.numatoms = 0x2;
  myEep.eeplen = 96;
  myEep.uuid[0] = '0'; //Serial number
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
  strcpy(myEep.pstr, "DigIO16-I2C");
  mux.setI2CChannel(SEL_DIGIO16);
  eeprom.begin();
  eeprom.writeBlock(0, (const uint8_t*) myEep.signature, 96);
  delay(10);
  eeprom.readBlock((const uint16_t) 0, (unsigned char*) readBuff, (const uint16_t) 96);
  mux.setI2CChannel(SEL_OLED);
  menuCard.setLED(1, HIGH);
  u8g.firstPage();
  do
  {
    setDisplayCursor(0, 0);
    u8g.print("Wrote EEPROM");

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

