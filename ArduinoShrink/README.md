# ArduinoShrink
This library replaces Arduino AVR Core functions with smaller and faster versions, with the same or better functionality. It is designed for the ATmega168 and 328 MCUs at 4 to 16 MHZ, though only 8MHz and 16Mhz are regularly tested.
The Arduino Blink example sketch built for the Uno takes 924 bytes of flash, but only needs 196 bytes with ArduinoShrink.

## Usage
Download [a release](https://github.com/nerdralph/ArduinoShrink/releases), and extract the files into your Arduino/libraries folder.  Select ArduinoShrink from the Sketch, Include Library menu.  This will replace several Arduino functions with smaller and faster versions. When using multiple libraries, ArduinoShrink must be the last library included in the sketch code. 

## Design and Implemenation
I've written <a href="http://nerdralph.blogspot.com/2021/04/honey-i-shrunk-arduino-core.html">a blog post</a> discussing the implementation details of ArduinoShrink.  Version 0.7.0 supports manipulation of pins that are not known at compile-time.  When the pin is known at compiletime, digitalWrite() will still compile to a single "sbi" or "cbi" instruction.

