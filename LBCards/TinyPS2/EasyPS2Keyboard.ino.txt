// ***********************************************************************
// ***** EASY ARDUINO PS/2 KEYBOARD READ OUT by Carsten Herting 2020 *****
// ***********************************************************************
// See end of file for license information.

// Lookup table (in: SHIFT state and PS2 scancode => out: desired ASCII code) change for your country
// QWERTZ layout
char ScancodeToASCII[2][128] = {
  { 0,0,0,0,0,0,0,0,         0,0,0,0,0,9,94,0,         0,0,0,0,0,113,49,0,       0,0,121,115,97,119,50,0,    // w/o SHIFT or ALT(GR)
    0,99,120,100,101,52,51,0,0,32,118,102,116,114,53,0,0,110,98,104,103,122,54,0,0,0,109,106,117,55,56,0,
    0,44,107,105,111,48,57,0,0,46,45,108,148,112,0,0,  0,0,132,0,129,96,0,0,     0,0,10,43,0,35,0,0,
    0,60,0,0,0,0,8,0,        0,0,0,0,0,0,0,0,          0,0,0,0,0,0,27,0,         0,0,0,0,0,0,0,0  },
  { 0,0,0,0,0,0,0,0,         0,0,0,0,0,0,248,0,        0,0,0,0,0,81,33,0,        0,0,89,83,65,87,34,0,       // with SHIFT
    0,67,88,68,69,36,0,0,    0,0,86,70,84,82,37,0,     0,78,66,72,71,90,38,0,    0,0,77,74,85,47,40,0,
    0,59,75,73,79,61,41,0,   0,58,95,76,153,80,63,0,   0,0,142,0,154,0,0,0,      0,0,0,42,0,39,0,0,
    0,62,0,0,0,0,0,0,        0,0,0,0,0,0,0,0,          0,0,0,0,0,0,0,0,          0,0,0,0,0,0,0,0  } };

// QWERTY layout
/*
char ScancodeToASCII[2][128] = {
  { 0,0,0,0,0,27,27,0,         0,0,0,0,0,9,96,0,         0,0,0,0,0,113,49,0,       0,0,122,115,97,119,50,0,    // w/o SHIFT or ALT(GR)
    0,99,120,100,101,52,51,0,0,32,118,102,116,114,53,0,0,110,98,104,103,121,54,0,0,0,109,106,117,55,56,0,
    0,44,107,105,111,48,57,0,0,46,47,108,59,112,45,0,  0,0,39,0,91,61,0,0,     0,0,10,93,0,124,0,0,
    0,60,0,0,0,0,8,0,        0,49,0,52,55,0,0,0,          0,46,50,53,54,56,27,0,         0,43,51,45,42,57,0,0  },
  { 0,0,0,0,0,0,0,0,         0,0,0,0,0,0,126,0,        0,0,0,0,0,81,33,0,        0,0,90,83,65,87,64,35,       // with SHIFT
    0,67,88,68,69,36,35,0,    0,32,86,70,84,82,37,0,     0,78,66,72,71,89,94,0,    0,0,77,74,85,38,42,0,
    0,60,75,73,79,41,40,0,   0,62,63,76,58,80,95,0,   0,0,34,0,123,43,0,0,      0,0,0,125,0,92,0,0,
    0,62,0,0,0,0,0,0,        0,0,0,0,0,0,0,0,          0,0,0,0,0,0,0,0,          0,0,0,0,0,0,0,0  } };
*/

void setup()
{
  noInterrupts();
    PCICR = 0b00000010;   // enable Port C pin change interrupt PCI "PCINT1"
    PCMSK1 = 0b00010000;  // unmask Pin A4 pin change interrupt PCI
  interrupts();
  Serial.begin(9600);
}

void loop() {}

ISR(PCINT1_vect)      // interrupt service routine
{
  int val = 0;
  for(int i=0; i<11; i++)
  {
    while(bitRead(PINC, 4) == true);
    val |= bitRead(PINC, 3)<<i;
    while(bitRead(PINC, 4) == false);    
  }
  val = (val>>1) & 255;

  static bool shiftIsActive = false;      // state of the SHIFT key
  static bool nextIsReleased = false;     // indicating that the next key was released

  switch (val)
  {
    case 18: case 89: shiftIsActive = !nextIsReleased; nextIsReleased = false; break;  // SHIFT LEFT, SHIFT RIGHT     
    case 240: nextIsReleased = true; break;                                            // key release indicator      
    default:                                                                           // any other key
      if (!nextIsReleased)                // is it a 'key pressed' event?
      {
        Serial.print(ScancodeToASCII[shiftIsActive][val & 127]);                       // do lookup raw -> ASCII
      }
      nextIsReleased = false;
      break;
  }
  PCIFR = 0x02;                           // clears the PCI flag 1
}

/*
------------------------------------------------------------------------------
This software is available under 2 licenses -- choose whichever you prefer.
------------------------------------------------------------------------------
ALTERNATIVE A - MIT License
Copyright (c) 2020 Carsten Herting
Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
of the Software, and to permit persons to whom the Software is furnished to do
so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
------------------------------------------------------------------------------
ALTERNATIVE B - Public Domain (www.unlicense.org)
This is free and unencumbered software released into the public domain.
Anyone is free to copy, modify, publish, use, compile, sell, or distribute this
software, either in source code form or as a compiled binary, for any purpose,
commercial or non-commercial, and by any means.
In jurisdictions that recognize copyright laws, the author or authors of this
software dedicate any and all copyright interest in the software to the public
domain. We make this dedication for the benefit of the public at large and to
the detriment of our heirs and successors. We intend this dedication to be an
overt act of relinquishment in perpetuity of all present and future rights to
this software under copyright law.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
------------------------------------------------------------------------------
*/
