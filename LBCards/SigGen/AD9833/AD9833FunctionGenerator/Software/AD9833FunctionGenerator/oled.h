#ifndef __OLED_H__
#define __OLED_H__

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "dds.h"
#include "pcint.h"

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

int linespace = 9;  //pixels for a newline

void oled_setup() 
{

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
  display.display();
  display.clearDisplay();
}

void oled_set_text(int pSize, int pColour) 
{
  display.setTextSize(pSize);
  display.setTextColor(pColour);
}

void oled_reset() 
{
  display.clearDisplay();
  display.setCursor(0,0);
  
}

void printCurrentFreq()
{
  if(currentFreq>999)
  {      
    display.print(currentFreq/1000.0); 
    
    display.print("KHz");        
  }
  else
  {      
    display.print(currentFreq);
   
    display.print("Hz");      
  }
}

void printLowerFreq()
{
  if(selectedLowerFreq>999)
  {      
    display.print(selectedLowerFreq/1000.0); 
    
    display.print("KHz");        
  }
  else
  {      
    display.print(selectedLowerFreq);
   
    display.print("Hz");      
  }
}

void printUpperFreq()
{
  if(selectedUpperFreq>999)
  {      
    display.print(selectedUpperFreq/1000.0); 
   
    display.print("KHz");        
  }
  else
  {      
    display.print(selectedUpperFreq);
    
    display.print("Hz");      
  }
}

void oled_draw()
{


  oled_reset();
  oled_set_text(1,1);
  
  // print function
  display.setCursor(0,0); 
  if(func==SINE) 
  {
    display.print("SINE");
  }
  else if(func==SQUARE)
  {
    display.print("SQ");
  }
  else if(func == TRIANGLE)
  {
    display.print("TRI");
  }

  
  if(mode == NORMAL)
  {
    display.print(" NORMAL");
    display.setCursor(20,linespace);
   
    // print upper freq only
    oled_set_text(2,1);
    printCurrentFreq();
    oled_set_text(1,1);
    
  }
  else 
  {
    display.print(" SWEEP");
    display.print(" Vel=");
    display.print(ADCInput6);
    
    display.setCursor(20,linespace);

    oled_set_text(2,1);
    printCurrentFreq();
    oled_set_text(1,1);

    display.setCursor(0,25);
    printLowerFreq();
    display.print(" -> ");
    printUpperFreq();

  }

  display.display();

}

#endif


