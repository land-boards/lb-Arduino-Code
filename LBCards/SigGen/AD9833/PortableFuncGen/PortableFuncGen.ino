/*
 * Portable Function Generator on Arduino v1.0 
 * Designed by Faransky, 2018
 * Custom libraries are designed by:
 *    LiguidCrystal - Core Arduino library
 *    SPI - Core Arduino library
 *    Arduino pin change block - Generic example on the https://playground.arduino.cc/
 *    MD_AD9833 Library by MajCDesigns https://github.com/MajcDesigns/
 */
// include the library code:
#include <LiquidCrystal.h>
#include <SPI.h>
#include <MD_AD9833.h>
#include "pins_arduino.h"

/* Digital potentiometer constants */
#define DP_nINC 4 // D4
#define DP_UnD  3 // D3
#define DP_nCS  2 // D2

/* LCD Constants */
#define LCD_D7 14 // A0
#define LCD_D6 15 // A1
#define LCD_D5 16 // A2
#define LCD_D4 17 // A3
#define LCD_E  19 // A5
#define LCD_RS 5 // D5

/* Function generator constants */
#define DATA 11 // D11
#define CLK 13 // D13
#define FSYNC 10 // D10

/* Other pin definition constants */
#define VBAT 21 // A7
#define CAP_ON 18 // A4
#define CATHODE_PWM 9 // D9

/* Boolean Constants */
#define OFF false
#define ON true

/* Encoder constants */
#define ENC_A 8   // D8
#define ENC_B 7   // D7
#define ENC_SW 6  // D6

/* Encoder States */
#define UP 1
#define DOWN -1 
#define SAME 0

/* Sequential state machine constants */
enum OutputConstants { NOFF = 1, SINE, TRIG, SQUARE };
enum States { StateOut = 1, StateAmplitude, Coupling, StateFreqHz, StateFreqKhz, StateFreqMhz, Brightness};

/* Custom LCD battery characters */
byte Bat0[8] = {0b01110, 0b11011, 0b10001, 0b10001, 0b10001, 0b10001, 0b10001, 0b11111};
byte Bat1[8] = {0b01110, 0b11011, 0b10001, 0b10001, 0b10001, 0b11111, 0b11111, 0b11111};
byte Bat2[8] = {0b01110, 0b11011, 0b10001, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111};
byte Bat3[8] = {0b01110, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111};

/* AD9833 & LCD Library objects definition */
MD_AD9833  AD(FSYNC);
MD_AD9833::channel_t chan;
MD_AD9833::mode_t mode;  
LiquidCrystal lcd(LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

/* Global state machine in-used variables */
unsigned char MenuState = StateOut;   // Initial state
volatile uint8_t OutType = NOFF;      // Output waveform type
volatile uint8_t DigiPotState = 0;    // Digital potentiometer wiper state
volatile bool CouplingOn = true;      // AC or DC coupling state
volatile uint8_t BrightnessState = 0; // LCD Backlight brightness state

/* Encoder pins state */
volatile bool encoder_A = false;
volatile bool encoder_B = false;
volatile bool encoder_A_prev = false;

/* Frequency states */
volatile uint32_t FreqHz = 0;
volatile uint32_t FreqKhz = 0;
volatile uint32_t FreqMhz = 0; 


/* Function prototypes */
volatile uint8_t *port_to_pcmask[] = { &PCMSK0, &PCMSK1,&PCMSK2 };
static int PCintMode[24];
typedef void (*voidFuncPtr)(void);
volatile static voidFuncPtr PCintFunc[24] = { NULL };
volatile static uint8_t PCintLast[3];
void EnableInterrupts();
void DisableInterrupts();
void InitEncoder();
void InitOther();
void InitDigipot();
void CreateLcdChars();
byte ProcessBatteryVoltage();
void SetLcdBrightness(int brightness);
void PotDown();
void PotUp();
void InitPotState();
void InitDevice();
void SetADFrequency();
void SetADOutput();
void SetADOutType();
void BrightnessUp();
void BrightnessDown();
volatile int GetEncoderPos();
void EncoderPositionChanged();
void MainMenu();

/* Pin-change interrupts block */
/* /////////////////////////// */
void PCattachInterrupt(uint8_t pin, void (*userFunc)(void), int mode) 
{
  uint8_t bit = digitalPinToBitMask(pin);
  uint8_t port = digitalPinToPort(pin);
  uint8_t slot;
  volatile uint8_t *pcmask;

  // map pin to PCIR register
  if (port == NOT_A_PORT) return;
  else {
    port -= 2;
    pcmask = port_to_pcmask[port];
  }
  if (port == 1) slot = port * 8 + (pin - 14);
  else slot = port * 8 + (pin % 8);
  PCintMode[slot] = mode;
  PCintFunc[slot] = userFunc;
  *pcmask |= bit;
  PCICR |= 0x01 << port;
}

void PCdetachInterrupt(uint8_t pin) {
  uint8_t bit = digitalPinToBitMask(pin);
  uint8_t port = digitalPinToPort(pin);
  volatile uint8_t *pcmask;
  // map pin to PCIR register
  if (port == NOT_A_PORT) return;
  else {
    port -= 2;
    pcmask = port_to_pcmask[port];
  }
  *pcmask &= ~bit;
  if (*pcmask == 0)  PCICR &= ~(0x01 << port);
}

static void PCint(uint8_t port) {
  uint8_t bit;
  uint8_t curr;
  uint8_t mask;
  uint8_t pin;
  curr = *portInputRegister(port+2);
  mask = curr ^ PCintLast[port];
  PCintLast[port] = curr;
  if ((mask &= *port_to_pcmask[port]) == 0) return;
  for (uint8_t i=0; i < 8; i++) {
    bit = 0x01 << i;
    if (bit & mask) {
      pin = port * 8 + i;
      // Trigger interrupt if mode is CHANGE, or if mode is RISING and
      // the bit is currently high, or if mode is FALLING and bit is low.
      if ((PCintMode[pin] == CHANGE
          || ((PCintMode[pin] == RISING) && (curr & bit))
          || ((PCintMode[pin] == FALLING) && !(curr & bit)))
          && (PCintFunc[pin] != NULL)) {
        PCintFunc[pin]();
      }
    }
  }
} 

/* Interrupt masking functions */
SIGNAL(PCINT0_vect) { PCint(0); }
SIGNAL(PCINT1_vect) { PCint(1); }
SIGNAL(PCINT2_vect) { PCint(2); }
/* End of pin-change interrupts block */
/* ////////////////////////////////// */

/* Enable/disable encoder pin interrupts */
void EnableInterrupts()
{
  PCattachInterrupt(ENC_A, EncoderPositionChanged, CHANGE);
  PCattachInterrupt(ENC_B, EncoderPositionChanged, CHANGE);
}

void DisableInterrupts()
{
  PCdetachInterrupt(ENC_A);
  PCdetachInterrupt(ENC_B);
}

void InitEncoder()
{
  pinMode(ENC_A, INPUT);
  pinMode(ENC_B, INPUT);
  pinMode(ENC_SW, INPUT);
}

void InitOther()
{
  pinMode(VBAT, INPUT_PULLUP);
  pinMode(CAP_ON, OUTPUT);
  pinMode(CATHODE_PWM, OUTPUT);
}


void InitDigipot()
{
  pinMode(DP_nINC, OUTPUT);
  pinMode(DP_UnD, OUTPUT);
  pinMode(DP_nCS, OUTPUT);
}

void CreateLcdChars()
{
  lcd.createChar(1, Bat0);
  lcd.createChar(2, Bat1);
  lcd.createChar(3, Bat2);
  lcd.createChar(4, Bat3);
}

/* Process Li-ion battery voltage state and return appropriate character */
byte ProcessBatteryVoltage() 
{
  int BatVoltage  = analogRead(VBAT);
  //Serial.println(BatVoltage);
  if (BatVoltage >= 950 && BatVoltage <= 1023) return (byte)4;
  else if (BatVoltage >= 900 && BatVoltage < 950) return (byte)3;
  else if (BatVoltage >= 850 && BatVoltage < 900) return (byte)2;
  else {
    //Serial.println("Encoder came here");
    return (byte)1;
  }
}




void SetLcdBrightness(int brightness)
{
  analogWrite(CATHODE_PWM, brightness);
}


void PotDown()
{
  for (uint8_t i = 0; i < 4; i++) {
  digitalWrite(DP_UnD, LOW);
  digitalWrite(DP_nINC, LOW);
  delayMicroseconds(100);
  digitalWrite(DP_nINC, HIGH);
  delayMicroseconds(100);
  if (DigiPotState <= 0) DigiPotState = 0;
  else DigiPotState--;
  }
}



void PotUp()
{
  for (uint8_t i = 0; i < 4; i++) {
  digitalWrite(DP_UnD, HIGH);
  digitalWrite(DP_nINC, LOW);
  delayMicroseconds(100);
  digitalWrite(DP_nINC, HIGH);
  delayMicroseconds(100);
  if (DigiPotState >= 255) DigiPotState = 255;
  else DigiPotState++;
  }
}

void InitPotState()
{
  digitalWrite(DP_nCS, LOW);
  _delay_ms(10);
  for (uint8_t i = 0; i < 255; i++) PotDown();  
}




void InitDevice()
{
  InitEncoder();
  InitDigipot();
  InitPotState();
  InitOther();
  Serial.begin(57600);
  Serial.println("Serial logger is enabled");
  lcd.begin(16, 2); 
  AD.begin();
}

void SetADFrequency()
{
  uint32_t u1 = FreqHz + (FreqKhz * 1000) + (FreqMhz * 1000000);
  chan = MD_AD9833::CHAN_0;
  AD.setFrequency(chan, u1);
}

void SetADOutput()
{
  chan = MD_AD9833::CHAN_0;
  AD.setActiveFrequency(chan);
}

void SetADOutType()
{
switch (OutType)
      {
      case NOFF: mode = MD_AD9833::MODE_OFF;    break;
      case SINE: mode = MD_AD9833::MODE_SINE;   break;
      case TRIG: mode = MD_AD9833::MODE_TRIANGLE;  break;
      case SQUARE: mode = MD_AD9833::MODE_SQUARE1;  break;
      default: break;
      }  
AD.setMode(mode);
}

void setup() {
  InitDevice();
  CreateLcdChars();
  SetADOutput();
  pinMode(A4,OUTPUT);
  digitalWrite(A4,HIGH);
  mode = MD_AD9833::MODE_OFF;
  AD.setMode(mode);
  SetADFrequency();
  BrightnessState = 127;
  SetLcdBrightness(BrightnessState);
}

void BrightnessUp() {
  if (BrightnessState >= 250) BrightnessState = 255;
  else BrightnessState += 4;
  SetLcdBrightness(BrightnessState);
}

void BrightnessDown() {
  if (BrightnessState <= 5) BrightnessState = 0;
  else BrightnessState -= 4;
  SetLcdBrightness(BrightnessState);
}

volatile int GetEncoderPos()
{  
    volatile int RetVal = 0;
    encoder_A = digitalRead(ENC_A); 
    encoder_B = digitalRead(ENC_B);   
    delay(10);
    if((!encoder_A) && (encoder_A_prev)){
      if(encoder_B) RetVal = 1;            
      else RetVal = -1;
    }   
    else RetVal = 0;
    encoder_A_prev = encoder_A;     // Store value of A for next time
    return RetVal;
}

void EncoderPositionChanged()
{
   switch(MenuState) {
    case StateFreqHz:
      switch(GetEncoderPos()) {  
            case UP:
              if (FreqHz >= 900) FreqHz = 900;
              else FreqHz += 10;
              break;
            case DOWN:
               if (FreqHz < 10) FreqHz = 0;
               else FreqHz-= 10;
               break;
            default: break;
          }
          SetADFrequency();
          break;
  case StateFreqKhz:
    switch(GetEncoderPos()) {  
            case UP:
              if (FreqKhz >= 900) FreqKhz = 900;
              else FreqKhz += 1;
              break;
            case DOWN:
               if (FreqKhz <= 10) FreqKhz = 0;
               else FreqKhz -= 1;
               break;
            default: break;
          }
          SetADFrequency();
          break;
  case StateFreqMhz:
    switch(GetEncoderPos()) {  
            case UP:
              if (FreqMhz >= 10) FreqMhz = 10;
              else FreqMhz++;
              break;
            case DOWN:
               if (FreqMhz <= 0) FreqMhz = 0;
               else FreqMhz--;
               break;
            default: break;
          }
          SetADFrequency();
          break;
  case StateAmplitude:
    switch(GetEncoderPos()) {  
            case UP: PotUp(); break;
            case DOWN: PotDown(); break;
            default: break;
          }
          break;
  case StateOut:
    switch(GetEncoderPos()) {  
            case UP:
              if (OutType >= SQUARE) OutType = SQUARE;
              else OutType++; 
              break;
            case DOWN: 
              if (OutType <= NOFF) OutType = NOFF;
              else OutType--; 
              break;
            default: break;
          }
          SetADOutType();
          break;
   case Coupling:
      switch(GetEncoderPos()) {
        case UP: CouplingOn = true; break;
        case DOWN: CouplingOn = false; break;
        default: break;
      }
      digitalWrite(CAP_ON,CouplingOn);
      break;
    case Brightness:
        switch(GetEncoderPos()) {  
            case UP: BrightnessUp(); break;
            case DOWN: BrightnessDown(); break;
            default: break;
          }
          break;
  default: break;   
   }
}

void MainMenu()
{
  MenuState = StateOut;
  EnableInterrupts();
  bool OutConfirm = false;
  while(!OutConfirm)
  {
    switch(MenuState)
    {
      case StateFreqHz:
        lcd.setCursor(0,0);
        lcd.print("<Frequency: Hz >");
        lcd.setCursor(0,1);
        lcd.print("<Val:");
        lcd.setCursor(5,1); 
        lcd.print(FreqHz);
        if (FreqHz <= 9) {
          lcd.setCursor(6,1);
          lcd.print("  ");         
        }
        else if (FreqHz > 9 && FreqHz <= 99) {
          lcd.setCursor(7,1);
          lcd.print(" ");         
        }
        lcd.setCursor(8,1);
        lcd.print("[Hz]   >");
          if (!digitalRead(ENC_SW)) {
            while(!digitalRead(ENC_SW));
            MenuState = StateFreqKhz;
          }
        break;

      case StateFreqKhz:
        lcd.setCursor(0,0);
        lcd.print("<Frequency:KHz >");
        lcd.setCursor(0,1);
        lcd.print("<Val:");
        lcd.setCursor(5,1);
        lcd.print(FreqKhz);
        if (FreqKhz <= 9) {
          lcd.setCursor(6,1);
          lcd.print("  ");         
        }
        else if (FreqKhz > 9 && FreqKhz <= 99) {
          lcd.setCursor(7,1);
          lcd.print(" ");         
        }
        lcd.setCursor(8,1);
        lcd.print("[KHz]  >");
          if (!digitalRead(ENC_SW)) {
            while(!digitalRead(ENC_SW));
            MenuState = StateFreqMhz;
          }
        break; 
        
      case StateFreqMhz:
        lcd.setCursor(0,0);
        lcd.print("<Frequency:MHz >");
        lcd.setCursor(0,1);
        lcd.print("<Val:");
        lcd.setCursor(5,1);
        lcd.print(FreqMhz);
        if (FreqMhz <= 9) {
          lcd.setCursor(6,1);
          lcd.print("  ");         
        }
        else if (FreqMhz > 9 && FreqMhz <= 99) {
          lcd.setCursor(7,1);
          lcd.print(" ");         
        }
        lcd.setCursor(8,1);
        lcd.print("[MHz]  >");
          if (!digitalRead(ENC_SW)) {
            while(!digitalRead(ENC_SW));
            MenuState = Brightness;
          }
        break;
    
      case StateAmplitude:
        lcd.setCursor(0,0);
        lcd.print("<Amplitude in %>");
        lcd.setCursor(0,1);
        lcd.print("<Value:");
        lcd.setCursor(7,1);
        lcd.print((DigiPotState*100)/255);
        if ((DigiPotState*100)/255 <= 9) {
          lcd.setCursor(8,1);
          lcd.print("  ");         
        }
        else if ((DigiPotState*100)/255 > 9 && (DigiPotState*100)/255 < 100) {
          lcd.setCursor(9,1);
          lcd.print(" ");         
        }
        lcd.setCursor(10,1);
        lcd.print(" [%] >");
          if (!digitalRead(ENC_SW)) {
            while(!digitalRead(ENC_SW));
            MenuState = Coupling;
          }
        break;
          
      case StateOut:
        lcd.setCursor(0,0);
        lcd.print("<   Out Type   >");
        lcd.setCursor(0,1);
        lcd.print("<Out:");
        lcd.setCursor(5,1);
        switch (OutType)
        {
          case NOFF:   lcd.print("Off       >"); break;
          case SINE:   lcd.print("Sine      >"); break;
          case TRIG:   lcd.print("Triangle  >"); break;
          case SQUARE: lcd.print("Square    >"); break;
          default: break;
        }
          if (!digitalRead(ENC_SW)) {
            while(!digitalRead(ENC_SW));
            MenuState = StateAmplitude;
            }
        break;

     case Coupling:
        lcd.setCursor(0,0);
        lcd.print("< Out Coupling >");
        lcd.setCursor(0,1);
        lcd.print("<Type:");
        lcd.setCursor(6,1);
        switch (CouplingOn)
        {
          case true:   lcd.print(" [DC]    >"); break;
          case false:   lcd.print(" [AC]    >"); break;
          default: break;
        }
          if (!digitalRead(ENC_SW)) {
            while(!digitalRead(ENC_SW));
            MenuState = StateFreqHz;
            }
        break;     

case Brightness:
        lcd.setCursor(0,0);
        lcd.print("<  Brightness  >");
        lcd.setCursor(0,1);
        lcd.print("<Value:");
        lcd.setCursor(7,1);
        lcd.print((BrightnessState*100)/255);
        if ((BrightnessState*100)/255 <= 9) {
          lcd.setCursor(8,1);
          lcd.print("  ");         
        }
        else if ((BrightnessState*100)/255 > 9 && (BrightnessState*100)/255 < 100) {
          lcd.setCursor(9,1);
          lcd.print(" ");         
        }
        lcd.setCursor(10,1);
        lcd.print(" [%] >");
          if (!digitalRead(ENC_SW)) {
            while(!digitalRead(ENC_SW));
            OutConfirm = true;
            }
        break;     
      }
      delay(50);
    }
    DisableInterrupts();
}

void loop() {                  
  /* Battery Character */
  lcd.setCursor(15, 0);
  lcd.write(ProcessBatteryVoltage());
  /* Out State */
  lcd.setCursor(0,0);
  lcd.print("<Output:");
  lcd.setCursor(8,0);
  if (OutType != NOFF) lcd.print("ON ");
  else lcd.print("OFF");
  lcd.setCursor(11,0);
  lcd.print(" > ");
  /* Output Type */
  lcd.setCursor(0,1);
  lcd.print("<Y:");
  lcd.setCursor(3,1);
  switch(OutType) {
    case NOFF:    lcd.print("OFF "); break;
    case SINE:    lcd.print("SIN "); break;
    case TRIG:    lcd.print("TRN "); break;
    case SQUARE:  lcd.print("SQR "); break;
    default: break;
  }
  /* Amplitude */
  lcd.setCursor(7,1);
  lcd.print("[A]:");
  lcd.print((DigiPotState*100)/255);
        if ((DigiPotState*100)/255 <= 9) {
          lcd.setCursor(12,1);
          lcd.print("  ");         
        }
        else if ((DigiPotState*100)/255 > 9 && (DigiPotState*100)/255 < 100) {
          lcd.setCursor(13,1);
          lcd.print(" ");         
        }
        lcd.setCursor(14,1);
        lcd.print("%>");
  if (!digitalRead(ENC_SW)) {
    while(!digitalRead(ENC_SW));
    MainMenu();
  }
  delay(50);
}

