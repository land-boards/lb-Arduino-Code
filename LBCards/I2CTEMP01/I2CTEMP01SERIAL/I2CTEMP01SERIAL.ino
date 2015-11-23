///////////////////////////////////////////////////
//Project 6.03 Read TCN75A Temperature Sensor
// http://learn.olympiacircuits.com/603-read-the-i2c-temperature-sensor.html

#include <Wire.h>

int tempreg = 0;
float temperature = 0;
byte address = 0x48;

void setup()
{
  Serial.begin(9600);
  Wire.begin();
  //Do some setup for the sensor
  // Set the resolution of the measurement
  Wire.beginTransmission(address);
  // point to Configuration Register
  Wire.write(0x01);
  // set the resolution
  Wire.write(0x60);
  // ends the command
  Wire.endTransmission();
  // points to the Temperature Register
  Wire.beginTransmission(address);
  Wire.write(0x00);
  Wire.endTransmission();
}

void loop()
{
  // Receives data from the Temperature Register
  Wire.requestFrom(address, byte(2));
  tempreg = Wire.read();
  tempreg = tempreg << 8;
  tempreg |= Wire.read();
  tempreg = tempreg >> 4;
  // Calculate the temperature
  temperature = ( float ) tempreg / 16;
  // Display the temperature in the Serial Monitor
  Serial.print("Temp F = ");
  Serial.print(temperature * 9 / 5 + 32, 2);
  Serial.print("   ");
  Serial.print("Temp C = ");
  Serial.println(temperature, 2);
  delay(500);
}

