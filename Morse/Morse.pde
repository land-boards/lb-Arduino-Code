// Author Erik Linder
// Released 2011 under GNU GPLv3
//
// Usage: morse( <pin number>, <speed WPM>, <1=beep, 0=PTT> )
//        sendmsg( "<text-to-send>" )
//

#include <Morse.h>

// Uncomment to beep a speaker at pin 9
Morse morse(9, 12, 1);

// Use pin 13 (built-in LED of Arduino 2009)
// Morse morse(13, 12, 0);

void setup()
{
  // Nothing here for the Morse lib
}

void loop()
{
  morse.sendmsg("HELLO WORLD!");
  delay (2000);
  morse.send(83);
  morse.send(77);
  morse.send(48);
  morse.send(82);
  morse.send(86);
  morse.send(86);
  delay (2000);
}
