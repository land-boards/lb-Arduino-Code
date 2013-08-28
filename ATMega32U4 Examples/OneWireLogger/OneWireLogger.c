/*
 One Wire Data Logger Firmware					
*/

#include <avr/io.h>
#include <util/delay.h>
#include <inttypes.h>

// Blinks LED connected between PD7 and VCC
// PB2 on GVS-32U4 board is near the reset switch wiring

void setup(void);
void loop(void);

int main (void)
{
	setup();
	while(1)
		loop();
}

void setup(void)
{
	CLKPR = 0x80; 	// Enable writing to the clock prescaler register
	CLKPR = 0x00;	// Clock divided by 1
	DDRD = 0x80;	// set PORTB LED pins for output
}

void loop(void)
{
	PORTD = 0x80;
	_delay_ms(1000);
	PORTD = 0x00;
	_delay_ms(1000);
}
