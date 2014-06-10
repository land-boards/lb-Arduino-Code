/*************************************************** 
This is a library for the MCP23008 i2c parallel I/O

These devices use I2C to communicate, 2 pins are required to  
interface (clock and data)

The following statement was in the Adafruit code. 
Although we modified this code substantially from the Adafruit code, 
keeping the original author is important to us. 
Do not reach out to Adafruit to maintain this code.
\/                                                       \/
Adafruit invests time and resources providing this open source code, 
please support Adafruit and open-source hardware by purchasing 
products from Adafruit!
Written by Limor Fried/Ladyada for Adafruit Industries.  
BSD license, all text above must be included in any redistribution
****************************************************/

#ifndef _MCP23008_H
#define _MCP23008_H
// Don't forget the Wire library
class MCP23008 {
public:
	int16_t begin(uint8_t);						// stores base address and sets all pins to inputs
	int16_t addCard(uint8_t);
	int16_t pinMode(uint8_t, uint8_t);			// set the mode register for the part
	int16_t digitalWrite(uint8_t, uint8_t);
	int16_t pullUp(uint8_t, uint8_t);
	int16_t digitalRead(uint8_t);
	int16_t readGPIO(void);
	int16_t writeGPIO(uint8_t);

private:
	uint8_t cardPresentFlagBits;				// base address of the part
	uint8_t cardTypeFlagBits;					// type of card (INPUT, OUTPUT)
	uint8_t readShadow[8];						// shadow copy to speed reads
	uint8_t writeShadow[8];						// shadow copy to speed writes
	uint8_t read8(uint8_t addr);		
	void write8(uint8_t addr, uint8_t data);
};

#define MCP23008_ADDRESS 0x20

// registers
#define MCP23008_IODIR 0x00
#define MCP23008_IPOL 0x01
#define MCP23008_GPINTEN 0x02
#define MCP23008_DEFVAL 0x03
#define MCP23008_INTCON 0x04
#define MCP23008_IOCON 0x05
#define MCP23008_GPPU 0x06
#define MCP23008_INTF 0x07
#define MCP23008_INTCAP 0x08
#define MCP23008_GPIO 0x09
#define MCP23008_OLAT 0x0A

#endif
