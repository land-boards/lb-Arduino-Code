/*
 IReflowv01.ino
*/

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
} myRprfiles;


//////////////////////////////////////////////////////////////////////////////
// Global variables follow
//////////////////////////////////////////////////////////////////////////////

uint8_t menuState;              // Menu State variable

LandBoards_IReflow myIReflow;

U8X8_SSD1306_128X64_NONAME_HW_I2C u8x8(/* reset=*/ U8X8_PIN_NONE, /* clock=*/ SCL, /* data=*/ SDA);   // OLEDs without Reset of the Display

LandBoards_MyMenu menuCard;

myRprfiles profileSelected;

void setup(void) 
{
  profileSelected = NO_PROFILE;
  menuState = FIRST_LINE_MENU;  // Set up the init menu state
  myIReflow.redLED(LOW);
  delay(250);
  myIReflow.redLED(HIGH);
  myIReflow.greenLED(LED_ON);
  delay(100);
  myIReflow.greenLED(LED_OFF);
  menuCard.begin();
  TWBR = 12;
  Serial.begin(9600);
  time_t t = now();
  delay(100);
//  Serial.println("Hey");
  u8x8.setI2CAddress(0x78);
  u8x8.begin();
  TWBR = 12;                    // 400 KHz I2C
  u8x8.setFont(u8x8_font_chroma48medium8_r);
  u8x8.drawString(0,1,"888!");

}

void loop(void) 
{
  menuRefresh();
  menuNav();
}


