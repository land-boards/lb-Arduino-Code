PS2KeyRaw additional information

Library to handle the two wire communications from a PS2 keyboard. See image
in extras\Images called NUMLock-77.png for the one byte sequence on the two 
wires for the one byte code from the Numlock key.

Library performs raw get of characters sent from keyboard, discards
characters with parity errors.

Example included of SimpleTest.ino allows monitoring keycodes in hex on serial
To connect to your Arduino change following lines to match your wiring.

    const int DataPin = 4;
    const int IRQpin = 3;

Make sure you have data and clock wires connected correctly. Clock wire
MUST be connected to an interrupt pin.

Do NOT use Pin 13 for either clock or data wires

PS2KeyRaw requires both pins specified for begin()

keyboard.begin( data_pin, irq_pin );

Valid irq pins:
     Arduino Uno:  2, 3
     Arduino Due:  All pins, except 13 (LED)
     Arduino Mega: 2, 3, 18, 19, 20, 21
     Teensy 2.0:   All pins, except 13 (LED)
     Teensy 2.0:   5, 6, 7, 8
     Teensy 1.0:   0, 1, 2, 3, 4, 6, 7, 16
     Teensy++ 2.0: 0, 1, 2, 3, 18, 19, 36, 37
     Teensy++ 1.0: 0, 1, 2, 3, 18, 19, 36, 37
     Sanguino:     2, 10, 11

See also file websites.txt for website information about PS2 interface, protocol
scancodes and UTF-8 encoding.

Paul Carpenter
PC Services
January 2016
http://www.pcserviceselectronics.co.uk