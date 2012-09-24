//////////////////////////////////////////////////////////////////////
// kick start the GPS

#include <Adafruit_GPS.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(3, 2);
Adafruit_GPS GPS(&mySerial);
boolean usingInterrupt = false;

void setup()  
{
  Serial.begin(9600);
<<<<<<< HEAD
  Serial.println("Serial started");
  GPS.begin(9600);
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);  // 1 Hz update rate
  useInterrupt(true);
  if (GPS.LOCUS_StartLogger())
=======
  GPS.begin(9600);
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);  // 1 Hz update rate
//  Serial.println("1 hz command set");
//  delay(1000);
//  Serial.println("Turning on interrupt");
//  delay(1000);
//  useInterrupt(true);
//  Serial.println("Turned on interrupt");
  delay(1000);
  Serial.println("Starting datalogger");
  delay(1000);
  GPS.sendCommand(PMTK_LOCUS_STARTLOG);
//  if (GPS.LOCUS_StartLogger())
>>>>>>> 61b7d5ef74090e6b3c2d43ace995c043a8df0257
    Serial.println("Logging STARTED!");
//  else
//    Serial.println("!No response!");
//  useInterrupt(false);
}

void useInterrupt(boolean v) {
  if (v) {
    // Timer0 is already used for millis() - we'll just interrupt somewhere
    // in the middle and call the "Compare A" function above
    OCR0A = 0xAF;
    TIMSK0 |= _BV(OCIE0A);
    usingInterrupt = true;
  } 
  else {
    // do not call the interrupt function COMPA anymore
    TIMSK0 &= ~_BV(OCIE0A);
    usingInterrupt = false;
  }
}

void loop(void)
{
  Serial.println("Looping");
}

