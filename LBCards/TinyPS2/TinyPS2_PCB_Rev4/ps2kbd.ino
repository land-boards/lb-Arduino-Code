// From
//  http://www.nerdkits.com/videos/interrupts_and_ps2_keyboard/

#include <stdio.h>

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <inttypes.h>

#include <util/delay.h>

#include "softuart.h"
#include "keymap.h"

//volatile uint8_t kbd_data;
//volatile uint8_t char_waiting;
//uint8_t started;
//uint8_t bit_count;
//uint8_t shift;
//uint8_t caps_lock;
//uint8_t extended;
//uint8_t release;
//
void init_keyboard()
{
  started = 0;
  kbd_data = 0;
  bit_count = 0;
  
  //make PB1 input pin
  //DDRB &= ~(1<<PB1);
  //turn on pullup resistor
  PORTB |= (1<<PB1);
  
  //Enable PIN Change Interrupt 1 - This enables interrupts on pins
  GIMSK |= (1<<PCIE);
  
  //Set the mask on Pin change interrupt 1 so that only PCINT1 (PB1) triggers
  //the interrupt.
  PCMSK |= (1<<PCINT1);
}

ISR(PCINT0_vect){

  //make sure clock line is low, if not ignore this transition
  if(PINB & (1<<PB1)){
    return;
  }

  //if we have not started, check for start bit on DATA line
  if(!started){
    if ( (PINB & (1<<PB0)) == 0 ) {
      started = 1;
      bit_count = 0;
      kbd_data = 0;
      //printf_P(PSTR("%d"),started);
      return;
    }
  } else if(bit_count < 8) { //we started, read in the new bit
    //put a 1 in the right place of kdb_data if PC2 is high, leave
    //a 0 otherwise
    if(PINB & (1<<PB0)){
      kbd_data |= (1<<bit_count);
    }
    bit_count++;
    return;
  } else if(bit_count == 8){ //pairty bit
    //not implemented
    bit_count++;
    return;
  } else {  //stop bit
    //should check to make sure DATA line is high, what to do if not?
    started = 0;
    bit_count = 0;
  }

  if(kbd_data == 0xF0){ //release code
    release = 1;
    kbd_data = 0;
    return;
  } else if ((kbd_data == 0x12) || (kbd_data == 0x59)) { //handle shift key
    if(release == 0){
      shift = 1;
    } else {
      shift = 0;
      release = 0;
    }
    return;
  } else { //not a special character
    if(release){ //we were in release mode - exit release mode
      release = 0;
      //ignore that character
    } else {
      char_waiting = 1;
    }
  }

}

char render_scan_code(uint8_t data){
  char to_ret;
  if (shift) {
      to_ret = pgm_read_byte(&(hkeymap[data]));
  } else {
      to_ret = pgm_read_byte(&(lkeymap[data]));
  }
  return to_ret;
}

uint8_t read_char(){
  while(!char_waiting){
     //wait for a character
  }
  char_waiting = 0;
  return kbd_data;
}
