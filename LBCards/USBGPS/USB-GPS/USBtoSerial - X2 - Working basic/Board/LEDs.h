/*
             LEDs Library
     Copyright (C) Douglas Gilliland, 2012.

  doug [at] douglasgilliland [dot] com
           www.douglasgilliland.com
*/

/*
  Copyright 2012  Douglas Gilliland (doug [at] douglasgilliland [dot] com)

  Permission to use, copy, modify, distribute, and sell this
  software and its documentation for any purpose is hereby granted
  without fee, provided that the above copyright notice appear in
  all copies and that both that the copyright notice and this
  permission notice and warranty disclaimer appear in supporting
  documentation, and that the name of the author not be used in
  advertising or publicity pertaining to distribution of the
  software without specific, written prior permission.

  The author disclaim all warranties with regard to this
  software, including all implied warranties of merchantability
  and fitness.  In no event shall the author be liable for any
  special, indirect or consequential damages or any damages
  whatsoever resulting from loss of use, data or profits, whether
  in an action of contract, negligence or other tortious action,
  arising out of or in connection with the use or performance of
  this software.
*/

#include <avr/io.h>
#include <util/delay.h>
#include <inttypes.h>
#include "USBtoSerial.h"

void LEDs_SetAllLEDs(int LEDVal)
{
	if (LEDVal & 0x1)
		PORTB |= 0x80;
	else
		PORTB &= 0x7f;
	if (LEDVal & 0x2)
		PORTD |= 0x01;
	else
		PORTD &= 0xfe;
}

void LEDs_Init(void)
{
	DDRB = 0x80;
	PORTB &= 0x7f;
  DDRD = 0x01;
  PORTD &= 0xfe;
}


