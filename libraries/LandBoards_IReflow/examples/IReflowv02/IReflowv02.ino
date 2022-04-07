/*
 IReflowv01.ino
*/

#include <Arduino.h>
#include <Time.h>
#include <TimeLib.h>
#include "Wire.h"
#include <SPI.h>

#include "LandBoards_IReflow.h"
#include "LandBoards_MyMenu.h"

#include <U8x8lib.h>

#include "Adafruit_MAX31855.h"

#define CS   9
Adafruit_MAX31855 thermocouple(CS);

double getDesiredTempLeadFree(int);
double getDesiredTempLeaded(int);

//////////////////////////////////////////////////////////////////////////////
// enums follow
//////////////////////////////////////////////////////////////////////////////

enum MENUITEMS
{
  FIRST_LINE_MENU,
  SECOND_LINE_MENU,
  THIRD_LINE_MENU,
  FOURTH_LINE_MENU,
  FIRST_SUB_MENU,
  SECOND_SUB_MENU,
  FSTL_TESTS_MENU,
  SCND_TESTS_MENU
};

typedef enum PROFILES
{
  NO_PROFILE,
  LEAD_FREE,
  LEADED
} myProfiles;


//////////////////////////////////////////////////////////////////////////////
// Global variables follow
//////////////////////////////////////////////////////////////////////////////

uint8_t menuState;              // Menu State variable

LandBoards_IReflow myIReflow;

U8X8_SSD1306_128X64_NONAME_HW_I2C u8x8(U8X8_PIN_NONE, SCL, SDA);   // OLEDs without Reset of the Display

LandBoards_MyMenu menuCard;                // MyMenu card by Land Boards, LLC

myProfiles profileSelected;

//////////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////////

void setup(void) 
{
  profileSelected = NO_PROFILE;
  menuState = FIRST_SUB_MENU;  // Pick profile first
  myIReflow.redLED(LOW);
  delay(250);
  myIReflow.redLED(HIGH);
  myIReflow.greenLED(LED_ON);
  delay(100);
  myIReflow.greenLED(LED_OFF);
  menuCard.begin(1);
  TWBR = 12;
  time_t t = now();
  u8x8.setI2CAddress(0x78);
  u8x8.begin();
  TWBR = 12;                    // 400 KHz I2C
  u8x8.setFont(u8x8_font_chroma48medium8_r);
  u8x8.draw2x2String(0, 2, "IReflow");
  u8x8.draw2x2String(0, 4, "   v2");
  delay(2000);

}

//////////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////////

void loop(void) 
{
  u8x8.clear();
  menuRefresh();
  menuNav();
}

