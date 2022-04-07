#include <LiquidCrystal.h>
#include <max6675.h>
#include <PID_v1.h>

// ***** TYPE DEFINITIONS *****
typedef enum REFLOW_STATE{
    REFLOW_STATE_IDLE,
    REFLOW_STATE_PREHEAT,
    REFLOW_STATE_SOAK,
    REFLOW_STATE_REFLOW,
    REFLOW_STATE_COOL,
    REFLOW_STATE_COMPLETE,
    REFLOW_STATE_ERROR
} reflowState_t;

typedef enum REFLOW_STATUS{
    REFLOW_STATUS_OFF,
    REFLOW_STATUS_ON
} reflowStatus_t;

typedef enum DEBOUNCE_STATE{
    DEBOUNCE_STATE_IDLE,
    DEBOUNCE_STATE_CHECK,
    DEBOUNCE_STATE_RELEASE
} debounceState_t;

// ***** CONSTANTS *****
#define TEMPERATURE_ROOM 50
#define TEMPERATURE_SOAK_MIN 150
#define TEMPERATURE_SOAK_MAX 200
#define TEMPERATURE_REFLOW_MAX 250
#define TEMPERATURE_COOL_MIN 100
#define SENSOR_SAMPLING_TIME 1000
#define SOAK_TEMPERATURE_STEP 5
#define SOAK_MICRO_PERIOD 9000
#define DEBOUNCE_PERIOD_MIN 50
#define THERMOCOUPLE_DISCONNECTED 10000

// ***** PID PARAMETERS *****
// ***** PRE-HEAT STAGE *****
#define PID_KP_PREHEAT 300
#define PID_KI_PREHEAT 0.05
#define PID_KD_PREHEAT 400

// ***** SOAKING STAGE *****
#define PID_KP_SOAK 300
#define PID_KI_SOAK 0.05
#define PID_KD_SOAK 250

// ***** REFLOW STAGE *****
#define PID_KP_REFLOW 300
#define PID_KI_REFLOW 0.05
#define PID_KD_REFLOW 350
#define PID_SAMPLE_TIME 1000

// ***** LCD MESSAGES *****
const char* lcdMessagesReflowStatus[] = {
    "Ready",
    "Pre-heat",
    "Soak",    
    "Reflow",
    "Cool",
    "Complete",
    "Error"
};

// ***** DEGREE SYMBOL FOR LCD *****
unsigned char degree[8]  = {140,146,146,140,128,128,128,128};

// ***** PIN ASSIGNMENT *****
int ssr = 5;
int thermocoupleSO = A5;
int thermocoupleCS = A4;
int thermocoupleCLK = A3;
int lcdRs = 7;
int lcdE = 8;
int lcdD4 = 9;
int lcdD5 = 10;
int lcdD6 = 11;
int lcdD7 = 12;
int ledRed = A1;
int ledGreen = A0;
int buzzer = 6;
int buttonup = 2;
int buttondown = 3;
int buttongo = 4;

// ***** PID CONTROL VARIABLES *****
double setpoint;
double input;
double output;
double kp = PID_KP_PREHEAT;
double ki = PID_KI_PREHEAT;
double kd = PID_KD_PREHEAT;
int windowSize;
unsigned long windowStartTime;
unsigned long nextCheck;
unsigned long nextRead;
unsigned long timerSoak;
unsigned long buzzerPeriod;

reflowState_t reflowState;															// Reflow oven controller state machine state variable
reflowStatus_t reflowStatus;														// Reflow oven controller status
debounceState_t debounceState;														// Button debounce state machine state variable
long lastDebounceTime;																// Button debounce timer
boolean buttonPressStatus;															// Button press status	
int timerSeconds;																	// Seconds timer

PID reflowOvenPID(&input, &output, &setpoint, kp, ki, kd, DIRECT);					// Specify PID control interface
LiquidCrystal lcd(lcdRs, lcdE, lcdD4, lcdD5, lcdD6, lcdD7);							// Specify LCD interface
MAX6675 thermocouple(thermocoupleCLK, thermocoupleCS, thermocoupleSO);				// Specify MAX6675 thermocouple interface

void setup() {
   
    digitalWrite(ssr, LOW);
    pinMode(ssr, OUTPUT);															// SSR pin initialization to ensure reflow oven is off
    
    digitalWrite(buzzer, LOW);
    pinMode(buzzer, OUTPUT);														// Buzzer pin initialization to ensure annoying buzzer is off
        
    digitalWrite(ledRed, LOW);														// LED pins initialization and turn on upon start-up (active low)
    digitalWrite(ledGreen, LOW);
    pinMode(ledRed, OUTPUT);
    pinMode(ledGreen, OUTPUT);
	
    pinMode(buttonup, INPUT);														// Push button pins initialization
    pinMode(buttondown, INPUT);
    pinMode(buttongo, INPUT);
	
    digitalWrite(buzzer, HIGH);														// Start-up splash
    lcd.begin(8, 2);
    lcd.createChar(0, degree);
    lcd.clear();
    lcd.print("Reflow");
    lcd.setCursor(0, 1);
    lcd.print("Oven V1");
    digitalWrite(buzzer, LOW);
    delay(2500);
    lcd.clear();
        
    Serial.begin(57600);															// Serial communication at 57600 bps
    
    digitalWrite(ledRed, HIGH);														// Turn off LED (active low)
    digitalWrite(ledGreen, HIGH);
        
    windowSize = 2000;																// Set window size    
    nextCheck = millis();															// Initialize time keeping variable	    
    nextRead = millis();															// Initialize thermocouple reading varible
}

void loop() {

    unsigned long now;																// Current time
        
    if (millis() > nextRead) {														// Time to read thermocouple?
    
        nextRead += SENSOR_SAMPLING_TIME;											// Read thermocouple next sampling period        
        input = thermocouple.readCelsius();											// Read current temperature	
                
        if (input == THERMOCOUPLE_DISCONNECTED) {										// If thermocouple is not connected
        
            reflowState = REFLOW_STATE_ERROR;										// Illegal operation without thermocouple
            reflowStatus = REFLOW_STATUS_OFF;
			
        }
    }
    
    if (millis() > nextCheck) {

        nextCheck += 1000;										       				// Check input in the next seconds

        if (reflowStatus == REFLOW_STATUS_ON)								        // If reflow process is on going
        {            
            digitalWrite(ledRed, !(digitalRead(ledRed)));							// Toggle red LED as system heart beat            
            timerSeconds++;															// Increase seconds timer for reflow curve analysis            
            Serial.print(timerSeconds);												// Send temperature and time stamp to serial 
            Serial.print(" ");
            Serial.print(setpoint);
            Serial.print(" ");
            Serial.print(input);
            Serial.print(" ");
            Serial.println(output);
        }
        else
        {
            // Turn off red LED
            digitalWrite(ledRed, HIGH);
        }
        
        lcd.clear();																// Clear LCD
        lcd.print(lcdMessagesReflowStatus[reflowState]);					        // Print current system state
        lcd.setCursor(0, 1);												        // Move the cursor to the 2 line

        if (reflowState == REFLOW_STATE_ERROR)								        // If currently in error state
        {
            lcd.print("No TC!");										            // No thermocouple wire connected
        }
        else
        {
            lcd.print(input);											            // Print current temperature
            lcd.print("C ");            											// Print degree Celsius symbol
        }
    }
    
    switch (reflowState) {															// Reflow oven controller state machine

        case REFLOW_STATE_IDLE:
            
            if (buttonPressStatus)													// If button is pressed to start reflow process
            {
                
                if (input <= TEMPERATURE_ROOM)										// Ensure current temperature is comparable to room temperature
                {                    
                    Serial.println("Time Setpoint Input Output");					// Send header for CSV file                    
                    timerSeconds = 0;												// Intialize seconds timer for serial debug information
                    windowStartTime = millis();										// Initialize PID control window starting time		                 
                    setpoint = TEMPERATURE_SOAK_MIN;								// Ramp up to minimum soaking temperature                    
                    reflowOvenPID.SetOutputLimits(0, windowSize);					// Tell the PID to range between 0 and the full window size
                    reflowOvenPID.SetSampleTime(PID_SAMPLE_TIME);                   
                    reflowOvenPID.SetMode(AUTOMATIC);								// Turn the PID on                    
                    reflowState = REFLOW_STATE_PREHEAT;								// Proceed to preheat stage
                }
            }
            break;

        case REFLOW_STATE_PREHEAT:
            reflowStatus = REFLOW_STATUS_ON;
               
            if (input >= TEMPERATURE_SOAK_MIN)										// If minimum soak temperature is achieve    
            {                
                timerSoak = millis() + SOAK_MICRO_PERIOD;							// Chop soaking period into smaller sub-period                
                reflowOvenPID.SetTunings(PID_KP_SOAK, PID_KI_SOAK, PID_KD_SOAK);	// Set less agressive PID parameters for soaking ramp                
                setpoint = TEMPERATURE_SOAK_MIN + SOAK_TEMPERATURE_STEP;   			// Ramp up to first section of soaking temperature	                
                reflowState = REFLOW_STATE_SOAK; 									// Proceed to soaking state
            }
            break;
        
        case REFLOW_STATE_SOAK:     

            if (millis() > timerSoak)												// If micro soak temperature is achieved   
            {
                timerSoak = millis() + SOAK_MICRO_PERIOD;                
                setpoint += SOAK_TEMPERATURE_STEP;									// Increment micro setpoint
                if (setpoint > TEMPERATURE_SOAK_MAX)
                {
                    // Set agressive PID parameters for reflow ramp
                    reflowOvenPID.SetTunings(PID_KP_REFLOW, PID_KI_REFLOW, PID_KD_REFLOW);
                    // Ramp up to first section of soaking temperature
                    setpoint = TEMPERATURE_REFLOW_MAX;   
                    // Proceed to reflowing state
                    reflowState = REFLOW_STATE_REFLOW; 
                }
            }
            break; 
         
        case REFLOW_STATE_REFLOW:
																					// We need to avoid hovering at peak temperature for too long
																					// Crude method that works like a charm and safe for the components
            if (input >= (TEMPERATURE_REFLOW_MAX - 5))
            {                
                reflowOvenPID.SetTunings(PID_KP_REFLOW, PID_KI_REFLOW, PID_KD_REFLOW);	// Set PID parameters for cooling ramp                
                setpoint = TEMPERATURE_COOL_MIN;									// Ramp down to minimum cooling temperature   	                
                reflowState = REFLOW_STATE_COOL; 									// Proceed to cooling state
            }
            break;   
            
        case REFLOW_STATE_COOL:
                
            if (input <= TEMPERATURE_COOL_MIN)										// If minimum cool temperature is achieve   		
            {                
                buzzerPeriod = millis() + 1000;										// Retrieve current time for buzzer usage                
                digitalWrite(ledGreen, LOW);										// Turn on buzzer and green LED to indicate completion
                digitalWrite(buzzer, HIGH);                
                reflowStatus = REFLOW_STATUS_OFF;									// Turn off reflow process     	                          
                reflowState = REFLOW_STATE_COMPLETE; 								// Proceed to reflow Completion state
            }         
            break;    
            
        case REFLOW_STATE_COMPLETE:
            if (millis() > buzzerPeriod)
            {                
                digitalWrite(buzzer, LOW);											// Turn off buzzer and green LED	
                digitalWrite(ledGreen, HIGH);                
                reflowState = REFLOW_STATE_IDLE; 									// Reflow process ended
            }
            break;
        
        case REFLOW_STATE_ERROR:
            
            if (input == THERMOCOUPLE_DISCONNECTED)									// If thermocouple is still not connected
            {                
                reflowState = REFLOW_STATE_ERROR;									// Wait until thermocouple wire is connected 
            }
            else
            {                
                reflowState = REFLOW_STATE_IDLE;									// Clear to perform reflow process 
            }
            break;    
    }    
        
    if (buttonPressStatus == true) {													// If button is pressed

        if (reflowStatus == REFLOW_STATUS_ON)										// If currently reflow process is on going // Button press is for cancelling
        {            
            reflowStatus = REFLOW_STATUS_OFF;										// Turn off reflow process            
            reflowState = REFLOW_STATE_IDLE;										// Reinitialize state machine
        }
    } 

    switch (debounceState) {														    // Simple button debounce state machine (for button #1 only)

        case DEBOUNCE_STATE_IDLE:													// TO DO: To be replaced with interrupt version in next revision
            
            buttonPressStatus = false;												// No valid button press
            
            if (digitalRead(button1) == LOW)										// If button #1 is pressed
            {                
                lastDebounceTime = millis();										// Intialize debounce counter                
                debounceState = DEBOUNCE_STATE_CHECK;								// Proceed to check validity of button press
            }
            break;
            
        case DEBOUNCE_STATE_CHECK:
            
            if (digitalRead(button1) == LOW)										// If button #1 is still pressed
            {
                
                if ((millis() - lastDebounceTime) > DEBOUNCE_PERIOD_MIN)			// If minimum debounce period is completed
                {                    
                    debounceState = DEBOUNCE_STATE_RELEASE;							// Proceed to wait for button release
                }
            }

            else														            // False trigger
            {
                debounceState = DEBOUNCE_STATE_IDLE;                				// Reinitialize button debounce state machine
            }
            break;
            
        case DEBOUNCE_STATE_RELEASE:
            if (digitalRead(button1) == HIGH)
            {
                // Valid button press
                buttonPressStatus = true;
                // Reinitialize button debounce state machine
                debounceState = DEBOUNCE_STATE_IDLE; 
            }
            break;
    }
    	
    if (reflowStatus == REFLOW_STATUS_ON) {											// PID computation and SSR control

        now = millis();														        //unsigned long now;
        
        reflowOvenPID.Compute();

        if((now - windowStartTime) > windowSize)
        { 
            windowStartTime += windowSize;								            // Time to shift the Relay Window
        }
        if(output > (now - windowStartTime)) digitalWrite(ssr, HIGH);
        else digitalWrite(ssr, LOW);   
    }

    else {																		    // Reflow oven process is off, ensure oven is off 
        digitalWrite(ssr, LOW);
    }

}

