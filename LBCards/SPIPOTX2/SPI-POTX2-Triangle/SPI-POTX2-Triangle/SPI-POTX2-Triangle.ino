/*
  SPI_POTX2 - Example code
  Generate triangles on both outputs - one at a time
*/

#include <LandBoards_MCP423X.h>

LandBoards_MCP423X SPI_POTX2;

void setup()
{
  // Initialize SPI
  SPI_POTX2.begin();
}

void loop()
{
  for (int i=0; i<=128; i++)
  {
    SPI_POTX2.writePot(POT_REG0, i);
  }
  for (int i=128; i>=0; i--)
  {
    SPI_POTX2.writePot(POT_REG0, i);
  } 
  for (int i=0; i<=128; i++)
  {
    SPI_POTX2.writePot(POT_REG1, i);
  }
  for (int i=128; i>=0; i--)
  {
    SPI_POTX2.writePot(POT_REG1, i);
  } 
}
