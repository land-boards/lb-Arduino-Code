#include <LandBoards_tcn75A.h>
#include "Wire.h"

landboards_TCN75A myTemp;

void setup()
{
  myTemp.begin(0x0);		// Begin communications with the I2C part at address 0
  Serial.begin(115200);
  Serial.print("Set control register value"
}

void loop()
{
  Serial.print("Temperature = ");
  Serial.println(myTemp.getTemp());
  delay(500);
}

