#include <avr/io.h>
#include <util/delay.h>
#include <inttypes.h>

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
	DDRB = 0x04;	// set PORTB LED pins for output
}

void loop(void)
{
	PORTB = 0x4;
	_delay_ms(1000);
	PORTB = 0x0;
	_delay_ms(1000);
}
