////////////////////////////////////////////////////////////////////////////////
// This is a library for the OPTO8 Card
//
// The cards have an MPC23008 which uses I2C to communicate to an 8 bit Parallel IO (PIO).
//	2 pins from the Arduino are required to interface (clock and data).
//	The base address of the MPC23008 parts is 0x20.
// The cards also have a 24C01C EEPROM memory which communicates over i2C.
//	The EEPROM memory is programmed with a cardType flag.
//	The base address of the 24C01C parts is 0x50.
////////////////////////////////////////////////////////////////////////////////

#include "Arduino.h"
#include <Wire.h>
#include <avr/pgmspace.h>
#include "OPTO8.h"

////////////////////////////////////////////////////////////////////////////////
// OPTO8 implementation
// Follows Arduino convention of using a begin function
// Scans the cards looking for a card present flag
////////////////////////////////////////////////////////////////////////////////

int16_t OPTO8::begin(void) 
{
	int8_t bitToTest;
	bitToTest = 1;
	return(0);
}

////////////////////////////////////////////////////////////////////////////////
// addCard(cardNumber) - Adds a card to the card present flag bits
//	:param cardNumber: The Card number (0-7)
//	:param cardType: The type of card (INPUT, OUTPUT)
//	:global cardPresentFlagBits: the bits that are set by this function
//	:returns:
//		0 if the bit could be set
//		-1 if the channel number was bad (>7)
//		-2 if the channel was already set
////////////////////////////////////////////////////////////////////////////////

int16_t OPTO8::addCard(uint8_t cardNumber, uint8_t cardType)
{
	uint8_t bitSet;
	if (cardNumber > 7)
		return(-1);
	bitSet = 1 << cardNumber;
	if ((cardPresentFlagBits & bitSet) == 0)	// card must be not present
	{
		cardPresentFlagBits |= bitSet;
		return(0);
	}
	else
		return (-2);
}

////////////////////////////////////////////////////////////////////////////////
// removeCard(cardNumber) - Removes a card from the card present flag bits
//	:param cardNumber: The Card number (0-7)
//	:global cardPresentFlagBits: the bits that are set by this function.
//	:returns:
//		0 if the bit could be set
//		-1 if the channel number was bad (>7)
//		-2 if the channel was already set
////////////////////////////////////////////////////////////////////////////////

int16_t OPTO8::removeCard(uint8_t cardNumber)
{
	uint8_t bitSet;
	if (cardNumber > 7)
		return(-1);
	bitSet = 1 << cardNumber;
	if ((cardPresentFlagBits & bitSet) == 1)	// card must not be present
	{
		cardPresentFlagBits &= ~bitSet;
		return(0);
	}
	else
		return (-2);
}

BOOL OPTO8::checkForCardPresent(uint8_t cardNumber)
{
	uint8_t bitSet;
	bitSet = 1 << cardNumber;
	if ((cardPresentFlagBits & bitSet) == 1)
		return TRUE;
	else
		return FALSE;
}

////////////////////////////////////////////////////////////////////////////////
// Set the pinMode register with pin number and direction
// :param p: pin number (0-7)
// :param d: direction (INPUT, OUTPUT)
// :returns: 0 if OK, -1 if card is not present, -2 if the pin number was > 7
////////////////////////////////////////////////////////////////////////////////

int16_t OPTO8::pinMode(uint8_t cardNumber, uint8_t p, uint8_t d) {
	uint8_t iodir;

	if (checkForCardPresent(cardNumber) == FALSE)
		return(-1);
	// only 8 bits!
	if (p > 7)
		return -2;

	iodir = read8(OPTO8_IODIR);

	// set the pin and direction
	if (d == INPUT) {
		iodir |= 1 << p; 
	} else {
		iodir &= ~(1 << p);
	}

	// write the new IODIR
	write8(OPTO8_IODIR, iodir);
}

int16_t OPTO8::readGPIO(uint8_t cardNumber) {
	// read the current GPIO output latches
	return read8(OPTO8_OLAT);
}

int16_t  OPTO8::writeGPIO(uint8_t cardNumber, uint8_t gpio) {
	write8(OPTO8_GPIO, gpio);
}

int16_t  OPTO8::digitalWrite(uint8_t cardNumber, uint8_t p, uint8_t d) {
	uint8_t gpio;

	// only 8 bits!
	if (p > 7)
		return -1;

	// read the current GPIO output latches
	gpio = readGPIO();

	// set the pin and direction
	if (d == HIGH)
		gpio |= 1 << p; 
	else
		gpio &= ~(1 << p);

	// write the new GPIO
	writeGPIO(gpio);
}

int16_t OPTO8::pullUp(uint8_t cardNumber, uint8_t p, uint8_t d) {
	uint8_t gppu;

	// only 8 bits!
	if (p > 7)
	return;

	gppu = read8(OPTO8_GPPU);
	// set the pin and direction
	if (d == HIGH) {
		gppu |= 1 << p; 
	} else {
		gppu &= ~(1 << p);
	}
	// write the new GPIO
	write8(OPTO8_GPPU, gppu);
}

int16_t OPTO8::digitalRead(uint8_t cardNumber, uint8_t p) {
	// Adafruit code returned a 0 if the port number was > 7
	// that is a conflict if the actual data read is 0
	if (p > 7)
	return -1;

	// read the current GPIO
	return (readGPIO() >> p) & 0x1;
}

int16_t OPTO8::read8(uint8_t cardNumber, uint8_t addr) {
	Wire.beginTransmission(OPTO8_ADDRESS | i2caddr);
	Wire.write((byte)addr);	
	Wire.endTransmission();
	Wire.requestFrom(OPTO8_ADDRESS | i2caddr, 1);

	return Wire.read();
}

int16_t OPTO8::write8(uint8_t cardNumber, uint8_t data) {
	uint8_t addr;
	addr = 0x20 + cardNumber;
	Wire.beginTransmission(OPTO8_ADDRESS | i2caddr);
	Wire.write((byte)addr);
	Wire.write((byte)data);
	Wire.endTransmission();
}
