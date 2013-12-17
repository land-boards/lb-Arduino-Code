/*
 * Displays text sent over the serial port (e.g. from the Serial Monitor) on
 * an attached LCD.
 */

// include the library code:
#include "Wire.h"
#include "LiquidCrystal.h"

// Connect via i2c, default address #0 (A0-A2 not jumpered)
LiquidCrystal lcd(0);

void setup() {
  // set up the LCD's number of rows and columns: 
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("*Accelerometer* ");
}

void loop() 
{
  signed int x,y,z;
  signed long acc;
  x = analogRead(A1);
  y = analogRead(A2);
  z = analogRead(A3);
  x -= 313;
  y -= 356;
  z -= 280;
  acc = sqrt((x*x)+(y*y)+(z*z));
  acc -= 161;
  lcd.setCursor(0,0);
  lcd.print("X=");
  lcd.print(x);
  lcd.print(", Y=");
  lcd.print(y);
  lcd.print("      ");
  lcd.setCursor(0,1);
  lcd.print("Z=");
  lcd.print(z);
  lcd.print(", a=");
  lcd.print(acc);
  lcd.print("      ");
  delay(200);
}


