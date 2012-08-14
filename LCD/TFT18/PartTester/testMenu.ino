////////////////////////////////////////////////////////////
// testMenu() - 
////////////////////////////////////////////////////////////

const char * menuHeader     = "** Test Menu **";
const char * menuTestKeypad = "Test Keypad ------A0";
const char * menuTest1Wire  = "Test 1-Wire Sens -D6";
const char * menuTestTMP36  = "Test TMP36 sensor A1";
const char * menuTestLDR    = "Test LDR sensor --A1";
const char * menuTestLED    = "Test GVS LED -----D6";
const char * menuTestRelay  = "Test 2 ch relay D2.3";

void testMenu(void)
{
  int pressedKey = myMiniDuino.pollKeypad();
  if (pressedKey != NONE)
    while (myMiniDuino.pollKeypad() != NONE);
  switch (menuState)
  {
  case MENU0:
    tft.fillScreen(ST7735_BLACK);
    displayMenuLine(0,ST7735_WHITE,ST7735_BLACK,(char *) menuHeader,0);
    displayMenuLine(1,ST7735_WHITE,ST7735_BLUE,(char *) menuTestKeypad,1);
    displayMenuLine(2,ST7735_WHITE,ST7735_BLACK,(char *) menuTest1Wire,0);
    displayMenuLine(3,ST7735_WHITE,ST7735_BLACK,(char *) menuTestTMP36,0);
    displayMenuLine(4,ST7735_WHITE,ST7735_BLACK,(char *) menuTestLDR,0);
    displayMenuLine(5,ST7735_WHITE,ST7735_BLACK,(char *) menuTestLED,0);
    displayMenuLine(6,ST7735_WHITE,ST7735_BLACK,(char *) menuTestRelay,0);
    menuState = MENU1;
    break;
  case MENU1:
    if (pressedKey != NONE)
    {
      switch (pressedKey)
      {
      case DOWN:
        menuState = MENU2;
        break;
      case SELECT:
      case RIGHT:
        menuState = MENU10;
        break;
      }
    } 
    break;
  case MENU2:
    tft.fillScreen(ST7735_BLACK);
    displayMenuLine(0,ST7735_WHITE,ST7735_BLACK,(char *) menuHeader,0);
    displayMenuLine(1,ST7735_WHITE,ST7735_BLACK,(char *) menuTestKeypad,1);
    displayMenuLine(2,ST7735_WHITE,ST7735_BLUE,(char *) menuTest1Wire,0);
    displayMenuLine(3,ST7735_WHITE,ST7735_BLACK,(char *) menuTestTMP36,0);
    displayMenuLine(4,ST7735_WHITE,ST7735_BLACK,(char *) menuTestLDR,0);
    displayMenuLine(5,ST7735_WHITE,ST7735_BLACK,(char *) menuTestLED,0);
    displayMenuLine(6,ST7735_WHITE,ST7735_BLACK,(char *) menuTestRelay,0);
    menuState = MENU3;
    break;
  case MENU3:
    if (pressedKey != NONE)
    {
      switch (pressedKey)
      {
      case DOWN:
        menuState = MENU4;
        break;
      case UP:
        menuState = MENU0;
        break;
      case SELECT:
      case RIGHT:
        menuState = MENU20;
        break;
      }
    } 
    break;
  case MENU4:
    tft.fillScreen(ST7735_BLACK);
    displayMenuLine(0,ST7735_WHITE,ST7735_BLACK,(char *) menuHeader,0);
    displayMenuLine(1,ST7735_WHITE,ST7735_BLACK,(char *) menuTestKeypad,1);
    displayMenuLine(2,ST7735_WHITE,ST7735_BLACK,(char *) menuTest1Wire,0);
    displayMenuLine(3,ST7735_WHITE,ST7735_BLUE,(char *) menuTestTMP36,0);
    displayMenuLine(4,ST7735_WHITE,ST7735_BLACK,(char *) menuTestLDR,0);
    displayMenuLine(5,ST7735_WHITE,ST7735_BLACK,(char *) menuTestLED,0);
    displayMenuLine(6,ST7735_WHITE,ST7735_BLACK,(char *) menuTestRelay,0);
    menuState = MENU5;
    break;
  case MENU5:
    if (pressedKey != NONE)
    {
      switch (pressedKey)
      {
      case DOWN:
        menuState = MENU6;
        break;
      case SELECT:
      case RIGHT:
        menuState = MENU30;
        break;
      case UP:
        menuState = MENU2;
        break;
      }
    } 
    break;
  case MENU6:
    tft.fillScreen(ST7735_BLACK);
    displayMenuLine(0,ST7735_WHITE,ST7735_BLACK,(char *) menuHeader,0);
    displayMenuLine(1,ST7735_WHITE,ST7735_BLACK,(char *) menuTestKeypad,1);
    displayMenuLine(2,ST7735_WHITE,ST7735_BLACK,(char *) menuTest1Wire,0);
    displayMenuLine(3,ST7735_WHITE,ST7735_BLACK,(char *) menuTestTMP36,0);
    displayMenuLine(4,ST7735_WHITE,ST7735_BLUE,(char *) menuTestLDR,0);
    displayMenuLine(5,ST7735_WHITE,ST7735_BLACK,(char *) menuTestLED,0);
    displayMenuLine(6,ST7735_WHITE,ST7735_BLACK,(char *) menuTestRelay,0);
    menuState = MENU7;
    break;
  case MENU7:
    if (pressedKey != NONE)
    {
      switch (pressedKey)
      {
      case DOWN:
        menuState = MENU8;
        break;
      case SELECT:
      case RIGHT:
        menuState = MENU40;
        break;
      case UP:
        menuState = MENU4;
        break;
      }
    } 
    break;
  case MENU8:
    tft.fillScreen(ST7735_BLACK);
    displayMenuLine(0,ST7735_WHITE,ST7735_BLACK,(char *) menuHeader,0);
    displayMenuLine(1,ST7735_WHITE,ST7735_BLACK,(char *) menuTestKeypad,1);
    displayMenuLine(2,ST7735_WHITE,ST7735_BLACK,(char *) menuTest1Wire,0);
    displayMenuLine(3,ST7735_WHITE,ST7735_BLACK,(char *) menuTestTMP36,0);
    displayMenuLine(4,ST7735_WHITE,ST7735_BLACK,(char *) menuTestLDR,0);
    displayMenuLine(5,ST7735_WHITE,ST7735_BLUE,(char *) menuTestLED,0);
    displayMenuLine(6,ST7735_WHITE,ST7735_BLACK,(char *) menuTestRelay,0);
    menuState = MENU9;
    break;
  case MENU9:
    if (pressedKey != NONE)
    {
      switch (pressedKey)
      {
      case SELECT:
      case RIGHT:
        menuState = MENU50;
        break;
      case DOWN:
        menuState = MENU12;
        break;
      case UP:
        menuState = MENU6;
        break;
      }
    } 
    break;
  case MENU10:
    tft.fillScreen(ST7735_BLACK);
    setCursorTFT(0,0);
    tft.setTextColor(ST7735_WHITE,ST7735_BLACK);
    tft.print("Testing Keypad");
    setCursorTFT(1,0);
    tft.setTextColor(ST7735_WHITE,ST7735_BLACK);
    tft.print("Hold SELECT to exit");
    menuState = MENU11;
    break;
  case MENU11:
    {
      long loopCount = 0;
      int key;
      tft.setTextColor(ST7735_WHITE,ST7735_BLACK);
      while (loopCount < 100)
      {
        key = myMiniDuino.pollKeypad();
        setCursorTFT(2,0);
        switch (key)
        {
        case NONE:
          tft.print("NONE  ");
          loopCount = 0;
          break;
        case LEFT:
          tft.print("LEFT  ");
          loopCount = 0;
          break;
        case RIGHT:
          tft.print("RIGHT ");
          loopCount = 0;
          break;
        case UP:
          tft.print("UP    ");
          loopCount = 0;
          break;
        case DOWN:
          tft.print("DOWN  ");
          loopCount = 0;
          break;
        case SELECT:
          tft.print("SELECT");
          loopCount++;
          break;
        }
      }
      setCursorTFT(3,0);
      tft.print("EXITING, release Sel");
      while (myMiniDuino.pollKeypad() == SELECT);
      menuState = MENU0;
    }
    break;

  case MENU12:
    tft.fillScreen(ST7735_BLACK);
    displayMenuLine(0,ST7735_WHITE,ST7735_BLACK,(char *) menuHeader,0);
    displayMenuLine(1,ST7735_WHITE,ST7735_BLACK,(char *) menuTestKeypad,1);
    displayMenuLine(2,ST7735_WHITE,ST7735_BLACK,(char *) menuTest1Wire,0);
    displayMenuLine(3,ST7735_WHITE,ST7735_BLACK,(char *) menuTestTMP36,0);
    displayMenuLine(4,ST7735_WHITE,ST7735_BLACK,(char *) menuTestLDR,0);
    displayMenuLine(5,ST7735_WHITE,ST7735_BLACK,(char *) menuTestLED,0);
    displayMenuLine(6,ST7735_WHITE,ST7735_BLUE,(char *) menuTestRelay,0);
    menuState = MENU13;
    break;
  case MENU13:
    if (pressedKey != NONE)
    {
      switch (pressedKey)
      {
      case SELECT:
      case RIGHT:
        menuState = MENU60;
        break;
      case UP:
        menuState = MENU6;
        break;
      }
    } 
    break;
  case MENU14:
    tft.fillScreen(ST7735_BLACK);
    setCursorTFT(0,0);
    tft.setTextColor(ST7735_WHITE,ST7735_BLACK);
    tft.print("Testing Keypad");
    setCursorTFT(1,0);
    tft.setTextColor(ST7735_WHITE,ST7735_BLACK);
    tft.print("Hold SELECT to exit");
    menuState = MENU11;
    break;


  case MENU20:
    tft.fillScreen(ST7735_BLACK);
    setCursorTFT(0,0);
    tft.setTextColor(ST7735_WHITE,ST7735_BLACK);
    tft.print("Testing 1-Wire");
    menuState = MENU21;
    break;
  case MENU21:
    read1Wire();
    if (pressedKey != NONE)
      menuState = MENU2;
    break;
  case MENU30:
    tft.fillScreen(ST7735_BLACK);
    setCursorTFT(0,0);
    tft.setTextColor(ST7735_WHITE,ST7735_BLACK);
    tft.print("Testing TMP36A");
    menuState = MENU31;
    break;
  case MENU31:
    {
      setCursorTFT(1,0);
      int tmpAna;
      tmpAna = analogRead(ANALOGIN1);
      tft.print(tmpAna);
      tft.print("   ");
      if (pressedKey != NONE)
        menuState = MENU4;
    }
    break;
  case MENU40:
    tft.fillScreen(ST7735_BLACK);
    setCursorTFT(0,0);
    tft.setTextColor(ST7735_WHITE,ST7735_BLACK);
    tft.print("Testing LDR");
    menuState = MENU41;
    break;
  case MENU41:
    {
      setCursorTFT(1,0);
      int tmpAna;
      tmpAna = analogRead(ANALOGIN1);
      tft.print(tmpAna);
      tft.print("   ");
      if (pressedKey != NONE)
        menuState = MENU6;
      break;
    }
  case MENU50:
    tft.fillScreen(ST7735_BLACK);
    setCursorTFT(0,0);
    tft.setTextColor(ST7735_WHITE,ST7735_BLACK);
    tft.print("Testing LED");
    menuState = MENU51;
    pinMode(DIGIO6, OUTPUT);
    break;
  case MENU51:
    {
      setCursorTFT(1,0);
      digitalWrite(DIGIO6, HIGH);   // turn the LED off
      if (myMiniDuino.delayAvailable(1000) != 0)
        menuState = MENU8;               // wait for a second
      digitalWrite(DIGIO6, LOW);    // turn the LED on
      if (myMiniDuino.delayAvailable(1000) != 0)
        menuState = MENU8;               // wait for a second
      if (menuState == MENU8)
        digitalWrite(DIGIO6, HIGH);
      break;
    }
  case MENU60:
    tft.fillScreen(ST7735_BLACK);
    setCursorTFT(0,0);
    tft.setTextColor(ST7735_WHITE,ST7735_BLACK);
    tft.print("Testing Relays");
    menuState = MENU61;
    pinMode(2, OUTPUT);
    pinMode(3, OUTPUT);
    break;
  case MENU61:
    {
      setCursorTFT(1,0);
      digitalWrite(2, LOW);    // turn the LED on
      if (myMiniDuino.delayAvailable(1000) != 0)
        menuState = MENU12;               // wait for a second
      digitalWrite(2, HIGH);   // turn the LED off
      if (myMiniDuino.delayAvailable(1000) != 0)
        menuState = MENU12;               // wait for a second
      digitalWrite(3, LOW);    // turn the LED on
      if (myMiniDuino.delayAvailable(1000) != 0)
        menuState = MENU12;               // wait for a second
      digitalWrite(3, HIGH);   // turn the LED off
      if (myMiniDuino.delayAvailable(1000) != 0)
        menuState = MENU12;               // wait for a second
      if (menuState == MENU12)
      {
        digitalWrite(2, HIGH);
        digitalWrite(3, HIGH);
      }
      break;
    }
  }
}

////////////////////////////////////////////////////////////
// displayMenuLine
////////////////////////////////////////////////////////////

void displayMenuLine(int row, int fontColor, int backgroundColor, char * menuString, int selected)
{
  setCursorTFT(row,0);
  tft.setTextColor(fontColor,backgroundColor);
  tft.print(menuString);
  return;
}

