//////////////////////////////////////////////////////////////////////////////
// MenuCodeOps() - Customize this code for the specific operations
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// testButtons() - Test the MyMenu system buttons
//////////////////////////////////////////////////////////////////////////////

void testButtons(void)
{
  uint8_t keyState;
  u8x8.clear();
  u8x8.drawString(0,1,"Button tests");  // write something to the internal memory
  u8x8.drawString(0,2,"Press button");  // write something to the internal memory
  u8x8.drawString(0,3,"Select=exit");  // write something to the internal memory

  do
  {
    delay(100);
    keyState = menuCard.pollKeypad();
    switch (keyState)
    {
      case RIGHT:
        u8x8.drawString(0,4,"Right button");  // write something to the internal memory
        break;
      case LEFT:
        u8x8.drawString(0,4,"Left Button ");  // write something to the internal memory
        break;
      case UP:
        u8x8.drawString(0,4,"Up Button   ");  // write something to the internal memory
        break;
      case DOWN:
        u8x8.drawString(0,4,"Down Button ");  // write something to the internal memory
        break;
    }
  }
  while (keyState != SELECT);
}

//////////////////////////////////////////////////////////////////////////////
// testLEDsFcn() - Test the MyMenu system LEDs
//////////////////////////////////////////////////////////////////////////////

void testLEDsFcn(void)
{
  u8x8.clear();
  u8x8.drawString(0,1,"Running");  // write something to the internal memory
  u8x8.drawString(0,2,"LED Tests");  // write something to the internal memory
  u8x8.drawString(0,3,"Select=exit");  // write something to the internal memory
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
