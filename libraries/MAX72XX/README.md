# MAX72XX 7-segment display library

This is a library for writing to one or more 7-segment displays driven by a
MAX7219 or MAX7221 IC. It is inspired by Frost Sheridan's MAX7219 library
(<https://github.com/Frostion/MAX7219-arduino-library>).

## Using the library

There are two objects which must be created to use the library. The MAX72XX object
defines the interface to the MAX7219/MAX7221 driver chip; only one MAX72XX object is
required for each chain of devices. The MAX72XXDisplay object defines a range of
digits. There can be multiple MAX72XXDisplay objects based on how you want to
divide the physical displays. The order of the devices and digits is dependent on the
construction and orientation of the device.

## Characters

Characters maybe written using either the MAX72XX::Character constants
(MAX72XX Code B Font) or as uint8_t values defining the segments to be lit. As
the Code B Fonts for 0 - 9 are BCD, they can be passed and decoded if the decoded
function parameter is passed as true.

In the display buffer characters are stored as MAX72XX_Digit_t structs. If
the decode method is set to 1, the character value is decoded as a Code B Font
character, otherwise the value is used to determine the segments to be lit.

## Hardware SPI support

Hardware SPI support is enabled by using the MAX72XX object declaration which
omits the dataPin and clockPin parameters. If hardware SPI is enabled use the
pins shown below. For other modules check the module's documentation.

| Arduino     | ESP8266               | ESP32       | MAX7219/MAX7221 |
| ----------- | --------------------- | ----------- | --------------- |
| MOSI (11)   | GPIO13 (D7 HMOSI)     | GPIO 23     | DIN             |
| SCK (13)    | CLK GPIO14 (D5 HSCLK) | GPIO 18     | CLK             |
| A Free GPIO | A Free GPIO           | A Free GPIO | LOAD/CS         |

## Declaring the MAX72XX object

```c++

MAX7219 objectName(const uint8_t dataPin, const uint8_t clockPin,
                   const uint8_t loadPin, const uint8_t numDevices = 1,
                   const uint8_t digitsPerDevice = 8)

```

- **objectName** - the name of the object
- **dataPin** - the pin that is connected to the MAX72XX data/DIN pin
- **clockPin** - the pin that is connected to the MAX72XX clock pin
- **loadPin** - the pin that is connected to the MAX7XX load/CS pin
- **numDevices** - the number of devices chained together
- **digitsPerDevice** - the number of digits per device

```c++

MAX7219 objectName(const uint8_t loadPin, const uint8_t numDevices = 1,
                   const uint8_t digitsPerDevice = 8)

```

- **objectName** - the name of the object
- **loadPin** - the pin that is connected to the MAX7XX load/CS pin
- **numDevices** - the number of devices chained together
- **digitsPerDevice** - the number of digits per device

## Declaring the MAX72XX display object

```c++
MAX72XXDisplay objectName(MAX72XX* max7219, const uint8_t start,
                          const uint8_t numDigits)
```

- **objectName** - the name of the object
- **max7219** - the MAX72XX object to use
- **start** - the first digit of the display
- **numDigits** - the number of digits in the display

## Functions available

### MAX72XXDisplay

```c++
MAX72XX::Error update(const bool force = false)
```

Update the display. If force is true all the digits are written, if false only
changed digits are written. Note that only the digits of the given display are
updated.

```c++
void fill(const uint8_t data, const bool decode = false)
void fill(const MAX72XX::Character data)
```

Fill the display with the given character

```c++

MAX72XX::Error writeChar(const uint8_t digit, const uint8_t data,
                         const bool decode = false)
MAX72XX::Error writeChar(const uint8_t digit,
                         const MAX72XX::Character data)

```

Write a single character at the given digit position.

```c++

MAX72XX::Error setDecimalPoint(const uint8_t digit,
                               const bool autoUpdate = true)

```

Set the decimal point at given digit position.

```c++

MAX72XX_Digit_t readChar(const uint8_t digit)

```

Read the character at the given digit position. If the digit position passed is
invalid, the error member in the returned value is 1.

```c++

MAX72XX::Error writeNumber(const int32_t num, const uint8_t paddingChar,
                           const int8_t decimalPlaces = -1,
                           const bool autoUpdate = true)
MAX72XX::Error writeNumber(const int32_t num,
                           const MAX72XX::Character paddingChar,
                           const int8_t decimalPlaces = -1,
                           const bool autoUpdate = true)
MAX72XX::Error writeNumber(const float num, const uint8_t paddingChar,
                           const int8_t decimalPlaces,
                           const bool autoUpdate = true)
MAX72XX::Error writeNumber(const float num,
                           const MAX72XX::Character paddingChar,
                           const int8_t decimalPlaces,
                           const bool autoUpdate = true)

```

Write a number to the display. Both long and float numbers are supported. If
autoUpdate is true the display is updated before return.  To specify no decimal
point use the value -1.

```c++

MAX72XX::Error shutdown(const bool status)

```

Shutdown the display (only the digits controlled by this display are shutdown).

### MAX72XX

```c++

MAX72XX::Error writeRegister(const uint8_t deviceNum, const uint8_t address,
                             const uint8_t value)
MAX72XX::Error writeRegister(const Device deviceNum, const Address address,
                             const Character value)
MAX72XX::Error writeRegister(const Device deviceNum, const Address address,
                             const uint8_t value)
MAX72XX::Error writeRegister(const uint8_t deviceNum, const Address address,
                             const uint8_t value)

```

Write an address and data value to the given device.

```c++

MAX72XX::Error writeRegister(const Address address, const uint8_t* data)

```

Write an address and data value to all devices. The data value must be large
enough for all devices and in the correct order.

```c++

MAX72XX::Error setIntensity(const uint8_t deviceNum, const uint8_t brightness)
MAX72XX::Error setIntensity(const uint8_t brightness)

```

Set the intensity for the given device or all devices.

```c++

MAX72XX::Error setScanLimit(const uint8_t deviceNum, const uint8_t limit)
MAX72XX::Error setScanLimit(const uint8_t limit)

```

The sets how many digits are displayed, from 1 to 8, for the given device or
all devices. Since the number of scanned digits affects the display brightness,
this should not be used to blank portions of the display (such as leading zero
suppression).

```c++

MAX72XX::Error shutdown(const uint8_t deviceNum, const bool status)
MAX72XX::Error shutdown(const bool status)

```

Shutdown the given device or all devices. Shutdown can be
used to save power or as an alarm to flash the display by
successively entering and leaving shutdown mode.
Typically, it takes less than 250µs for the MAX7219/
MAX7221 to leave shutdown mode. The display driver
can be programmed while in shutdown mode, and
shutdown mode can be overridden by the display-test
function.

```c++

MAX72XX::Error update(const uint8_t start, const uint8_t numDigits,
                      MAX72XX_Digit_t* vram, const bool force = false)

```

Update a range of digits. See the Character section for the format of vram.

```c++

MAX72XX::Error update(const uint8_t start, const uint8_t numDigits,
                      const uint8_t value, const bool decode = false)
MAX72XX::Error update(const uint8_t start, const uint8_t numDigits,
                      const Character value)

```

Update a range of digits with a single value.

```c++

uint8_t digitsPerDevice()

```

Returns the configured number of digits per device.

## Constants available

### Devices

- **MAX72XX::Device::ALL** - All devices

### Segment

- **MAX72XX::Segment::A** - A Segment
- **MAX72XX::Segment::B** - B Segment
- **MAX72XX::Segment::C** - C Segment
- **MAX72XX::Segment::D** - D Segment
- **MAX72XX::Segment::E** - E Segment
- **MAX72XX::Segment::F** - F Segment
- **MAX72XX::Segment::G** - G Segment
- **MAX72XX::Segment::DP** - Decimal Point

### Characters (MAX72XX Code B Font)

- **MAX72XX::Character::ZERO** - 0
- **MAX72XX::Character::ONE** - 1
- **MAX72XX::Character::TWO** - 2
- **MAX72XX::Character::THREE** - 3
- **MAX72XX::Character::FOUR** - 4
- **MAX72XX::Character::FIVE** - 5
- **MAX72XX::Character::SIX** - 6
- **MAX72XX::Character::SEVEN** - 7
- **MAX72XX::Character::EIGHT** - 8
- **MAX72XX::Character::NINE** - 9
- **MAX72XX::Character::DASH** - Dash
- **MAX72XX::Character::E** - E
- **MAX72XX::Character::H** - H
- **MAX72XX::Character::L** - L
- **MAX72XX::Character::P** - P
- **MAX72XX::Character::BLANK** - Blank
- **MAX72XX::Character::DECIMALPOINT** - Decimal Point

### Address

- **MAX72XX::Address::NOOP** - No-Op
- **MAX72XX::Address::DIGIT0** - Digit 0
- **MAX72XX::Address::DIGIT1** - Digit 1
- **MAX72XX::Address::DIGIT2** - Digit 2
- **MAX72XX::Address::DIGIT3** - Digit 3
- **MAX72XX::Address::DIGIT4** - Digit 4
- **MAX72XX::Address::DIGIT5** - Digit 5
- **MAX72XX::Address::DIGIT6** - Digit 6
- **MAX72XX::Address::DIGIT7** - Digit 7
- **MAX72XX::Address::DECODE** - Decode Mode
- **MAX72XX::Address::INTENSITY** - Intensity
- **MAX72XX::Address::SCANLIMIT** - Scan Limit
- **MAX72XX::Address::SHUTDOWN** - Shutdown
- **MAX72XX::Address::DISPLAYTEST** - Display Test

### Error

- **MAX72XX::ERROR::OK** - No Error
- **MAX72XX::ERROR::INVALID_DIGIT** - Invalid Digit
- **MAX72XX::ERROR::INVALID_DEVICE** - Invalid Device

## How the segments map to bits

Each bit in the byte passed to a function in non-decode mode controls
one of the digit's 8 segments. The MAX72XX::Segment constants may be used to
refer to the desired segment.
![Chart of segments](https://i.imgur.com/IkFAebV.png)
