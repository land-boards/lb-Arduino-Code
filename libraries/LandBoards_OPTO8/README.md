This code is based on the [Adafruit MCP23008 driver](https://github.com/adafruit/Adafruit-MCP23008-library).

[https://www.arduino.cc/en/Guide/Libraries?setlang=en#importing-a-zip-library Importing an Arduino ZIP library]

The Adafruit driver was "very much beta" with the following features:

* "it seems to work fine"
* "sets pin directions"
* "sets inputs and outputs"
* "turns off and the pull-up resistors"

The Adafruit driver also had the following caveats:

* "it's not optimized:
* "doesn't suport the interrupt capability of the chip"
* It also didn't support multiple different chips.

Check [the datasheet for more info](http://ww1.microchip.com/downloads/en/DeviceDoc/21919b.pdf).

We have extended the driver to:

* TODO - Supports multiple chips
* TODO - Support interrupts
