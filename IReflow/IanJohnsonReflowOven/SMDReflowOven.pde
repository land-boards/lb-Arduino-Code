/*
SMD Reflow Oven Controller
  By Ian Johnston (www.ianjohnston.com)

Version V1.8a (11/01/14)

This version incorporates Gobetwino logging activated on the com port.
Create a blank text file called OvenData.txt
Edit gcs.txt and add the following line (adjust the path accordingly):-
#S|LOGTEST|LGFIL|[C:\Users\Ian\Desktop\gobetwino\OvenData.txt&$1&0]#

Three profiles embedded in the code below L, M & H. Press INFO when run has started to change.
Current profile used is stored in EEprom.
Fan operates when START is pressed and doesn't stop till STOP is pressed.

DISCLAIMER:
  With this design, including both the hardware & software I offer no guarantee that it is bug
  free or reliable. So, if you decide to build one and you have problems or issues and/or causes
  damage/harm to you, others or property then you are on your own. This work is experimental.
*/

#include <LiquidCrystal.h>
#include <TimedAction.h>
#include <Servo.h>
#include <EEPROM.h>

// Logging vars
int serInLen = 25;
char serInString[25];
int result;

// Setup fan drive
Servo myservo;

// Setup LCD
const int Rows = 2; // LCD rows
const int Cols = 8; // LCD columns
LiquidCrystal lcd(8, 9, 5, 4, 3, 2); // Pin assignment of LCD interface: RS, ENABLE, D4, D5, D6, D7

// Setup Profiles
int Time[5] = { 0, 0, 0, 0, 0 };  // Time (secs) Pre-heat start, Soak start, Reflow start, Reflow cool, Reflow finish
int Temp[5] = { 0, 0, 0, 0, 0 };  // Heat (DegC) to match the above timing, The start temp is read at boot/restart
int Time0[5] = { 0, 100, 200, 250, 280 };  // Profile - Lower, quicker temperature
int Temp0[5] = { 20, 150, 180, 220, 180 };
int Time1[5] = { 0, 120, 230, 320, 350 };  // Profile - Medium temperature
int Temp1[5] = { 20, 150, 180, 220, 180 };
int Time2[5] = { 0, 120, 230, 320, 350 };  // Profile - Higher temperature
int Temp2[5] = { 20, 150, 180, 240, 180 };

// Setup Digital & Analogue I/O pins
int AI_KTemp = 0;
int DI_StopSW = 12;
int DI_StartSW = 11;
int DI_ModeSW = 10;
int DO_Relay = 13;
int DO_Fan = 6;
int DO_Buzz = 7;

// Misc vars
int Seconds = 0;
int Seconds5th = 0;
int KTemp = 0;
int StopSW = 0;
int StartSW = 0;
int ModeSW = 0;
int Status = 0;
int DegC = 0;
float tempstep = 0;
float DegCtempstep = 0;
float DegCtemp = 0;
int zone = 1;
int Profile = 0;
int fanspeed = 0;
int fanspeedslow = 75; // Slowest speed at which my motor will run. Anything much less and it won't actually start.
int fanspeedzero = 30; // Minimum speed is 30 on my RC ESC/Motor. Anything less then the ESC won't startup properly. Basically needs 1mS pulse width.
int ProfileAddr = 0;   // Eeprom address for Profile storage

// Buzzer vars
long previousMillis = 0;
unsigned long currentMillis;
unsigned char buzzeractivate = 0;
long buzzinterval;
unsigned char buzzloop = 0;

// Preload the AI averaging formula
float KTempAve = (AI_KTemp);
float kana = 5;

// Initializes TimedAction - Timer Interrupt
TimedAction Timedact01 = TimedAction(40,TimerService01);  // 40mS
int tickfast = 0;
int tickslow = 0;
int tickslow2 = 0;


// *********************** Void Setup *************************
void setup() {

    Serial.begin(9600); 
    
    myservo.attach(DO_Fan);   // Attach pin to fan motor drive output
	fanspeed = fanspeedzero;  
    myservo.write(fanspeed);
 
	// Set up pins
	pinMode(DI_StopSW, INPUT);
	pinMode(DI_StartSW, INPUT);
	pinMode(DI_ModeSW, INPUT);
	pinMode(DO_Relay, OUTPUT);
	pinMode(DO_Buzz, OUTPUT);
	digitalWrite(DI_StopSW, HIGH);   // turn on pullup resistors on switch inputs
	digitalWrite(DI_StartSW, HIGH);
	digitalWrite(DI_ModeSW, HIGH);

	digitalWrite(DO_Relay, LOW);   // Turn the relay off
	digitalWrite(DO_Buzz, LOW);    // Turn the buzzer off

	Status = 0;  // Initial status set
	
	// Set up the LCD Col and Row count
	lcd.begin(8,2);
	lcd.clear();
	lcd.setCursor(0,0);  // column, row
	lcd.print("SMD Oven");
	lcd.setCursor(0,1);
	lcd.print("by IanJ ");
	delay(3000);
	lcd.clear();

	currentMillis = millis();  // Prepare buzzer timing
	previousMillis = millis();

    // Get start temperature, this will be done again when Start Switch is pressed
	DegC = map(analogRead(AI_KTemp), 0, 1002, 0, 480); // Generate temperature in degC
	Temp[0] = DegC; // set start temp into profile
	DegCtempstep = Temp[0];

	// Set active profile from eeprom
    Profile = EEPROM.read(ProfileAddr); // Read back stored Profile setting L, M or H
    
    // Set Profile to 0 if corrupt eeprom
    if (Profile != 0  && Profile != 1 && Profile != 2) {
      Profile = 0;
      EEPROM.write(ProfileAddr, Profile);
      digitalWrite(DO_Buzz, HIGH);  // Turn on buzzer
      delay(2000);
      digitalWrite(DO_Buzz, LOW);  // Turn off buzzer
      delay(250);
      digitalWrite(DO_Buzz, HIGH);  // Turn on buzzer
      delay(2000);
      digitalWrite(DO_Buzz, LOW);  // Turn off buzzer
    }

    if(Profile == 0) {
	  Time[0] = Time0[0];
	  Time[1] = Time0[1];
	  Time[2] = Time0[2];
	  Time[3] = Time0[3];
	  Time[4] = Time0[4];
	  Temp[0] = Temp0[0];
	  Temp[1] = Temp0[1];
	  Temp[2] = Temp0[2];
	  Temp[3] = Temp0[3];
	  Temp[4] = Temp0[4];
    }   
    if(Profile == 1) {
	  Time[0] = Time1[0];
	  Time[1] = Time1[1];
	  Time[2] = Time1[2];
	  Time[3] = Time1[3];
	  Time[4] = Time1[4];
	  Temp[0] = Temp1[0];
	  Temp[1] = Temp1[1];
	  Temp[2] = Temp1[2];
	  Temp[3] = Temp1[3];
	  Temp[4] = Temp1[4];
    }     
    if(Profile == 2) {
	  Time[0] = Time2[0];
	  Time[1] = Time2[1];
	  Time[2] = Time2[2];
	  Time[3] = Time2[3];
	  Time[4] = Time2[4];
	  Temp[0] = Temp2[0];
	  Temp[1] = Temp2[1];
	  Temp[2] = Temp2[2];
	  Temp[3] = Temp2[3];
	  Temp[4] = Temp2[4];
    }      
	
}


// *********************** Main Loop **************************
void loop() {

    Timedact01.check();  // Timed Action service

    if(tickfast == 5) {  // 5 * 40 = 200mS tick subroutine generator
        tickfast = 0;
        tickslowmS(); // Jump to tickslowmS sub
    }

    buzzer();  // Refresh buzzer

}


// ************* Timed Action Tick Fast Service **************
void TimerService01() {

    tickfast++; // Increment tick counter. This is used to generate tickslow service.

    KTempAve = KTempAve + (1 / kana * ((double)analogRead(AI_KTemp) - KTempAve)); // Averaging formula applied to smooth out bumps
	DegC = map(KTempAve, 0, 1002, 0, 480); // Generate temperature in degC
    StopSW = digitalRead(DI_StopSW);
    StartSW = digitalRead(DI_StartSW);
	ModeSW = digitalRead(DI_ModeSW);

}


// ******************** Tick Slow Service *******************
void tickslowmS() {  

	if(StopSW == 0) { Status = 0; buzzeractivate = 5; }
	if(ModeSW == 0 && Status == 0) { Status = 1; buzzeractivate = 5; }
	if(StartSW == 0) {
	    Seconds = 0;
        Seconds5th = 0;
        KTemp = 0;
        DegC = 0;
        tempstep = 0;
        DegCtempstep = 0;
        DegCtemp = 0;
        zone = 1;
	    Status = 2;
		buzzeractivate = 5;
	    DegC = map(analogRead(AI_KTemp), 0, 1002, 0, 480); // Generate temperature in degC
	    Temp[0] = DegC; // set start temp into profile
	    DegCtempstep = Temp[0];
	}
	
	// Work out what zone we should be in
	if(Seconds == Time[1]) { zone = 2; DegCtempstep = Temp[1]; }	// end of PREHEAT so now into SOAK
	if(Seconds == Time[2]) { zone = 3; DegCtempstep = Temp[2]; }    // SOAK --> REFLOW HEAT
	if(Seconds == Time[3]) { zone = 4; DegCtempstep = Temp[3]; }    // REFLOW HEAT --> REFLOW COOL
	if(Seconds == Time[4]) { Status = 0; }                          // FINISHED

    if(++tickslow == 5) { // 5 * 200 = 1000mS
        tickslow = 0;
		++Seconds;
	    logData(DegC,Seconds);  // Send log data every second
	}
	
 	if(Status == 0) {  // Stop or finished mode
	    digitalWrite(DO_Relay, LOW);   // Turn the relay off
        lcd.setCursor(7,0); // column, row
        lcd.print(" "); // indicate heaters off
		lcd.setCursor(0,0); // column, row
        lcd.print("Oven    ");
        lcd.setCursor(0,1);
        lcd.print("Off     ");
    	tickslow = 0;
		Seconds = 0;
		DegCtempstep = Temp[0];
		fanspeed = fanspeedzero;  // Stop fan motor
		myservo.write(fanspeed); 
	}

	if(Status == 1) {  // Only allowable in STOP mode
		lcd.clear();
		lcd.setCursor(0,0); // column, row
        lcd.print("Temp:");
        lcd.setCursor(0,1);
        lcd.print(DegC);
		lcd.print("  ");
	}

	if(Status == 2) {  // Prepare for Oven start
		lcd.clear();
     	lcd.setCursor(0,1); // column, row
		lcd.print(DegC); lcd.print(" ");
		lcd.setCursor(5,1); // column, row
        lcd.print(Seconds);
		Seconds = 0;
		Status = 3;
		if(Profile == 0) {
	       lcd.setCursor(6,0); // column, row
           lcd.print("L");	
		}
		if(Profile == 1) {
	       lcd.setCursor(6,0); // column, row
           lcd.print("M");	
		}	
		if(Profile == 2) {
	       lcd.setCursor(6,0); // column, row
           lcd.print("H");	
		}        
	}
	
    if(Status == 3 && ModeSW == 0) {  // If oven started and INFO button pressed then rotate through alternative profiles
	   Profile++;
       if(Profile == 3) { Profile = 0; }
       if(Profile == 0) {
	      Time[0] = Time0[0];
	      Time[1] = Time0[1];
	      Time[2] = Time0[2];
	      Time[3] = Time0[3];
	      Time[4] = Time0[4];
		  
	      Temp[0] = Temp0[0];
	      Temp[1] = Temp0[1];
	      Temp[2] = Temp0[2];
	      Temp[3] = Temp0[3];
	      Temp[4] = Temp0[4];	
          EEPROM.write(ProfileAddr, Profile);
	      buzzeractivate = 1;
		  lcd.setCursor(6,0); // column, row
          lcd.print("L");
	   }
       if(Profile == 1) {
	      Time[0] = Time1[0];
	      Time[1] = Time1[1];
	      Time[2] = Time1[2];
	      Time[3] = Time1[3];
	      Time[4] = Time1[4];
		  
	      Temp[0] = Temp1[0];
	      Temp[1] = Temp1[1];
	      Temp[2] = Temp1[2];
	      Temp[3] = Temp1[3];
	      Temp[4] = Temp1[4];
          EEPROM.write(ProfileAddr, Profile);
	      buzzeractivate = 1;
		  lcd.setCursor(6,0); // column, row
          lcd.print("M");
	   }
       if(Profile == 2) {
	      Time[0] = Time2[0];
	      Time[1] = Time2[1];
	      Time[2] = Time2[2];
	      Time[3] = Time2[3];
	      Time[4] = Time2[4];	
		  
	      Temp[0] = Temp2[0];
	      Temp[1] = Temp2[1];
	      Temp[2] = Temp2[2];
	      Temp[3] = Temp2[3];
	      Temp[4] = Temp2[4];
          EEPROM.write(ProfileAddr, Profile);
	      buzzeractivate = 1;
		  lcd.setCursor(6,0); // column, row
          lcd.print("H");
	   }
	}

    if(Status == 3) {  // Oven is now go
		lcd.setCursor(0,1); // column, row
		lcd.print(DegC); lcd.print("  ");
		lcd.setCursor(5,1); // column, row
        lcd.print(Seconds);

		if(Seconds >= Time[2]) {  // Reflow heat & cool buzzer
		    buzzeractivate = 5;
		}
		
		if(Seconds > Time[3]) {  // Reflow cool, no heater
		    digitalWrite(DO_Relay, LOW);
            lcd.setCursor(7,0); // column, row
            lcd.print(" "); // indicate heaters off
		}		
		
		if(Seconds == Time[0]) {  // PRE-HEAT
		    lcd.setCursor(0,0); // column, row
            lcd.print("PRE-H ");			
		    buzzeractivate = 2;
			fanspeed = fanspeedslow;
		    myservo.write(fanspeed);
        }
		
		if(Seconds == Time[1]) {  // SOAK
		    lcd.setCursor(0,0); // column, row
            lcd.print("SOAK  ");			
		    buzzeractivate = 2;
			fanspeed = fanspeedslow;
		    myservo.write(fanspeed);
        }
		
		if(Seconds == Time[2]) {  // REFLOW HEAT
		    lcd.setCursor(0,0); // column, row
            lcd.print("FLO-H ");			
		    buzzeractivate = 2;
			fanspeed = fanspeedslow;
		    myservo.write(fanspeed);
        }

		if(Seconds == Time[3]) {  // REFLOW COOL
		    lcd.setCursor(0,0); // column, row
            lcd.print("FLO-C ");			
		    buzzeractivate = 2;
			fanspeed = fanspeedslow;
		    myservo.write(fanspeed);
        }

		if(Seconds >= Time[4]) {  // REFLOW FINISHED
		    lcd.clear();
		    lcd.setCursor(0,0); // column, row
            lcd.print("DONE  ");
		    buzzeractivate = 4;
			Status = 0;  // Finished so abort
			//fanspeed = fanspeedzero;  // Stop Fan motor
		    //myservo.write(fanspeed);
        }			

        if(++tickslow2 == 10) { // 2 * 1000 = 2000mS
            tickslow2 = 0;

			float var1 = (Temp[zone] - Temp[zone-1]);
			float var2 = (Time[zone] - Time[zone-1]);
			tempstep = (var1 / var2) * 2;  // temperature increase per sec required (x2 since loop is 2secs)
			DegCtempstep = DegCtempstep + tempstep;
			
            if(DegC < DegCtempstep) {  // If temperature is too low then turn on heater
	            digitalWrite(DO_Relay, HIGH);
                lcd.setCursor(7,0); // column, row
                lcd.print("*"); // indicate heaters on
	        }
            if(DegC > DegCtempstep) {  // If temperature is too high then turn off heater
	            digitalWrite(DO_Relay, LOW);
                lcd.setCursor(7,0); // column, row
                lcd.print(" "); // indicate heaters off
			}
        }		
	
	}	
	
}


// ************************* Buzzer ***************************
void buzzer() {  // This sub activates the buzzer without using delay()
    currentMillis = millis();
    if (buzzeractivate == 1) {
	   previousMillis = currentMillis;  // save off the start of the buzz
	   buzzloop = 1;
	   buzzeractivate = 0;
	   buzzinterval = 50;  // buzzer duration in mS
	}

    if (buzzeractivate == 2) { 
	   previousMillis = currentMillis;  // save off the start of the buzz
	   buzzloop = 1;
	   buzzeractivate = 0;
	   buzzinterval = 1000;  // buzzer duration in mS
	}

    if (buzzeractivate == 3) { 
	   previousMillis = currentMillis;  // save off the start of the buzz
	   buzzloop = 1;
	   buzzeractivate = 0;
	   buzzinterval = 1250;  // buzzer duration in mS
	}

    if (buzzeractivate == 4) { 
	   previousMillis = currentMillis;  // save off the start of the buzz
	   buzzloop = 1;
	   buzzeractivate = 0;
	   buzzinterval = 1500;  // buzzer duration in mS
	}

    if (buzzeractivate == 5) { 
	   previousMillis = currentMillis;  // save off the start of the buzz
	   buzzloop = 1;
	   buzzeractivate = 0;
	   buzzinterval = 30;  // buzzer duration in mS
	}

    if (buzzeractivate == 6) { 
	   previousMillis = currentMillis;  // save off the start of the buzz
	   buzzloop = 1;
	   buzzeractivate = 0;
	   buzzinterval = 200;  // buzzer duration in mS
	}
	
	if (buzzloop == 1) {  // buzz loop activated
        if (currentMillis - previousMillis < buzzinterval) {  // if true then keep buzzing
           digitalWrite(DO_Buzz, HIGH);  // Turn on buzzer
           } else {
	       buzzloop = 0;
	       digitalWrite(DO_Buzz, LOW);   // stop buzzing
        }
	}
	
}


// ************************* Log Data ***************************
// Send the LOGTEST command to Gobetwino seperated by semicolon
void logData( int value1, int value2) {
   char buffer[5];
   Serial.print("#S|LOGTEST|[");
   Serial.print(itoa((value1), buffer, 10));
   Serial.print(";");
   Serial.print(itoa((value2), buffer, 10));
   Serial.println("]#");
} 
