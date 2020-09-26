#include "AD9833.h"

/**
* This is a class to provide basic functionality of the AD9833
* function generator. This class only provides frequency and
* waveform control of a single register to keep code base small.
*/
AD9833::AD9833() {}


//Global variables
uint8_t funcPin = 4;

/*
* Initialisation function to set up communication and begin
* using the device. This must be called first, before anything
* else will work.
*/
void AD9833 :: begin(uint8_t fPin) {
	/*Set the function pin to output.
	* This controls SPI communication with the
	* chip. Active LOW.
	*/
	funcPin = fPin;
	pinMode(funcPin, OUTPUT);
	digitalWrite(funcPin, HIGH);

	//Begin SPI communication
	SPI.begin();

	//Short delay and reset required by the device
	delay(100);
	reset();
}

/*
* Calculates and applies a frequency to the FREQ0 register.
* Because both double, long, and float are all 4 bytes long
* we will measure everything in kilohertz to allow the higher
* frequency ranges to be selected.
* Waveforms can be of the type SINE_WAVE, SQUARE_WAVE, or 
* TRIANGLE_WAVE.
*/
void AD9833 :: setFrequency(uint16_t waveType, double freqInKHz) {
	/*
	* According to the datasheet:
	* f = (clk / 2^28) * FREQREG
	*
	* The clock frequency is 12.5MHz so FREQREG
	* will always equal f * (2^28 / 12,500,000)
	*/

	//Pre-calculated magic number because the full numbers don't fit in 4-byte LONGs.
	float clock_multiplier = 2684356 / 125000;
	uint32_t REG_value = (uint32_t)((freqInKHz * clock_multiplier) * 1000);

	//Split in two MSB and LSB
	int16_t FREQ_MSB = (int16_t)((REG_value) >> 15);
	int16_t FREQ_LSB = (int16_t)(REG_value & 0x3FFF);

	//Combine with the command to write to FREQ0 register
	FREQ_MSB |= CMD_FREQ0_WRITE;
	FREQ_LSB |= CMD_FREQ0_WRITE;

	//Send commands
	sendControlCommand(waveType);
	sendCommand(FREQ_LSB);
	sendCommand(FREQ_MSB);
}

/*
* Send the reset command to the chip.
*/
void AD9833 :: reset() {
	sendCommand(CMD_RESET);
}

/*
* Sends the initial control command to prepare the
* chip to receive frequency information. This will
* also update the waveform.
* (Other features can be implemented here if
* required)
*/
void AD9833 :: sendControlCommand(uint16_t waveType) {
	uint16_t cmd_reg = 0;

	//OR together all the options that we want
	cmd_reg &= ~CMD_FREQ0_OUTPUT; //Use FREQ0 register for output
	cmd_reg |= waveType; //set sine wave form
	cmd_reg &= ~CMD_RESET; //Remove the reset bit to enable output

	//Send the command
	sendCommand(cmd_reg);
}

/*
* Sends a pre-written command to the control register
* of the AD9833 chip.
*/
void AD9833 :: sendCommand(int16_t cmd) {
	//Enable SPI transmission
	SPI.setDataMode(SPI_MODE2);

	//Set the function pin to LOW (active)
	digitalWrite(funcPin, LOW);

	//Send MSB first, LSB second
	SPI.transfer(highByte(cmd));
	SPI.transfer(lowByte(cmd));

	//Set the function pin inactive
	digitalWrite(funcPin, HIGH);
}
