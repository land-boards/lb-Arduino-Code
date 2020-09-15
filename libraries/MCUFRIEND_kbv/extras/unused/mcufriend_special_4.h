#define SSD1289_JUMPERS 2       //Uno Shield with VERY different pin-out to Mcufriend
//#define USE_SSD1289_SHIELD_UNO 
//#define USE_SSD1289_SHIELD_MEGA 
#define USE_SSD1289_SHIELD_DUE  //Due only works with JUMPERS==2

#if 0

//################################# SSD1289 SHIELD #######################
// SSD1289 shield has LCD_D0 on RXD0. SD_CS=D8, T_IRQ=D9, T_CS=D10
// This is fine for write-only operations with NO Serial.  A4, A5 are available for I2C
// NOTE THAT Serial.end() IS REQUIRED FOR NO JUMPERS
// Read operations,  lose I2C (on Uno) but gain Serial, Bootloader etc
// jumper D0 to A4, D1 to A5, Switch #1 to OFF, #2 to OFF
#elif defined(__AVR_ATmega328P__) && defined(USE_SSD1289_SHIELD_UNO)    //on UNO
#warning using SSD1289 Shield for mega328
#define RD_PORT PORTC
#define RD_PIN  3
#define WR_PORT PORTC
#define WR_PIN  2
#define CD_PORT PORTC
#define CD_PIN  1
#define CS_PORT PORTC
#define CS_PIN  0
#define RESET_PORT PORTB
#define RESET_PIN  1      //D9 actually T_IRQ

#if SSD1289_JUMPERS == 0   //data bus on D0..D7
#warning no jumpers.  Switch #1=ON, #2=ON
#define BMASK         0x00       //0x00 for output, 0x01 for Read + Serial
#define CMASK         0x00       //0x20 for Read + Serial 
#define DMASK         0xFF
#define write8(x)     { PORTD = x; WR_STROBE; }
#define read_8()      ( 0xAB )   //this shield is WRITE-ONLY
#elif SSD1289_JUMPERS == 2
#warning jumper D0 to A4, D1 to A5.  Switch #1=OFF, #2=OFF
#define BMASK         0x00            //D8 is unused now
#define CMASK         ((1<<4)|(1<<5)) //A4, A5 
#define DMASK         (0xFC)
#define write8(x)     { PORTC = (PORTC & ~CMASK) | ((x<<4) & CMASK);\
                        PORTD = (PORTD & ~DMASK) | (x & DMASK); WR_STROBE; }
#define read_8()      ( ((PINC & CMASK)>>4)|(PIND & DMASK) )
#endif
#define setWriteDir() { DDRC |=  CMASK; DDRD |=  DMASK; DDRB |=  BMASK; }
#define setReadDir()  { DDRC &= ~CMASK; DDRD &= ~DMASK; DDRB &= ~BMASK; }
#define write16(x)    { uint8_t h = (x)>>8, l = x; write8(h); write8(l); }
#define READ_8(dst)   { RD_STROBE; dst = read_8(); RD_IDLE; }
#define READ_16(dst)  { uint8_t hi; READ_8(hi); READ_8(dst); dst |= (hi << 8); }

#define PIN_LOW(p, b)        (p) &= ~(1<<(b))
#define PIN_HIGH(p, b)       (p) |= (1<<(b))
#define PIN_OUTPUT(p, b)     *(&p-1) |= (1<<(b))

#elif defined(__AVR_ATmega2560__) && defined(USE_SSD1289_SHIELD_MEGA)
#warning using SSD1289 Shield for mega2560
#define RD_PORT PORTF
#define RD_PIN  3      //A3
#define WR_PORT PORTF
#define WR_PIN  2      //A2
#define CD_PORT PORTF
#define CD_PIN  1      //A1
#define CS_PORT PORTF
#define CS_PIN  0      //A0
#define RESET_PORT PORTH
#define RESET_PIN  6   //D9 (D10=T_CS, D9=T_IRQ, D8=SD_CS)

#if (SSD1289_JUMPERS == 0)   //data bus on D0..D7
#warning no jumpers Switch #1=ON, #2=ON
#define EMASK         ((1<<0)|(1<<1)|(1<<4)|(1<<5)|(1<<3))
#define FMASK         0x00
#define HMASK         ((1<<3)|(1<<4))
#define GMASK         (1<<5)
#define write_8(x)   {  PORTH &= ~HMASK; PORTG &= ~GMASK; PORTF &= ~FMASK; PORTE &= ~EMASK; \
	PORTE |= (((x) & (1<<0)) << 0); \
	PORTE |= (((x) & (1<<1)) << 0); \
	PORTE |= (((x) & (3<<2)) << 2); \
	PORTG |= (((x) & (1<<4)) << 1); \
	PORTE |= (((x) & (1<<5)) >> 2); \
	PORTH |= (((x) & (3<<6)) >> 3); \
}

#define read_8()      ( 0xBC )   //this shield is WRITE-ONLY

#elif (SSD1289_JUMPERS == 2)    //jumper D0 to A4, D1 to A5.  Switch #1=OFF, #2=OFF
#warning jumper D0 to A4, D1 to A5.  Switch #1=OFF, #2=OFF
#define EMASK         ((1<<4)|(1<<5)|(1<<3))
#define FMASK         ((1<<4)|(1<<5))
#define HMASK         ((1<<3)|(1<<4))
#define GMASK         (1<<5)
#define write_8(x)   {  PORTH &= ~HMASK; PORTG &= ~GMASK; PORTF &= ~FMASK; PORTE &= ~EMASK; \
	PORTF |= (((x) & (1<<0)) << 4); \
	PORTF |= (((x) & (1<<1)) << 4); \
	PORTE |= (((x) & (3<<2)) << 2); \
	PORTG |= (((x) & (1<<4)) << 1); \
	PORTE |= (((x) & (1<<5)) >> 2); \
	PORTH |= (((x) & (3<<6)) >> 3); \
}

#define read_8()      ( ((PINF & (1<<4)) >> 4)\
                      | ((PINF & (1<<5)) >> 4)\
                      | ((PINE & (3<<4)) >> 2)\
                      | ((PING & (1<<5)) >> 1)\
                      | ((PINE & (1<<3)) << 2)\
                      | ((PINH & (3<<3)) << 3)\
                      )
#endif
#define setWriteDir() { DDRH |=  HMASK; DDRG |=  GMASK; DDRF |=  FMASK; DDRE |=  EMASK;  }
#define setReadDir()  { DDRH &= ~HMASK; DDRG &= ~GMASK; DDRF &= ~FMASK; DDRE &= ~EMASK;  }
#define write8(x)     { write_8(x); WR_STROBE; }
#define write16(x)    { uint8_t h = (x)>>8, l = x; write8(h); write8(l); }
#define READ_8(dst)  { RD_STROBE; dst = read_8(); RD_IDLE; }
#define READ_16(dst)  { RD_STROBE; dst = read_8(); RD_IDLE; RD_STROBE; dst = (dst<<8) | read_8(); RD_IDLE; }

#define PIN_LOW(p, b)        (p) &= ~(1<<(b))
#define PIN_HIGH(p, b)       (p) |= (1<<(b))
#define PIN_OUTPUT(p, b)     *(&p-1) |= (1<<(b))

#elif defined(__SAM3X8E__) && defined(USE_SSD1289_SHIELD_DUE)   // on DUE
#warning USE_SSD1289_SHIELD_DUE
// configure macros for the control pins
#define RD_PORT PIOA
#define RD_PIN  22     //A3
#define WR_PORT PIOA
#define WR_PIN  23     //A2
#define CD_PORT PIOA
#define CD_PIN  24     //A1
#define CS_PORT PIOA
#define CS_PIN  16     //A0
#define RESET_PORT PIOC
#define RESET_PIN  21  //D9 Touch_IRQ
// configure macros for data bus
#if SSD1289_JUMPERS == 0   //data bus on D0..D7
#warning no jumpers Switch #1=ON, #2=ON
#define AMASK         ((1<<8)|(1<<9))   //D0, D1
#define BMASK         (1<<25)
#define CMASK         ((1<<28)|(1<<26)|(1<<25)|(1<<24)|(1<<23))
#define write_8(x)   { PIOA->PIO_CODR = AMASK; PIOB->PIO_CODR = BMASK; PIOC->PIO_CODR = CMASK; \
	                   PIOA->PIO_SODR = (((x) & (1<<0)) << 8); \
	                   PIOA->PIO_SODR = (((x) & (1<<1)) << 8); \
	                   PIOB->PIO_SODR = (((x) & (1<<2)) << 23); \
	                   PIOC->PIO_SODR = (((x) & (1<<3)) << 25); \
	                   PIOC->PIO_SODR = (((x) & (1<<4)) << 22); \
	                   PIOC->PIO_SODR = (((x) & (1<<5)) << 20); \
	                   PIOC->PIO_SODR = (((x) & (1<<6)) << 18); \
	                   PIOC->PIO_SODR = (((x) & (1<<7)) << 16); \
                     }

#define read_8()      ( 0xCD )   //this shield is WRITE-ONLY

#elif SSD1289_JUMPERS == 2    //jumper D0 to A4, D1 to A5.  Switch #1=OFF, #2=OFF
#warning jumper D0 to A4, D1 to A5.  Switch #1=OFF, #2=OFF
#define AMASK         ((1<<6)|(1<<4))   //A4, A5
#define BMASK         (1<<25)
#define CMASK         ((1<<28)|(1<<26)|(1<<25)|(1<<24)|(1<<23))
#define write_8(x)   { PIOA->PIO_CODR = AMASK; PIOB->PIO_CODR = BMASK; PIOC->PIO_CODR = CMASK; \
	                   PIOA->PIO_SODR = (((x) & (1<<0)) << 6); \
	                   PIOA->PIO_SODR = (((x) & (1<<1)) << 3); \
	                   PIOB->PIO_SODR = (((x) & (1<<2)) << 23); \
	                   PIOC->PIO_SODR = (((x) & (1<<3)) << 25); \
	                   PIOC->PIO_SODR = (((x) & (1<<4)) << 22); \
	                   PIOC->PIO_SODR = (((x) & (1<<5)) << 20); \
	                   PIOC->PIO_SODR = (((x) & (1<<6)) << 18); \
	                   PIOC->PIO_SODR = (((x) & (1<<7)) << 16); \
                     }

#define read_8()      ( ((PIOA->PIO_PDSR & (1<<6)) >> 6)\
                      | ((PIOA->PIO_PDSR & (1<<4)) >> 3)\
                      | ((PIOB->PIO_PDSR & (1<<25)) >> 23)\
                      | ((PIOC->PIO_PDSR & (1<<28)) >> 25)\
                      | ((PIOC->PIO_PDSR & (1<<26)) >> 22)\
                      | ((PIOC->PIO_PDSR & (1<<25)) >> 20)\
                      | ((PIOC->PIO_PDSR & (1<<24)) >> 18)\
                      | ((PIOC->PIO_PDSR & (1<<23)) >> 16)\
                      )
#endif
#define setWriteDir() { PIOA->PIO_OER = AMASK; PIOB->PIO_OER = BMASK; PIOC->PIO_OER = CMASK; }
#define setReadDir()  { \
	PMC->PMC_PCER0 = (1 << ID_PIOA)|(1 << ID_PIOB)|(1 << ID_PIOC);\
	PIOA->PIO_ODR = AMASK; PIOB->PIO_ODR = BMASK; PIOC->PIO_ODR = CMASK;\
}
#define write8(x)     { write_8(x); WR_ACTIVE; WR_STROBE; WR_IDLE; }
#define write16(x)    { uint8_t h = (x)>>8, l = x; write8(h); write8(l); }
#define READ_8(dst)   { RD_STROBE; RD_ACTIVE4; dst = read_8(); RD_IDLE; RD_IDLE; RD_IDLE; }
#define READ_16(dst)  { uint8_t hi; READ_8(hi); READ_8(dst); dst |= (hi << 8); }
// Shield Control macros.
#define PIN_LOW(port, pin)    (port)->PIO_CODR = (1<<(pin))
#define PIN_HIGH(port, pin)   (port)->PIO_SODR = (1<<(pin))
#define PIN_OUTPUT(port, pin) (port)->PIO_OER = (1<<(pin))

