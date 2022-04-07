// ----------------------------------------------------------------------------
// Reflow Oven Controller
// (c) 2014 Karl Pitrich <karl@pitrich.com>
// (c) 2012-2013 Ed Simmons
// ----------------------------------------------------------------------------

//#define FAKE_HW 1
//#define PIDTUNE 1 // autotune wouldn't fit in the 28k available on my arduino pro micro.

// run a calibration loop that measures how many timer ticks occur between 2 zero corssings
// FIXME: does not work reliably at the moment, so a oscilloscope-determined value is used.
//#define WITH_CALIBRATION 1 // loop timing calibration
#define DEFAULT_LOOP_DELAY 89 // should be about 16% less for 60Hz mains

#include <avr/eeprom.h>
#include <EEPROM.h>
#include <PID_v1.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>
#include <Menu.h>
#include <TimerOne.h>
#include <ClickEncoder.h>
#include "temperature.h"
#include "helpers.h"
#ifdef FAKE_HW
#include <TimerThree.h>
#endif
#ifdef PIDTUNE
#include <PID_AutoTune_v0.h>
#endif
// ----------------------------------------------------------------------------

const char * ver = "3.1";

// ----------------------------------------------------------------------------

#define MS_PER_SINE 100       // for 50Hz mains; 100ms per sinusoid
//#define MS_PER_SINE  83.333 // for 60Hz Mains; 83,3333ms per sinusoid

// ----------------------------------------------------------------------------
// Hardware Configuration 

// 1.8" TFT via SPI -> breadboard
#ifdef FAKE_HW
#define LCD_CS  10
#define LCD_DC   7
#define LCD_RST  8
#else 
#define LCD_CS   10
#define LCD_DC   9
#define LCD_RST  8
#endif

// Thermocouple via SPI
#define THERMOCOUPLE1_CS  3

#define PIN_HEATER   0 // SSR for the heater
#define PIN_FAN      1 // SSR for the fan

#define PIN_ZX       2 // pin for zero crossing detector
#define INT_ZX       1 // interrupt for zero crossing detector
                       // Leonardo == Pro Micro:
                       //   Pin: 3 2 0 1 7
                       //   Int: 0 1 2 3 4 

// ----------------------------------------------------------------------------

#define WITH_SPLASH 1

// ----------------------------------------------------------------------------

volatile uint32_t timerTicks     = 0;
volatile uint32_t zeroCrossTicks = 0;
volatile uint8_t  phaseCounter   = 0;

char buf[20]; // generic char buffer

// ----------------------------------------------------------------------------

// data type for the values used in the reflow profile
typedef struct profileValues_s {
  int16_t soakTemp;
  int16_t soakDuration;
  int16_t peakTemp;
  int16_t peakDuration;
  double  rampUpRate;
  double  rampDownRate;
  uint8_t checksum;
} Profile_t;

Profile_t activeProfile; // the one and only instance
int activeProfileId = 0;

int idleTemp = 50; // the temperature at which to consider the oven safe to leave to cool naturally
int fanAssistSpeed = 33; // default fan speed

const uint8_t maxProfiles = 30;

// EEPROM offsets
const uint16_t offsetFanSpeed   = maxProfiles * sizeof(Profile_t) + 1; // one byte
const uint16_t offsetProfileNum = maxProfiles * sizeof(Profile_t) + 2; // one byte
const uint16_t offsetPidConfig  = maxProfiles * sizeof(Profile_t) + 3; // sizeof(PID_t)

Thermocouple A;

// ----------------------------------------------------------------------------

uint32_t startCycleZeroCrossTicks;
uint32_t lastUpdate = 0;
uint32_t lastDisplayUpdate = 0;

// ----------------------------------------------------------------------------
// UI

// NB: Adafruit GFX ASCII-Table is bogous: https://github.com/adafruit/Adafruit-GFX-Library/issues/22
//
Adafruit_ST7735 tft = Adafruit_ST7735(LCD_CS, LCD_DC, LCD_RST);

#ifdef FAKE_HW
ClickEncoder Encoder(A0, A1, A2, 2);
#else
ClickEncoder Encoder(A1, A0, A2, 2);
#endif

Menu::Engine Engine;

int16_t encMovement;
int16_t encAbsolute;
int16_t encLastAbsolute = -1;

const uint8_t menuItemsVisible = 5;
const uint8_t menuItemHeight = 12;
bool menuUpdateRequest = true;
bool initialProcessDisplay = false;

// ----------------------------------------------------------------------------
// state machine

typedef enum {
  None     = 0,
  Idle     = 1,
  Settings = 2,
  Edit     = 3,

  UIMenuEnd = 9,

  RampToSoak = 10,
  Soak,
  RampUp,
  Peak,
  RampDown,
  CoolDown,

  Complete = 20,

  Tune = 30
} State;

State currentState  = Idle;
State previousState = Idle;
bool stateChanged = false;
uint32_t stateChangedTicks = 0;

// ----------------------------------------------------------------------------

// track menu item state to improve render preformance
typedef struct {
  const Menu::Item_t *mi;
  uint8_t pos;
  bool current;
} LastItemState_t;

LastItemState_t currentlyRenderedItems[menuItemsVisible];

void clearLastMenuItemRenderState() {
  // memset(&currentlyRenderedItems, 0xff, sizeof(LastItemState_t) * menuItemsVisible);
  for (uint8_t i = 0; i < menuItemsVisible; i++) {
    currentlyRenderedItems[i].mi = NULL;
    currentlyRenderedItems[i].pos = 0xff;
    currentlyRenderedItems[i].current = false;
  }
}

// ----------------------------------------------------------------------------

extern const Menu::Item_t miRampUpRate, miRampDnRate, miSoakTime, 
                          miSoakTemp, miPeakTime, miPeakTemp,
                          miLoadProfile, miSaveProfile,
                          miPidSettingP, miPidSettingI, miPidSettingD,
                          miFanSettings;

// ----------------------------------------------------------------------------
// PID

uint8_t fanValue;
uint8_t heaterValue;

double Setpoint;
double Input;
double Output;

typedef struct {
  double Kp;
  double Ki;
  double Kd;
} PID_t;

PID_t heaterPID = { 4.00, 0.05,  2.00 };
PID_t fanPID    = { 1.00, 0.03, 10.00 };

PID PID(&Input, &Output, &Setpoint, heaterPID.Kp, heaterPID.Ki, heaterPID.Kd, DIRECT);

#ifdef PIDTUNE
PID_ATune PIDTune(&Input, &Output);

double aTuneStep       =  50,
       aTuneNoise      =   1,
       aTuneStartValue =  50; // is set to Output, i.e. 0-100% of Heater

unsigned int aTuneLookBack = 30;
#endif

// ----------------------------------------------------------------------------

bool menuExit(const Menu::Action_t a) {
  clearLastMenuItemRenderState();
  Engine.lastInvokedItem = &Menu::NullItem;
  menuUpdateRequest = false;
  return false;
}

// ----------------------------------------------------------------------------

bool menuDummy(const Menu::Action_t a) {
  return true;
}

// ----------------------------------------------------------------------------

void printDouble(double val, uint8_t precision = 1) {
  ftoa(buf, val, precision);
  tft.print(buf);
}

// ----------------------------------------------------------------------------

void getItemValuePointer(const Menu::Item_t *mi, double **d, int16_t **i) {
  if (mi == &miRampUpRate)  *d = &activeProfile.rampUpRate;
  if (mi == &miRampDnRate)  *d = &activeProfile.rampDownRate;
  if (mi == &miSoakTime)    *i = &activeProfile.soakDuration;
  if (mi == &miSoakTemp)    *i = &activeProfile.soakTemp;
  if (mi == &miPeakTime)    *i = &activeProfile.peakDuration;
  if (mi == &miPeakTemp)    *i = &activeProfile.peakTemp;
  if (mi == &miPidSettingP) *d = &heaterPID.Kp;
  if (mi == &miPidSettingI) *d = &heaterPID.Ki;
  if (mi == &miPidSettingD) *d = &heaterPID.Kd; 
  if (mi == &miFanSettings) *i = &fanAssistSpeed;
}

// ----------------------------------------------------------------------------

bool isPidSetting(const Menu::Item_t *mi) {
  return mi == &miPidSettingP || mi == &miPidSettingI || mi == &miPidSettingD;
}

bool isRampSetting(const Menu::Item_t *mi) {
  return mi == &miRampUpRate || mi == &miRampDnRate;
}

// ----------------------------------------------------------------------------

bool getItemValueLabel(const Menu::Item_t *mi, char *label) {
  int16_t *iValue = NULL;
  double  *dValue = NULL;
  char *p;
  
  getItemValuePointer(mi, &dValue, &iValue);

  if (isRampSetting(mi) || isPidSetting(mi)) {
    p = label;
    ftoa(p, *dValue, (isPidSetting(mi)) ? 2 : 1); // need greater precision with pid values
    p = label;
    
    if (isRampSetting(mi)) {
      while(*p != '\0') p++;
      *p++ = 0xf7; *p++ = 'C'; *p++ = '/'; *p++ = 's';
      *p = '\0';
    }
  }
  else {
    if (mi == &miPeakTemp || mi == &miSoakTemp) {
      itostr(label, *iValue, "\367C");
    }
    if (mi == &miPeakTime || mi == &miSoakTime) {
      itostr(label, *iValue, "s");
    }
    if (mi == &miFanSettings) {
      itostr(label, *iValue, "%");
    }
  }

  return dValue || iValue;
}

// ----------------------------------------------------------------------------

bool editNumericalValue(const Menu::Action_t action) { 
  if (action == Menu::actionDisplay) {
    bool initial = currentState != Edit;
    currentState = Edit;

    if (initial) {
      tft.setTextColor(ST7735_BLACK, ST7735_WHITE);
      tft.setCursor(10, 80);
      tft.print("Edit & click to save.");
      Encoder.setAccelerationEnabled(true);
    }

    for (uint8_t i = 0; i < menuItemsVisible; i++) {
      if (currentlyRenderedItems[i].mi == Engine.currentItem) {
        uint8_t y = currentlyRenderedItems[i].pos * menuItemHeight + 2;

        if (initial) {
          tft.fillRect(69, y - 1, 60, menuItemHeight - 2, ST7735_RED);
        }

        tft.setCursor(70, y);
        break;
      }
    }

    tft.setTextColor(ST7735_WHITE, ST7735_RED);

    int16_t *iValue = NULL;
    double  *dValue = NULL;
    getItemValuePointer(Engine.currentItem, &dValue, &iValue);

    if (isRampSetting(Engine.currentItem) || isPidSetting(Engine.currentItem)) {
      double tmp;
      double factor = (isPidSetting(Engine.currentItem)) ? 100 : 10;
      
      if (initial) {
        tmp = *dValue;
        tmp *= factor;
        encAbsolute = (int16_t)tmp;
      }
      else {
        tmp = encAbsolute;
        tmp /= factor;
        *dValue = tmp;
      }      
    }
    else {
      if (initial) encAbsolute = *iValue;
      else *iValue = encAbsolute;
    }

    getItemValueLabel(Engine.currentItem, buf);
    tft.print(buf);
    tft.setTextColor(ST7735_BLACK, ST7735_WHITE);
  }

  if (action == Menu::actionParent || action == Menu::actionTrigger) {
    clearLastMenuItemRenderState();
    menuUpdateRequest = true;
    Engine.lastInvokedItem = &Menu::NullItem;


    if (currentState == Edit) { // leave edit mode, return to menu
      if (isPidSetting(Engine.currentItem)) {
        savePID();
      }
      else if (Engine.currentItem == &miFanSettings) {
        saveFanSpeed();
      }
      // don't autosave profile, so that one can do "save as" without overwriting the current profile

      currentState = Settings;
      Encoder.setAccelerationEnabled(false);
      return false;
    }

    return true;
  }
}

// ----------------------------------------------------------------------------

bool factoryReset(const Menu::Action_t action) {
#ifndef PIDTUNE
  if (action == Menu::actionDisplay) {
    bool initial = currentState != Edit;
    currentState = Edit;

    if (initial) { // TODO: add eyecandy: colors or icons
      tft.setTextColor(ST7735_BLACK, ST7735_WHITE);
      tft.setCursor(10, 80);
      tft.print("Click to confirm");
      tft.setCursor(10, 90);
      tft.print("Doubleclick to exit");
    }
  }

  if (action == Menu::actionTrigger) { // do it
    factoryReset();
    tft.fillScreen(ST7735_WHITE);
    Engine.navigate(Engine.getParent());
    return false;
  }

  if (action == Menu::actionParent) {
    if (currentState == Edit) { // leave edit mode only, returning to menu
      currentState = Settings;
      clearLastMenuItemRenderState();
      return false;
    }
  }
#endif // PIDTUNE
}

// ----------------------------------------------------------------------------

void saveProfile(unsigned int targetProfile, bool quiet = false);

// ----------------------------------------------------------------------------

bool saveLoadProfile(const Menu::Action_t action) {
#ifndef PIDTUNE
  bool isLoad = Engine.currentItem == &miLoadProfile;

  if (action == Menu::actionDisplay) {
    bool initial = currentState != Edit;
    currentState = Edit;

    tft.setTextColor(ST7735_BLACK, ST7735_WHITE);

    if (initial) {
      encAbsolute = activeProfileId;      
      tft.setCursor(10, 90);
      tft.print("Doubleclick to exit");
    }

    if (encAbsolute > maxProfiles) encAbsolute = maxProfiles;
    if (encAbsolute <  0) encAbsolute =  0;

    tft.setCursor(10, 80);
    tft.print("Click to ");
    tft.print((isLoad) ? "load " : "save ");
    tft.setTextColor(ST7735_WHITE, ST7735_RED);
    tft.print(encAbsolute);
  }

  if (action == Menu::actionTrigger) {
    (isLoad) ? loadProfile(encAbsolute) : saveProfile(encAbsolute);
    tft.fillScreen(ST7735_WHITE);
    Engine.navigate(Engine.getParent());
    return false;
  }

  if (action == Menu::actionParent) {    
    if (currentState == Edit) { // leave edit mode only, returning to menu
      currentState = Settings;
      clearLastMenuItemRenderState();
      return false;
    }
  }
#endif // PIDTUNE
}

// ----------------------------------------------------------------------------

void toggleAutoTune();

bool cycleStart(const Menu::Action_t action) {
  if (action == Menu::actionDisplay) {
    startCycleZeroCrossTicks = zeroCrossTicks;
    menuExit(action);

#ifndef PIDTUNE    
    currentState = RampToSoak;
#else
    toggleAutoTune();
#endif
    initialProcessDisplay = false;
    menuUpdateRequest = false;
  }

  return true;
}

// ----------------------------------------------------------------------------

void renderMenuItem(const Menu::Item_t *mi, uint8_t pos) {
  //ScopedTimer tm("  render menuitem");
  bool isCurrent = Engine.currentItem == mi;
  uint8_t y = pos * menuItemHeight + 2;

  if (currentlyRenderedItems[pos].mi == mi 
      && currentlyRenderedItems[pos].pos == pos 
      && currentlyRenderedItems[pos].current == isCurrent) 
  {
    return; // don't render the same item in the same state twice
  }

  tft.setCursor(10, y);

  // menu cursor bar
  tft.fillRect(8, y - 2, tft.width() - 16, menuItemHeight, isCurrent ? ST7735_BLUE : ST7735_WHITE);
  if (isCurrent) tft.setTextColor(ST7735_WHITE, ST7735_BLUE);
  else tft.setTextColor(ST7735_BLACK, ST7735_WHITE);

  tft.print(Engine.getLabel(mi));

  // show values if in-place editable items
  if (getItemValueLabel(mi, buf)) {
    tft.print(' '); tft.print(buf); tft.print("   ");
  }

  // mark items that have children
  if (Engine.getChild(mi) != &Menu::NullItem) {
    tft.print(" \x10   "); // 0x10 -> filled right arrow
  }

  currentlyRenderedItems[pos].mi = mi;
  currentlyRenderedItems[pos].pos = pos;
  currentlyRenderedItems[pos].current = isCurrent;
}

// ----------------------------------------------------------------------------
// Name, Label, Next, Previous, Parent, Child, Callback

MenuItem(miExit, "", Menu::NullItem, Menu::NullItem, Menu::NullItem, miCycleStart, menuExit);

#ifndef PIDTUNE
MenuItem(miCycleStart,  "Start Cycle",  miEditProfile, Menu::NullItem, miExit, Menu::NullItem, cycleStart);
#else
MenuItem(miCycleStart,  "Start Autotune",  miEditProfile, Menu::NullItem, miExit, Menu::NullItem, cycleStart);
#endif
MenuItem(miEditProfile, "Edit Profile", miLoadProfile, miCycleStart,   miExit, miRampUpRate, menuDummy);
  MenuItem(miRampUpRate, "Ramp up  ",   miSoakTemp,      Menu::NullItem, miEditProfile, Menu::NullItem, editNumericalValue);
  MenuItem(miSoakTemp,   "Soak temp", miSoakTime,      miRampUpRate,   miEditProfile, Menu::NullItem, editNumericalValue);
  MenuItem(miSoakTime,   "Soak time", miPeakTemp,      miSoakTemp,     miEditProfile, Menu::NullItem, editNumericalValue);
  MenuItem(miPeakTemp,   "Peak temp", miPeakTime,      miSoakTime,     miEditProfile, Menu::NullItem, editNumericalValue);
  MenuItem(miPeakTime,   "Peak time", miRampDnRate,    miPeakTemp,     miEditProfile, Menu::NullItem, editNumericalValue);
  MenuItem(miRampDnRate, "Ramp down", Menu::NullItem,  miPeakTime,     miEditProfile, Menu::NullItem, editNumericalValue);
MenuItem(miLoadProfile,  "Load Profile",  miSaveProfile,  miEditProfile, miExit, Menu::NullItem, saveLoadProfile);
MenuItem(miSaveProfile,  "Save Profile",  miFanSettings,  miLoadProfile, miExit, Menu::NullItem, saveLoadProfile);
MenuItem(miFanSettings,  "Fan Speed",  miPidSettings,  miSaveProfile, miExit, Menu::NullItem, editNumericalValue);
MenuItem(miPidSettings,  "PID Settings",  miFactoryReset, miFanSettings, miExit, miPidSettingP,  menuDummy);
  MenuItem(miPidSettingP,  "Heater Kp",  miPidSettingI, Menu::NullItem, miPidSettings, Menu::NullItem, editNumericalValue);
  MenuItem(miPidSettingI,  "Heater Ki",  miPidSettingD, miPidSettingP,  miPidSettings, Menu::NullItem, editNumericalValue);
  MenuItem(miPidSettingD,  "Heater Kd",  Menu::NullItem, miPidSettingI, miPidSettings, Menu::NullItem, editNumericalValue);
MenuItem(miFactoryReset, "Factory Reset", Menu::NullItem, miPidSettings, miExit, Menu::NullItem, factoryReset);

// ----------------------------------------------------------------------------

#define NUMREADINGS 10

typedef struct {
  double temp;
  uint16_t ticks;
} Temp_t;

Temp_t airTemp[NUMREADINGS];

double readingsT1[NUMREADINGS]; // the readings used to make a stable temp rolling average
double runningTotalRampRate;
double rampRate = 0;
double rateOfRise = 0;          // the result that is displayed
double totalT1 = 0;             // the running total
double averageT1 = 0;           // the average
uint8_t index = 0;              // the index of the current reading

// ----------------------------------------------------------------------------
// Ensure that Solid State Relais are off when starting
//
void setupRelayPins(void) {
  DDRD  |= (1 << 2) | (1 << 3); // output
  //PORTD &= ~((1 << 2) | (1 << 3));
  PORTD |= (1 << 2) | (1 << 3); // off
}

void killRelayPins(void) {
  Timer1.stop();
  detachInterrupt(INT_ZX);
  PORTD |= (1 << 2) | (1 << 3);
}

// ----------------------------------------------------------------------------
// wave packet control: only turn the solid state relais on for a percentage 
// of complete sinusoids (i.e. 1x 360°)

#define CHANNELS       2
#define CHANNEL_HEATER 0
#define CHANNEL_FAN    1

typedef struct Channel_s {
  volatile uint8_t target; // percentage of on-time
  uint8_t state;           // current state counter
  int32_t next;            // when the next change in output shall occur  
  bool action;             // hi/lo active
  uint8_t pin;             // io pin of solid state relais
} Channel_t;

Channel_t Channels[CHANNELS] = {
  // heater
  { 0, 0, 0, false, 2 }, // PD2 == RX == Arduino Pin 0
  // fan
  { 0, 0, 0, false, 3 }  // PD3 == TX == Arduino Pin 1
};

// delay to align relay activation with the actual zero crossing
uint16_t zxLoopDelay = 0;

#ifdef WITH_CALIBRATION
// calibrate zero crossing: how many timerIsr happen within one zero crossing
#define zxCalibrationLoops 128
struct {
  volatile int8_t iterations;
  volatile uint8_t measure[zxCalibrationLoops];
} zxLoopCalibration = {
  0, {}
};
#endif

// ----------------------------------------------------------------------------
// Zero Crossing ISR; per ZX, process one channel per interrupt only
// NB: use native port IO instead of digitalWrite for better performance
void zeroCrossingIsr(void) {
  static uint8_t ch = 0;

  // reset phase control timer
  phaseCounter = 0;
  TCNT1 = 0;

  zeroCrossTicks++;

  // calculate wave packet parameters
  Channels[ch].state += Channels[ch].target;
  if (Channels[ch].state >= 100) {
    Channels[ch].state -= 100;
    Channels[ch].action = false;
  }
  else {
    Channels[ch].action = true;
  }
  Channels[ch].next = timerTicks + zxLoopDelay; // delay added to reach the next zx

  ch = ((ch + 1) % CHANNELS); // next channel

#ifdef WITH_CALIBRATION
  if (zxLoopCalibration.iterations < zxCalibrationLoops) {
    zxLoopCalibration.iterations++;
  }
#endif
}

// ----------------------------------------------------------------------------
// timer interrupt handling

void timerIsr(void) { // ticks with 100µS
  static uint32_t lastTicks = 0;

  // phase control for the fan 
  if (++phaseCounter > 90) {
    phaseCounter = 0;
  }

  if (phaseCounter > Channels[CHANNEL_FAN].target) {
    PORTD &= ~(1 << Channels[CHANNEL_FAN].pin);
  }
  else {
    PORTD |=  (1 << Channels[CHANNEL_FAN].pin);
  }

  // wave packet control for heater
  if (Channels[CHANNEL_HEATER].next > lastTicks // FIXME: this looses ticks when overflowing
      && timerTicks > Channels[CHANNEL_HEATER].next) 
  {
    if (Channels[CHANNEL_HEATER].action) PORTD |= (1 << Channels[CHANNEL_HEATER].pin);
    else PORTD &= ~(1 << Channels[CHANNEL_HEATER].pin);
    lastTicks = timerTicks;
  }

  // handle encoder + button
  if (!(timerTicks % 10)) {
    Encoder.service();
  }

  timerTicks++;

#ifdef WITH_CALIBRATION
  if (zxLoopCalibration.iterations < zxCalibrationLoops) {
    zxLoopCalibration.measure[zxLoopCalibration.iterations]++;
  }
#endif
}

// ----------------------------------------------------------------------------

void abortWithError(int error) {
  killRelayPins();

  tft.setTextColor(ST7735_WHITE, ST7735_RED);
  tft.fillScreen(ST7735_RED);

  tft.setCursor(10, 10);
  
  if (error < 9) {
    tft.println("Thermocouple Error");
    tft.setCursor(10, 30);
    switch (error) {
      case 0b001:
        tft.println("Open Circuit");
        break;
      case 0b010:
        tft.println("GND Short");
        break;
      case 0b100:
        tft.println("VCC Short");
        break;
    }
    tft.setCursor(10, 60);
    tft.println("Power off,");
    tft.setCursor(10, 75);
    tft.println("check connections");
  }
  else {
    tft.println("Temperature"); 
    tft.setCursor(10, 30);
    tft.println("following error");
    tft.setCursor(10, 45);
    tft.print("during ");
    tft.println((error == 10) ? "heating" : "cooling");
  }

  while (1) { //  stop
    ;
  }
}

// ----------------------------------------------------------------------------

void displayThermocoupleData(struct Thermocouple* input) {
  switch (input->stat) {
    case 0:
      printDouble(input->temperature);
      tft.print("\367C");
      break;
    case 1:
      tft.print("---");
      break;
  }
}

// ----------------------------------------------------------------------------

void alignRightPrefix(uint16_t v) {
  if (v < 1e2) tft.print(' '); 
  if (v < 1e1) tft.print(' ');
}

uint16_t pxPerS;
uint16_t pxPerC;
uint16_t xOffset; // used for wraparound on x axis

void updateProcessDisplay() {
  const uint8_t h =  86;
  const uint8_t w = 160;
  const uint8_t yOffset =  30; // space not available for graph  

  uint16_t dx, dy;
  uint8_t y = 2;
  double tmp;

  // header & initial view
  tft.setTextColor(ST7735_WHITE, ST7735_BLUE);

  if (!initialProcessDisplay) {
    initialProcessDisplay = true;

    tft.fillScreen(ST7735_WHITE);
    tft.fillRect(0, 0, tft.width(), menuItemHeight, ST7735_BLUE);
    tft.setCursor(2, y);
#ifndef PIDTUNE
    tft.print("Profile ");
    tft.print(activeProfileId);
#else
    tft.print("Tuning ");
#endif

    tmp = h / (activeProfile.peakTemp * 1.10) * 100.0;
    pxPerC = (uint16_t)tmp;
    
#if 0 // pxPerS should be calculated from the selected profile, wint fit in flash right now
    double estimatedTotalTime = 60 * 12;
    // estimate total run time for current profile
    estimatedTotalTime = activeProfile.soakDuration + activeProfile.peakDuration;
    estimatedTotalTime += (activeProfile.soakTemp - 20.0) / (activeProfile.rampUpRate / 10);
    estimatedTotalTime += (activeProfile.peakTemp - activeProfile.soakTemp) / (activeProfile.rampUpRate / 10);
    estimatedTotalTime += (activeProfile.peakTemp - 20.0) / (activeProfile.rampDownRate  / 10);
    //estimatedTotalTime *= 2; // add some spare
    Serial.print("total est. time: ");
    Serial.println((uint16_t)estimatedTotalTime);
#endif
    tmp = 60 * 8;
    tmp = w / tmp * 10.0; 
    pxPerS = (uint16_t)tmp;

    // 50°C grid
    int16_t t = (uint16_t)(activeProfile.peakTemp * 1.10);
    for (uint16_t tg = 0; tg < t; tg += 50) {
      uint16_t l = h - (tg * pxPerC / 100) + yOffset;
      tft.drawFastHLine(0, l, 160, tft.Color565(0xe0, 0xe0, 0xe0));
    }
#ifdef GRAPH_VERBOSE
    Serial.print("Calc pxPerC/S: ");
    Serial.print(pxPerC);
    Serial.print("/");
    Serial.println(pxPerS);
#endif
  }

  // elapsed time
  uint16_t elapsed = (zeroCrossTicks - startCycleZeroCrossTicks) / 100;
  tft.setCursor(125, y);
  alignRightPrefix(elapsed); 
  tft.print(elapsed);
  tft.print("s");

  y += menuItemHeight + 2;

  tft.setCursor(2, y);
  tft.setTextColor(ST7735_BLACK, ST7735_WHITE);

  // temperature
  tft.setTextSize(2);
  alignRightPrefix((int)A.temperature);
  displayThermocoupleData(&A);
  tft.setTextSize(1);

#ifndef PIDTUNE
  // current state
  y -= 2;
  tft.setCursor(95, y);
  tft.setTextColor(ST7735_BLACK, ST7735_GREEN);
  
  switch (currentState) {
    #define casePrintState(state) case state: tft.print(#state); break;
    casePrintState(RampToSoak);
    casePrintState(Soak);
    casePrintState(RampUp);
    casePrintState(Peak);
    casePrintState(RampDown);
    casePrintState(CoolDown);
    casePrintState(Complete);
    default: tft.print((uint8_t)currentState); break;
  }
  tft.print("        "); // lazy: fill up space

  tft.setTextColor(ST7735_BLACK, ST7735_WHITE);
#endif

  // set point
  y += 10;
  tft.setCursor(95, y);
  tft.print("Sp:"); 
  alignRightPrefix((int)Setpoint); 
  printDouble(Setpoint);
  tft.print("\367C  ");

  // draw temperature curves
  //

  if (xOffset >= elapsed) {
    xOffset = 0;
  }

  do { // x with wrap around
    dx = ((elapsed - xOffset) * pxPerS) / 10;
    if (dx > w) {
      xOffset = elapsed;
    }
  } while(dx > w);

  // temperature setpoint
  dy = h - ((uint16_t)Setpoint * pxPerC / 100) + yOffset;
  tft.drawPixel(dx, dy, ST7735_BLUE);

  // actual temperature
  dy = h - ((uint16_t)A.temperature * pxPerC / 100) + yOffset;
  tft.drawPixel(dx, dy, ST7735_RED);

  // bottom line
  y = 119;

  // set values
  tft.setCursor(2, y);
  tft.print("\xef");
  alignRightPrefix((int)heaterValue); 
  tft.print((int)heaterValue);
  tft.print('%');

  tft.print(" \x2a");
  alignRightPrefix((int)fanValue); 
  tft.print((int)fanValue);
  tft.print('%');

  tft.print(" \x12 "); // alternative: \x7f
  printDouble(rampRate);
  tft.print("\367C/s    ");
}

// ----------------------------------------------------------------------------

void setup() {
  setupRelayPins();

  tft.initR(INITR_BLACKTAB);
  tft.setTextWrap(false);
  tft.setTextSize(1);
  tft.setRotation(1);

  if (firstRun()) {
    factoryReset();
    loadParameters(0);
  } 
  else {
    loadLastUsedProfile();
  }

  tft.fillScreen(ST7735_WHITE);
  tft.setTextColor(ST7735_BLACK, ST7735_WHITE);

  Timer1.initialize(100);
  Timer1.attachInterrupt(timerIsr);

#ifndef FAKE_HW
  pinMode(PIN_ZX, INPUT_PULLUP);
  attachInterrupt(INT_ZX, zeroCrossingIsr, RISING);
  delay(100);
#else
  Timer3.initialize(1000); // x10 speed
  Timer3.attachInterrupt(zeroCrossingIsr);
#endif

#ifdef WITH_SPLASH
  // splash screen
  tft.setCursor(10, 30);
  tft.setTextSize(2);
  tft.print("Reflow");
  tft.setCursor(24, 48);
  tft.print("Controller");
  tft.setTextSize(1);
  tft.setCursor(52, 67);
  tft.print("v"); tft.print(ver);
  #ifdef FAKE_HW
  tft.print("-fake");
  #endif
  tft.setCursor(7, 119);
  tft.print("(c)2014 karl@pitrich.com");
  delay(1000);
#endif

  // setup /CS line for thermocouple and read initial temperature
  A.chipSelect = THERMOCOUPLE1_CS;
  pinMode(A.chipSelect, OUTPUT);
  digitalWrite(A.chipSelect, HIGH);
#ifndef FAKE_HW
  readThermocouple(&A);
#endif
  if (A.stat != 0) {
    abortWithError(A.stat);
  }

  // initialize moving average filter
  runningTotalRampRate = A.temperature * NUMREADINGS;
  for(int i = 0; i < NUMREADINGS; i++) {
    airTemp[i].temp = A.temperature;
  }

#ifdef WITH_CALIBRATION
  tft.setCursor(7, 99);  
  tft.print("Calibrating... ");
  delay(400);

  // FIXME: does not work reliably
  while (zxLoopDelay == 0) {
    if (zxLoopCalibration.iterations == zxCalibrationLoops) { // average tick measurements, dump 1st value
      for (int8_t l = 0; l < zxCalibrationLoops; l++) {
        zxLoopDelay += zxLoopCalibration.measure[l];
      }
      zxLoopDelay /= zxCalibrationLoops;
      zxLoopDelay -= 10; // compensating loop runtime
    }
  }
  tft.print(zxLoopDelay);
#else
  zxLoopDelay = DEFAULT_LOOP_DELAY;
#endif

  loadFanSpeed();
  loadPID();

  PID.SetOutputLimits(0, 100); // max output 100%
  PID.SetMode(AUTOMATIC);

  delay(1000);

  menuExit(Menu::actionDisplay); // reset to initial state
  Engine.navigate(&miCycleStart);
  currentState = Settings;
  menuUpdateRequest = true;
}

// ----------------------------------------------------------------------------
/* moving average
    int samples[8];

    total -= samples[i];
    samples[i] = A.temperature; // new value
    total += samples[i];

    i = (i + 1) % 8; // next position
    average = total >> 3; // == div by 8 */
// ----------------------------------------------------------------------------

uint32_t lastRampTicks;

void updateRampSetpoint(bool down = false) {
  if (zeroCrossTicks > lastRampTicks + MS_PER_SINE) {
    double rate = (down) ? activeProfile.rampDownRate : activeProfile.rampUpRate;
    Setpoint += (rate / MS_PER_SINE * (zeroCrossTicks - lastRampTicks)) * ((down) ? -1 : 1);
    lastRampTicks = zeroCrossTicks;
  }
}

// ----------------------------------------------------------------------------

#ifdef PIDTUNE
void toggleAutoTune() {
 if(currentState != Tune) { //Set the output to the desired starting frequency.
    currentState = Tune;

    Output = aTuneStartValue;
    PIDTune.SetNoiseBand(aTuneNoise);
    PIDTune.SetOutputStep(aTuneStep);
    PIDTune.SetLookbackSec((int)aTuneLookBack);
  }
  else { // cancel autotune
    PIDTune.Cancel();
    currentState = CoolDown;
  }
}
#endif // PIDTUNE

// ----------------------------------------------------------------------------

uint8_t thermocoupleErrorCount;
#define TC_ERROR_TOLERANCE 5 // allow for n consecutive errors due to noisy power supply before bailing out

// ----------------------------------------------------------------------------

void loop(void) 
{
  // --------------------------------------------------------------------------
  // handle encoder
  //
  encMovement = Encoder.getValue();
  if (encMovement) {
    encAbsolute += encMovement;
    if (currentState == Settings) {
      Engine.navigate((encMovement > 0) ? Engine.getNext() : Engine.getPrev());
      menuUpdateRequest = true;
    }
  }

  // --------------------------------------------------------------------------
  // handle button
  //
  switch (Encoder.getButton()) {
    case ClickEncoder::Clicked:
      if (currentState == Complete) { // at end of cycle; reset at click
        menuExit(Menu::actionDisplay); // reset to initial state
        Engine.navigate(&miCycleStart);
        currentState = Settings;
        menuUpdateRequest = true;
      }
      else if (currentState < UIMenuEnd) {
        menuUpdateRequest = true;
        Engine.invoke();
      }
      else if (currentState > UIMenuEnd) {
        currentState = CoolDown;
      }
      break;

    case ClickEncoder::DoubleClicked:
      if (currentState < UIMenuEnd) {
        if (Engine.getParent() != &miExit) {
          Engine.navigate(Engine.getParent());
          menuUpdateRequest = true;
        }
      }
      break;
  }

  // --------------------------------------------------------------------------
  // update current menu item while in edit mode
  //
  if (currentState == Edit) {
    if (Engine.currentItem != &Menu::NullItem) {
      Engine.executeCallbackAction(Menu::actionDisplay);      
    }
  }

  // --------------------------------------------------------------------------
  // handle menu update
  //
  if (menuUpdateRequest) {
    menuUpdateRequest = false;
    if (currentState < UIMenuEnd && !encMovement && currentState != Edit && previousState != Edit) { // clear menu on child/parent navigation
      tft.fillScreen(ST7735_WHITE);
    }  
    Engine.render(renderMenuItem, menuItemsVisible);
  }

  // --------------------------------------------------------------------------
  // track state changes
  //
  if (currentState != previousState) {
    stateChangedTicks = zeroCrossTicks;
    stateChanged = true;
    previousState = currentState;
  }

  // --------------------------------------------------------------------------

  if (zeroCrossTicks - lastUpdate >= 10) {
    uint32_t deltaT = zeroCrossTicks - lastUpdate;
    lastUpdate = zeroCrossTicks;

#ifndef FAKE_HW
    readThermocouple(&A); // should be sufficient to read it every 250ms or 500ms
#else
    A.temperature = encAbsolute;
#endif

    if (A.stat > 0) {
      thermocoupleErrorCount++;
    }
    else {
      thermocoupleErrorCount = 0;
    }

    if (thermocoupleErrorCount > TC_ERROR_TOLERANCE) {
      abortWithError(A.stat);
    }

#if 0 // verbose thermocouple error bits
    tft.setCursor(10, 40);
    for (uint8_t mask = B111; mask; mask >>= 1) {
      tft.print(mask & A.stat ? '1' : '0');
    }
#endif
      
    // rolling average of the temp T1 and T2
    totalT1 -= readingsT1[index];       // subtract the last reading
    readingsT1[index] = A.temperature;
    totalT1 += readingsT1[index];       // add the reading to the total
    index = (index + 1) % NUMREADINGS;  // next position
    averageT1 = totalT1 / NUMREADINGS;  // calculate the average temp

    // need to keep track of a few past readings in order to work out rate of rise
    for (int i = 1; i < NUMREADINGS; i++) { // iterate over all previous entries, moving them backwards one index
      airTemp[i - 1].temp = airTemp[i].temp;
      airTemp[i - 1].ticks = airTemp[i].ticks;     
    }

    airTemp[NUMREADINGS - 1].temp = averageT1; // update the last index with the newest average
    airTemp[NUMREADINGS - 1].ticks = deltaT;

    // calculate rate of temperature change
    uint32_t collectTicks;
    for (int i = 0; i < NUMREADINGS; i++) {
      collectTicks += airTemp[i].ticks;
    }
    rampRate = (airTemp[NUMREADINGS - 1].temp - airTemp[0].temp) / collectTicks * MS_PER_SINE;

    Input = airTemp[NUMREADINGS - 1].temp; // update the variable the PID reads

    // display update
    if (zeroCrossTicks - lastDisplayUpdate > 50) {
      lastDisplayUpdate = zeroCrossTicks;
      if (currentState > UIMenuEnd) {
        updateProcessDisplay();
      }
    }

    switch (currentState) {
#ifndef PIDTUNE
      case RampToSoak:
        if (stateChanged) {
          lastRampTicks = zeroCrossTicks;
          stateChanged = false;
          Output = 80;
          PID.SetMode(AUTOMATIC);
          PID.SetControllerDirection(DIRECT);
          PID.SetTunings(heaterPID.Kp, heaterPID.Ki, heaterPID.Kd);
          Setpoint = airTemp[NUMREADINGS - 1].temp;
        }

        updateRampSetpoint();

        if (Setpoint >= activeProfile.soakTemp - 1) {
          currentState = Soak;
        }
        break;

      case Soak:
        if (stateChanged) {
          stateChanged = false;
          Setpoint = activeProfile.soakTemp;
        }

        if (zeroCrossTicks - stateChangedTicks >= (uint32_t)activeProfile.soakDuration * MS_PER_SINE) {
          currentState = RampUp;
        }
        break;

      case RampUp:
        if (stateChanged) {
          stateChanged = false;
          lastRampTicks = zeroCrossTicks;
        }

        updateRampSetpoint();

        if (Setpoint >= activeProfile.peakTemp - 1) {
          Setpoint = activeProfile.peakTemp;
          currentState = Peak;
        }
        break;

      case Peak:
        if (stateChanged) {
          stateChanged = false;
          Setpoint = activeProfile.peakTemp;
        }

        if (zeroCrossTicks - stateChangedTicks >= (uint32_t)activeProfile.peakDuration * MS_PER_SINE) {
          currentState = RampDown;
        }
        break;

      case RampDown:
        if (stateChanged) {
          stateChanged = false;
          lastRampTicks = zeroCrossTicks;
          PID.SetControllerDirection(REVERSE);
          PID.SetTunings(fanPID.Kp, fanPID.Ki, fanPID.Kd);
          Setpoint = activeProfile.peakTemp - 15; // get it all going with a bit of a kick! v sluggish here otherwise, too hot too long
        }

        updateRampSetpoint(true);

        if (Setpoint <= idleTemp) {
          currentState = CoolDown;
        }
        break;
#endif
      case CoolDown:
        if (stateChanged) {
          stateChanged = false;
          PID.SetControllerDirection(REVERSE);
          PID.SetTunings(fanPID.Kp, fanPID.Ki, fanPID.Kd);
          Setpoint = idleTemp;
        }

        if (Input < (idleTemp + 5)) {
          currentState = Complete;
          PID.SetMode(MANUAL);
          Output = 0;
        }

#ifdef PIDTUNE
      case Tune:
        {
          Setpoint = 210.0;
          int8_t val = PIDTune.Runtime();
          PIDTune.setpoint = 210.0;

          if (val != 0) {
            currentState = CoolDown;
          }

          if (currentState != Tune) { // we're done, set the tuning parameters
            heaterPID.Kp = PIDTune.GetKp();
            heaterPID.Ki = PIDTune.GetKi();
            heaterPID.Kd = PIDTune.GetKd();
            
            savePID();

            tft.setCursor(40, 40);
            tft.print("Kp: "); tft.print((uint32_t)(heaterPID.Kp * 100));
            tft.setCursor(40, 52);
            tft.print("Ki: "); tft.print((uint32_t)(heaterPID.Ki * 100));
            tft.setCursor(40, 64);
            tft.print("Kd: "); tft.print((uint32_t)(heaterPID.Kd * 100));
          }
        }
        break;
#endif
    }
  }

  // safety check that we're not doing something stupid. 
  // if the thermocouple is wired backwards, temp goes DOWN when it increases
  // during cooling, the t962a lags a long way behind, hence the hugely lenient cooling allowance.
  // both of these errors are blocking and do not exit!
  //if (Setpoint > Input + 50) abortWithError(10); // if we're 50 degree cooler than setpoint, abort
  //if (Input > Setpoint + 50) abortWithError(20); // or 50 degrees hotter, also abort
  
#ifndef PIDTUNE
  PID.Compute();

  // decides which control signal is fed to the output for this cycle
  if (   currentState != RampDown
      && currentState != CoolDown
      && currentState != Settings
      && currentState != Complete
      && currentState != Idle
      && currentState != Settings
      && currentState != Edit)
  {
    heaterValue = Output;
    fanValue = fanAssistSpeed;
  } 
  else {
    heaterValue = 0;
    fanValue = Output;
  }
#else
  heaterValue = Output;
  fanValue = fanAssistSpeed;
#endif

  Channels[CHANNEL_HEATER].target = heaterValue;

  double fanTmp = 90.0 / 100.0 * fanValue; // 0-100% -> 0-90° phase control
  Channels[CHANNEL_FAN].target = 90 - (uint8_t)fanTmp;
}

void memoryFeedbackScreen(uint8_t profileId, bool loading) {
  tft.fillScreen(ST7735_GREEN);
  tft.setTextColor(ST7735_BLACK);
  tft.setCursor(10, 50);
  tft.print(loading ? "Loading" : "Saving");
  tft.print(" profile ");
  tft.print(profileId);  
}

void saveProfile(unsigned int targetProfile, bool quiet) {
#ifndef PIDTUNE
  activeProfileId = targetProfile;

  if (!quiet) {
    memoryFeedbackScreen(activeProfileId, false);
  }
  saveParameters(activeProfileId); // activeProfileId is modified by the menu code directly, this method is called by a menu action

  if (!quiet) delay(500);
#endif
}

void loadProfile(unsigned int targetProfile) {
  memoryFeedbackScreen(activeProfileId, true);
  bool ok = loadParameters(targetProfile);

#if 0
  if (!ok) {
    lcd.setCursor(0, 2);
    lcd.print("Checksum error!");
    lcd.setCursor(0, 3);
    lcd.print("Review profile.");
    delay(2500);
  }
#endif

  // save in any way, as we have no undo
  activeProfileId = targetProfile;
  saveLastUsedProfile();

  delay(500);
}

#define WITH_CHECKSUM 1

bool saveParameters(uint8_t profile) {
#ifndef PIDTUNE
  uint16_t offset = profile * sizeof(Profile_t);

#ifdef WITH_CHECKSUM
  activeProfile.checksum = crc8((uint8_t *)&activeProfile, sizeof(Profile_t) - sizeof(uint8_t));
#endif

  do {} while (!(eeprom_is_ready()));
  eeprom_write_block(&activeProfile, (void *)offset, sizeof(Profile_t));
#endif
  return true;
}

bool loadParameters(uint8_t profile) {
  uint16_t offset = profile * sizeof(Profile_t);

  do {} while (!(eeprom_is_ready()));
  eeprom_read_block(&activeProfile, (void *)offset, sizeof(Profile_t));

#ifdef WITH_CHECKSUM
  return activeProfile.checksum == crc8((uint8_t *)&activeProfile, sizeof(Profile_t) - sizeof(uint8_t));
#else
  return true;  
#endif
}

bool savePID() {
  do {} while (!(eeprom_is_ready()));
  eeprom_write_block(&heaterPID, (void *)offsetPidConfig, sizeof(PID_t));
  return true;
}

bool loadPID() {
  do {} while (!(eeprom_is_ready()));
  eeprom_read_block(&heaterPID, (void *)offsetPidConfig, sizeof(PID_t));
  return true;  
}

bool firstRun() { 
#ifndef PIDTUNE
  // if all bytes of a profile in the middle of the eeprom space are 255, we assume it's a first run
  unsigned int offset = 15 * sizeof(Profile_t);

  for (uint16_t i = offset; i < offset + sizeof(Profile_t); i++) {
    if (EEPROM.read(i) != 255) {
      return false;
    }
  }
#endif
  return true;
}

void makeDefaultProfile() {
  activeProfile.soakTemp     = 130;
  activeProfile.soakDuration =  80;
  activeProfile.peakTemp     = 220;
  activeProfile.peakDuration =  40;
  activeProfile.rampUpRate   =   0.80;
  activeProfile.rampDownRate =   2.0;
}

void factoryReset() {
#ifndef PIDTUNE
  makeDefaultProfile();

  tft.fillScreen(ST7735_RED);
  tft.setTextColor(ST7735_WHITE);
  tft.setCursor(10, 50);
  tft.print("Resetting...");

  // then save the same profile settings into all slots
  for (uint8_t i = 0; i < maxProfiles; i++) {
    saveParameters(i);
  }

  fanAssistSpeed = 33;
  saveFanSpeed();

  heaterPID.Kp =  0.60; 
  heaterPID.Ki =  0.01;
  heaterPID.Kd = 19.70;
  savePID();

  activeProfileId = 0;
  saveLastUsedProfile();

  delay(500);
#endif
}

void saveFanSpeed() {
  EEPROM.write(offsetFanSpeed, (uint8_t)fanAssistSpeed & 0xff);
  delay(250);
}

void loadFanSpeed() {
  fanAssistSpeed = EEPROM.read(offsetFanSpeed) & 0xff;
}

void saveLastUsedProfile() {
  EEPROM.write(offsetProfileNum, (uint8_t)activeProfileId & 0xff);
}

void loadLastUsedProfile() {
  activeProfileId = EEPROM.read(offsetProfileNum) & 0xff;
  loadParameters(activeProfileId);
}
