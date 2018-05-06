#include "Adafruit_MAX31855.h"
#include <SPI.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <PID_v1.h>
#include "U8glib.h"

//  Temperature data table
#define TIME0_LEADFREE 0
#define TIMET1_LEADFREE 90
#define TIMET2_LEADFREE 180
#define TIMET3_LEADFREE 210
#define TIMET4_LEADFREE 230
#define TIMET5_LEADFREE 600

#define TEMPT0_LEADFREE 22.0
#define TEMPT1_LEADFREE 150.0
#define TEMPT2_LEADFREE 180
#define TEMPT3_LEADFREE 225.0
#define TEMPT4_LEADFREE 225.0
#define TEMPT5_LEADFREE 40

// Delays associated with different power levels
#define POWERLEVEL0 0
#define POWERLEVEL1 1
#define POWERLEVEL2 5
#define POWERLEVEL3 15
#define POWERLEVEL4 30
#define POWERLEVEL5 50
#define POWERLEVEL6 70
#define POWERLEVEL7 85
#define POWERLEVEL8 95
#define POWERLEVEL9 99
#define POWERLEVEL10 100
// Delay needed for corrisponding power level (Counts)
#define DELAY0 510
#define DELAY1 468
#define DELAY2 416
#define DELAY3 364
#define DELAY4 312
#define DELAY5 260
#define DELAY6 218
#define DELAY7 156
#define DELAY8 105
#define DELAY9 52
#define DELAY10 10

// Define pins that will be used
#define DETECT 2  // Zero cross detect
#define GATE 4    // Triac gate
#define PULSE 5   // Trigger pulse width (counts)
#define BUZZER 10 // BUZZER

// Initialize global variables
double currTime, Time, Input, Output, Setpoint, DesiredPower = 0;
int i, btTemp = 0, btTime = 0, btSet, TriacDelay = 0;

// Initialize OLED screen
U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_NO_ACK); 
// Initialize PID
PID myPID(&Input, &Output, &Setpoint,7,0.035,0.4, DIRECT);
// Initialize the Thermocouple
#define CS   9
Adafruit_MAX31855 thermocouple(CS);


void setup() {
  // Setup Code

  // Bluetooth Initialization
  Serial.begin(115200);
  Serial.print("$$$");
  delay(100);
  Serial.println("SM,0");
  delay(100);
  Serial.println("U,115200,N");
  delay(100);
  Serial.begin(115200);
  delay(100);
  
  // Setup OLED Display
  if ( u8g.getMode() == U8G_MODE_R3G3B2 ) {
    u8g.setColorIndex(255);     // white
  }
  else if ( u8g.getMode() == U8G_MODE_GRAY2BIT ) {
    u8g.setColorIndex(3);         // max intensity
  }
  else if ( u8g.getMode() == U8G_MODE_BW ) {
    u8g.setColorIndex(1);         // pixel on
  }
  else if ( u8g.getMode() == U8G_MODE_HICOLOR ) {
    u8g.setHiColorByRGB(255,255,255);
  } 
  
  // set up pins
  pinMode(BUZZER, OUTPUT);    // Buzzer Pin
  pinMode(DETECT, INPUT);     //zero cross detect
  digitalWrite(DETECT, HIGH); //enable pull-up resistor
  pinMode(GATE, OUTPUT);      //triac gate control

  myPID.SetOutputLimits(0, 100);  // 0-100% Power Level
  myPID.SetMode(AUTOMATIC);     
  

  // set up Timer1 for phase control
  OCR1A = 100;      //Initialize the comparator
  TIMSK1 = 0x03;    //Enable comparator A and overflow interrupts
  TCCR1A = 0x00;    //Timer control registers set for
  TCCR1B = 0x00;    //Normal operation, timer disabled


  // Set up zero crossing interrupt
  attachInterrupt(0,zeroCrossingInterrupt, RISING);    
    //IRQ0 is pin 2. Calls zeroCrossingInterrupt 
    //on rising signal
}



// ******Functions******

// Buzzes on and off
void Buzz(){
  for(i=0;i<5;i++){
    tone(BUZZER, 3000); // 2khz Sound 
    delay(3000);        // 3 Seconds On
    noTone(BUZZER);     // Stop Sound
    delay(2000);        // 3 Seconds Off
    // Loops 5 Times
}}

// Sets amount of power to the heaters
// by setting triac delay time
void SetPower(double delayCounts){
  OCR1A = delayCounts;
}

// Reads the temperature of the MAX38155
double ReadTemp(){
  double currTemp = thermocouple.readCelsius();
  return currTemp;
}

// Calculates the temperature setpoint at current time based on table
double GetDesiredTempLeadFree(int currTime)
{
  if (currTime < TIMET1_LEADFREE)
    return (TEMPT0_LEADFREE + ((double)currTime                   * ((TEMPT1_LEADFREE-TEMPT0_LEADFREE)/(double)(TIMET1_LEADFREE-TIME0_LEADFREE))));
  else if (currTime < TIMET2_LEADFREE)
    return (TEMPT1_LEADFREE + ((double)(currTime-TIMET1_LEADFREE) * ((TEMPT2_LEADFREE-TEMPT1_LEADFREE)/(double)(TIMET2_LEADFREE-TIMET1_LEADFREE))));
  else if (currTime < TIMET3_LEADFREE)
    return (TEMPT2_LEADFREE + ((double)(currTime-TIMET2_LEADFREE) * ((TEMPT3_LEADFREE-TEMPT2_LEADFREE)/(double)(TIMET3_LEADFREE-TIMET2_LEADFREE))));
  else if (currTime < TIMET4_LEADFREE)
    return (TEMPT3_LEADFREE);
  else if (currTime < TIMET5_LEADFREE)
    return (TEMPT4_LEADFREE + ((double)(currTime-TIMET4_LEADFREE) * ((TEMPT5_LEADFREE-TEMPT4_LEADFREE)/(double)(TIMET5_LEADFREE-TIMET4_LEADFREE))));
  else
    return 0;
}

// Calculates Triac Delay for given power level based on data tables
double GetDesiredDelay(double PwrLvl)
{
  if (PwrLvl < POWERLEVEL1)
    return 500;
  else if (PwrLvl < POWERLEVEL2)
    return (30+DELAY1 + ((double)(PwrLvl-POWERLEVEL1) * ((DELAY2-DELAY1)/(double)(POWERLEVEL2-POWERLEVEL1))));
  else if (PwrLvl < POWERLEVEL3)
    return (30+DELAY2 + ((double)(PwrLvl-POWERLEVEL2) * ((DELAY3-DELAY2)/(double)(POWERLEVEL3-POWERLEVEL2))));
  else if (PwrLvl < POWERLEVEL4)
    return (30+DELAY3 + ((double)(PwrLvl-POWERLEVEL3) * ((DELAY4-DELAY3)/(double)(POWERLEVEL4-POWERLEVEL3))));
  else if (PwrLvl < POWERLEVEL5)
    return (30+DELAY4 + ((double)(PwrLvl-POWERLEVEL4) * ((DELAY5-DELAY4)/(double)(POWERLEVEL5-POWERLEVEL4))));
  else if (PwrLvl < POWERLEVEL6)
    return (30+DELAY5 + ((double)(PwrLvl-POWERLEVEL5) * ((DELAY6-DELAY5)/(double)(POWERLEVEL6-POWERLEVEL5))));
  else if (PwrLvl < POWERLEVEL7)
    return (30+DELAY6 + ((double)(PwrLvl-POWERLEVEL6) * ((DELAY7-DELAY6)/(double)(POWERLEVEL7-POWERLEVEL6))));
  else if (PwrLvl < POWERLEVEL8)
    return (30+ DELAY7 + ((double)(PwrLvl-POWERLEVEL7) * ((DELAY8-DELAY7)/(double)(POWERLEVEL8-POWERLEVEL7))));
  else if (PwrLvl < POWERLEVEL9)
    return (30+ DELAY8 + ((double)(PwrLvl-POWERLEVEL8) * ((DELAY9-DELAY8)/(double)(POWERLEVEL9-POWERLEVEL8))));
  else if (PwrLvl <= POWERLEVEL10)
    return (30+DELAY10);
}

void Draw(void) {
  // graphic commands to redraw the complete screen should be placed here  
  u8g.setFont(u8g_font_unifont);
  u8g.drawStr( 0, 22, "Temp");
  u8g.drawStr( 0, 42, "Time");
  u8g.drawStr( 0, 62, "Pwr");
  u8g.setPrintPos(44, 22);      // Print position for temp
  u8g.print(Input,0);           // Temp sensor input
  u8g.setPrintPos(75, 22);      // Print position for temp
  u8g.print(Setpoint,0); 
  u8g.drawStr(90, 22, " C");    // Celsius
  u8g.setPrintPos(44, 42);      // Print position for Time
  u8g.print(currTime,0);        // Time input
  u8g.drawStr(70, 42, "s");     // Seconds since start
  u8g.setPrintPos(44, 62);      //Print position for PWR%
  u8g.print(DesiredPower,0);    // Pwr input
  u8g.drawStr(70, 62, "%");     //Percentage
}

// Delivers Data over Bluetooth
void UIupdate(double Input, double currTime, double Setpoint){

  btTemp = (int)(Input);
  btTime = (int)(currTime);
  btSet = (int)(Setpoint);

  Serial.print(btTemp);
  Serial.print(",");
  Serial.println(btSet);

}


//******Interrupt Service Routines********

void zeroCrossingInterrupt(){ // Zero cross detect   
  TCCR1B=0x04; // Start timer with divide by 256 input
  TCNT1 = 0;   // Reset timer - count from zero
}

ISR(TIMER1_COMPA_vect){ //comparator match
  if( DesiredPower > 2 ){
    digitalWrite(GATE,HIGH);  // Set triac gate to high
  }
  TCNT1 = 65536-PULSE;        // Triigger pulse width
}

ISR(TIMER1_OVF_vect){// Timer1 overflow
  digitalWrite(GATE,LOW); // Turn off triac gate
  TCCR1B = 0x00;          // Disable timer stopd unintended triggers
}


void loop() {
  // Read Temperature
  Input = ReadTemp();

  // Signal conditioning
  // Ensures good reading
  while(isnan(Input)){
    Input = ReadTemp();
  }

  // Find current time in run
  currTime = millis();
  currTime = currTime/1000;
  
  // Find Temperature Setpoint
  Setpoint = GetDesiredTempLeadFree(currTime);

  // Compute new PID output value
  myPID.Compute();

  // Sets desired Power based on PID output
  DesiredPower = (double)Output;
    
  // Find Corrisponidng Triac delay for desired %Power
  TriacDelay = GetDesiredDelay(DesiredPower);

  // Use desired power to set triac delay
  SetPower(TriacDelay);

  // Update OLED Screen
  u8g.firstPage();  
  do {
    Draw();
  } while( u8g.nextPage() );

  // Allows Bluetooth data to be sent once per second
  if(Time<currTime){
    UIupdate(Input, currTime, Setpoint);
    Time = Time+1;
  }
  
  // Buzz when done
  if(currTime > 600){
  Buzz();
  }

}
