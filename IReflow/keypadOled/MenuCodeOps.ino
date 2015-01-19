//////////////////////////////////////////////////////////////////////////////
// MenuCodeOps() - Run the Example Menu Functions
//////////////////////////////////////////////////////////////////////////////

void exampleFcn1(void)
{
  digitalWrite(RED_LITE, LOW);
  u8g.firstPage();  
  do 
  {
    setDisplayCursor(3,0);
    u8g.print("first");
  } 
  while( u8g.nextPage() );
  delay(500);
  digitalWrite(RED_LITE, HIGH);
}

void exampleFcn2(void)
{
  u8g.firstPage();  
  do 
  {
  setDisplayCursor(3,0);
    u8g.print("third");
  } 
  while( u8g.nextPage() );
  delay(2000);  
}

void exampleFcn3(void)
{
  digitalWrite(GRN_LITE, LOW);
  u8g.firstPage();  
  do 
  {
  setDisplayCursor(3,0);
     u8g.print("submenu");
  } 
  while( u8g.nextPage() );
  delay(2000);  
  delay(500);
  digitalWrite(GRN_LITE, HIGH);
}

