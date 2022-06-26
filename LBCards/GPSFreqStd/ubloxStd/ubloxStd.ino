#include <SoftwareSerial.h>
 
//Create software serial object to communicate with GPS
//D3=TX-Arduino to RX-GPS, D4=RX-Arduino to TX-GPS
SoftwareSerial gps(4, 3);
 
void setup() {
  //Begin serial communication with Arduino and Arduino IDE (Serial Monitor)
  Serial.begin(9600);
  while(!Serial);
   
  //Begin serial communication with Arduino and GPS Module rate must be 9600
  gps.begin(9600);
  delay(1000);
   
  Serial.println("Setup Complete!");
}
 
void loop() {
  //Read GPS module data (if available) and print it in Arduino IDE Serial Monitor
  if(gps.available()){
    Serial.write(gps.read());
  }
  //Read Arduino IDE Serial Monitor inputs (if available) and send them to GPS module
  if(Serial.available()){    
    gps.write(Serial.read());
  }
}
