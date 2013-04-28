// [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]
// []
// []       i2c LCD library Custom Character
// []	
// []	4-2-2009  dale@wentztech.com
// []
// []
// [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]


#define VERSION "1.2"

#include <Wire.h>
#include "macros.h"

//  Uncomment the two lines for the display you are using

 //   http://www.newhavendisplay.com display

#include <LCDi2cNHD.h>
LCDi2cNHD lcd = LCDi2cNHD(4,20,0x50>>1,0);


//	web4robot.com display

//#include <LCDi2cW.h>                    
//LCDi2cW lcd = LCDi2cW(2,16,0x4C,0);             


 //   robot-electronics.co.uk 

//#include <LCDi2cR.h>                      
//LCDi2cR lcd = LCDi2cR(4,40,0x63,0);



void setup()
{

  //    Note custom char 0 does not work on version 1.3 or 1.4 of the web4robots display
  //    Define Custom Characters 0 - 7
  //    A 1 in the binary representation of the character means it is filled in
  //    characters are 5 pixels wide by 7 pixels tall
  
  uint8_t cc0[8] = {     // Custom Character 0
    B8(00000),
    B8(10001),
    B8(01010),
    B8(00100),
    B8(01010),
    B8(10001),
    B8(00000),
    B8(00000)
};

  uint8_t cc1[8] = {     // Custom Character 1
    B8(10001),
    B8(01110),
    B8(10101),
    B8(01110),
    B8(10001),
    B8(10001),
    B8(00000),
    B8(00000)
};

  uint8_t cc2[8] = {    // Custom Character 2
    B8(10001),
    B8(01110),
    B8(10101),
    B8(01110),
    B8(01010),
    B8(01010),
    B8(00000),
    B8(00000)
};

  uint8_t cc3[8] = {   // Custom Character 3
    B8(00000),
    B8(00000),
    B8(00000),
    B8(00000),
    B8(00000),
    B8(00000),
    B8(00000),
    B8(00000)
  };

 uint8_t cc4[8] = {    // Custom Character 4
    B8(00000),
    B8(00000),
    B8(00000),
    B8(00000),
    B8(00000),
    B8(00100),
    B8(01110),
    B8(11111)
 };


 uint8_t cc5[8] = {   // Custom Character 5
    B8(00100),
    B8(00100),
    B8(00100),
    B8(00100),
    B8(00000),
    B8(00100),
    B8(01110),
    B8(11111)
 };
 
  uint8_t cc6[8] = {  // Custom Character 6
    B8(00000),
    B8(00000),
    B8(00000),
    B8(00000),
    B8(00100),
    B8(00100),
    B8(00100),
    B8(00100)
  };
  
  uint8_t cc7[8] = {   // Custom Character 7
    B8(00100),
    B8(00100),
    B8(00100),
    B8(00100),
    B8(00000),
    B8(00000),
    B8(00000),
    B8(00000)
};

 

  lcd.init();                             // Init the display
  
  
  
  lcd.load_custom_character(0,cc0);      // send custom characters to the display
  lcd.load_custom_character(1,cc1);
  lcd.load_custom_character(2,cc2);
  lcd.load_custom_character(3,cc3);
  lcd.load_custom_character(4,cc4);
  lcd.load_custom_character(5,cc5);
  lcd.load_custom_character(6,cc6);
  lcd.load_custom_character(7,cc7);

  
  lcd.clear();                          // clear the display after sending characters. Cursor goes to odd place after uploading
  
  lcd.print("Hello World!");            // Print hello world and customer characters

  lcd.setCursor(1,0);                   // Print out the custom characters from 0 to 7 on next line
  
  for(int i=0; i<8 ; i++){
      lcd.write(i);
  }  

  delay(2000);                          // just sleep a bit so we can see the display
  lcd.clear();

  
}

void loop()            // Space invaders loop
{

  int j=1;
  int move=1;
  int pos=1;
  int posmove=1;
  
  for(int i=0;i < 2000;i++){
    
      lcd.setCursor(0,pos);
      lcd.print(" ");
      lcd.write(0x01);
      lcd.print(" ");
      

      
      lcd.setCursor(0,pos+4);
      lcd.print(" ");
      lcd.write(0x02);
      lcd.print(" ");
       
      if (j == 15)
        move = -1;
      if (j == 0)
        move = 1;
        
      lcd.setCursor(1,j);
      lcd.print(" ");
      lcd.write(0x04);
      lcd.print(" ");
      j = j + move;
      
      #ifdef LCDi2cR_h

      delay(200);     // If using with the robot electronics display we need to add a delay, as the display is to fast

      #endif
      
      
      
      lcd.setCursor(0,pos);   
      lcd.print(" ");
      lcd.write(0x02);
      lcd.print(" ");

      lcd.setCursor(0,pos+4);
      lcd.print(" ");
      lcd.write(0x01);
      lcd.print(" ");    

      
      if(pos == 0)
        posmove = 1;
      if(pos == 10)
        posmove = -1;
      
      pos = pos + posmove;
   
      #ifdef LCDi2cR_h

      delay(200);     // If using with the robot electronics display we need to add a delay, as the display is to fast

      #endif

      
  }
  
}
