/* Version V1.0.5
  PS2KeyRaw.cpp - PS2KeyRaw library
  Copyright (c) 2007 Free Software Foundation.  All right reserved.
  Written by Paul Carpenter, PC Services <sales@pcserviceselectronics.co.uk>
    Update Jan-2020 Paul Carpenter, Improve conditionals for other platform support

  Stripped down version of PS2Keyboard to get every key code byte from a PS2 
  Keyboard for testing purposes. Enables capture of all bytes see example.

  IMPORTANT WARNING
 
    If using a DUE or similar board with 3V3 I/O you MUST put a level translator 
    like a Texas Instruments TXS0102 or FET circuit as the signals are 
    Bi-directional (signals transmitted from both ends on same wire).
 
    Failure to do so may damage your Arduino Due or similar board.

  Test History
    September 2014 Uno and Mega 2560 September 2014 using Arduino V1.6.0
    January 2016   Uno, Mega 2560 and Due using Arduino 1.6.7 and Due Board 
                    Manager V1.6.6

  Created September 2014 based, on PS2Keyboard which was
  Written by Christian Weichel <info@32leaves.net>
  ** Mostly rewritten Paul Stoffregen <paul@pjrc.com> 2010, 2011
  ** Modified for use beginning with Arduino 13 by L. Abraham Smith, <n3bah@microcompdesign.com> *
  ** Modified for easy interrupt pin assignment on method begin(datapin,irq_pin). Cuningan <cuninganreset@gmail.com> **
  V1.0.1 Modified September 2014 Paul Carpenter for easier state machines and parity checks
  V1.0.2 Modified January 2016 to improve interrupt assignment with new Arduino macros
  
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "PS2KeyRaw.h"

/* Private variable definition */
#define BUFFER_SIZE 16
volatile uint8_t buffer[ BUFFER_SIZE ];
volatile uint8_t head, tail;
uint8_t PS2_DataPin;

/* Private function declarations */
uint8_t get_scan_code( );

// The ISR for the external interrupt
// To receive 11 bits start, 8 data, ODD parity, stop
// Interrupt every falling incoming clock edge from keyboard
void ps2interrupt( void )
{
	static uint8_t bitcount = 0;      // Main state variable and bit count
	static uint8_t incoming;
    static uint8_t parity;
	static uint32_t prev_ms = 0;
	uint32_t now_ms;
	uint8_t val;

	val = digitalRead( PS2_DataPin );
	now_ms = millis();
	if( now_ms - prev_ms > 250 )
	  bitcount = 0;
	prev_ms = now_ms;
    bitcount++;         // Now point to next bit
    switch( bitcount )
       {
       case 1:  // Start bit
                incoming = 0;
                parity = 0;
                break;
       case 2:
       case 3:
       case 4:
       case 5:
       case 6:
       case 7:
       case 8:
       case 9:  // Data bits
                parity += val;        // another one received ?
                incoming >>= 1;       // right shift one place for next bit
                incoming |= ( val ) ? 0x80 : 0;    // or in MSbit
                break;
       case 10: // Parity check
                parity &= 1;          // Get LSB if 1 = odd number of 1's so parity should be 0
                if( parity == val )   // Both same parity error
                  parity = 0xFD;      // To ensure at next bit count clear and discard
                break;
       case 11: // Stop bit
                if( parity >= 0xFD )  // had parity error
                  {
                  // Should send resend byte command here currently discard
                  }
                else                  // Good so save byte in buffer
                  {
                  val = head + 1;
                  if( val >= BUFFER_SIZE )
                    val = 0;
                  if( val != tail )
                    {
                    buffer[ val ] = incoming;
                    head = val;
                    }
                  }
                bitcount = 0;
                break;
       default: // in case of weird error and end of byte reception re-sync
                bitcount = 0;
      }
}


uint8_t get_scan_code(void)
{
	uint8_t  i;

	i = tail;
	if( i == head )     // check for empty buffer
      return 0;
	i++;
	if( i >= BUFFER_SIZE )
      i = 0;
	tail = i;
	return buffer[ i ];
}


int8_t PS2KeyRaw::available()
{
int8_t  i;

i = head - tail;
if( i < 0 )
  i += BUFFER_SIZE;
return i;
}


int PS2KeyRaw::read()
{
uint8_t result;

result = 0;
if( ( result = available() ) )
  result = get_scan_code();
if( result == 0 )
  result = -1;
return result;
}


PS2KeyRaw::PS2KeyRaw() {
  // nothing to do here, begin() does it all
}


void PS2KeyRaw::begin( uint8_t data_pin, uint8_t irq_pin )
{
PS2_DataPin = data_pin;

// initialize the pins
#ifdef INPUT_PULLUP
pinMode(irq_pin, INPUT_PULLUP);
pinMode(data_pin, INPUT_PULLUP);
#else
pinMode(irq_pin, INPUT);
digitalWrite(irq_pin, HIGH);
pinMode(data_pin, INPUT);
digitalWrite(data_pin, HIGH);
#endif

// Initialise buffer indexes
head = 0;
tail = 0;

// Setup interrupt handler
attachInterrupt( digitalPinToInterrupt( irq_pin ), ps2interrupt, FALLING );
}

