// ER_SCOPE_V01_SPI.ino
//
// HAGIWO's Arduino OLED Oscilloscope & Spectrum Analyzer
// https://note.com/solder_state/n/n6b4cc8d1c6b9
// Card
//  http://land-boards.com/blwiki/index.php?title=ER-SCOPE-01
//
// Resources (ATMega328)
//  Sketch uses 19866 bytes (64%) of program storage space. Maximum is 30720 bytes.
//  Global variables use 807 bytes (39%) of dynamic memory, leaving 1241 bytes for local variables.
//    Maximum is 2048 bytes.

#include <avr/io.h>//for fast PWM
#include "fix_fft.h"//spectrum analyze

//OLED display setting
#include <SPI.h>//for OLED SPI display
//#include <Wire.h>
#include <Adafruit_GFX.h>//for OLED display
#include <Adafruit_SSD1306.h> //for OLED display
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// I2C or SPI display
// I2C constructor
// Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
// SPI constructor
#define OLED_MOSI   9
#define OLED_CLK   10
#define OLED_DC    11
#define OLED_CS    12
#define OLED_RESET 13
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

//  Rotary encoder setting
//   Good Performance: only the first pin has interrupt capability
#define  ENCODER_OPTIMIZE_INTERRUPTS //contermeasure of rotary encoder noise
#include <Encoder.h>
Encoder myEnc(2, 4);//rotary encoder digitalRead pin
float oldPosition  = -999;//rotary encoder counter
float newPosition = -999;

byte mode = 1;//1=low freq oscilo , 2=high freq oscilo , 3 = mid freq oscilo with external trig , 4 = spectrum analyze
byte old_mode = 1;//for initial setting when mode change.
byte param_select = 0;
byte param = 0;
byte param1 = 1;
bool param1_select = 0;
byte param2 = 1;
bool param2_select = 0;
int rfrs = 0;//display refresh rate

bool trig = 0;//external trig
bool old_trig = 0;//external trig , OFF -> ON detect
bool old_SW = 0;//push sw, OFF -> ON detect
bool SW = 0;//push sw

unsigned long trigTimer = 0;
unsigned long hideTimer = 0;//hide parameter count
bool hide = 0; //1=hide,0=not hide

char data[128], im[128] , cv[128]; //data and im are used for spectrum , cv is used for oscilo.

void setup() {
 // Display setting for I2C or SPI display
 display.begin(SSD1306_SWITCHCAPVCC, 0x3C);   // OLED I2C
// display.begin(SSD1306_SWITCHCAPVCC);   // OLED SPI
 display.clearDisplay();
 display.setTextSize(0);
 display.setTextColor(WHITE);
 analogReference(DEFAULT);

#define PWM_OUT 3
#define INPUT_SW 5
#define FILTER_SEL 6
#define EXT_TRIG 7

 //pin mode setting
 pinMode(PWM_OUT, OUTPUT) ;       // Offset voltage
 pinMode(INPUT_SW, INPUT_PULLUP); // Push sw
 pinMode(FILTER_SEL, INPUT) ;     // Input is high impedance -> no active 2pole filter , output is active 2pole filter
 pinMode(EXT_TRIG, INPUT);        // External triger detect

 //fast pwm setting
 TCCR2B &= B11111000;
 TCCR2B |= B00000001;

 //fast ADC setting
 ADCSRA = ADCSRA & 0xf8;//fast ADC *8 speed
 ADCSRA = ADCSRA | 0x04;//fast ADC *8 speed
};

void loop() {
 old_SW = SW;
 old_mode = mode;

 SW = digitalRead(INPUT_SW);
 //select mode by push sw
 if (old_SW == 0 && SW == 1 && param_select == param) {
   param_select = 0;
   hideTimer = millis();
 }
 else if (old_SW == 0 && SW == 1 && param == 1) {
   param_select = param;
   hideTimer = millis();
 }
 else   if (old_SW == 0 && SW == 1 && param == 2) {
   param_select = param;
   hideTimer = millis();
 }
 else   if (old_SW == 0 && SW == 1 && param == 3) {
   param_select = param;
   hideTimer = millis();
 }
 mode = constrain(mode, 1, 4);
 param = constrain(param, 1, 3);

 // Rotary encoder input
 newPosition = myEnc.read();
 if ( (newPosition - 3) / 4  > oldPosition / 4) {
   oldPosition = newPosition;
   hideTimer = millis();
   switch (param_select) {
     case 0:
       param --;
       break;

     case 1:
       mode --;
       break;

     case 2:
       param1 --;
       break;

     case 3:
       param2 --;
       break;
   }
 }

 else if ( (newPosition + 3) / 4  < oldPosition / 4 ) {
   oldPosition = newPosition;
   hideTimer = millis();
   switch (param_select) {
     case 0:
       param ++;
       break;

     case 1:
       mode ++;
       break;

     case 2:
       param1 ++;
       break;

     case 3:
       param2 ++;
       break;

   }
 }

 //initial settin when mode change.
 if (old_mode != mode) {
   switch (mode) {
     case 1:
       param1 = 2; //time
       param2 = 1; //offset
       pinMode(FILTER_SEL, INPUT);//no active 2pole filter
       analogWrite(PWM_OUT, 0); //offset = 0V
       ADCSRA = ADCSRA & 0xf8;//fast ADC *8 speed
       ADCSRA = ADCSRA | 0x04;//fast ADC *8 speed
       break;

     case 2:
       param1 = 3; //time
       param2 = 3; //offset
       analogWrite(PWM_OUT, 127); //offset = 2.5V
       pinMode(FILTER_SEL, INPUT);//no active 2pole filter
       ADCSRA = ADCSRA & 0xf8;//fast ADC *8 speed
       ADCSRA = ADCSRA | 0x04;//fast ADC *8 speed
       break;

     case 3:
       param1 = 2; //time
       analogWrite(PWM_OUT, 127); //offset = 2.5V
       pinMode(FILTER_SEL, INPUT);//no active 2pole filter
       ADCSRA = ADCSRA & 0xf8;//fast ADC *8 speed
       ADCSRA = ADCSRA | 0x04;//fast ADC *8 speed
       break;

     case 4:
       param1 = 2; //high freq amp
       param2 = 3; //noise filter
       analogWrite(PWM_OUT, 127); //offset = 2.5V
       pinMode(FILTER_SEL, OUTPUT);//active 2pole filter
       digitalWrite(FILTER_SEL, LOW);//active 2pole filter
       ADCSRA = ADCSRA & 0xf8;//standard ADC speed
       ADCSRA = ADCSRA | 0x07;//standard ADC speed
       break;
   }
 }

 //OLED parameter hide while no operation
 if ( hideTimer + 5000 >= millis() ) {//
   hide = 1;
 }
 else {
   hide = 0;
 }

 //LFO mode--------------------------------------------------------------------------------------------
 if (mode == 1) {
   param = constrain(param, 1, 3);
   param1 = constrain(param1, 1, 8);
   param2 = constrain(param2, 1, 8);

   display.clearDisplay();

   //store data
   for (int i = 126 / (9 - param1); i >= 0; i--) {
     display.drawLine(127 - (i * (9 - param1)) , 63 - cv[i] - (param2 - 1) * 4, 127 - (i + 1) * (9 - param1) , 63 - cv[(i + 1 )] - (param2 - 1) * 4, WHITE); //right to left
     cv[i + 1] = cv[i];
     if (i == 0) {
       cv[0] = analogRead(0) / 16;
     }
   }

   //display
   if (hide == 1) {
     display.drawLine((param - 1) * 42, 8,   (param - 1) * 42 + 36, 8, WHITE);

     display.setTextColor(WHITE);
     if (param_select == 1) {
       display.setTextColor(BLACK, WHITE);
     }
     display.setCursor(0, 0);
     display.print("Mode:");
     display.setCursor(30, 0);
     display.print(mode);

     display.setTextColor(WHITE);
     if (param_select == 2) {
       display.setTextColor(BLACK, WHITE);
     }
     display.setCursor(42, 0);
     display.print("Time:");
     display.setCursor(72, 0);
     display.print(param1);

     display.setTextColor(WHITE);
     if (param_select == 3) {
       display.setTextColor(BLACK, WHITE);
     }
     display.setCursor(84, 0);
     display.print("Offs:");
     display.setCursor(114, 0);
     display.print(param2);
   }
 }

 //wave mode---------------------------------------------------------------------------------------------
 else if (mode == 2) {
   param = constrain(param, 1, 3);
   param1 = constrain(param1, 1, 8);
   param2 = constrain(param2, 1, 6);

   //store data
   if (param1 > 5) {//for mid frequency
     for (int i = 127 ; i >= 0; i--) {
       cv[i] = analogRead(0) / 16;
       delayMicroseconds((param1 - 5) * 20);
     }
     rfrs++;
     if (rfrs >= (param2 - 1) * 2) {
       rfrs = 0;
       display.clearDisplay();
       for (int i = 127 ; i >= 1; i--) {
         display.drawLine(127-i , 63 - cv[i - 1], 127-(i + 1)  , 63 - cv[(i)], WHITE);
       }
     }
   }

   else if (param1 <= 5) {//for high frequency
     for (int i = 127 / (6 - param1); i >= 0; i--) {
       cv[i] = analogRead(0) / 16;
     }
     rfrs++;
     if (rfrs >= (param2 - 1) * 2) {
       rfrs = 0;
       display.clearDisplay();
       for (int i = 127 / (6 - param1); i >= 1; i--) {
         display.drawLine(127-i * (6 - param1), 63 - cv[i - 1], 127-(i + 1) * (6 - param1)  , 63 - cv[(i)], WHITE);
       }
     }
   }

   //display
   if (hide == 1) {
     display.drawLine((param - 1) * 42, 8,   (param - 1) * 42 + 36, 8, WHITE);
     display.setTextColor(WHITE);
     if (param_select == 1) {
       display.setTextColor(BLACK, WHITE);
     }
     display.setCursor(0, 0);
     display.print("Mode:");
     display.setCursor(30, 0);
     display.print(mode);

     display.setTextColor(WHITE);
     if (param_select == 2) {
       display.setTextColor(BLACK, WHITE);
     }
     display.setCursor(42, 0);
     display.print("Time:");
     display.setCursor(72, 0);
     display.print(param1);

     display.setTextColor(WHITE);
     if (param_select == 3) {
       display.setTextColor(BLACK, WHITE);
     }
     display.setCursor(84, 0);
     display.print("Rfrs:");
     display.setCursor(114, 0);
     display.print(param2);
   }
 }

 //shot mode---------------------------------------------------------------------------------------------
 else if (mode == 3) {
   param = constrain(param, 1, 2);
   param1 = constrain(param1, 1, 4);
   old_trig = trig;
   trig = digitalRead(INPUT_SW);

   //    trig detect
   if (old_trig == 0 && trig == 1  ) {
     for (int i = 10 ; i <= 127; i++) {
       cv[i] = analogRead(0) / 16;
       delayMicroseconds(100000 * param1);//100000 is magic number
     }
     for (int i = 0 ; i < 10; i++) {
       cv[i] = 32;
     }
   }

   display.clearDisplay();
   for (int i = 126 ; i >= 1; i--) {
     display.drawLine(i , 63 - cv[i], (i + 1)  , 63 - cv[(i + 1)], WHITE);
   }

   //display
   if (hide == 1) {
     display.drawLine((param - 1) * 42, 8,   (param - 1) * 42 + 36, 8, WHITE);
     display.setTextColor(WHITE);
     if (param_select == 1) {
       display.setTextColor(BLACK, WHITE);
     }
     display.setCursor(0, 0);
     display.print("Mode:");
     display.setCursor(30, 0);
     display.print(mode);

     display.setTextColor(WHITE);
     if (param_select == 2) {
       display.setTextColor(BLACK, WHITE);
     }
     display.setCursor(42, 0);
     display.print("Time:");
     display.setCursor(72, 0);
     display.print(param1);
     display.setTextColor(WHITE);
     if (trig == 1) {
       display.setTextColor(BLACK, WHITE);
     }
     display.setCursor(84, 0);
     display.print("TRIG");
   }
 }

 //spectrum analyze mode---------------------------------------------------------------------------------------------
 else if (mode == 4) {
   param = constrain(param, 1, 3);
   param1 = constrain(param1, 1, 4);//high freq sence
   param2 = constrain(param2, 1, 8);//noise filter

   for (byte i = 0; i < 128; i++) {
     int spec = analogRead(0);
     data[i] = spec / 4 - 128;
     im[i] = 0;
   };
   fix_fft(data, im, 7, 0);
   display.clearDisplay();
   for (byte i = 0; i < 64; i++) {
     int level = sqrt(data[i] * data[i] + im[i] * im[i]);;
     if (level >= param2) {
       display.fillRect(i * 2, 63 - (level + i * (param1 - 1) / 8), 2, (level + i * (param1 - 1) / 8), WHITE); // i * (param1 - 1) / 8 is high freq amp
     }
   }

   //display
   if (hide == 1) {
     display.drawLine((param - 1) * 42, 8,   (param - 1) * 42 + 36, 8, WHITE);
     display.setTextColor(WHITE);
     if (param_select == 1) {
       display.setTextColor(BLACK, WHITE);
     }
     display.setCursor(0, 0);
     display.print("Mode:");
     display.setCursor(30, 0);
     display.print(mode);

     display.setTextColor(WHITE);
     if (param_select == 2) {
       display.setTextColor(BLACK, WHITE);
     }
     display.setCursor(42, 0);
     display.print("High:");
     display.setCursor(72, 0);
     display.print(param1);

     display.setTextColor(WHITE);
     if (param_select == 3) {
       display.setTextColor(BLACK, WHITE);
     }
     display.setCursor(84, 0);
     display.print("Filt:");
     display.setCursor(114, 0);
     display.print(param2);
   }
 }

 display.display();
}
