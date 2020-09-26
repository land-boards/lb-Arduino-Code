/* Based on AD9851 code from Andrew Smallbone - modified for AD9850
   http://www.rocketnumbernine.com/2011/10/25/programming-the-ad9851-dds-synthesizer
 */

#include <Arduino.h>
#include <Adafruit_GFX.h>       // Core graphics library https://github.com/adafruit/Adafruit-GFX-Library
#include <Adafruit_ST7735.h>    // Hardware-specific library https://github.com/adafruit/Adafruit-ST7735-Library
#include <SPI.h>

#include <Rotary.h>            //  Rotary encoder: https://github.com/brianlow/Rotary

int TFT_LED = 9;
#define TFT_SCLK 13             // 1.8" TFT Display.
#define TFT_MOSI 11             //
#define TFT_CS   10
#define TFT_RST  A1
#define TFT_DC   A0

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_RST);

#define AD9850_CLOCK 125000000         // Module crystal frequency. Tweak here for accuracy.

#define W_CLK 8                        // AD9850 Module pins.
#define FQ_UD 7
#define DATA  6
#define RESET 5

#define stepPin1 A3                    // Set 'Step' rotary encoder pins
#define stepPin2 A2

int forceHzStep = A4;                  // 'Step' rotary encoder's push button - Set 1 Hz steps.
int forcekHz = 4;                     // Interrupt-driven encoder's push button - force 1kHz freq.

Rotary i = Rotary(stepPin1, stepPin2); // Rotart encoder for setting increment.
Rotary r = Rotary(2, 3);               // Rotary encoder for frequency connects to interrupt pins

long unsigned int freq = 1000;         // Set initial frequency.
long unsigned int freqOld = freq;

long int timer;


char* stepText[11] = {"  1  Hz", " 10  Hz", " 50  Hz", "100  Hz", "500  Hz", "  1 kHz", "2.5 kHz",
                     "  5 kHz", " 10 kHz", "100 kHz", "500 kHz"};

// set decade steps
//char* stepText[6] = {"  1  Hz", " 10  Hz", "100  Hz", "  1 kHz", " 10 kHz", "100 kHz"};

int stepPointer = 0;
unsigned long  incr = 0;
String units = stepText[stepPointer];

#define pulseHigh(pin) {digitalWrite(pin, HIGH); digitalWrite(pin, LOW); }


 // transfers a byte, a bit at a time, LSB first to the 9850 via serial DATA line
void tfr_byte(byte data) {
  for (int i = 0; i < 8; i++, data >>= 1) {
    digitalWrite(DATA, data & 0x01);
    pulseHigh(W_CLK);   //after each bit sent, CLK is pulsed high
  }
}

void sendFrequency(double frequency) {
  int32_t freq1 = frequency * 4294967295/AD9850_CLOCK;  // note 125 MHz clock on 9850
  for (int b = 0; b < 4; b++, freq1 >>= 8) {
    tfr_byte(freq1 & 0xFF);
  }
  tfr_byte(0x000);                     // Final control byte, all 0 for 9850 chip
  pulseHigh(FQ_UD);                    // Done!  Should see output
}

void format(long value);
void updateDisplay();

void setup() {

  Serial.begin(115200);
  pinMode(2, INPUT_PULLUP);            // Pins for interrupt-driven rotary encoder and push buttons
  pinMode(3, INPUT_PULLUP);
  pinMode(forceHzStep, INPUT_PULLUP);
  pinMode(forcekHz, INPUT_PULLUP);

  pinMode(FQ_UD, OUTPUT);              // Configure pins for output to AD9850 module.
  pinMode(W_CLK, OUTPUT);
  pinMode(DATA, OUTPUT);
  pinMode(RESET, OUTPUT);

  pinMode(TFT_RST, OUTPUT);            // Configure pins for output to TFT display.
  pinMode(TFT_DC, OUTPUT);
  pinMode(TFT_LED, OUTPUT);

  pinMode(A3, INPUT_PULLUP);          // Configure pins for the encoder
  pinMode(A2, INPUT_PULLUP);

  analogWrite(TFT_LED, 255);           // Adjust backlight brightness.

 // Configure interrupt and enable for rotary encoder.
  PCICR |= (1 << PCIE2);
  PCMSK2 |= (1 << PCINT18) | (1 << PCINT19);
  sei();


  tft.initR(INITR_BLACKTAB);           // initialize a ST7735S chip, black tab

  tft.setRotation(2);
  tft.setTextWrap(false);              // Allow text to run off right edge
  tft.fillScreen(ST7735_BLACK);

  tft.setCursor(8, tft.height() -20);
  tft.setTextSize(1);
  tft.drawFastHLine(0, tft.height() - 23, tft.width()-10, ST7735_BLUE);
  tft.setTextColor(ST7735_BLUE);
  tft.println("AD9850 1 Hz to 5 MHz");
  tft.print("  sinewave generator");

  // Initialise the AD9850 module.
  pulseHigh(RESET);
  pulseHigh(W_CLK);
  pulseHigh(FQ_UD);    // this pulse enables serial mode - Datasheet page 12 figure 10

  updateDisplay();       // Update the TFT display.
}

void getStep() {
  switch(stepPointer) {
    case 0:  incr = 1; break;
    case 1:  incr = 10; break;
    case 2:  incr = 50; break;
    case 3:  incr = 100; break;
    case 4:  incr = 500; break;
    case 5:  incr = 1000; break;
    case 6:  incr = 2500; break;
    case 7:  incr = 5000; break;
    case 8:  incr = 10000; break;
    case 9:  incr = 100000; break;
    case 10: incr = 500000; break;
  }
}


void updateDisplay() {
  getStep();                          //
  units = stepText[stepPointer];

  tft.fillRect(0, 15, 160, 20, ST7735_BLACK);

  tft.setTextColor(ST7735_YELLOW);
  tft.setCursor(5, 10);
  tft.setTextSize(1);
  tft.print("Step: ");
  tft.setTextSize(2);
  tft.setCursor(30, 20);
  tft.print(units);

  tft.fillRect(0, 40, 160, 60, ST7735_BLACK);
  tft.setTextColor(ST7735_GREEN);
  tft.setCursor(5, 40);
  tft.setTextSize(1);
  tft.print("Frequency: ");
  tft.setTextSize(2);
  if (freq < 1000) {
    tft.setCursor(85, 50);
    tft.print(freq);
    tft.setCursor(75, 75);
    tft.print(" Hz");
  } else
  if (freq < 1000000) {
   tft.setCursor(40, 50);
   if (freq >= 1000 && freq < 9999) tft.print("  ");
   if (freq >= 10000 && freq < 99999) tft.print(" ");
   tft.print((float)freq/1000, 3);
   tft.setCursor(75, 75);
   tft.print("kHz");
  }  else {
   format(freq);
   tft.setCursor(75, 75);
   tft.print("MHz");
  }
}

void format(long value) {
  int M = (value/1000000);
  int T100 = ((value/100000)%10);
  int T10 = ((value/10000)%10);
  int T1 = ((value/1000)%10);
  int U100 = ((value/100)%10);
  int U10 = ((value/10)%10);
  int U1 = ((value/1)%10);
  tft.setCursor(5, 50);
  tft.print(M);tft.print(".");tft.print(T100);tft.print(T10);tft.print(T1);
  tft.print(",");tft.print(U100);tft.print(U10);tft.print(U1);
}

void loop() {
  // Check 'Step' rotary encoder.
  unsigned char result = i.process();
  if (result) {
    if (result == DIR_CCW)  {if (stepPointer < 10) stepPointer++;}
    if (result == DIR_CW) {if (stepPointer > 0) stepPointer--;}
    updateDisplay();
  }

  if (digitalRead(forceHzStep) == LOW) {
    stepPointer = 2;
    updateDisplay();
    delay(50);
  }

  if (digitalRead(forcekHz) == LOW) {
    freq = 1000;
    sendFrequency(freq);
    updateDisplay();
    delay(350);
  }

  if (freqOld != freq) {
    sendFrequency(freq);
    updateDisplay();
    freqOld = freq;
  }
}

ISR(PCINT2_vect) {
  unsigned char result = r.process();
  if (result) {
    if (result == DIR_CW) {
      if ((freq + incr) <= 10000000) freq += incr;
    } else {
      if ((freq - incr) >= incr) freq -= incr;
    }
    if (freq <= 10)  freq = 10;
    if (freq >=10000000) freq = 10000000;
  }
}
