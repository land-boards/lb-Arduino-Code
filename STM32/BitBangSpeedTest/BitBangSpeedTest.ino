/*
  Blink
  Turns on an LED on and off, repeatedly.

  STM32 code
  
  Downloaded per:
  https://circuitdigest.com/microcontroller-projects/getting-started-with-stm32-development-board-stm32f103c8-using-arduino-ide
  
 */

#define ON_BOARD_LED 5

// the setup function runs once when you press reset or power the board
void setup() 
{
  // initialize digital pin PC13 as an output.
  pinMode(ON_BOARD_LED, OUTPUT);
}

// the loop function runs over and over again forever
void loop() 
{
  digitalWrite(ON_BOARD_LED, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(ON_BOARD_LED, LOW);    // turn the LED off by making the voltage LOW
}
