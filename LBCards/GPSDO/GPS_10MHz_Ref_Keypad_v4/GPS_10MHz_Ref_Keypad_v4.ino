/*********************************************************************
SCULLCOM Hobby Electronics
10MHz GPS linked Frequency Standard
Software version 4.0v
Authors: Louis Scully and Andre Eisenbach
Special thanks to Andre for the hard work with coding the ublox library.
*********************************************************************/
// LCD RS pin to digital pin 7
// LCD Enable pin to digital pin 8
// LCD D4 pin to digital pin 9
// LCD D5 pin to digital pin 10
// LCD D6 pin to digital pin 11
// LCD D7 pin to digital pin 12
// LCD R/W pin connect to ground

#include <LiquidCrystal.h>
#include <Keypad.h>   //dowmload and add this library from http://playground.arduino.cc/uploads/Code/Keypad.zip

#include "ublox.h"

#define PIN_GPS_RX    14
#define PIN_GPS_TX    15

#define PIN_BUTTON1    3
#define PIN_BUTTON2    13

UBloxGPS gps(PIN_GPS_RX, PIN_GPS_TX);

LiquidCrystal lcd(7, 8, 9, 10, 11, 12); // (RS, E, D4, D5, D6, D7)

long StartFreq = 1000000;   //sets initial frequency of locked GPS frequency at 1MHz
long SetFreq = 0;
long NewFreq = 0;

const float R11 = 100000; //Resistor values in ohms for the volt meter divider
const float R12 = 47000;
const float RefVolt = 5; //use default reference of 5 volt on Arduino
float ResistorDivideFactor = 0;
float voltage_reading = 0;
float battery_voltage = 0;

char customKey;
const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {5, 4, 3, 2}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {16, 17, 18, 19}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS); 

void setup() {

  lcd.begin(16, 2);
  lcd.print("SCULLCOM");
  lcd.setCursor(0,1);
  lcd.print("Freq Standard");
  delay(3000);
  lcd.clear();
  
  lcd.setCursor(0,0);
  lcd.print("Frequency");

  gps.writeFrequency(StartFreq); //sets start up frequency when locked
  lcd.setCursor(0,1);
  lcd.print(StartFreq);
  lcd.setCursor(14,1);
  lcd.print("Hz");

}

void loop() {
customKey = customKeypad.getKey();
  switch(customKey) 
  {
  case '0' ... '9': // accept number input
    lcd.setCursor(0,0);
    SetFreq = SetFreq * 10 + (customKey - '0');
    lcd.setCursor(0,1);
    lcd.print(SetFreq);
    break;
  
  case 'A':                   //enter new frequency in Hertz
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Set Frequency");
    lcd.setCursor(0,1);
     break;

  case 'B':                   //send new frequency to GPS module
    NewFreq=SetFreq;
    gps.writeFrequency(NewFreq);
    delay(1000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Frequency");
    lcd.setCursor(0,1);
    lcd.print(NewFreq);
    lcd.setCursor(14,1);
    lcd.print("Hz");
    SetFreq = 0;
    break;

  case 'C':                   //battery voltage check
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Battery Check");
    voltage_reading = analogRead(A6);
    ResistorDivideFactor = 1023 * (R12/(R11+R12));
    battery_voltage = (voltage_reading * RefVolt)/ResistorDivideFactor;
    lcd.setCursor(0,1);
    lcd.print(battery_voltage,2);
    lcd.print(" Volts"); 
    break;

  case 'D':                  //display current frequency
    lcd.clear();
    lcd.print("Frequency");
    lcd.setCursor(0,1);
    lcd.print(NewFreq);
    lcd.setCursor(14,1);
    lcd.print("Hz");
    break;

  case '*':                   //For future upgrade
    
    break;

    
   case '#':                  //For future upgrade
    
    
    break;
  }
}
