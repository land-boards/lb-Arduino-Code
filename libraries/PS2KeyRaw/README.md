# PS2KeyRaw
## Arduino PS2 keyboard interface light footprint all bytes from keyboard

V1.0.4 October 2018 Fix wrong numbers reported for PS2KeyRaw::available() and simplify

V1.0.3 July 2018 Improved keywords file

First Public Release Version V1.0.2

Smaller footprint than any others found

For other versions that convert the up to 8 byte keycode sequences to a single integer for all keyboard types or allow you to get the full UTF-8 configurable for any LATIN keyboard with extra functions keys as simple codes see associated reporitories for PS2KeyAdvanced and PS2KeyMap libraries. Yes these libraries even provide codes for multimedia keys and Function keys F1 to F24 (yes that is F24).

### Platforms

- Arduino AVR - tested on Uno and Mega 2560
- Arduino SAM - tested on DUE

### Test Environment
   - All platforms versions of test R3 Hardware
   - Arduino V1.6.7
   - DUE Board Manager package V1.6.6
 
## Important Hardware Notes
 1.  Make sure you have data and clock wires connected correctly. Clock wire MUST be connected to an interrupt pin.
   - Do NOT use Pin 13 for either clock or data wires
   - PS2KeyRaw requires both pins specified for begin() as in  keyboard.begin( data_pin, irq_pin );
   - Valid irq pins:
     - Arduino Uno:  2, 3
     - Arduino Due:  All pins, except 13 (LED)
     - Arduino Mega: 2, 3, 18, 19, 20, 21
     - Teensy 2.0:   All pins, except 13 (LED)
     - Teensy 2.0:   5, 6, 7, 8
     - Teensy 1.0:   0, 1, 2, 3, 4, 6, 7, 16
     - Teensy++ 2.0: 0, 1, 2, 3, 18, 19, 36, 37
     - Teensy++ 1.0: 0, 1, 2, 3, 18, 19, 36, 37
     - Sanguino:     2, 10, 11

 2.  When using DUE or other boards with 3V3 I/O you *MUST* use a level translator FET or IC like Texas Instruments TXS0102 or similar as most keyboards not only operate at 5V but the two wire communications are pulled up by a resistor to 5V at the keyboard end

### Introduction

After looking round for suitable libraries I found most were lacking in functionality and high in code and data footprint, so I created a series of PS2 Keyboard libraries. The first here is the simplest one suitable for testing your keyboard hardware and understanding what keyboard protocol is.

The PS2 Keyboard interface is still needed for systems that have no USB and even if you have USB, you want it left for other uses.

The PS2 Keyboard interface is a *Bi-directional* two wire interface with a clock line and a data line which you connect to your Arduino (see above), the keyboard protocol has many nuances all of which are used in the other libraries of this series. this library allows you to access the keycodes sent from a keyboard into its small buffer and read out the codes with simple methods
    - available() return count of bytes waiting
    - read() return next byte in keycode buffer
    
### Installation

Performed by standard zip file library inclusion into Arduino IDE

### Examples

This library has ONE example, SimpleTest that uses the serial port to output the codes received on every keystroke and auto-repeat, some keyboards change codes on auto-repeat; which you will be able to see for yourself.

#### Contributor and Author Details

Author   Paul Carpenter, PC Services
Web Site http://www.pcserviceselectronics.co.uk
