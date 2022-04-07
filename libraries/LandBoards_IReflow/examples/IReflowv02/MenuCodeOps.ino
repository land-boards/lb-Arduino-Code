//////////////////////////////////////////////////////////////////////////////
// MenuCodeOps() - Run the IReflow Menu Functions
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// runProfileFcn() - Run the selected Profile
// profileSelected - global which tells which soldering profile was selected
// Function uses a piecewise linear solution
// Can exit function by pressing any key on the keypad
// Also exits at 600 seconds
//////////////////////////////////////////////////////////////////////////////

#define LOOP_TIME 100     // the delay (in mS) between samples and on/off cycles

void runProfileFcn(void)
{
  double myTemp;
  double goalTemp;
  uint8_t keyState;
  menuCard.setLED(1, HIGH);
  u8x8.clear();
  setTime(0);
  time_t t = now();
  do
  {
    u8x8.setFont(u8x8_font_amstrad_cpc_extended_r);
    if (profileSelected == LEAD_FREE)
      u8x8.drawString(0, 0, "Lead-Free Cycle");
    else if (profileSelected == LEADED)
      u8x8.drawString(0, 0, "Leaded Cycle");
    else
    {
      u8x8.drawString(0, 0, "Must first");
      u8x8.drawString(1, 1, "select profile");
      u8x8.setFont(u8x8_font_chroma48medium8_r);
      u8x8.drawString(0, 3, "SELECT=EXIT");
      while (menuCard.pollKeypad() != SELECT);
      return;
    }
    myTemp = thermocouple.readCelsius();
    u8x8.setFont(u8x8_font_chroma48medium8_r);
    u8x8.drawString(0, 1, "Meas=");
    u8x8.setCursor(5, 1);
    u8x8.print(myTemp);
    if (profileSelected == LEAD_FREE)
    {
      goalTemp = getDesiredTempLeadFree(60 * minute(t) + second(t));
    }
    else if (profileSelected == LEADED)
    {
      goalTemp = getDesiredTempLeaded(60 * minute(t) + second(t));
    }
    else
    {
      goalTemp = -10.0;
    }
    u8x8.drawString(0, 2, "Goal=     ");
    u8x8.setCursor(5, 2);
    u8x8.print(goalTemp);
    if (myTemp > goalTemp)
    {
      u8x8.drawString(0, 3, "SSR=Off");
      digitalWrite(SSR, LOW);
      menuCard.setLED(2, LOW);
    }
    else
    {
      u8x8.drawString(0, 3, "SSR=On ");
      digitalWrite(SSR, HIGH);
      menuCard.setLED(2, HIGH);
    }
    u8x8.drawString(0, 4, "Time=     ");
    u8x8.setCursor(5, 4);
    u8x8.print((60 * minute(t)) + second(t));
    delay(LOOP_TIME);
    t = now();
    keyState = menuCard.pollKeypad();   // Select key exits
  }
  while ( (keyState != SELECT) && (t < 600));
  digitalWrite(SSR, LOW);
  menuCard.setLED(1, LOW);
  menuCard.setLED(2, LOW);
}

//////////////////////////////////////////////////////////////////////////////
// monTempFcn()
//////////////////////////////////////////////////////////////////////////////

void monTempFcn(void)
{
  double myTemp;
  uint8_t keyState;
  menuCard.setLED(0, HIGH);
  u8x8.clear();
  setTime(0);
  time_t t = now();
  do
  {
    myTemp = thermocouple.readCelsius();
    if (isnan(myTemp) == 1)
      {
        u8x8.drawString(0,0,"Error Reading");
        u8x8.drawString(1,1,"Thermocouple");
        delay(1000);
        return;
      }
    u8x8.drawString(0, 0, "Temp=");
    u8x8.setCursor(5, 0);
    u8x8.print(myTemp);
    u8x8.drawString(0, 1, "Time=");
    u8x8.setCursor(5, 1);
    u8x8.print((60 * minute(t)) + second(t));
    delay(100);
    t = now();
    keyState = menuCard.pollKeypad();
  }
  while (keyState != SELECT);
  menuCard.setLED(0, LOW);
}

//////////////////////////////////////////////////////////////////////////////
// LeadFreeFcn()
//////////////////////////////////////////////////////////////////////////////

void LeadFreeFcn(void)
{
  u8x8.clear();
  profileSelected = LEAD_FREE;
  digitalWrite(GRN_LITE, LOW);
  u8x8.drawString(0, 1, "Lead free");
  u8x8.drawString(0, 2, "profile");
  u8x8.drawString(0, 3, "selected");
  delay(2000);
  delay(500);
  digitalWrite(GRN_LITE, HIGH);
}

//////////////////////////////////////////////////////////////////////////////
// LeadFcn()
//////////////////////////////////////////////////////////////////////////////

void LeadFcn(void)
{
  u8x8.clear();
  profileSelected = LEADED;
  digitalWrite(GRN_LITE, LOW);
  u8x8.drawString(0, 1, "Lead profile");
  u8x8.drawString(0, 2, "selected");
  delay(2000);
  delay(500);
  digitalWrite(GRN_LITE, HIGH);
}

//////////////////////////////////////////////////////////////////////////////
// testButtons()
//////////////////////////////////////////////////////////////////////////////

void testButtons(void)
{
  u8x8.clear();
  uint8_t keyState;
  u8x8.drawString(0, 1, "Button tests"); // write something to the internal memory
  u8x8.drawString(0, 2, "Press button"); // write something to the internal memory
  u8x8.drawString(0, 3, "Select=exit"); // write something to the internal memory

  do
  {
    delay(100);
    keyState = menuCard.pollKeypad();
    switch (keyState)
    {
      case RIGHT:
        u8x8.drawString(0, 4, "Right button"); // write something to the internal memory
        break;
      case LEFT:
        u8x8.drawString(0, 4, "Left Button "); // write something to the internal memory
        break;
      case UP:
        u8x8.drawString(0, 4, "Up Button   "); // write something to the internal memory
        break;
      case DOWN:
        u8x8.drawString(0, 4, "Down Button "); // write something to the internal memory
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
  u8x8.drawString(0, 1, "Running"); // write something to the internal memory
  u8x8.drawString(0, 2, "LED Tests"); // write something to the internal memory
  u8x8.drawString(0, 3, "Select=exit"); // write something to the internal memory
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

