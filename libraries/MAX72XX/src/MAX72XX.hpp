#ifndef MAX72XX_h
#define MAX72XX_h

//library for using MAX7129 to drive 7-segment numerical displays

#include <Arduino.h>
#include <SPI.h>

typedef struct {
  uint8_t decode : 1,
					written : 1,
					error : 1;
  uint8_t value;
} MAX72XX_Digit_t;

class MAX72XX
{
	public:
		enum class Device : uint8_t {
			ALL	= 0xFF,
		};

		enum class Segment : uint8_t {
			A 	= 0b01000000,
			B 	= 0b00100000,
			C 	= 0b00010000,
			D 	= 0b00001000,
			E 	= 0b00000100,
			F 	= 0b00000010,
			G 	= 0b00000001,
			DP	= 0b10000000,
		};

		enum class Address : uint8_t {
			NOOP 				= 0x00,
			DIGIT0 			= 0x01,
			DIGIT1 			= 0x02,
			DIGIT2 			= 0x03,
			DIGIT3 			= 0x04,
			DIGIT4 			= 0x05,
			DIGIT5 			= 0x06,
			DIGIT6 			= 0x07,
			DIGIT7 			= 0x08,
			DECODE 			= 0x09,
			INTENSITY		=	0x0A,
			SCANLIMIT  	= 0x0B,
			SHUTDOWN 		= 0x0C,
			DISPLAYTEST = 0x0F,
		};

		enum class Character : uint8_t {
			ZERO 					= 0x00,
			ONE 					= 0x01,
			TWO 					= 0x02,
			THREE 				= 0x03,
			FOUR 					= 0x04,
			FIVE 					= 0x05,
			SIX 					= 0x06,
			SEVEN 				= 0x07,
			EIGHT 				= 0x08,
			NINE 					= 0x09,
			DASH 					= 0x0A,
			E 						= 0x0B,
			H 						= 0x0C,
			L 						= 0x0D,
			P 						= 0x0E,
			BLANK 				= 0x0F,
			DECIMALPOINT	=	(uint8_t)Segment::DP,
		};

		enum class Error : uint8_t {
			OK,
			INVALID_DIGIT,
			INVALID_DEVICE,
			INVALID_SCAN_LIMIT,
		};

		/*
			If using hardware SPI
			For other modules check the documentation.
			| Arduino     | ESP8266                | MAX7219/MAX7221 |
			| ----------- | ---------------------- | --------------- |
			| MOSI (11)   | GPIO13 (D7 HMOSI)      | DIN             |
			| SCK (13)    | CLK	GPIO14 (D5 HSCLK)  | CLK             |
			| a free GPIO | a free GPIO            | LOAD/CS         |
		*/

		MAX72XX(const uint8_t dataPin, const uint8_t clockPin,
						const uint8_t loadPin, const uint8_t numDevices = 1,
					  const uint8_t digitsPerDevice = 8);

		MAX72XX(const uint8_t loadPin, const uint8_t numDevices = 1,
					  const uint8_t digitsPerDevice = 8);

		Error writeRegister(const uint8_t deviceNum, const uint8_t address,
											 const uint8_t value) const;
	 	Error writeRegister(const Device deviceNum, const Address address,
											 const Character value) const;
	  Error writeRegister(const Device deviceNum, const Address address,
										   const uint8_t value) const;
	 	Error writeRegister(const uint8_t deviceNum, const Address address,
	 										 const uint8_t value) const;

		Error writeRegister(const Address address, const uint8_t* data) const;

		Error setIntensity(const uint8_t deviceNum, const uint8_t brightness) const;
		Error setIntensity(const uint8_t brightness) const;

		Error setScanLimit(const uint8_t deviceNum, const uint8_t limit) const;
		Error setScanLimit(const uint8_t limit) const;

		Error shutdown(const uint8_t deviceNum, const bool status) const;
		Error shutdown(const bool status) const;

		Error update(const uint8_t start, const uint8_t numDigits,
								 MAX72XX_Digit_t* vram, const bool force = false);

	  Error update(const uint8_t start, const uint8_t numDigits,
								 const uint8_t value, const bool decode = false);

	  Error update(const uint8_t start, const uint8_t numDigits,
								 const Character value);

		uint8_t digitsPerDevice() { return _digitsPerDevice; }

	private:
		void begin() const;
		Error setDecodeReg(const uint8_t digit, const uint8_t decode);
		void writeToDevice(const uint8_t addr, const uint8_t data) const;
		void writeDigit(const uint8_t digit, const uint8_t value) const;
		void startWrite() const;
		void endWrite() const;

		const uint8_t _dataPin, _clockPin, _loadPin, _numDevices, _digitsPerDevice;
		const bool _hardwareSPI;
		uint8_t* _decodeReg;
};

class MAX72XXDisplay
{
	public:
		MAX72XXDisplay(MAX72XX* max72xx, const uint8_t start,
									 const uint8_t numDigits);

    MAX72XX::Error update(const bool force = false) const;

    void fill(const uint8_t data, const bool decode = false);
		void fill(const MAX72XX::Character data);

		MAX72XX::Error writeChar(const uint8_t digit, const uint8_t data,
														 const bool decode = false);
		MAX72XX::Error writeChar(const uint8_t digit,
														 const MAX72XX::Character data);

		MAX72XX_Digit_t readChar(const uint8_t digit) const;

		MAX72XX::Error setDecimalPoint(const uint8_t digit,
                                   const bool autoUpdate = true);

		MAX72XX::Error writeNumber(const int32_t num,
															 const uint8_t paddingChar,
									 	 					 const int8_t decimalPlaces = -1,
															 const bool autoUpdate = true);
	  MAX72XX::Error writeNumber(const int32_t num,
															 const MAX72XX::Character paddingChar,
									 	 					 const int8_t decimalPlaces = -1,
															 const bool autoUpdate = true);

		MAX72XX::Error writeNumber(const float num,
															 const uint8_t paddingChar,
										 					 const int8_t decimalPlaces,
															 const bool autoUpdate = true);
		MAX72XX::Error writeNumber(const float num,
															 const MAX72XX::Character paddingChar,
										 					 const int8_t decimalPlaces,
															 const bool autoUpdate = true);

		MAX72XX::Error shutdown(const bool status) const;

	private:
		MAX72XX::Error doWriteNumber(const int32_t num,
																 const uint8_t paddingChar,
											 					 const bool decodePadding,
																 const int8_t decimalPlaces,
											 				 	 const bool autoUpdate);

		MAX72XX* _max72xx;
		const uint8_t _start, _numDigits;
		MAX72XX_Digit_t* vram;
};

#endif
