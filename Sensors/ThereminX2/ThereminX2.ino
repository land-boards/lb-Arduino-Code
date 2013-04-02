//////////////////////////////////////////////////////////////////////////////
//
// Theremin - Theremin software
//
// Hardware -
//  Microprocessor Board is a Integrated Theremin
//   ------> http://dougspcbdesigns.pbworks.com/IntegTheremin
//  Keypad is a 5-way switch
//   ------> http://dougspcbdesigns.pbworks.com/w/page/55033879/Sw5Way
//  IR Sensor is a 
//   ------> http://dougspcbdesigns.pbworks.com/IR%20Sensor
//  Display is a 
//   ------> http://myarduino.pbworks.com/w/page/53173808/TFT_Display1p8in
//  This sketch works with the library for the Adafruit 1.8" TFT Breakout
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// Includes follow
//////////////////////////////////////////////////////////////////////////////

#include <SPI.h>
#include <EEPROM.h>
#include <MiniDuino.h>       // MiniDuino board library
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library
#include <EEPROMAnything.h>

#define VOLDAT	2
#define FREQDAT	3
#define CLK	4
#define SYNC0	5

//////////////////////////////////////////////////////////////////////////////
//#define SERIAL_OUT
//////////////////////////////////////////////////////////////////////////////

//#define SERIAL_OUT
#undef SERIAL_OUT

//////////////////////////////////////////////////////////////////////////////
// enums follow
//////////////////////////////////////////////////////////////////////////////

// MENU_ITEMS needs to be ordered to match the order on the menu

enum MENUITEMS
{
  THEREMIN_MENU,
  CALIBR_MENU,
  CAL_LEV_MENU,
  VIEWCAL_MENU,
  TESTKEYPAD_MENU,
  TESTIR_MENU,
  SETVOL_MENU,
  SETFRQ_MENU,
};

//////////////////////////////////////////////////////////////////////////////
// defines follow
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// Global variables follow
//////////////////////////////////////////////////////////////////////////////

int menuState;  // Used to implement the menuing state machine

int lastVol;    // The last volume that was sent to the HV Pot
int lastFreq;   // The last frequency that was sent to the HV Pot
int freq1024;    // The current value of the frequency to be send to the HV Pot
int vol1024;     // The current value of the volume to be send to the HV Pot

//////////////////////////////////////////////////////////////////////////////
// IR Configuration stored in EEPROM
// Stores the high and low position of the hand with respect to the IR sensors.
// This allows the Theremin to come up on a state where it is running without
// any calibration in known states.
//////////////////////////////////////////////////////////////////////////////

struct IR_Cfgs_t
{
  int freqLoEE;
  int freqHiEE;
  int volLoEE;
  int volHiEE;
  int levelCal;
} IRConfigs;

//////////////////////////////////////////////////////////////////////////////
// class initializers
//////////////////////////////////////////////////////////////////////////////

Adafruit_ST7735 tft = Adafruit_ST7735(LCD_CS, LCD_DC, LCD_RST);
MiniDuino myMiniDuino;

//////////////////////////////////////////////////////////////////////////////
// setup()
//////////////////////////////////////////////////////////////////////////////

void setup()  
{
#ifdef SERIAL_OUT
  Serial.begin(9600);
#endif

  pinMode(VOLDAT, OUTPUT);
  pinMode(FREQDAT, OUTPUT);
  pinMode(CLK, OUTPUT);
  pinMode(SYNC0, OUTPUT);
  digitalWrite(VOLDAT, LOW);
  digitalWrite(FREQDAT, LOW);
  digitalWrite(SYNC0, HIGH);
  digitalWrite(CLK, HIGH);
  delay(1);
  enableRDAC();
  // Turn down the volume initially
  vol1024 = 0;
  freq1024 = 0;
  setHVPots();
  lastVol = 0;
  lastFreq = 0;

  menuState = THEREMIN_MENU;

  tft.initR(INITR_REDTAB);
  tft.setTextSize(1);
  tft.fillScreen(ST7735_BLACK);
  tft.setCursor(0, 0);
  tft.setTextColor(ST7735_WHITE,ST7735_BLACK);
  
  EEPROM_readAnything(0, IRConfigs);
  
  menuRefresh();

}

//////////////////////////////////////////////////////////////////////////////
// loop()
//////////////////////////////////////////////////////////////////////////////

void loop()                     // run over and over again
{
  menuRefresh();
  menuNav();
#ifdef SERIAL_OUT
  Serial.println(pitch);
  Serial.println(vol);
#endif
}

//////////////////////////////////////////////////////////////////////////////////////
// setCursorTFT(int row, int col)
//////////////////////////////////////////////////////////////////////////////////////

void setCursorTFT(int row, int col)
{
  tft.setCursor(col*6, row*10);
}

