/*********************************************************************
SCULLCOM Hobby Electronics
10MHz GPS linked Frequency Standard
Software version 6.0v
24th March 2016
Keypad frequency entry and Satellite data
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

#include <LiquidCrystal.h>  //LCD library
#include <Keypad.h>   //dowmload and add this library from http://playground.arduino.cc/uploads/Code/Keypad.zip

#include "ublox.h"

#define PIN_GPS_RX    255 //was 14 changed to 255 a nonexsistent pin number used to free up a pin
#define PIN_GPS_TX    15  //to GPS module RX pin

UBloxGPS gps(PIN_GPS_RX, PIN_GPS_TX);   //PIN_GPS_TX is connected to the RX pin on the GPS module.

SoftwareSerial GPSreceiver (14,255); //14 (A0) is RX in on Arduino connected to GPS TX pin. 255 a nonexsistent pin number used to free up a pin

LiquidCrystal lcd(7, 8, 9, 10, 11, 12); // (RS, E, D4, D5, D6, D7)

long StartFreq = 1000000;   //sets initial frequency of locked GPS frequency at 1MHz
long SetFreq = 0;
float NewFreq = StartFreq;
float CurrentFrequency = 0;

const float R11 = 100000; //Resistor values in ohms for the volt meter divider
const float R12 = 47000;
const float RefVolt = 5; //use default reference of 5 volt on Arduino
float ResistorDivideFactor = 0;
float voltage_reading = 0;
float battery_voltage = 0;

String sats;        //number of satellites detected
String GPGGAdata;   //satellte data string from GPS module
String FreqStatus;  //used to print Frequency locked if applicable
int satNum;         //number of satellites detected as an interger

String range;       //frequency range for display either MHz, KHz or Hz
int decimalPlaces;  //number of decimal places used dependant on range

char customKey;     //key pressed
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

  Serial.begin(57600);
  GPSreceiver.begin(9600);

  lcd.begin(16, 2);
  lcd.print("SCULLCOM");
  lcd.setCursor(0,1);
  lcd.print("Freq Standard v6");
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
    displayCurrentFrequency();
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
    displayCurrentFrequency();
    break;

  case '*':                   //For future upgrade
    
    break;

    
  case '#':                  //Show number of satellites detected and frequency locked status
    lcd.clear();                        //clear LCD
    lcd.print("Satellites =");          //print the word “Satellites =” on the top line of the LCD

  do {                                  //now loop
  GPSreceiver.flush();                  //clear any data which may be in the Serial Buffer
  if (GPSreceiver.available())          //if any GPS data is available
  {
    GPSreceiver.read();                 //read GPS serial data streams if available
  }
  char gpsin[8] = "$GPGGA,";            //define a character string “$GPGGA,”
  if (GPSreceiver.find(gpsin)) {        //if serial data starts with the characters “$GPGGA,”
   GPGGAdata = GPSreceiver.readStringUntil('\n');   //read data until a carriage return
    sats = GPGGAdata.substring(39,41);  //extract number of satellites data
  }
    
    satNum = sats.toInt();              //convert sats string to an integeter so as to remove leading zero
    if (satNum >0){
      FreqStatus = "Frequency Locked";  //if satellites detected the status string = “Frequency Locked”
    }else{
      FreqStatus = "                ";  //16 spaces to clear line if no lock
    }
    
    Serial.print(GPGGAdata);          //These serial print lines are for testing using Serial Monitor
    Serial.println();                 //full GPGGA data sentence and then carriage return
    Serial.print("Satellite = ");
    Serial.print(satNum);
    Serial.println();
    Serial.print(FreqStatus);
    Serial.println();
    
    lcd.setCursor(13,0);      //set cusor position to column 13 of row 0 (first line on LCD)
    lcd.print("   ");         //clears number if no satellites detected (3 spaces used)
    lcd.setCursor(13,0);      //set cusor position to column 13 of row 0 (first line on LCD)
    lcd.print(satNum);        //print number of satellites to LCD
    lcd.setCursor(0,1);       //set cusor position to column 0 of row 1 (second line on LCD)
    lcd.print(FreqStatus);    //print Frequency Locked status
  }
    while (customKeypad.getKey()!= '#');  //if # key pressed again break out of loop
    displayCurrentFrequency();            //and display current frequency
    break;                    //break and return to main program loop
  }    
}

void displayCurrentFrequency(){               //subroutine to display current frequency
 lcd.clear();

    CurrentFrequency = NewFreq;             //current frequency is set to new frequency entered
    if (CurrentFrequency >=1000000)
    {
      CurrentFrequency = CurrentFrequency / 1000000;
      range = "MHz";
      decimalPlaces = 6;        //sets number of decimal places to 6 if MHz range used
    }
   else if (CurrentFrequency >=1000)
   {
     CurrentFrequency = CurrentFrequency /1000;
    range = "KHz";
      decimalPlaces = 3;        //sets number of decimal places to 3 if KHz range used
    }
    else
    {
      range = "Hz";
      decimalPlaces =0;         //sets number of decimal places to 0 if Hz range used
    }
        
    lcd.print("Frequency");
    lcd.setCursor(0,1);
    lcd.print(CurrentFrequency,decimalPlaces);
    lcd.setCursor(13,1);
    lcd.print(range); 
}

 
