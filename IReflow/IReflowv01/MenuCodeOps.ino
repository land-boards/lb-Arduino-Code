//////////////////////////////////////////////////////////////////////////////
// MenuCodeOps() - Run the Example Menu Functions
//////////////////////////////////////////////////////////////////////////////

void runProfileFcn(void)
{
  digitalWrite(RED_LITE, LOW);
  u8g.firstPage();  
  do 
  {
    setDisplayCursor(0,0);
    u8g.print("Running");
    setDisplayCursor(1,0);
    u8g.print("profile");
  } 
  while( u8g.nextPage() );
  delay(500);
  digitalWrite(RED_LITE, HIGH);
}

void monTempFcn(void)
{
  double myTemp = thermocouple.readCelsius();
  u8g.firstPage();  
  do 
  {
    setDisplayCursor(0,0);
    u8g.print("Temp = ");
    setDisplayCursor(1,0);
    u8g.print(myTemp);
  } 
  while( u8g.nextPage() );
  delay(5000);  
}

void LeadFreeFcn(void)
{
  digitalWrite(GRN_LITE, LOW);
  u8g.firstPage();  
  do 
  {
    setDisplayCursor(1,0);
    u8g.print("Lead free");
    setDisplayCursor(2,0);
    u8g.print("profile");
    setDisplayCursor(3,0);
    u8g.print("selected");
  } 
  while( u8g.nextPage() );
  delay(2000);  
  delay(500);
  digitalWrite(GRN_LITE, HIGH);
}

void LeadFcn(void)
{
  digitalWrite(GRN_LITE, LOW);
  u8g.firstPage();  
  do 
  {
    setDisplayCursor(1,0);
    u8g.print("Lead profile");
    setDisplayCursor(2,0);
    u8g.print("selected");
  } 
  while( u8g.nextPage() );
  delay(2000);  
  delay(500);
  digitalWrite(GRN_LITE, HIGH);
}


