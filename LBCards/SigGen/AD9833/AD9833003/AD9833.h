#ifndef __AD9833__
#define __AD9833__

#include <Arduino.h>
#include<SPI.h>

//Pre-defined commands from the datasheet
#define CMD_RESET         0x100
#define CMD_FREQ0_WRITE   0x4000
#define CMD_FREQ0_OUTPUT  0x800
//These are the supported waveform types:
#define SINE_WAVE         0x2000
#define TRIANGLE_WAVE     0x2002
#define SQUARE_WAVE       0x2028

class AD9833 {
public:
	AD9833();

	void begin(uint8_t funcPin);

	void setFrequency(uint16_t waveType, double freqInKHz);

	void reset();

private:
	void sendControlCommand(uint16_t waveType);

	void sendCommand(int16_t cmd);
};

#endif