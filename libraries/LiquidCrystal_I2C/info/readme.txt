LiquidCrystal_I2C V1.0

The LiquidCrystal_I2C library is a modified version of the standard LiquidCrystal library as found on 
the Arduino website.
This library is intended to be used when a parallel HD44780 compatible LCD is controlled over I2C using 
a PCF8574 extender (see datasheet for details).
4 of the 8 outputs are used for LDC data lines 4 to 7.
3 outputs are used for the Enable, register-select and Read/Write lines.
The one output left can be used to control the backlight of the LCD (if available).
For backlight control some extra resistors and a pnp-type transistor are required (for details see 
schematic diagram).

The PCF8574 extender is available in two versions, the PCF8574 and the PCF8574A.
The only difference between the two is the I2C base address.
The base address for the PCF8574=0x20 and the base address for the PCF8574A is 0x38.
The examples included in this zip file assume the use of an PCF8574 set for address 0x20 
(A0, A1 and A3 grounded).

For compatibility reasons this library contains some aliases for functions that are known under different 
names in other libraries. This should make it fairly easy to implement the library in existing sketches 
without changing to much code.
Functions not supported by this library will return nothing at all and in case a return value is expected 
the function will return 0.

Currently (sept. 2009) the library is tested with Arduino Duemilanove & IDE 0016.
LCD's tested: 
  TRI-T CG046-3007 A00 (2 x 16 with 20mA backlight)
  Sure DE-LM220        (4 x 20 with 10mA backlight)

Update:
User submitted compatibility notifications:
AV-DISPLAY  LCD 0802 (2 X 8  with LED (GREEN/K) Negative) on Duemilanove & IDE 0017. By Federico Galli

Download latest version from:  
http://www.xs4all.nl/~hmario/arduino/LiquidCrystal_I2C/LiquidCrystal_I2C.zip

Mario H.
atmega@xs4all.nl