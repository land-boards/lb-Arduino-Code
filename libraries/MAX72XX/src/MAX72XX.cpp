//library for using MAX7129 to drive 7-segment numerical displays

#include "Arduino.h"
#include "MAX72XX.hpp"

// MAX72XX

MAX72XX::MAX72XX(const uint8_t dataPin, const uint8_t clockPin,
								 const uint8_t loadPin, const uint8_t numDevices,
		 					   const uint8_t digitsPerDevice) :
	_dataPin(dataPin), _clockPin(clockPin), _loadPin(loadPin),
  _numDevices(numDevices), _digitsPerDevice(digitsPerDevice),
	_hardwareSPI(false), _decodeReg(new uint8_t[numDevices]())

{
	pinMode(_dataPin, OUTPUT);
	pinMode(_clockPin, OUTPUT);
	begin();
}

MAX72XX::MAX72XX(const uint8_t loadPin, const uint8_t numDevices,
								 const uint8_t digitsPerDevice)  :
	_dataPin(0), _clockPin(0), _loadPin(loadPin),
	_numDevices(numDevices), _digitsPerDevice(digitsPerDevice),
	_hardwareSPI(true), _decodeReg(new uint8_t[numDevices]())
{
	SPI.begin();
	begin();
}

void MAX72XX::begin() const
{
	pinMode(_loadPin, OUTPUT);

	writeRegister(Device::ALL, Address::DISPLAYTEST, 0x00);
	writeRegister(Device::ALL, Address::SCANLIMIT, _digitsPerDevice - 1);
	setIntensity(0x0F / 2);
	shutdown(false);
}

void MAX72XX::startWrite() const
{
	if (_hardwareSPI)
		SPI.beginTransaction(SPISettings(SPI_CLOCK_DIV2, MSBFIRST, SPI_MODE0));
	digitalWrite(_loadPin, LOW);
}

void MAX72XX::endWrite() const
{
	digitalWrite(_loadPin, HIGH);
	if (_hardwareSPI) SPI.endTransaction();
}

void MAX72XX::writeToDevice(const uint8_t addr, const uint8_t data) const
{
	switch (_hardwareSPI) {
		case true:
			SPI.transfer(addr);
			SPI.transfer(data);
			break;
		case false:
			shiftOut(_dataPin, _clockPin, MSBFIRST, addr);
			shiftOut(_dataPin, _clockPin, MSBFIRST, data);
			break;
	}
}

MAX72XX::Error MAX72XX::writeRegister(const uint8_t deviceNum,
																			const uint8_t address,
														 					const uint8_t data) const
{
	if (deviceNum >= _numDevices && deviceNum != (uint8_t)Device::ALL)
		return Error::INVALID_DEVICE;

	startWrite();
		for (uint8_t d = 0; d < _numDevices; d++) {
			uint8_t addr = (d == deviceNum || deviceNum == (uint8_t)Device::ALL)
				? address : (uint8_t)Address::NOOP;
			writeToDevice(addr, data);
		}
	endWrite();

	return Error::OK;
}

MAX72XX::Error MAX72XX::writeRegister(const Address address,
																			const uint8_t* data) const
{
	startWrite();
		for (uint8_t d = 0; d < _numDevices; d++)
			writeToDevice((uint8_t)address, data[d]);
	endWrite();

	return Error::OK;
}

MAX72XX::Error MAX72XX::writeRegister(const Device deviceNum,
																			const Address address,
																			const Character data) const
{
	return writeRegister((uint8_t)deviceNum, (uint8_t)address, (uint8_t)data);
}

MAX72XX::Error MAX72XX::writeRegister(const Device deviceNum,
																			const Address address,
																			const uint8_t data) const
{
	return writeRegister((uint8_t)deviceNum, (uint8_t)address, data);
}

MAX72XX::Error MAX72XX::writeRegister(const uint8_t deviceNum,
																		 	const Address address,
																			const uint8_t data) const
{
	return writeRegister(deviceNum, (uint8_t)address, data);
}

MAX72XX::Error MAX72XX::setIntensity(const uint8_t deviceNum,
																		 const uint8_t brightness) const
{
	return writeRegister(deviceNum, Address::INTENSITY, brightness);
}

MAX72XX::Error MAX72XX::setIntensity(const uint8_t brightness) const
{
	return writeRegister(Device::ALL, Address::INTENSITY, brightness);
}

MAX72XX::Error MAX72XX::setScanLimit(const uint8_t deviceNum,
																		 const uint8_t limit) const
{
	if (limit == 0 || limit > 8) return Error::INVALID_SCAN_LIMIT;
	return writeRegister(deviceNum, Address::SCANLIMIT, limit - 1);
}

MAX72XX::Error MAX72XX::setScanLimit(const uint8_t limit) const
{
	return setScanLimit((uint8_t)Device::ALL, limit);
}

MAX72XX::Error MAX72XX::shutdown(const uint8_t deviceNum,
																 const bool status) const {
	return writeRegister(deviceNum, Address::SHUTDOWN, (status) ? 0x00 : 0x01);
}

MAX72XX::Error MAX72XX::shutdown(const bool status) const {
	return writeRegister(Device::ALL, Address::SHUTDOWN, (status) ? 0x00 : 0x01);
}

MAX72XX::Error MAX72XX::setDecodeReg(const uint8_t digit, const uint8_t decode) {
	if (digit >= (_numDevices * _digitsPerDevice)) return Error::INVALID_DIGIT;

	bitWrite(_decodeReg[digit / _digitsPerDevice], digit % _digitsPerDevice, decode);

	return Error::OK;
}

MAX72XX::Error MAX72XX::update(const uint8_t start, const uint8_t numDigits,
										 					 MAX72XX_Digit_t* vram, const bool force)
{
	bool needUpdate = false;
	for (uint8_t digit = 0; digit < numDigits; digit++) {
		if (vram[digit].written == 0) needUpdate = true;
		Error err = setDecodeReg(start + digit, vram[digit].decode);
		if (err != Error::OK) return err;
	}

	if (needUpdate || force) {
		writeRegister(Address::DECODE, _decodeReg);

		for (uint8_t digit = 0; digit < numDigits; digit++)
			if (vram[digit].written == 0 || force) {
				writeDigit(start + digit, vram[digit].value);
				vram[digit].written = 1;
			}
	}

	return Error::OK;
}

MAX72XX::Error MAX72XX::update(const uint8_t start, const uint8_t numDigits,
						 									 const uint8_t value, const bool decode)
{
	for (uint8_t digit = 0; digit < numDigits; digit++) {
		Error err = setDecodeReg(start + digit, (decode) ? 1 : 0);
		if (err != Error::OK) return err;
	}
	writeRegister(Address::DECODE, _decodeReg);

	for (uint8_t digit = 0; digit < numDigits; digit++)
		writeDigit(start + digit, value);

	return Error::OK;
}

MAX72XX::Error MAX72XX::update(const uint8_t start, const uint8_t numDigits,
						 									 const Character value)
{
	return update(start, numDigits, (uint8_t)value, true);
}

void MAX72XX::writeDigit(const uint8_t digit, const uint8_t value) const
{
	writeRegister(digit / _digitsPerDevice,
								(uint8_t)Address::DIGIT0 + (digit % _digitsPerDevice),
								value);
}

// MAX72XXDisplay

MAX72XXDisplay::MAX72XXDisplay(MAX72XX* max72xx, const uint8_t start,
															 const uint8_t numDigits) :
  _max72xx(max72xx), _start(start), _numDigits(numDigits),
	vram(new MAX72XX_Digit_t[_numDigits]()) {
	update();
}

MAX72XX::Error MAX72XXDisplay::update(const bool force) const
{
	return _max72xx->update(_start, _numDigits, vram, force);
}

void MAX72XXDisplay::fill(const uint8_t data, const bool decode)
{
	for (uint8_t d = 0; d < _numDigits; d++) writeChar(d, data, decode);
}

void MAX72XXDisplay::fill(const MAX72XX::Character data)
{
	fill((uint8_t)data, true);
}

MAX72XX::Error MAX72XXDisplay::writeChar(const uint8_t digit, const uint8_t data,
																				 const bool decode)
{
	if (digit >= _numDigits) return MAX72XX::Error::INVALID_DIGIT;

	if (vram[digit].value != data || vram[digit].decode != (decode) ? 1 : 0) {
		vram[digit].value = data;
		vram[digit].decode = (decode) ? 1 : 0;
		vram[digit].written = 0;
	}

	return MAX72XX::Error::OK;
}

MAX72XX::Error MAX72XXDisplay::writeChar(const uint8_t digit,
																				 const MAX72XX::Character data)
{
	return writeChar(digit, (uint8_t)data, true);
}

MAX72XX::Error MAX72XXDisplay::setDecimalPoint(const uint8_t digit,
																							 const bool autoUpdate)
{
	if (digit >= _numDigits) return MAX72XX::Error::INVALID_DIGIT;

	if ((vram[digit].value & (uint8_t)MAX72XX::Character::DECIMALPOINT) == 0) {
		vram[digit].value |= (uint8_t)MAX72XX::Character::DECIMALPOINT;
		vram[digit].written = 0;
	}

	return (autoUpdate) ? update() : MAX72XX::Error::OK;
}

MAX72XX_Digit_t MAX72XXDisplay::readChar(const uint8_t digit) const
{
	switch (digit < _numDigits) {
		case true:
			return vram[digit];
		case false:
			MAX72XX_Digit_t err;
			err.error = 1;
			return err;
	}
}

MAX72XX::Error MAX72XXDisplay::doWriteNumber(const int32_t num,
																						 const uint8_t paddingChar,
									 								 					 const bool decodePadding,
																	 				 	 const int8_t decimalPlaces,
									 							 	 		 			 const bool autoUpdate)
{
	uint8_t digit = 0;
	for (uint32_t number = abs(num);
			 digit < _numDigits && number != 0;
			 digit++, number /= 10) {
		MAX72XX::Error err = writeChar(digit, number % 10, true);
		if (err != MAX72XX::Error::OK) return err;
	}

	while (digit <= decimalPlaces && digit < _numDigits) {
		MAX72XX::Error err = writeChar(digit++,  MAX72XX::Character::ZERO);
		if (err != MAX72XX::Error::OK) return err;
	}

	if (num < 0) {
		MAX72XX::Error err = writeChar(digit++, MAX72XX::Character::DASH);
		if (err != MAX72XX::Error::OK) return err;
	}

	while (digit < _numDigits) {
		MAX72XX::Error err = writeChar(digit++,  paddingChar, decodePadding);
		if (err != MAX72XX::Error::OK) return err;
	}

	if (decimalPlaces >= 0) {
		MAX72XX::Error err = setDecimalPoint(decimalPlaces, false);
		if (err != MAX72XX::Error::OK) return err;
	}

  return (autoUpdate) ? update() : MAX72XX::Error::OK;
}

MAX72XX::Error MAX72XXDisplay::writeNumber(const int32_t num,
																					 const uint8_t paddingChar,
																 					 const int8_t decimalPlaces,
																					 const bool autoUpdate)
{
	return doWriteNumber(num, paddingChar, false, decimalPlaces, autoUpdate);
}

MAX72XX::Error MAX72XXDisplay::writeNumber(const int32_t num,
																					 const MAX72XX::Character paddingChar,
																 					 const int8_t decimalPlaces,
																					 const bool autoUpdate)
{
	return doWriteNumber(num, (uint8_t)paddingChar, true, decimalPlaces, autoUpdate);
}

MAX72XX::Error MAX72XXDisplay::writeNumber(const float num,
																					 const uint8_t paddingChar,
												 				 					 const int8_t decimalPlaces,
																					 const bool autoUpdate)
{
	return doWriteNumber(int32_t(num * pow(10.0, decimalPlaces)), paddingChar,
											 false, decimalPlaces,	autoUpdate);
}

MAX72XX::Error MAX72XXDisplay::writeNumber(const float num,
																					 const MAX72XX::Character paddingChar,
												 				 					 const int8_t decimalPlaces,
																					 const bool autoUpdate)
{
	return doWriteNumber(int32_t(num * pow(10.0, decimalPlaces)),
											 (uint8_t)paddingChar, true,
											 decimalPlaces, autoUpdate);
}

MAX72XX::Error MAX72XXDisplay::shutdown(const bool status) const {
	switch (status) {
		case true:
			return _max72xx->update(_start, _numDigits, MAX72XX::Character::BLANK);
		case false:
			return update(true);
	}
}
