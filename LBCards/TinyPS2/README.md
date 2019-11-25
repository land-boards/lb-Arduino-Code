PS/2 Keyboard to TTL Serial Adapter
Scott Baker, smbaker@gmail.com

This program implements a receiver for a PS/2 keyboard, decodes the scan keys,
and sends them out as a serial stream. The purpose (or at least my purpose) was
to connect a PS/2 keyboard to a retrocomputer that featured only a TTL serial
input. 

This is based almost entirely on other peoples' work, see the attribution section below.
I found a PS/2 keyboard library and a soft-uart library and hooked them together.

Pin Assignments:
   PB0 - PS/2 data
   PB1 - PS/2 CLK
   PB2 - Serial Out

Attribution:
   ATTiny85 UART Library 
      The Garage Lab
      https://github.com/thegaragelab/tinytemplate
      Creative Commons Attribution-ShareAlike 4.0 International License (http://creativecommons.org/licenses/by-sa/4.0/)

   PS/2 Keyboard Library
      Interrupts: Interfacing a Microcontroller with a PS/2 Keyboard
      http://www.nerdkits.com/videos/interrupts_and_ps2_keyboard/

License:
   Creative Commons Attribution-ShareAlike 4.0 International License (http://creativecommons.org/licenses/by-sa/4.0/)
