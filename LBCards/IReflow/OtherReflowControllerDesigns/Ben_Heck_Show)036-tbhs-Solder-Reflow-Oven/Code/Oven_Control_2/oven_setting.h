
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
int button1 = 2;
int button2 = 3;

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

