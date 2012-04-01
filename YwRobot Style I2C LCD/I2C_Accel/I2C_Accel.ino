/*
 * Display accelerometer values on the I2C LCD.
 */
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup()
{
  lcd.init();                      // initialize the lcd 
  lcd.backlight();
//  Serial.begin(9600);
  lcd.setCursor(0,1);
  lcd.print("Accelerometer   ");
  lcd.setCursor(0,1);
}

void loop()
{
  signed int x, y, z;
  signed long int accel;
  x = analogRead(A1);
  y = analogRead(A2);
  z = analogRead(A3);
  x -= 313;
  y -= 355;
  z -= 280;
  accel = sqrt((x*x)+(y*y)+(z*z));
  accel -= 155;
  
  lcd.setCursor(0,0);
  lcd.print("                ");
  lcd.setCursor(0,0);
  lcd.print("x=");
  lcd.print(x);
  lcd.print(", y=");
  lcd.print(y);
  lcd.setCursor(0,1);
  lcd.print("                ");
  lcd.setCursor(0,1);
  lcd.print("z=");
  lcd.print(z);
  lcd.print(", a=");
  lcd.print(accel);
  delay(500);

}

