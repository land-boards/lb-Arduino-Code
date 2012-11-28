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

//#define LEDMASK_USB_READY 
//#define LEDMASK_USB_ERROR
//#define LEDMASK_USB_NOTREADY 
//#define LEDMASK_USB_ENUMERATING

void LEDs_SetAllLEDs(int LEDVal)
{
	if (LEDVal & 0x1)
		PORTB |= 0x2;
	else
		PORTB &= 0xfd;
	if (LEDVal & 0x2)
		PORTB |= 0x4;
	else
		PORTB &= 0xfb;
}

void LEDs_Init(void)
{
	DDRB = 0x06;
	PORTB &= 0xfa;
}


