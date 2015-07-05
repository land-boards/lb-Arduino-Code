//////////////////////////////////////////////////////////////////////////////
// MenuCodeOps() - Run the Example Menu Functions
//////////////////////////////////////////////////////////////////////////////

void exampleFcn1(void)
{
  setDisplayCursor(8,0);
  tft.print("You pressed Select on the first menu item");
  delay(2000);
}

void exampleFcn2(void)
{
  setDisplayCursor(8,0);
  tft.print("You pressed Select on the third menu item");
  delay(2000);  
}

void exampleFcn3(void)
{
  setDisplayCursor(8,0);
  tft.print("You pressed Select on the submenu item");
  delay(2000);  
}

