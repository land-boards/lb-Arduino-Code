# arduino-lib-MCP42010
Arduino library for using the MCP42010 digital potentiometer with SPI

This simple class makes it easy to use an MCP42010 digital potentiometer with 2 pots. It's also tested and confirmed to work fine with an MCP41010 with a single pot. Other chips from the same family will probably work fine too.

The library uses bit banging for SPI, because I wanted to use it with an ESP8266 using the Arduino IDE and couldn't get hardware SPI to work reliably (yet).

Tested on an Arduino UNO and an ESP8266 using the [Arduino IDE for ESP8266](https://github.com/esp8266/Arduino).

You can quickly install this library by downloading [this .ZIP file](https://github.com/mensink/arduino-lib-MCP42010/releases/download/v1.0/MCP42010.zip) and use the "Add .ZIP library" in the Arduino IDE.
