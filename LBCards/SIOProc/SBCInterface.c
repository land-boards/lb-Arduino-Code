//
// KEYBOARD, SERIAL AND DISPLAY INTERFACE
// (c) GRANT SEARLE 2007-13
//
// http://searle.hostei.com/grant/MonitorKeyboard/index.html
//
// Use a search engine (Google etc) to search for "Grant Searle" if the web page is no longer active
// in case it has moved.

#define KBBUFSIZE 50
#define SERBUFSIZE 800
#define F_CPU 11059200ul
#define USART_BAUD 115200ul
#define USART_UBBR_VALUE ((F_CPU/(USART_BAUD<<4))-1)

// Two-wire interface definitions
#define START 0x08
#define MT_DATA_ACK 0x28
#define MT_SLA_ACK 0x18
#define SLA_W 0x02 // Addr = 1, read/write = low

#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <avr/io.h>
#include <util/delay.h>

unsigned char kbBuffer[KBBUFSIZE];
unsigned int volatile kbInPointer;
unsigned int volatile kbOutPointer;
unsigned char kbClockCount;
unsigned char kbTemp;
unsigned char kbShift;
unsigned char kbCrtl;
unsigned char kbAlt;
unsigned char kbCaps;
unsigned char kbNumLock;
unsigned char kbScrollLock;
unsigned char kbValue;
unsigned char prevKbCode;

unsigned char kbAckReceived;
unsigned char kbWriteActive;
unsigned char kbWriteDataVal;

unsigned char kbWriteCount;
unsigned char kbBuffer1;
unsigned char kbBuffer2;
unsigned char kbBuffer3;
unsigned char kbWrPar;

unsigned char enableAnsiConversion;
unsigned char serBuffer[SERBUFSIZE];
int volatile serInPointer;
int volatile serOutPointer;
unsigned char twiStarted;
//Keycode values up to 131 (max returned from a 102 key keyboard)
//These values are for a UK keyboard mapping
const unsigned char kbNormal[132] PROGMEM = {
	0 , 137 , 0 , 133 , 131 , 129 , 130 , 140 , 0 , 138 , 136 , 134 , 132 , 07 , 06 , 0 ,
	0 , 0 , 0 , 0 , 0 , 113 , 49 , 0 , 0 , 0 , 122 , 115 , 97 , 119 , 50 , 0 ,
	0 , 99 , 120 , 100 , 101 , 52 , 51 , 59 , 0 , 32 , 118 , 102 , 116 , 114 , 53 , 0 ,
	0 , 110 , 98 , 104 , 103 , 121 , 54 , 7 , 8 , 44 , 109 , 106 , 117 , 55 , 56 , 0 ,
	0 , 44 , 107 , 105 , 111 , 48 , 57 , 0 , 0 , 46 , 47 , 108 , 59 , 112 , 45 , 0 ,
	0 , 0 , 39 , 0 , 91 , 61 , 0 , 0 , 0 , 0 , 13 , 93 , 0 , 35 , 0 , 0 ,
	0 , 92 , 0 , 0 , 0 , 0 , 8 , 0 , 0 , 49 , 0 , 52 , 55 , 0 , 0 , 0 ,
   48 , 46 , 50 , 53 , 54 , 56 , 03 , 0 , 139 , 43 , 51 , 45 , 42 , 57 , 0 , 0 ,
    0 , 0 , 0 , 135};


const unsigned char kbShifted[132] PROGMEM = {
	0 , 149 , 0 , 145 , 143 , 141 , 142 , 152 , 0 , 150 , 148 , 146 , 144 , 0 , 172 , 0 ,
	0 , 0 , 0 , 0 , 0 , 81 , 33 , 0 , 0 , 0 , 90 , 83 , 65 , 87 , 34 , 0 ,
	0 , 67 , 88 , 68 , 69 , 36 , 163 , 58 , 0 , 32 , 86 , 70 , 84 , 82 , 37 , 0 ,
	0 , 78 , 66 , 72 , 71 , 89 , 94 , 0 , 0 , 76 , 77 , 74 , 85 , 38 , 42 , 0 ,
	0 , 60 , 75 , 73 , 79 , 41 , 40 , 0 , 0 , 62 , 63 , 76 , 58 , 80 , 95 , 0 ,
	0 , 0 , 64 , 0 , 123 , 43 , 0 , 0 , 0 , 0 , 13 , 125 , 0 , 126 , 0 , 0 ,
	0 , 124 , 0 , 0 , 0 , 8 , 0 , 0 , 49 , 0 , 52 , 55 , 0 , 0 , 0 , 0 ,
   48 , 46 , 50 , 53 , 54 , 56 , 03 , 0 , 151 , 43 , 51 , 45 , 42 , 57 , 0 , 0 ,
    0 , 0 , 0 , 135};

void setRTS()
{
	unsigned int temp1;
	unsigned int temp2;
	unsigned int bufferUsed;

	temp1 = serInPointer;
	temp2 = serOutPointer;

	if(temp2 <= temp1)
	{
		bufferUsed = temp1 - temp2;
	}
	else
	{
		bufferUsed = SERBUFSIZE + temp1 - temp2;
	}
	if (bufferUsed < 32)
	{
		PORTC = PORTC & 0b11110111;
	}
	if (bufferUsed > SERBUFSIZE-32)
	{
		PORTC = PORTC | 0b00001000;
	}
}

void setKeyboardToReceiveMode()
{
	TCNT2=0;
	// Bring clock low
	_delay_us(500);
	DDRC = DDRC | 0b00000010;
	PORTC=PORTC & 0b11111101;
	_delay_us(500);
	// Bring data low
	DDRC = DDRC | 0b00000100;
	PORTC=PORTC & 0b11111011;
	_delay_us(500);
	// Release clock
	DDRC = DDRC & 0b11111101;
	PORTC=PORTC & 0b11111101;
	TCNT2=0;
	kbWrPar=1;
	kbClockCount=0;
	kbWriteActive=1;
}

void setKeyboardToSendMode()
{
	DDRC = DDRC & 0b11111001;
}

void sendBitToKB(unsigned char val)
{
	if (val==1)
	{
		PORTC=PORTC | 0b00000100;
	}
	else
	{
		PORTC=PORTC & 0b11111011;
	}
	
}

// This is activated on the keyboard clock signal for both low and high transitions
ISR(PCINT1_vect)
{
	unsigned int kbTempptr;

	//Reset the 20ms timeout
	TCNT2=0;

	if (kbWriteActive==1)
	{
		// When writing to the keyboard, set data on low to high transitions
		// so if the clock is low, don't do any more processing
		if ((PINC & 2)==0)
		{
			return;
		}
		kbClockCount++;
		if (kbClockCount==10)
		{
			setKeyboardToSendMode();
		}
		if (kbClockCount==11)
		{
			kbWriteActive=0;
			kbClockCount=0;
			kbTemp=0;
		}
		else if (kbClockCount==9)
		{
			//sendBitToKB(1);
			if (kbWrPar==1)
			{
				sendBitToKB(1);
			}
			else
			{
				sendBitToKB(0);
			}
		}
		else
		{
			if ((kbWriteDataVal & 1)==1)
			{
				sendBitToKB(1);
				if (kbWrPar==1)
				{
					kbWrPar=0;
				}
				else
				{
					kbWrPar=1;
				}
			}
			else
			{
				sendBitToKB(0);
			}
			kbWriteDataVal=kbWriteDataVal>>1;			
		}
		return;
	}
	// When reading the keyboard, only use high-to-low transitions
	// so if the clock is high, don't do any more processing
	if ((PINC & 2)>0)
	{
		return;
	}
	
	kbClockCount++;
	if (kbClockCount==1 || kbClockCount==10)
	{
		// ignore
	}
	else if (kbClockCount==11)
	{
		kbClockCount=0;
	}
	else
	{
		// Shift value right and set high bit if needed
		kbTemp =kbTemp/2;
		if ((PINC & 4)>0)
		{
			kbTemp=kbTemp+128;
		}

		// When complete, store in the key buffer
		if (kbClockCount==9)
		{
			kbTempptr = kbInPointer;
			kbTempptr++;
			if (kbTempptr >(KBBUFSIZE-1))
			{
				kbTempptr = 0;
			}

			if (kbTempptr == kbOutPointer)
			{
				// ignore
			}
			else
			{
				kbBuffer[kbTempptr] = kbTemp;
				kbInPointer = kbTempptr;
			}
			kbTemp = 0;
		}
	}
}

void updateKeyboardLEDs()
{
	unsigned char ledVals;
	ledVals=0;
	if (kbScrollLock==1)
	{
		ledVals+=1;
	}
	if (kbNumLock==1)
	{
		ledVals+=2;
	}
	if (kbCaps==1)
	{
		ledVals+=4;
	}
	kbBuffer2=0xED;
	kbBuffer1=ledVals;
	kbWriteCount=2;
	kbAckReceived=1;
}

ISR (USART_RX_vect)
{
	unsigned char  tempSts;
	unsigned char 	inByte;
	int tempPtr;
	tempSts = UCSR0A & 0x1C;
	inByte = UDR0;
	if (tempSts > 0)
	{
		inByte = '?';
	}

	tempPtr = serInPointer+1;
	if (tempPtr > SERBUFSIZE-1)
	{
		tempPtr = 0;
	}
	if (tempPtr == serOutPointer)
	{
		//ignore because buffer is full
	}
	else
	{
		serBuffer[tempPtr] = inByte;
		serInPointer = tempPtr;
	}

	setRTS();
}

void initUSART(void)
{
	// Set baud rate
	UBRR0H = (unsigned char)(USART_UBBR_VALUE>>8);
	UBRR0L = (unsigned char)USART_UBBR_VALUE;

	// Set frame format to 8 data bits, no parity, 1 stop bit
	UCSR0C = (0<<USBS0)|(1<<UCSZ01)|(1<<UCSZ00);

	// Enable rec interrupt, receiver and transmitter
	UCSR0B = (1<<RXCIE0)|(1<<RXEN0)|(1<<TXEN0);
}

void sendUSART(unsigned char c)
{
	// Wait if a byte is being transmitted
	while((UCSR0A&(1<<UDRE0)) == 0);

	// Transmit data
	UDR0 = c;
}

void sendToDisplay(unsigned char c)
{
	// Check PB1 and PB2 to see if a Two-wire, 4 bit or 8 bit interface to the monitor is being used
	unsigned char fourBit = PINB & 0b00000010; //PB1
	unsigned char twi = PINB & 0b00000100; //PB2
	if (fourBit==0)
	{
		send2x4BitToDisplay(c);
	}
	else if (twi==0)
	{
		sendTWItoDisplay(c);
	}
	else
	{
		send8BitToDisplay(c);
	}
}
	
void send8BitToDisplay(unsigned char c)
{
	unsigned char temp;
	unsigned char dataAvail;
	unsigned char ackIn;

	// Check to see if the acknowledge pin is the same as the data available pin
	// If not then wait until it is (the display processor will change it to be the same when ready)
	dataAvail=PORTC & 0b00100000;
	ackIn=(PINC & 0b00010000) << 1;

	while (dataAvail!=ackIn)
	{
		dataAvail=PORTC & 0b00100000;
		ackIn=(PINC & 0b00010000) << 1;
	}
	// Move the data into the appropriate output pins
	temp = PORTB & 0b11011110;
    if ((c & 1)>0) { temp=temp+1; }
    if ((c & 16)>0) { temp=temp+32; }
	PORTB = temp;
	temp=0;		
	if ((c & 2)>0) { temp=temp+128; }
	if ((c & 4)>0) { temp=temp+64; }
	if ((c & 8)>0) { temp=temp+32; }
	if ((c & 32)>0) { temp=temp+16; }
	if ((c & 64)>0) { temp=temp+8; }
	if ((c & 128)>0) { temp=temp+4; }
	PORTD = temp;
	
	// Flip the data avail bit to tell the display that there is a character/command ready for display
	PORTC = PORTC ^ 0b00100000;
}

void send2x4BitToDisplay(unsigned char c)
{
	unsigned char temp;
	unsigned char ackIn;

	PORTC = PORTC & 0b11011111; // Should already be low, set just in case

	// Check to see if the acknowledge pin is low
	// If not then wait until it is (the display processor will change to low when ready)
	ackIn=PINC & 0b00010000;
	while (ackIn!=0)
	{
		ackIn=PINC & 0b00010000;
	}
	// Move the data into the appropriate output pins
	temp = PORTB & 0b11111110;
    if ((c & 16)>0) { temp=temp+1; }
	PORTB = temp;
	temp=0;		
	if ((c & 32)>0) { temp=temp+128; }
	if ((c & 64)>0) { temp=temp+64; }
	if ((c & 128)>0) { temp=temp+32; }
	PORTD = temp;
	
	// Flip the data avail bit to tell the display that high 4 bits are ready for display
	PORTC = PORTC | 0b00100000;

	// Check to see if the acknowledge pin is high
	// If not then wait until it is (the display processor will change to high when ready)
	ackIn=PINC & 0b00010000;
	while (ackIn==0)
	{
		ackIn=PINC & 0b00010000;
	}
	// Move the data into the appropriate output pins
	temp = PORTB & 0b11111110;
	if ((c & 1)>0) { temp=temp+1; }
	PORTB = temp;
	temp=0;
	if ((c & 2)>0) { temp=temp+128; }
	if ((c & 4)>0) { temp=temp+64; }
	if ((c & 8)>0) { temp=temp+32; }
	PORTD = temp;
	
	// Flip the data avail bit to tell the display that low 4 bits are ready for display
	PORTC = PORTC & 0b11011111;
}

void sendTWItoDisplay(unsigned char c)
{
	unsigned char retCode;
    // If first char then start TWI data stream
	if (twiStarted==0)
	{
		startTWI();
	}

	TWDR = c;
	TWCR = (1<<TWINT) | (1<<TWEN); // Clear TWINT bit in TWCR to start transmission of data
	while ((TWCR & (1<<TWINT))==0); // Wait
	retCode=TWSR & 0xF8;
	if (retCode != MT_DATA_ACK)
	{
		// If error, try to restart TWI and resume
		startTWI();
		TWDR = c;
		TWCR = (1<<TWINT) | (1<<TWEN); // Clear TWINT bit in TWCR to start transmission of data
		while ((TWCR & (1<<TWINT))==0); // Wait
		retCode=TWSR & 0xF8;
		if (retCode != MT_DATA_ACK)
		{
			error(3,retCode); // ERROR
		}
	} 

//	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO); // Send stop - NOT USED BECAUSE DATA STREAM REMAINS OPEN
}
void startTWI()
{
		TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN); // Send start
		while ((TWCR & (1<<TWINT))==0) ; // Wait
		unsigned char retCode=TWSR & 0xF8;
		if (retCode!=START) error(1,retCode); // ERROR

		TWDR = SLA_W; // Load SLA_W (address of display and low-write bit) into TWDR
		TWCR = (1<<TWINT) | (1<<TWEN); // Clear TWINT bit in TWCR to start transmission of address
		while ((TWCR & (1<<TWINT))==0) ; // Wait
		retCode=TWSR & 0xF8;
		if (retCode != MT_SLA_ACK) error(2,retCode); // ERROR
		twiStarted=1;
}

unsigned char getInChar()
{
	unsigned char retVal=0;
	unsigned int tempPointer;
	while (serInPointer==serOutPointer)
	{
		asm volatile ("nop");
	}
	cli();
	tempPointer=serOutPointer+1;
	if (tempPointer >(SERBUFSIZE-1))
	{
		tempPointer = 0;
	}
	retVal=serBuffer[tempPointer];
	serOutPointer=tempPointer;
	sei();
	setRTS();

	return retVal;
}


unsigned char isInCharAvailable()
{
	if (serInPointer==serOutPointer)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

unsigned char getKbCode()
{
	unsigned char retVal=0;
	unsigned int tempPointer;
	if (kbInPointer==kbOutPointer)
	{
		return 0;
	}
	cli();
	tempPointer=kbOutPointer+1;
	if (tempPointer >(KBBUFSIZE-1))
	{
		tempPointer = 0;
	}
	retVal=kbBuffer[tempPointer];
	kbOutPointer=tempPointer;
	sei();
	return retVal;
}

void processATKeyboard()
{
	unsigned char  kbCode=0;
	unsigned char keyValue=0;
	kbCode = getKbCode();
	if (kbCode>0)
	{
		if (kbCode==0xFA)
		{
			kbAckReceived = 1;
			prevKbCode=kbCode;
			return;
		}
		//Ignore E0 prefixes if part of the key up as they are not significant
		//prev code will remain as F0 to ensure the following is processed properly
		if (prevKbCode==0xF0 && kbCode==0xE0)
		{
			return;	
		}				
		if (prevKbCode==0xF0)
		{
			prevKbCode=kbCode;
			if (kbCode == 0x12 || kbCode ==0x59)
			{
				kbShift = 0;
			}
			if (kbCode == 0x14)
			{
				kbCrtl = 0;
			}
			if (kbCode == 0x11)
			{
				kbAlt = 0;
			}
			return;
		}
		if (prevKbCode==0xE0 || kbNumLock==0)
		{
			prevKbCode=kbCode;
			// Cursor keys - no ascii equiv, so sending "Wordstar" equivalents - CTRL E,S,D,X
			if (kbCode == 0x75) //up
			{
				sendUSART(5);
				return;
			}
			if (kbCode == 0x72) //down
			{
				sendUSART(24);
				return;
			}
			if (kbCode == 0x6B) //left
			{
				sendUSART(16);
				return;
			}
			if (kbCode == 0x74) //right
			{
				sendUSART(4);
				return;
			}
			if (kbCode == 0x70) //ins
			{
				sendUSART(1);
				return;
			}
			if (kbCode == 0x71) //del
			{
				sendUSART(1);
				return;
			}
			if (kbCode == 0x6C) //home
			{
				sendUSART(1);
				return;
			}
			if (kbCode == 0x69) //end
			{
				sendUSART(1);
				return;
			}
			if (kbCode == 0x7D) //page up
			{
				sendUSART(1);
				return;
			}
			if (kbCode == 0x7A) //page down
			{
				sendUSART(1);
				return;
			}
		}

		if (kbCode == 0x12 || kbCode ==0x59)
		{
			kbShift = 1;
		}
		else if (kbCode == 0x14)
		{
			kbCrtl = 1;
		}
		else if (kbCode == 0x11)
		{
			kbAlt = 1;
		}
		else if (kbCode == 0x58)
		{
			if (kbCaps==1)
			{
				kbCaps=0;
			}
			else
			{
				kbCaps=1;
			}
			updateKeyboardLEDs();
		}
		else if (kbCode == 0x77)
		{
			if (kbNumLock==1)
			{
				kbNumLock=0;
			}
			else
			{
				kbNumLock=1;
			}
			updateKeyboardLEDs();
		}
		else if (kbCode == 0x7E)
		{
			if (kbScrollLock==1)
			{
				kbScrollLock=0;
			}
			else
			{
				kbScrollLock=1;
			}
			updateKeyboardLEDs();
		}

		else if (kbCode<132)
		{
			if (kbShift==0)
			{
				keyValue = pgm_read_byte(&kbNormal[kbCode]);
			}
			else
			{
				keyValue = pgm_read_byte(&kbShifted[kbCode]);
			}

			if (keyValue>0)
			{
				if ((keyValue>='a') && (keyValue<='z') && (kbCaps==1))
				{
					keyValue=keyValue-32;
				}
				else if ((keyValue>='A') && (keyValue<='Z') && (kbCaps==1))
				{
					keyValue=keyValue+32;
				}

				if (kbCrtl==1)
				{
					keyValue=keyValue & 0x1F;
				}

				sendUSART(keyValue);
			}
		}
		prevKbCode=kbCode;
	}
}

//20ms interrupt resets the keyboard values unless clock read within this time
ISR(TIMER2_COMPA_vect)
{

	//Timeout, so reset the keyboard read variables
	kbClockCount=0;
	kbTemp=0;
	
	//Also reset any pending command
	kbWriteCount=0;
	if (kbWriteActive==1)
	{
		setKeyboardToReceiveMode();
		setKeyboardToSendMode();
		kbWriteActive=0;
	}

}

void error(unsigned char location, unsigned char err)
{
	// Disable errors
	if (1)
	{
		return;
	}
	
	// SIMPLE DISPLAY OF ERROR STATUS AND LOCATION USING 1 PIN
	//
	// LED connected in series with a resistor to PB3 to show error conditions
	// Watching and counting the flashes allows the error code and location to be read as follows:
	//
	// Start of sequence - one very long flash (2 seconds)
	// 1 second delay
	// Set of very short flashes for location (ie. place in code where error occurred)
	// 1 second delay
	// Set of long flashes for high 4 bits of err ("1x"=1 flash ... "Fx"=15 flashes, "0x" = 16 flashes)
	// 1 second delay
	// Set of short flashes for low 4 bits of err ("x1"=1 flash ... "xF"=15 flashes, "x0" = 16 flashes)
	// 2 second delay
	// Repeat
	
	// SYSTEM HALT ONCE IN THIS ROUTINE
	cli();
	
	while (1)
	{
		PORTB|=0b00001000;
		for (int i=0;i<2000;i++) _delay_ms(1);
		PORTB&=0b11110111;
		for (int i=0;i<1000;i++) _delay_ms(1);

		for (int c=0;c<location;c++)
		{
			PORTB|=0b00001000;
			for (int i=0;i<50;i++) _delay_ms(1);
			PORTB&=0b11110111;
			for (int i=0;i<200;i++) _delay_ms(1);
		}
		for (int i=0;i<1000;i++) _delay_ms(1);

		unsigned char temp=err>>4;
		if (temp==0) temp=16;
		for (unsigned char c=0;c<temp;c++)
		{
			PORTB|=0b00001000;
			for (int i=0;i<800;i++) _delay_ms(1);
			PORTB&=0b11110111;
			for (int i=0;i<200;i++) _delay_ms(1);
		}
		for (int i=0;i<1000;i++) _delay_ms(1);

		temp=err & 0x0F;
		if (temp==0) temp=16;
		for (unsigned char c=0;c<temp;c++)
		{
			PORTB|=0b00001000;
			for (int i=0;i<200;i++) _delay_ms(1);
			PORTB&=0b11110111;
			for (int i=0;i<800;i++) _delay_ms(1);
		}
		for (int i=0;i<2000;i++) _delay_ms(1);
	}	
}
int main(void)
{
	unsigned char serInChar;
	unsigned char prevInChar;
	kbInPointer=0;
	kbOutPointer=0;
	kbClockCount=0;
	prevKbCode=0;
	prevInChar=0;
	unsigned char escParam1;
	unsigned char escParam2;
	
	enableAnsiConversion=1;

	twiStarted=0;
	
	serInPointer=0;
	serOutPointer=0;

	kbWriteActive=0;
	kbWriteCount=0;
	kbAckReceived=0;
	kbWrPar=0;

	PORTB = 0b00000110; // TWI and 4 bit interface select pin pull-up
	DDRB = 0b00101001;
	PORTD = 0x00;
	PORTC = 0x00; // ACK = low

	DDRD = 0b11111111;
	unsigned char twiPin = PINB & 0b00000100; //PB2=0 if two wire interface selected

	if (twiPin==0) // Two wire interface selected so both TWI pins to be inputs by default
	{
		DDRC = 0b00001000; // Only PC3 is an output (/RTS)
		// Two wire speed initialisation
		// SCL freq = CPU freq / (16+2*TWBR*Prescaler)
		TWSR=0; // Prescaler = 1
		TWBR=7; // Bit rate 7 = 400KHz for 12MHz clk  (=12 for 16MHz clk)
	}
	else
	{
		DDRC = 0b00101000; // PC3 and PC5 are outputs (/RTS and AVAIL)
	}	

	PCICR=1<<PCIE1; // Interrupt on pin change
	PCMSK1=1<<PCINT9; // enable pin PC1 change (KB clock) to interrupt

	kbShift=0;
	kbCrtl=0;
	kbAlt=0;
	kbCaps=0;
	kbNumLock=0;
	kbScrollLock=0;
	
	initUSART();

	TIMSK2 = TIMSK2 | (1<<OCIE2A);  // Enable Interrupt TimerCounter2 Compare Match A (TIMER2_COMPA_vect)
	TCCR2A = 1<<WGM21;  // Mode = CTC
	TCCR2B = (1<<CS22) | (1<<CS21) | (1<<CS20);   // Clock div 1024
	OCR2A = 215;          // Interrupt every 20mS unless value reset

	sei();

	// Loop forever
	while (1==1)
	{
		//Get a character from the serial port
		
		if (isInCharAvailable()==1)
		{
			serInChar=getInChar();
			//If it is an escape character then get the following characters to interpret
			//them as an ANSI escape sequence
			if (serInChar==27 && enableAnsiConversion==1) // && prevInChar!=26) // If the previous char was a "force character (26)" prefix then don't treat 27 as an escape
			{
				escParam1=0;
				escParam2=0;
				serInChar=getInChar();

				if (serInChar=='-')
				{
					enableAnsiConversion=0;  // ESC- will turn off the ANSI interpreter
				}
				if (serInChar=='[')
				{
					serInChar=getInChar();
					// Process a number after the "[" character
					while (serInChar>='0' && serInChar<='9')
					{
						serInChar=serInChar-'0';
						if (escParam1<100)
						{
							escParam1=escParam1*10;
							escParam1=escParam1+serInChar;
						}
 						serInChar=getInChar();
					}
					// If a ";" then process the next number
					if (serInChar==';')
					{
						serInChar=getInChar();
						while (serInChar>='0' && serInChar<='9')
						{
							serInChar=serInChar-'0';
							if (escParam2<100)
							{
								escParam2=escParam2*10;
								escParam2=escParam2+serInChar;
							}
	 						serInChar=getInChar();
						}

					}
					// Esc[line;ColumnH or Esc[line;Columnf moves cursor to that coordinate
					if (serInChar=='H' || serInChar=='f')
					{
						if (escParam1>0)
						{
							escParam1--;
						}
						if (escParam2>0)
						{
							escParam2--;
						}
						sendToDisplay(0x0F);
						sendToDisplay(escParam1);
						sendToDisplay(0x0E);
						sendToDisplay(escParam2);
					}
					//Esc[J=clear from cursor down, Esc[1J=clear from cursor up, Esc[2J=clear complete screen
					else if (serInChar=='J')
					{
						if (escParam1==0)
						{
							sendToDisplay(0x13);
						}
						if (escParam1==1)
						{
							sendToDisplay(0x12);
						}
						if (escParam1==2)
						{
							sendToDisplay(0x0C);
						}

					}
					// Esc[K = erase to end of line, Esc[1K = erase to start of line
					else if (serInChar=='K')
					{
						if (escParam1==0)
						{
							sendToDisplay(0x11);
						}
						if (escParam1==1)
						{
							sendToDisplay(0x10);
						}

					}
					// Esc[L = scroll down
					else if (serInChar=='L')
					{
						sendToDisplay(0x15);
					}
					// Esc[M = scroll up
					else if (serInChar=='M')
					{
						sendToDisplay(0x14);
					}
				} // end of in char = '['
			} // end of in char = 27
			else
			{

	 			sendToDisplay(serInChar);
			}
			prevInChar=serInChar;
		}

		processATKeyboard();
		
		if (kbWriteActive==0 && kbWriteCount>0)
		{
			if (kbWriteCount==3)
			{
				kbWriteDataVal=kbBuffer3;
				kbWriteCount--;
				setKeyboardToReceiveMode();
			}				
			else if (kbWriteCount==2 && kbAckReceived==1)
			{
				kbAckReceived=0;
				kbWriteDataVal=kbBuffer2;
				kbWriteCount--;
				setKeyboardToReceiveMode();
			}
			else if (kbWriteCount==1 && kbAckReceived==1)
			{
				kbWriteDataVal=kbBuffer1;
				kbWriteCount--;
				setKeyboardToReceiveMode();
			}
		}
	}

	return 0;
}
