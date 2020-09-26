
#include <avr/sfr_defs.h>

#include <Arduino.h>
#include <TimerOne.h>

#include "BinaryUtils.h"
#include "dds.h"
#include "adc.h"
#include "oled.h"
#include "pcint.h"
//#include "spi_utils.h"
//Beginning of Auto generated function prototypes by Atmel Studio
void doTimer1Int();
//End of Auto generated function prototypes by Atmel Studio


volatile const uint8_t adc0 = (1<<ADLAR) | 0;
volatile const uint8_t adc1 = (1<<ADLAR) | 1;
int gain, offset;
int tmp = 0;

volatile int ohms = 0;

// Declared weak in Arduino.h to allow user redefinitions.
int atexit(void (* /*func*/ )()) { return 0; }

// Weak empty variant initialization function.
// May be redefined by variant files.
//void initVariant() __attribute__((weak));
//void initVariant() { }

void setupUSB() __attribute__((weak));
void setupUSB() { }

// controls the mode behavior (sweep/normal)
void doTimer1Int()
{ 
  dds_callback_func();
}

void setup() 
{
  Serial.begin(9600);
  
  Timer1.initialize(clkspeed);
  Timer1.attachInterrupt(doTimer1Int);
  
  setup_pcint();

  adc_setup();
  oled_setup();
  
  
  pinMode (digipot_ss_pin, OUTPUT);
  digitalWrite(digipot_ss_pin, HIGH);
  pinMode (dds_ss_pin, OUTPUT);
  digitalWrite(dds_ss_pin, HIGH);
  SPI.begin();
  
  digipot_write_spi(MCP_WRITEPB0, TriUnityLvl, digipot_ss_pin);
  digipot_write_spi(MCP_WRITEPB0, SquareUnityLvl, digipot_ss_pin);
  digipot_write_spi(MCP_WRITEPB0, SineUnityLvl, digipot_ss_pin);

  digipot_write_spi(MCP_WRITEPB1, TriOffsetLvl, digipot_ss_pin);
  digipot_write_spi(MCP_WRITEPB1, SquareOffsetLvl, digipot_ss_pin);
  digipot_write_spi(MCP_WRITEPB1, SineOffsetLvl, digipot_ss_pin);
}

void loop() 
{
  oled_draw();
}


int main(void)
{
	
	init();

	//initVariant();

		
	
	setup();
	
	for (;;) {
		loop();
		if (serialEventRun) serialEventRun();
	}
	
	return 0;
}










