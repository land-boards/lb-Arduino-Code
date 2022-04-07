/////////////////////////////////////////////////////////////////////////////////////////////
// I2CIO8ECHO3 - Echo the I/O lines
// Polls the interrupt line.
// If the interrupt is active. read the (4) input bits and write the bits out.

// Hardware used
// I2CIO-8 card
//  http://land-boards.com/blwiki/index.php?title=I2CIO-8
// GVSDuino (Arduino Uno Compatible)
//  http://land-boards.com/blwiki/index.php?title=GVSDuino
// Cables
//  4-pin to 2x3 pin connects I2CIO-8 (SDA,SCL,GND,VCC) to GVSDuino (A4,A5,GND,VCC) (female)
//  1 pin female I2CIO-8 INT to GVSDuino D9
/////////////////////////////////////////////////////////////////////////////////////////////

#include <Wire.h>

// MCP23008 registers
#define M08_IODIR 0x00
#define M08_IPOL 0x01
#define M08_GPINTEN 0x02
#define M08_DEFVAL 0x03
#define M08_INTCON 0x04
#define M08_IOCON 0x05
#define M08_GPPU 0x06
#define M08_INTF 0x07
#define M08_INTCAP 0x08
#define M08_GPIO 0x09
#define M08_OLAT 0x0A

#define INTPOLACTHI 0x02
#define INTLINE 9

/////////////////////////////////////////////////////////////////////////////////////////////
// Setup the I2CIO-8 card registers
/////////////////////////////////////////////////////////////////////////////////////////////

void setup()
{
  Serial.begin(9600);   // 9600 baud serial
  Wire.begin();
#if defined(ARDUINO_ARCH_AVR)
  Wire.setClock(400000);  // 400KHz speed
#elif defined(ARDUINO_ARCH_STM32F1)
  Wire.setClock(400000);  // 400KHz speed
#else
  #error “This library only supports boards with an AVR or SAM processor.”
#endif
  mcpWrite8(M08_IODIR,0xf0);         // Set I/O direction control
  mcpWrite8(M08_IOCON, INTPOLACTHI); // Set interrupt polarity to high
  mcpWrite8(M08_IPOL, 0xf0);         // Interrupt on polarity change
  mcpWrite8(M08_GPINTEN, 0xf0);      // Enable Interrupts on all inputs
}

/////////////////////////////////////////////////////////////////////////////////////////////
// Read the interrupt line
// Interrupt is present when the line is high
// If there is an interrupt read the input register
// Reading the register clears the interrupt
// There is no debouncing
/////////////////////////////////////////////////////////////////////////////////////////////

void loop()
{
  char theChar;
  if (digitalRead(INTLINE) == 1)        // If the interrupt line is active
  {
    delay(50);                          // minimal debounce
    theChar = mcpRead8(M08_GPIO);          // Read the input register
    mcpWrite8(M08_OLAT, theChar >> 4);  // Write to the LEDs
    Serial.println("Int");              // print
  }
}

/////////////////////////////////////////////////////////////////////////////////////////////
// mcpWrite8
/////////////////////////////////////////////////////////////////////////////////////////////

void mcpWrite8(uint8_t addr, uint8_t data) {
  Wire.beginTransmission(0x20);
  Wire.write((byte)addr);
  Wire.write((byte)data);
  Wire.endTransmission();
}

/////////////////////////////////////////////////////////////////////////////////////////////
// mcpRead8
/////////////////////////////////////////////////////////////////////////////////////////////

uint8_t mcpRead8(uint8_t addr) {
  Wire.beginTransmission(0x20);
  Wire.write((byte)addr);
  Wire.endTransmission();
  Wire.requestFrom(0x20, 1);

  return Wire.read();
}
