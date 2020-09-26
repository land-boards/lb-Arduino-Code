/*

Original Code and Instructions: http://www.vwlowen.co.uk/arduino/AD9833-waveform-generator/AD9833-waveform-generator.htm
AD9833 Waveform Module vwlowen.co.uk

----------------
modified by Wilhelm Zeuschner
10.07.2018, Version 1.1 - modified UI
07.08.2018, Version 1.2 - added RTC support

*/

//IF YOU WANT TO USE A DS3231 RTC COMMENT OUT THE LINE BELOW
#define USE_RTC
//Even with the RTC enabled, the sketch will still upload to a Pro Mini / Nano with an Atmega 168
//RTC Libary used:
//https://github.com/adafruit/RTClib

#include <Adafruit_GFX.h>			// Core graphics library
#include <Adafruit_ST7735.h>		// Hardware-specific library

#include <SPI.h>
#include <Rotary.h>					// Rotary encoder: https://github.com/brianlow/Rotary 

#ifdef USE_RTC
#include <RTClib.h>
#endif

#define TFT_CS     4
#define TFT_RST    9				//You can also connect this to the Arduino reset in which case, set this #define pin to -1!
#define TFT_DC     8 

//The UI can be configured to use a variety of different colors
//https://stackoverflow.com/questions/13720937/c-defined-16bit-high-color
#define Black           0x0000      /*   0,   0,   0 */
#define Orange          0xFD20      /* 255, 165,   0 */
#define Yellow          0xFFE0      /* 255, 255,   0 */
#define Red             0xF800      /* 255,   0,   0 */
#define LightGrey       0xC618      /* 192, 192, 192 */
#define White           0xFFFF      /* 255, 255, 255 */
//#define Navy            0x000F      /*   0,   0, 128 */
//#define DarkGreen       0x03E0      /*   0, 128,   0 */
//#define DarkCyan        0x03EF      /*   0, 128, 128 */
//#define Maroon          0x7800      /* 128,   0,   0 */
//#define Purple          0x780F      /* 128,   0, 128 */
//#define Olive           0x7BE0      /* 128, 128,   0 */
//#define LightGrey       0xC618      /* 192, 192, 192 */
//#define DarkGrey        0x7BEF      /* 128, 128, 128 */
//#define Blue            0x001F      /*   0,   0, 255 */
//#define Green           0x07E0      /*   0, 255,   0 */
//#define Cyan            0x07FF      /*   0, 255, 255 */
//#define Red             0xF800      /* 255,   0,   0 */
//#define Magenta         0xF81F      /* 255,   0, 255 */
//#define Yellow          0xFFE0      /* 255, 255,   0 */
//#define White           0xFFFF      /* 255, 255, 255 */
//#define Orange          0xFD20      /* 255, 165,   0 */
//#define GreenYellow     0xAFE5      /* 173, 255,  47 */
//#define Pink            0xF81F

const int SINE = 0x2000;                    // Define AD9833's waveform register value.
const int SQUARE = 0x2028;                  // When we update the frequency, we need to
const int TRIANGLE = 0x2002;                // define the waveform when we end writing.    

int wave = 0;
int waveType = SINE;
int wavePin = 7;

int freqUpPin = 2;                          // Define rotary encoder pins.
int freqDownPin = 3;
int stepUpPin = 5;
int stepDownPin = 6;

const float refFreq = 25000000.0;           // On-board crystal reference frequency

const int FSYNC = 10;                       // Standard SPI pins for the AD9833 waveform generator.
const int CLK = 13;                         // CLK and DATA pins are shared with the TFT display.
const int DATA = 11;

Rotary r = Rotary(freqUpPin, freqDownPin);    // Rotary encoder for frequency connects to interrupt pins
Rotary i = Rotary(stepUpPin, stepDownPin);    // Rotart encoder for setting increment.

unsigned long freq = 1000;               // Set initial frequency.
unsigned long freqOld = freq;

unsigned long incr = 1;
unsigned long oldIncr = 1;

#ifdef USE_RTC
byte timing = 61;
#endif


bool wave_type_changed = 1;

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);
#ifdef USE_RTC
RTC_DS3231 rtc;
#endif

void setup() {
	pinMode(TFT_CS, OUTPUT);				//Pin (4) is TFT_CS and has to be set as an output, otherwise the pin won't toggle!
	pinMode(freqUpPin, INPUT_PULLUP);		//Set pins for rotary encoders as INPUTS and enable
	pinMode(freqDownPin, INPUT_PULLUP);		//Internal pullup resistors.
	pinMode(stepUpPin, INPUT_PULLUP);
	pinMode(stepDownPin, INPUT_PULLUP);
	pinMode(wavePin, INPUT_PULLUP);

	//RTC
	#ifdef USE_RTC
	rtc.begin();
	#endif
	

	// Can't set SPI MODE here because the display and the AD9833 use different MODES.
	SPI.begin();

	//Adafruit display      
	tft.initR(INITR_BLACKTAB);   // initialize a ST7735S chip, black tab

	tft.setRotation(3);
	tft.setTextWrap(false);                                  // Allow text to run off right edge

	tft.fillScreen(Black);
	tft.drawFastVLine(20, tft.height() - 55, 4, LightGrey);         // Display 'static' cosmetic text.
	tft.drawFastVLine(40, tft.height() - 55, 4, LightGrey);
	tft.drawFastVLine(47, tft.height() - 55, 4, LightGrey);
	tft.drawFastVLine(88, tft.height() - 55, 4, LightGrey);
	tft.drawFastVLine(95, tft.height() - 55, 4, LightGrey);
	tft.drawFastVLine(134, tft.height() - 55, 4, LightGrey);

	tft.drawFastHLine(20, tft.height() - 52, 20, LightGrey);
	tft.drawFastHLine(47, tft.height() - 52, 42, LightGrey);
	tft.drawFastHLine(95, tft.height() - 52, 40, LightGrey);

	tft.setTextColor(White);
	tft.setCursor(23, tft.height() - 48);
	tft.print("MHz     kHz");
	tft.setCursor(123, tft.height() - 48);
	tft.print("Hz");


	tft.drawRoundRect(0, tft.height() - 25, tft.width(), 25, 4, Orange);
	//tft.drawFastHLine(0, tft.height() - 23, tft.width()-10, Olive);
	tft.setTextColor(Orange);
	tft.setCursor(18, tft.height() - 20);
	tft.setTextSize(1);
	tft.println("AD9850 10 Hz to 5 MHz ");
	tft.setCursor(28, tft.height() - 11);
	tft.println("Waveform Generator");


	tft.drawRoundRect(0, 0, tft.width(), tft.height() - 25, 4, Orange);
	tft.drawFastHLine(4, tft.height() - 93, tft.width() - 8, Orange);


	// Configure interrupt for rotary encoder and enable.
	PCICR |= (1 << PCIE2);
	PCMSK2 |= (1 << PCINT18) | (1 << PCINT19);
	sei();

	AD9833reset();                                   // Reset AD9833 module after power-up.
	delay(50);
	AD9833setFrequency(freq, SINE);                  // Set the frequency and Sine Wave output
	updateDisplay();

	tft.fillRect(25, 50, 120, 14, Black);
	tft.setTextSize(2);
	tft.setCursor(25, 50);
	format(freq);

	
}

void updateDisplay() {

	// To complicate things, the display uses SPI MODE0 but the AD9833 uses SPI MODE3 so it's
	// necessary to switch modes before each SPI transfer.
	SPI.setDataMode(SPI_MODE0);

	//Conditions remove unnecessary flicker	
	if (wave_type_changed) {

		tft.setTextColor(Yellow);
		tft.setTextSize(2);

		#ifdef USE_RTC
		tft.fillRect(2, 5, 95, 25, Black);            // Clear text.
		switch (waveType) {
			case SINE: tft.setCursor(26, 10); tft.println("SINE"); break;
			case SQUARE: tft.setCursor(15, 10); tft.println("SQUARE"); break;
			case TRIANGLE: tft.setCursor(3, 10); tft.println("TRIANGLE"); break;
		}
		#else
		tft.fillRect(32, 5, 95, 25, BLACK);            // Clear text.
		switch (waveType) {
			case SINE: tft.setCursor(56, 10); tft.println("SINE"); break;
			case SQUARE: tft.setCursor(45, 10); tft.println("SQUARE"); break;
			case TRIANGLE: tft.setCursor(33, 10); tft.println("TRIANGLE"); break;
		}
		#endif
		
		
		wave_type_changed = 0;		
	}
	else {
		tft.fillRect(25, 50, 110, 14, Black);           // Clear frequency numerals.
		tft.setTextSize(2);
		tft.setCursor(25, 50);
		format(freq);                                   // Show frequency in formatted form.  
	}
}

void format(unsigned long value) {

	// Break the frequency value down into individual digits & into variable 'digit'.
	// If a digit corresponds with the currently-selected x10 increment, change the 
	// text colour to YELLOW. All other digits and commas are GREEN. 

	unsigned long j = 1000000;

	for (int i = 6; i >= 0; i--) {
		int digit = (value / j) % 10;
		incr == j ? tft.setTextColor(Yellow) : tft.setTextColor(Red);
		tft.print(digit);
		if ((i == 6) || (i == 3)) {                  // Add commas at millions and thousands
			tft.setTextColor(Red);
			tft.print(",");
		}
		j /= 10;
	}
}


void loop() {

	if (oldIncr != incr) {
		updateDisplay();
		oldIncr = incr;
	}

	// Check 'increment' rotary encoder. Increase or decrease 'increment' by a factor of x10
	// if encoder has been turned.
	unsigned char result = i.process();
	if (result) {
		if (result == DIR_CW) { if (incr < 1000000) incr *= 10; }
		if (result == DIR_CCW) { if (incr >= 10) incr /= 10; }
		updateDisplay();
	}

	// Check if push button on 'increment' rotary encoder is pushed and set Wave Type accordingly.
	if (digitalRead(wavePin) == LOW) {
		wave_type_changed = 1;
		wave += 1;
		if (wave > 2) wave = 0;
		switch (wave) {
		case 0: waveType = SINE; break;
		case 1: waveType = SQUARE; break;
		case 2: waveType = TRIANGLE; break;
		}
		AD9833setFrequency(freq, waveType);     // Set AD9833 to frequency and selected wave type.
		updateDisplay();
		delay(200);
	}

	if (freq != freqOld) {                    // If frequency has changed, interrupt rotary encoder
		AD9833setFrequency(freq, waveType);     // must have been turned so update AD9833 and display.
		updateDisplay();
		freqOld = freq;                         // Remember new frequency to avoid unwanted display 
	}                                       // and AD9833 updates.

	//RTC
	#ifdef USE_RTC
	DateTime now = rtc.now();
	if (timing != now.minute()) {
		tft.fillRect(100, 7, 57, 24, Black);
		timing = now.minute();
		tft.setCursor(120, 8);
		tft.setTextColor(White);
		tft.setTextSize(1);
		tft.print(now.hour());
		tft.print(":");
		if (timing < 10) {
			tft.print("0");
		}
		tft.print(now.minute());

		//Date
		tft.setCursor(99, 20);
		if (now.day() < 10) {
			tft.print("0");
		}
		tft.print(now.day());
		tft.print(".");
		if (now.month() < 10) {
			tft.print("0");
		}
		tft.print(now.month());
		tft.print(".");
		tft.print(now.year());
	}
	#endif
	
}

// AD9833 documentation advises a 'Reset' on first applying power.
void AD9833reset() {
	WriteRegister(0x100);   // Write '1' to AD9833 Control register bit D8.
	delay(10);
}

// Set the frequency and waveform registers in the AD9833.
void AD9833setFrequency(long frequency, int Waveform) {

	long FreqWord = (frequency * pow(2, 28)) / refFreq;

	int MSB = (int)((FreqWord & 0xFFFC000) >> 14);    //Only lower 14 bits are used for data
	int LSB = (int)(FreqWord & 0x3FFF);

	//Set control bits 15 ande 14 to 0 and 1, respectively, for frequency register 0
	LSB |= 0x4000;
	MSB |= 0x4000;

	WriteRegister(0x2100);
	WriteRegister(LSB);                  // Write lower 16 bits to AD9833 registers
	WriteRegister(MSB);                  // Write upper 16 bits to AD9833 registers.
	WriteRegister(0xC000);               // Phase register
	WriteRegister(Waveform);             // Exit & Reset to SINE, SQUARE or TRIANGLE

}

void WriteRegister(int dat) {

	// Display and AD9833 use different SPI MODES so it has to be set for the AD9833 here.
	SPI.setDataMode(SPI_MODE2);

	digitalWrite(FSYNC, LOW);           // Set FSYNC low before writing to AD9833 registers
	delayMicroseconds(10);              // Give AD9833 time to get ready to receive data.

	SPI.transfer(highByte(dat));        // Each AD9833 register is 32 bits wide and each 16
	SPI.transfer(lowByte(dat));         // bits has to be transferred as 2 x 8-bit bytes.

	digitalWrite(FSYNC, HIGH);          //Write done. Set FSYNC high
}


// Interrupt service routine for the 'frequency' rotary encoder.

ISR(PCINT2_vect) {

	unsigned char result = r.process();
	if (result) {
		if (result == DIR_CW) {                   // Clockwise rotation so add increment to frequency
			if ((freq + incr) < 6000000) freq += incr;

		}
		else {
			if (freq > incr) {                    // Counter-clockwise rotation so subtract increment
				freq -= incr;                       // from frequency unless it would result in a negative
			}
			else {                              // number.
				if (freq >= 1) incr /= 10;
				if (incr < 1) incr = 1;             // Compensate for math rounding error.
			}
		}
	}
}
