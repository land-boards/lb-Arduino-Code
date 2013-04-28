////////////////////////////////////////////////////////////////////////////////////
// []    i2c LCD library Display Test Demo
// []	 Original was 4-2-2009  dale@wentztech.com
// []    DGG 2012-04-11 - Libraries were modified to run under Arduino 1.0
////////////////////////////////////////////////////////////////////////////////////

#define VERSION "1.X"

#include <Wire.h>
#include <inttypes.h>

//  Uncomment the two lines for the display you are using
//	http://www.newhavendisplay.com display

#include <LCDi2cNHD.h>                    
LCDi2cNHD lcd = LCDi2cNHD(4,20,0x50>>1,0);

// web4robot.com display
//#include <LCDi2cW.h>                    
//LCDi2cW lcd = LCDi2cW(2,16,0x4C,0);             
 //   robot-electronics.co.uk 
//#include <LCDi2cR.h>                      
//LCDi2cR lcd = LCDi2cR(4,40,0x63,0);

uint8_t rows = 4;
uint8_t cols = 20;

void setup() 
{
  lcd.init();                          // Init the display, clears the display
  lcd.print("Hello World!");       // Classic Hello World!
  delay(1000);
}


void loop()
{
  lcdtest_basic();
}


void lcdtest_basic(){
  
  lcd.clear();
  lcd.print ("Cursor Test");
  delay(1000);
  Cursor_Type();
  
  lcd.clear();
  lcd.print("Characters Test");
  delay(1000);
  Characters();
  delay(1000);

  lcd.clear();
  lcd.print("Every Line");
  delay(1000);
  Every_Line(rows);
  delay(1000);
  
  lcd.clear();
  lcd.print("Every Position");
  delay(1000);
  Every_Pos(rows,cols);
  delay(1000);
  

  //Fancy_Clear();
  
   // Count_Numbers();
   // Fancy_Clear();


}

void Cursor_Type(){

  lcd.setCursor(0,0);
  lcd.print("Underline Cursor");
  lcd.setCursor(1,0);
  lcd.cursor_on();
  delay(1000);
  lcd.cursor_off();
  lcd.setCursor(0,0);
  lcd.print("Block Cursor    ");
  lcd.setCursor(1,0);
  lcd.blink_on();
  delay(1000);
  lcd.blink_off();
  lcd.setCursor(0,0);
  lcd.print("No Cursor      ");
  lcd.setCursor(1,0);
  delay(1000);
  }
  



void Count_Numbers(){

  lcd.clear();
  lcd.print("Count to 255");

  for (int i=0;i<255;i++){
    
    lcd.setCursor(1,0);
    
    lcd.print(i,DEC);
    
    lcd.setCursor(1,7);
    
     lcd.print(i,BIN);
    
    // delay(10);
    
  }
  
}


// Assume 16 character lcd

void Characters(){
  
int  chartoprint=48;
char a;

        lcd.clear();
 
  for(int i=0 ; i < rows ; i++){

      for(int j=0 ; j < cols ; j++){
        
          lcd.setCursor(i,j);
          a = char(chartoprint);
          lcd.print(char(chartoprint));
          chartoprint++;
          if(chartoprint == 127)
              return;
 
      }
  }
 
}


void Fancy_Clear(){
  
     for (int i=0 ; i < rows ; i++){
       
       for(int j=0 ; j < cols/2 ; j++){
       lcd.setCursor(i,j);
       lcd.print(" ");
  
       lcd.setCursor(i, cols - j);
       lcd.print(" ");
       }
       //delay(10);
       
     }
    
}

void Every_Line(int lines){

  lcd.clear();
  for(int i=0 ; i < lines ; i++){
      lcd.setCursor(i,0);
      lcd.print("Line : ");
      lcd.print(i,DEC);
      
  }  
}

void Every_Pos(int lines,int cols){
  
  lcd.clear();

  for(int i=0 ; i < lines ; i++){
    for(int j=0 ; j< cols ; j++){
      lcd.setCursor(i,j);
      lcd.print(i,DEC);
    }

  } 

}
