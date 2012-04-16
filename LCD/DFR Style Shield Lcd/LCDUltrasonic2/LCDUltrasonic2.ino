#include "Ultrasonic.h"
#include <LiquidCrystal.h>
#include <LCDKeypad.h>

LCDKeypad lcd;

Ultrasonic ultrasonic(13,2);

short ranges[5];

void setup() {
  lcd.begin(16, 2);
  lcd.setCursor(0,0);
  lcd.print("Distance");
  initRanges();
}

void putNewRange(long newRangeVal)
{
 ranges[0] = ranges[1];
 ranges[1] = ranges[2];
 ranges[2] = ranges[3];
 ranges[3] = ranges[4];
 ranges[4] = newRangeVal;
 return;
}

void initRanges(void)
{
  putNewRange(ultrasonic.Ranging(INC));
  putNewRange(ultrasonic.Ranging(INC));
  putNewRange(ultrasonic.Ranging(INC));
  putNewRange(ultrasonic.Ranging(INC));
  putNewRange(ultrasonic.Ranging(INC));  
}

short getRangeVal(void)
{
  if (ranges[4] == ranges[3])
    return(ranges[4]);
  else if (ranges[4] == ranges[3] + 1)
    return(ranges[3]);
  else if (ranges[4] == ranges[3] -1 )
    return(ranges[3]);
  else if (ranges[4] == ranges[2])
    return(ranges[4]);
  else if (ranges[3] == ranges[2])
    return(ranges[3]);
  else if (ranges[2] == ranges[1])
    return(ranges[2]);
  else return(ranges[4]);
  
}

void loop()
{
  initRanges();
  lcd.setCursor(0,1);
  putNewRange(ultrasonic.Ranging(INC));
  lcd.print(getRangeVal());
  lcd.print(" in   ");
//  delay(200);
}

