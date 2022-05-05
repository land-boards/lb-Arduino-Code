// TinyPS02 - Read PS/2 Keyboard, write Serial data out

#include <PS2Keyboard_ATT85.h>
// #include <SoftwareSerial.h>

const int DataPin = 0;
const int IRQpin =  1;

// #define rxPin 3
#define txPin 2

// Set up SoftwareSerial and PS/2 objects
// SoftwareSerial mySerial =  SoftwareSerial(rxPin, txPin);
PS2Keyboard_ATT85 keyboard;

void setup() {

//  pinMode(rxPin, INPUT_PULLUP);
  pinMode(txPin, OUTPUT);
  tx_pin_write(HIGH);
//  mySerial.begin(9600);
  
  keyboard.begin(DataPin, IRQpin);
}

void loop() {
  char c;
  if (keyboard.available()) 
  {
    c = keyboard.read();    // read the next key
    outSer(c);
  }
}

const uint16_t _tx_delay = 112;
const int XMIT_START_ADJUSTMENT = 5;


void outSer(uint8_t b)
{
  uint8_t oldSREG = SREG;
  uint8_t _inverse_logic = 0;
  //cli();  // turn off interrupts for a clean txmit

  // Write the start bit
  tx_pin_write(_inverse_logic ? HIGH : LOW);
  tunedDelay(_tx_delay + XMIT_START_ADJUSTMENT);

  // Write each of the 8 bits
  if (_inverse_logic)
  {
    for (byte mask = 0x01; mask; mask <<= 1)
    {
      if (b & mask) // choose bit
        tx_pin_write(LOW); // send 1
      else
        tx_pin_write(HIGH); // send 0
    
      tunedDelay(_tx_delay);
    }

    tx_pin_write(LOW); // restore pin to natural state
  }
  else
  {
    for (byte mask = 0x01; mask; mask <<= 1)
    {
      if (b & mask) // choose bit
        tx_pin_write(HIGH); // send 1
      else
        tx_pin_write(LOW); // send 0
    
      tunedDelay(_tx_delay);
    }

    tx_pin_write(HIGH); // restore pin to natural state
  }

  //SREG = oldSREG; // turn interrupts back on
  tunedDelay(_tx_delay);
  
  return 1;
}

inline void tunedDelay(uint16_t delay) { 
  uint8_t tmp=0;

  asm volatile("sbiw    %0, 0x01 \n\t"
    "ldi %1, 0xFF \n\t"
    "cpi %A0, 0xFF \n\t"
    "cpc %B0, %1 \n\t"
    "brne .-10 \n\t"
    : "+r" (delay), "+a" (tmp)
    : "0" (delay)
    );
}

void tx_pin_write(uint8_t pin_state)
{
  digitalWrite(txPin,pin_state);
}
