// only define one "USE_XXX" macro at any time

//#define USE_MEGA_8BIT_PROTOSHIELD
//#define USE_MEGA_8BIT_SHIELD      // 4.7sec Mega2560 Shield
//#define USE_MEGA_8BIT_PORTC_SHIELD // 4.7sec Mega2560 Shield
//#define USE_MEGA_16BIT_SHIELD     // 2.14sec Mega2560 Shield 
//#define USE_BLD_BST_MEGA32U4
//#define USE_BLD_BST_MEGA2560      // 12.23sec Uno Shield (17.38s C)
//#define USE_BLD_BST_MEGA4809      // 5.43sec XPRO-Adapter (7.09s C)
//#define USE_DUE_8BIT_PROTOSHIELD
//#define USE_DUE_16BIT_SHIELD        //RD on PA15 (D24) 
//#define USE_BOBCACHELOT_TEENSY
//#define USE_OPENSMART_SHIELD_PINOUT_UNO
//#define USE_OPENSMART_SHIELD_PINOUT_MEGA
//#define USE_OPENSMART_SHIELD_PINOUT_DUE //thanks Michel53
//#define USE_ELECHOUSE_DUE_16BIT_SHIELD    //Untested yet
//#define USE_MY_BLUEPILL
//#define USE_ADIGITALEU_TEENSY
//#define USE_MIKROELEKTRONIKA
//#define USE_XPRO_MEGA4809
//#define USE_MY_PICO
//#define USE_CURIOSITY_AVR128DA48
//#define USE_CURIOSITY_AVR128DB48


/*
HX8347A  tWC =100ns  tWRH = 35ns  tRCFM = 450ns  tRC = ?  ns
HX8347D  tWC = 66ns  tWRH = 15ns  tRCFM = 450ns  tRC = 160ns
HX8347I  tWC =100ns  tWRH = 15ns  tRCFM = 600ns  tRC = 160ns
HX8357C  tWC = 50ns  tWRH = 15ns  tRCFM = 450ns  tRC = 160ns
ILI9320  tWC =100ns  tWRH = 50ns  tRCFM = 300ns  tRC = 300ns
ILI9341  tWC = 66ns  tWRH = 15ns  tRCFM = 450ns  tRC = 160ns
ILI9481  tWC =100ns  tWRH = 30ns  tRCFM = 450ns  tRC = 450ns
ILI9486  tWC = 66ns  tWRH = 15ns  tRCFM = 450ns  tRC = 160ns (tWCFM= 286ns on mystery 9486_16)
ILI9486L tWC = 50ns  tWRH = 15ns  tRCFM = 450ns  tRC = 160ns
ILI9488  tWC = 30ns  tWRH = 15ns  tRCFM = 450ns  tRC = 160ns
NT35310  tWC = 40ns  tWRH = 19ns  tRCFM = 400ns  tRC = 160ns
RM68140  tWC = 50ns  tWRH = 15ns  tRCFM = 450ns  tRC = 160ns (tWCFM= 119ns)
SPFD5408 tWC =125ns  tWRH = 70ns  tRCFM = 450ns  tRC = 450ns
SSD1289  tWC =100ns  tWRH = 50ns  tRCFM =1000ns  tRC =1000ns (tWCFM= 238ns)
SSD1963  tWC = 26ns  tWRH = 13ns  tRCFM = 110ns  tRC =  72ns
ST7789V  tWC = 66ns  tWRH = 15ns  tRCFM = 450ns  tRC = 160ns
ST7793   tWC = 75ns  tWRH = 25ns  tRCFM = 450ns  tRC = 450ns
ST7796S  tWC = 66ns  tWRH = 15ns  tRCFM = 450ns  tRC = 160ns
*/

#if 0

//################################### Curiosity AVR128DA48 ##############################
#elif defined(__AVR_AVR128DA48__) && defined(USE_CURIOSITY_AVR128DA48)     // 
#warning Curiosity AVR128DA48
//LCD pins  |D7 |D6 |D5 |D4 |D3 |D2 |D1 |D0 | |RD |WR |RS |CS |RST| |SDA0|SCL0| |SDA1|SCL1|
//DA48  pin |PA3|PA2|PB5|PB4|PB3|PB2|PB1|PB0| |PD0|PD1|PD2|PD3|PD4| |PC2 |PC3 | |PF2 |PF3 |
//DB48  pin |PC7|PC6|PC5|PC4|PC3|PC2|PC1|PC0| |PD0|PD1|PD2|PD4|PD5| |PA2 |PA3 | |PF2 |PF3 |
//Curiosity |37 |36 |35 |34 |23 |22 |21 |20 | |46 |47 |48 |43 |44 | |9   |10  | |18  |19  |
//UNO pins  |7  |6  |5  |4  |3  |2  |9  |8  | |A0 |A1 |A2 |A3 |A4 | |18  |19  |
//LCD pins  |CS  |MOSI|MISO|SCK | |SDA|SCL|
//128DA pin |PA7 |PA4 |PA5 |PA6 | |PF2|GP7|
//UNO pins  |10  |11  |12  |13  | |18 |19 |

#define WRITE_DELAY {  }
#define READ_DELAY  { RD_ACTIVE2; }

#define RD_PORT VPORTD
#define RD_PIN  0
#define WR_PORT VPORTD
#define WR_PIN  1
#define CD_PORT VPORTD
#define CD_PIN  2
#define CS_PORT VPORTD
#define CS_PIN  3
#define RESET_PORT VPORTD
#define RESET_PIN  4

#define BMASK 0x3F
#define AMASK 0x0C
//#define write_8(x)    { VPORTB.OUT = ((x) & BMASK) | (VPORTB.OUT & 0xC0); VPORTA.OUT = (((x) & 0xC0) >> 4) | (VPORTA.OUT & ~AMASK);}
//#define write_8(x)    { PORTB.OUTCLR = BMASK; PORTB.OUTSET =((x) & BMASK); PORTA.OUTCLR = AMASK; PORTA.OUTSET = ((x) >> 4) & AMASK;}
#define write_8(x)    { PORTB.OUTCLR = BMASK; PORTA.OUTCLR = AMASK; PORTB.OUTSET =((x) & BMASK); PORTA.OUTSET = ((x) >> 4) & AMASK;}
#define read_8()      ( (VPORTB_IN & BMASK) | ((VPORTA_IN & AMASK) << 4) )
#define setWriteDir() { VPORTB.DIR |=  BMASK; VPORTA.DIR |=  AMASK; }
#define setReadDir()  { VPORTB.DIR &= ~BMASK; VPORTA.DIR &= ~AMASK; }
#define write8(x)     { write_8(x); WRITE_DELAY; WR_STROBE; }
#define write16(x)    { uint8_t h = (x)>>8, l = x; write8(h); write8(l); }
#define READ_8(dst)   { RD_STROBE; READ_DELAY; dst = read_8(); RD_IDLE; }
#define READ_16(dst)  { uint8_t hi; READ_8(hi); READ_8(dst); dst |= (hi << 8); }

#define PIN_LOW(p, b)        (p).OUT &= ~(1<<(b))
#define PIN_HIGH(p, b)       (p).OUT |= (1<<(b))
#define PIN_OUTPUT(p, b)     (p).DIR |= (1<<(b))

//################################### Curiosity AVR128DB48 ##############################
#elif defined(__AVR_AVR128DB48__) && defined(USE_CURIOSITY_AVR128DB48)       //
#warning Curiosity AVR128DB48
//LCD pins  |D7 |D6 |D5 |D4 |D3 |D2 |D1 |D0 | |RD |WR |RS |CS |RST|
//DA48  pin |PA3|PA2|PB5|PB4|PB3|PB2|PB1|PB0| |PD0|PD1|PD2|PD3|PD4|
//DB48  pin |PC7|PC6|PC5|PC4|PC3|PC2|PC1|PC0| |PD0|PD1|PD2|PD4|PD5|
//Curiosity |37 |36 |35 |34 |23 |22 |21 |20 | |46 |47 |48 |43 |44 |
//UNO pins  |7  |6  |5  |4  |3  |2  |9  |8  | |A0 |A1 |A2 |A3 |A4 |

#define WRITE_DELAY {  }
#define READ_DELAY  { RD_ACTIVE2; }

#define RD_PORT VPORTD
#define RD_PIN  0
#define WR_PORT VPORTD
#define WR_PIN  1
#define CD_PORT VPORTD
#define CD_PIN  2
#define CS_PORT VPORTD
#define CS_PIN  4
#define RESET_PORT VPORTD
#define RESET_PIN  5

#define CMASK 0xFF
#define write_8(x)    { PORTC.OUT = x; }
#define read_8()      ( (PORTC.IN) )
#define setWriteDir() { VPORTC.DIR |=  CMASK; }
#define setReadDir()  { VPORTC.DIR &= ~CMASK; }
#define write8(x)     { write_8(x); WRITE_DELAY; WR_STROBE; }
#define write16(x)    { uint8_t h = (x)>>8, l = x; write8(h); write8(l); }
#define READ_8(dst)   { RD_STROBE; READ_DELAY; dst = read_8(); RD_IDLE; }
#define READ_16(dst)  { uint8_t hi; READ_8(hi); READ_8(dst); dst |= (hi << 8); }

#define PIN_LOW(p, b)        (p).OUT &= ~(1<<(b))
#define PIN_HIGH(p, b)       (p).OUT |= (1<<(b))
#define PIN_OUTPUT(p, b)     (p).DIR |= (1<<(b))

//################################### RP2040 ##############################
#elif defined(USE_MY_PICO) && defined(ARDUINO_ARCH_RP2040)       //regular UNO shield on PICO
//LCD pins  |D7  |D6  |D5  |D4  |D3  |D2 |D1  |D0  | |RD  |WR  |RS  |CS  |RST |    |
//RP2040 pin|GP13|GP12|GP11|GP10|GP9 |GP8|GP19|GP18| |GP14|GP26|GP27|GP28|GP16|GP17|
//BODMER pin|GP13|GP12|GP11|GP10|GP9 |GP8|GP7 |GP6 | |GP14|GP22|GP27|GP28|GP16|GP17|
//UNO pins  |7   |6   |5   |4   |3   |2  |9   |8   | |A0  |A1  |A2  |A3  |A4  |A5  |
//LCD pins  |CS  |MOSI|MISO|SCK | |SDA|SCL|
//RP2040 pin|GP21|GP3 |GP4 |GP2 | |GP6|GP7|
//UNO pins  |10  |11  |12  |13  | |18 |19 |

//#define USE_BODMER

#define WRITE_DELAY { WR_ACTIVE4; }
#define IDLE_DELAY  { WR_IDLE; }
#define READ_DELAY  { RD_ACTIVE8; }

#define RD_PORT sio_hw
#define RD_PIN  14
#define WR_PORT sio_hw
#define WR_PIN  26
#define CD_PORT sio_hw
#define CD_PIN  27
#define CS_PORT sio_hw
#define CS_PIN  28
#define RESET_PORT sio_hw
#define RESET_PIN  16

#define LMASK         (0x03 << 18)
#define HMASK         (0xFC << 6)
#if defined(USE_BODMER)
//#define WR_PIN        22
#define LMASK         (0x00 << 18)
#define HMASK         (0xFF << 6)
#endif
#define GPMASK        (LMASK | HMASK)       //more intuitive style for mixed Ports
#define write_8(x)    { sio_hw->gpio_clr = GPMASK; \
                        sio_hw->gpio_set = (((x) << 18) & LMASK) | (((x) << 6) & HMASK); \
                      }
#define read_8()      ( ((sio_hw->gpio_in & HMASK) >> 6) | ((sio_hw->gpio_in & LMASK) >> 18) )
#define setWriteDir() { sio_hw->gpio_oe_set = GPMASK; }
#define setReadDir()  { sio_hw->gpio_oe_clr = GPMASK; }
#define GPIO_INIT() {for (int i = 6; i <= 14; i++) pinMode(i, OUTPUT); for (int i = 16; i <= 28; i++) pinMode(i, OUTPUT);}
#define write8(x)     { write_8(x); WRITE_DELAY; WR_STROBE; IDLE_DELAY; }
#define write16(x)    { uint8_t h = (x)>>8, l = x; write8(h); write8(l); }
#define READ_8(dst)   { RD_STROBE; READ_DELAY; dst = read_8(); RD_IDLE2; RD_IDLE; }
#define READ_16(dst)  { uint8_t hi; READ_8(hi); READ_8(dst); dst |= (hi << 8); }

#define PIN_LOW(port, pin)    (port)->gpio_clr = (1<<(pin))
#define PIN_HIGH(port, pin)   (port)->gpio_set = (1<<(pin))
#define PIN_OUTPUT(port, pin) (port)->gpio_oe_set = (1<<(pin))

//################################### XMEGA BOARDS ##############################
#elif defined(__AVR_ATxmega128A1__)||defined(__AVR_ATxmega128A4U__)||defined(__AVR_ATxmega32A4U__)||defined(__AVR_ATxmega32E5__)

#if defined(__AVR_ATxmega128A1__) && defined(USE_CVSTK600)
#warning Home made shield with Xplained A1: CTL=J3 (PD), DATA=J2 (PA)
#define VPMAP10 0x10    // VPORT0=A, 1=B, 2=C, 3=D
#define VPMAP32 0x32    // VPORT0=A, 1=B, 2=C, 3=D
#define DATPORT VPORT0  //PORTA
#define CTLPORT VPORT3  //PORTD
#define RD_PORT CTLPORT //PD2. use individual jumper cables
#define RD_PIN  2
#define WR_PORT CTLPORT
#define WR_PIN  3
#define CD_PORT CTLPORT
#define CD_PIN  1
#define CS_PORT CTLPORT
#define CS_PIN  0
#define RESET_PORT CTLPORT
#define RESET_PIN  4

#elif defined(__AVR_ATxmega128A1__) && defined(USE_MIKROELEKTRONIKA)     // HX8347-D 16.2ns@62MHz 20.9ns@48MHz
#if F_CPU > 46000000
#error MIKROELEKTRONIKA must be less than 48MHz
#else
#warning MIKROELEKTRONIKA DEV BOARD (48MHz max)
#endif
#define VPMAP10 0x58    // VPORT0=J, 1=F, 2=K, 3=D
#define VPMAP32 0x39    // VPORT0=J, 1=F, 2=K, 3=D
#define DATPORT VPORT2  //PORTK
#define CTLPORT VPORT0  //PORTJ
#define RD_PORT CTLPORT //PJ2.
#define RD_PIN  2
#define WR_PORT CTLPORT
#define WR_PIN  3
#define CD_PORT CTLPORT
#define CD_PIN  4
#define CS_PORT CTLPORT
#define CS_PIN  5
#define RESET_PORT CTLPORT //PJ1
#define RESET_PIN  1

#elif defined(__AVR_ATxmega128A1__)
#define VPMAP10 0x50    // VPORT0=A, 1=F, 2=C, 3=D
#define VPMAP32 0x32    // VPORT0=A, 1=F, 2=C, 3=D
#define DATPORT VPORT0  //PORTA
#define CTLPORT VPORT1  //PORTF i.e. CTL=J1 (PF), DATA=J2 (PA)
#warning Home made shield with Xplained A1 CTL=J1 (PF), DATA=J2 (PA)
//#define CTLPORT VPORT2  //PORTC i.e. CTL=J4 (PC), DATA=J2 (PA) upsets Serial on PC2,PC3
//#warning Home made shield with Xplained A1 CTL=J4 (PC), DATA=J2 (PA) upsets Serial on PC2,PC3
//#define CTLPORT VPORT3  //PORTD i.e. CTL=J3 (PD), DATA=J2 (PA) note J3 VCC pin=5V0
//#warning Home made shield with Xplained A1 CTL=J3 (PD), DATA=J2 (PA) note J3 VCC pin=5V0
#define RD_PORT CTLPORT //PC0.
#define RD_PIN  0
#define WR_PORT CTLPORT
#define WR_PIN  1
#define CD_PORT CTLPORT
#define CD_PIN  2
#define CS_PORT CTLPORT
#define CS_PIN  3
#define RESET_PORT CTLPORT //PC4
#define RESET_PIN  4

#elif defined(__AVR_ATxmega32A4U__) || defined(__AVR_ATxmega128A4U__) // Home made shield with Batsocks module
#warning Home made shield with Batsocks module
#define VPMAP10 0x10    // VPORT0=A, 1=B, 2=C, 3=D
#define VPMAP32 0x32    // VPORT0=A, 1=B, 2=C, 3=D
#define DATPORT VPORT2  //PORTC
#define CTLPORT VPORT1  //PORTB
#define RD_PORT CTLPORT //PB0. 
#define RD_PIN  0
#define WR_PORT CTLPORT
#define WR_PIN  1
#define CD_PORT CTLPORT
#define CD_PIN  2
#define CS_PORT CTLPORT
#define CS_PIN  3
#define RESET_PORT PORTE
#define RESET_PIN  0

#elif defined(__AVR_ATxmega32E5__)   // Xplained E5 F_CPU <= 46MHz
#warning Home made shield with Xplained E5: CTL=J4 (PD), DATA=J2 (PA)
//no VPMAPxx on 32E5. Fixed VPORT0=A, 1=C, 2=D, 3=R
#define CTLPORT VPORT2  //PORTD on J4
#define DATPORT VPORT0  //PORTA on J2, SW103=hdr
#define RD_PORT CTLPORT //PD0.
#define RD_PIN  0
#define WR_PORT CTLPORT
#define WR_PIN  1
#define CD_PORT CTLPORT
#define CD_PIN  2
#define CS_PORT CTLPORT
#define CS_PIN  3
#define RESET_PORT CTLPORT //10k p.u. to 3V3
#define RESET_PIN  4

#endif                  //VPORT and pin mapping

#if defined(VPMAP10)
#define MAP_VPORTS() { PORTCFG.VPCTRLA=VPMAP10; PORTCFG.VPCTRLB=VPMAP32; }
#else
#define MAP_VPORTS() 
#endif

// VPORTs are very fast.   CBI, SBI are only one cycle.    Hence all those RD_ACTIVEs
// ILI9320 data sheet says tDDR=100ns.    We need 218ns to read REGs correctly.
// S6D0154 data sheet says tDDR=250ns.    We need ~500ns to read REGs correctly.
// ST7789 data sheet says tRC=450ns.    We need ~167ns to read REGs correctly. (10 cycles @ 60MHz )
// ST7789 says tRC=160ns for ID and tRC=450ns for Frame Memory
// ILI9341 says tRC=160ns for ID and tRC=450ns for Frame Memory.  They are FASTER
#define WRITE_DELAY   { }
#define READ_DELAY    { RD_ACTIVE4; }
#define write_8(x)    { DATPORT.OUT = x; }
#define read_8()      ( DATPORT.IN )
#define setWriteDir() { MAP_VPORTS(); DATPORT.DIR = 0xFF; }
#define setReadDir()  { DATPORT.DIR = 0x00; }
#define write8(x)     { write_8(x); WRITE_DELAY; WR_STROBE; }
#define write16(x)    { uint8_t h = (x)>>8, l = x; write8(h); write8(l); }
#define READ_8(dst)   { RD_STROBE; READ_DELAY; dst = read_8(); RD_IDLE; }
#define READ_16(dst)  { uint8_t hi; READ_8(hi); READ_8(dst); dst |= (hi << 8); }

#define PIN_LOW(p, b)        (p).OUT &= ~(1<<(b))
#define PIN_HIGH(p, b)       (p).OUT |= (1<<(b))
#define PIN_OUTPUT(p, b)     (p).DIR |= (1<<(b))

//################################# XPRO-4809 with XPRO-Shield_Adapter ############################
#elif defined(__AVR_ATmega4809__) && !defined(USE_BLD_BST_MEGA4809) && defined(USE_XPRO_MEGA4809) // XPRO-4809 with XPRO-Shield_Adapter
//LCD pins  |D7 |D6 |D5 |D4 |D3 |D2 |D1 |D0 | |RD |WR |RS |CS |RST| |CS |DI |
//4809  pin |PE1|PB3|PF6|PC7|PC6|PB2|PA3|PA2| |PD2|PD3|PD4|PD5|PC2| |PA7]PA4|
//XPRO      |215|210|206|110|109|209|106|105| |103|104|203|204|111| |115|116|
//UNO pins  |7  |6  |5  |4  |3  |2  |9  |8  | |A0 |A1 |A2 |A3 |A4 | |10 |11 |
//XPRO Shield Adapter SW100=down for D11=EXT1.16.  SW101=up for D3=EXT1.9 
#warning XPRO-4809 with XPRO-Shield_Adapter using PORT.OUTSET
#define RD_PORT PORTD  //
#define RD_PIN  2
#define WR_PORT PORTD
#define WR_PIN  3
#define CD_PORT PORTD
#define CD_PIN  4
#define CS_PORT PORTD
#define CS_PIN  5
#define RESET_PORT PORTC
#define RESET_PIN  2

// PORT.OUTSET is fast but still 2 cycles.    Hence all those RD_ACTIVEs
#define AMASK         (3<<2)
#define BMASK         (3<<2)
#define CMASK         (3<<6)
#define EMASK         (1<<1)
#define FMASK         (1<<6)
#define write_8(x)   {   \
                        PORTA.OUTCLR = AMASK; PORTA.OUTSET = (((x) & (3<<0)) << 2); \
                        PORTB.OUTCLR = BMASK; PORTB.OUTSET = (((x) & (1<<2))) | (((x) & (1<<6)) >> 3); \
                        PORTC.OUTCLR = CMASK; PORTC.OUTSET = (((x) & (3<<3)) << 3); \
                        PORTE.OUTCLR = EMASK; PORTE.OUTSET = (((x) & (1<<7)) >> 6); \
                        PORTF.OUTCLR = FMASK; PORTF.OUTSET = (((x) & (1<<5)) << 1); \
					 }
#define read_8()      ( ((PORTA.IN & AMASK) >> 2)\
| ((PORTB.IN & (1<<2)) >> 0)\
| ((PORTB.IN & (1<<3)) << 3)\
| ((PORTC.IN & CMASK) >> 3)\
| ((PORTE.IN & EMASK) << 6)\
| ((PORTF.IN & FMASK) >> 1)\
)
#define setWriteDir() { PORTA.DIRSET = AMASK; PORTB.DIRSET = BMASK; PORTC.DIRSET = CMASK; PORTE.DIRSET = EMASK; PORTF.DIRSET = FMASK; }
#define setReadDir()  { PORTA.DIRCLR = AMASK; PORTB.DIRCLR = BMASK; PORTC.DIRCLR = CMASK; PORTE.DIRCLR = EMASK; PORTF.DIRCLR = FMASK; }

#define WRITE_DELAY   { WR_ACTIVE2; WR_ACTIVE; }   //-Os=7.09s @20MHz (-O1=8.13s, -O3=6.03s)
#define READ_DELAY    { RD_ACTIVE2; }              //ID=0x7789
#define write8(x)     { write_8(x); WRITE_DELAY; WR_STROBE; }
#define write16(x)    { uint8_t h = (x)>>8, l = x; write8(h); write8(l); }
#define READ_8(dst)   { RD_STROBE; READ_DELAY; dst = read_8(); RD_IDLE; }
#define READ_16(dst)  { uint8_t hi; READ_8(hi); READ_8(dst); dst |= (hi << 8); }

#define PIN_LOW(p, b)        (p).OUTCLR = (1<<(b))
#define PIN_HIGH(p, b)       (p).OUTSET = (1<<(b))
#define PIN_OUTPUT(p, b)     (p).DIRSET = (1<<(b))

#elif defined(__AVR_ATmega4809__) && defined(USE_BLD_BST_MEGA4809) && defined(USE_XPRO_MEGA4809)  // XPRO-4809 with XPRO-Shield_Adapter
#warning XPRO-4809 with XPRO-Shield_Adapter using VPORT.OUT and BLD/BST
#define RD_PORT VPORTD  //
#define RD_PIN  2
#define WR_PORT VPORTD
#define WR_PIN  3
#define CD_PORT VPORTD
#define CD_PIN  4
#define CS_PORT VPORTD
#define CS_PIN  5
#define RESET_PORT VPORTC
#define RESET_PIN  2

#define AMASK         (3<<2)
#define BMASK         (3<<2)
#define CMASK         (3<<6)
#define EMASK         (1<<1)
#define FMASK         (1<<6)
static __attribute((always_inline))
 void write_8(uint8_t val)
{
	asm volatile("in __tmp_reg__,0x01" "\n\t"    //VPORTA.OUT
	"BST %0,0" "\n\t" "BLD __tmp_reg__,2" "\n\t"
	"BST %0,1" "\n\t" "BLD __tmp_reg__,3" "\n\t"
	"out 0x01,__tmp_reg__" : : "a" (val));
	asm volatile("in __tmp_reg__,0x05" "\n\t"    //VPORTB.OUT
	"BST %0,2" "\n\t" "BLD __tmp_reg__,2" "\n\t"
	"BST %0,6" "\n\t" "BLD __tmp_reg__,3" "\n\t"
	"out 0x05,__tmp_reg__" : : "a" (val));
	asm volatile("in __tmp_reg__,0x09" "\n\t"    //VPORTC.OUT
	"BST %0,3" "\n\t" "BLD __tmp_reg__,6" "\n\t"
	"BST %0,4" "\n\t" "BLD __tmp_reg__,7" "\n\t"
	"out 0x09,__tmp_reg__" : : "a" (val));
	asm volatile("in __tmp_reg__,0x11" "\n\t"    //VPORTE.OUT
	"BST %0,7" "\n\t" "BLD __tmp_reg__,1" "\n\t"
	"out 0x11,__tmp_reg__" : : "a" (val));
	asm volatile("in __tmp_reg__,0x15" "\n\t"    //VPORTF.OUT
	"BST %0,5" "\n\t" "BLD __tmp_reg__,6" "\n\t"
	"out 0x15,__tmp_reg__" : : "a" (val));
}

#define read_8()      ( ((VPORTA_IN & AMASK) >> 2)\
| ((VPORTB_IN & (1<<2)) >> 0)\
| ((VPORTB_IN & (1<<3)) << 3)\
| ((VPORTC_IN & CMASK) >> 3)\
| ((VPORTE_IN & EMASK) << 6)\
| ((VPORTF_IN & FMASK) >> 1)\
)
#define setWriteDir() { VPORTA_DIR |=  AMASK; VPORTB_DIR |=  BMASK; VPORTC_DIR |=  CMASK; VPORTE_DIR |=  EMASK; VPORTF_DIR |=  FMASK; }
#define setReadDir()  { VPORTA_DIR &= ~AMASK; VPORTB_DIR &= ~BMASK; VPORTC_DIR &= ~CMASK; VPORTE_DIR &= ~EMASK; VPORTF_DIR &= ~FMASK; }

//#define WRITE_DELAY   { WR_ACTIVE; WR_ACTIVE; }   //6.47s no_inline
#define WRITE_DELAY   { WR_ACTIVE2; WR_ACTIVE; }   //-Os=5.43s @20MHz always_inline. (-O1=5.41s, -O3=5.25s) 
#define READ_DELAY    { RD_ACTIVE4; }              //ID=0x7789
#define write8(x)     { write_8(x); WRITE_DELAY; WR_STROBE; }
#define write16(x)    { uint8_t h = (x)>>8, l = x; write8(h); write8(l); }
#define READ_8(dst)   { RD_STROBE; READ_DELAY; dst = read_8(); RD_IDLE; }
#define READ_16(dst)  { uint8_t hi; READ_8(hi); READ_8(dst); dst |= (hi << 8); }

#define PIN_LOW(p, b)        (p).OUT &= ~(1<<(b))
#define PIN_HIGH(p, b)       (p).OUT |= (1<<(b))
#define PIN_OUTPUT(p, b)     (p).DIR |= (1<<(b))

#elif defined(__AVR_ATmega328P__) && defined(USE_OPENSMART_SHIELD_PINOUT_UNO)
//LCD pins  |D7 |D6 |D5 |D4 |D3 |D2 |D1 |D0 | |RD |WR |RS |CS |RST|
//AVR   pin |PD7|PD6|PB5|PD4|PB3|PB2|PB1|PB0| |PC0|PC1|PC2|PC3|PD2|
//UNO pins  |7  |6  |13 |4  |11 |10 |9  |8  | |A0 |A1 |A2 |A3 |2  |
#define RD_PORT PORTC
#define RD_PIN  0
#define WR_PORT PORTC
#define WR_PIN  1
#define CD_PORT PORTC
#define CD_PIN  2
#define CS_PORT PORTC
#define CS_PIN  3
#define RESET_PORT PORTD //n.c. on Open-Smart shields
#define RESET_PIN  2  // aliexpress.com/store/1199788

#define BMASK         0b00101111
#define DMASK         0b11010000

#define write_8(x) {                          \
        PORTD = (PORTD & ~DMASK) | ((x) & DMASK); \
        PORTB = (PORTB & ~BMASK) | ((x) & BMASK);} // STROBEs are defined later

#define read_8()   ((PIND & DMASK) | (PINB & BMASK))

#define setWriteDir() { DDRD |=  DMASK; DDRB |=  BMASK; }
#define setReadDir()  { DDRD &= ~DMASK; DDRB &= ~BMASK; }


#define write8(x)     { write_8(x); WR_STROBE; }
#define write16(x)    { uint8_t h = (x)>>8, l = x; write8(h); write8(l); }
#define READ_8(dst)   { RD_STROBE; dst = read_8(); RD_IDLE; }
#define READ_16(dst)  { uint8_t hi; READ_8(hi); READ_8(dst); dst |= (hi << 8); }

#define PIN_LOW(p, b)        (p) &= ~(1<<(b))
#define PIN_HIGH(p, b)       (p) |= (1<<(b))
#define PIN_OUTPUT(p, b)     *(&p-1) |= (1<<(b))

#elif defined(__AVR_ATmega2560__) && defined(USE_OPENSMART_SHIELD_PINOUT_MEGA)
#define RD_PORT PORTF
#define RD_PIN  0
#define WR_PORT PORTF
#define WR_PIN  1
#define CD_PORT PORTF
#define CD_PIN  2
#define CS_PORT PORTF
#define CS_PIN  3
#define RESET_PORT PORTF
#define RESET_PIN  1  // n/a. so mimic WR_PIN

#define BMASK         0b10110000 //D13, D11, D10
#define GMASK         0x20      //D4
#define HMASK         0x78      //D6, D7, D8, D9

#if defined(USE_BLD_BST_MEGA2560)
static __attribute((always_inline)) void write_8(uint8_t val)
{
	asm volatile("lds __tmp_reg__,0x0102" "\n\t"  //PORTH
	"BST %0,0" "\n\t" "BLD __tmp_reg__,5" "\n\t"
	"BST %0,1" "\n\t" "BLD __tmp_reg__,6" "\n\t"
	"BST %0,6" "\n\t" "BLD __tmp_reg__,3" "\n\t"
	"BST %0,7" "\n\t" "BLD __tmp_reg__,4" "\n\t"
	"sts 0x0102,__tmp_reg__" : : "a" (val));
	asm volatile("in __tmp_reg__,0x05" "\n\t"     //PORTB
	"BST %0,2" "\n\t" "BLD __tmp_reg__,4" "\n\t"
	"BST %0,3" "\n\t" "BLD __tmp_reg__,5" "\n\t"
	"BST %0,5" "\n\t" "BLD __tmp_reg__,7" "\n\t"
	"out 0x05,__tmp_reg__" : : "a" (val));
	asm volatile("in __tmp_reg__,0x14" "\n\t"     //PORTG
	"BST %0,4" "\n\t" "BLD __tmp_reg__,5" "\n\t"
	"out 0x14,__tmp_reg__" : : "a" (val));
}
#else
#define write_8(x) {  \
        PORTH = (PORTH&~HMASK)|(((x)& 0b11000000)>>3)|(((x)& 0b00000011)<<5); \
        PORTB = (PORTB&~BMASK)|(((x)& 0b00101100)<<2); \
        PORTG = (PORTG&~GMASK)|(((x)& 0b00010000)<<1); \
    }
#endif

#define read_8()(\
                 ((PINH & 0b00011000) << 3) | ((PINB & BMASK) >> 2) | \
                 ((PING & GMASK) >> 1) | ((PINH & 0b01100000) >> 5) )
#define setWriteDir() { DDRH |=  HMASK; DDRB |=  BMASK; DDRG |=  GMASK; }
#define setReadDir()  { DDRH &= ~HMASK; DDRB &= ~BMASK; DDRG &= ~GMASK; }

#define write8(x)     { write_8(x); WR_STROBE; }
#define write16(x)    { uint8_t h = (x)>>8, l = x; write8(h); write8(l); }
#define READ_8(dst)   { RD_STROBE; dst = read_8(); RD_IDLE; }
#define READ_16(dst)  { uint8_t hi; READ_8(hi); READ_8(dst); dst |= (hi << 8); }

#define PIN_LOW(p, b)        (p) &= ~(1<<(b))
#define PIN_HIGH(p, b)       (p) |= (1<<(b))
#define PIN_OUTPUT(p, b)     *(&p-1) |= (1<<(b))

#elif defined(__SAM3X8E__) && defined(USE_OPENSMART_SHIELD_PINOUT_DUE)  //OPENSMART shield on DUE
#warning USE_OPENSMART_SHIELD_PINOUT on DUE
 // configure macros for the control pins
#define RD_PORT PIOA
#define RD_PIN  16
#define WR_PORT PIOA
#define WR_PIN  24
#define CD_PORT PIOA
#define CD_PIN  23
#define CS_PORT PIOA
#define CS_PIN  22
#define RESET_PORT PIOA
#define RESET_PIN  24  // n/a. so mimic WR_PIN
 // configure macros for data bus
#define BMASK         (1<<27)
#define CMASK         (0x12F << 21)
#define DMASK         (1<<7)
#define write_8(x)   {  PIOB->PIO_CODR = BMASK; PIOC->PIO_CODR = CMASK; PIOD->PIO_CODR = DMASK; \
                        PIOC->PIO_SODR = (((x) & (1<<0)) << 22); \
                        PIOC->PIO_SODR = (((x) & (1<<1)) << 20); \
                        PIOC->PIO_SODR = (((x) & (1<<2)) << 27); \
                        PIOD->PIO_SODR = (((x) & (1<<3)) << 4); \
                        PIOC->PIO_SODR = (((x) & (1<<4)) << 22); \
                        PIOB->PIO_SODR = (((x) & (1<<5)) << 22); \
                        PIOC->PIO_SODR = (((x) & (1<<6)) << 18); \
                        PIOC->PIO_SODR = (((x) & (1<<7)) << 16); \
					 }

#define read_8()      ( ((PIOC->PIO_PDSR & (1<<22)) >> 22)\
                      | ((PIOC->PIO_PDSR & (1<<21)) >> 20)\
                      | ((PIOC->PIO_PDSR & (1<<29)) >> 27)\
                      | ((PIOD->PIO_PDSR & (1<<7))  >> 4)\
                      | ((PIOC->PIO_PDSR & (1<<26)) >> 22)\
                      | ((PIOB->PIO_PDSR & (1<<27)) >> 22)\
                      | ((PIOC->PIO_PDSR & (1<<24)) >> 18)\
                      | ((PIOC->PIO_PDSR & (1<<23)) >> 16)\
                      )
#define setWriteDir() { PIOB->PIO_OER = BMASK; PIOC->PIO_OER = CMASK; PIOD->PIO_OER = DMASK; }
#define setReadDir()  { \
                          PMC->PMC_PCER0 = (1 << ID_PIOB)|(1 << ID_PIOC)|(1 << ID_PIOD);\
						  PIOB->PIO_ODR = BMASK; PIOC->PIO_ODR = CMASK; PIOD->PIO_ODR = DMASK;\
						}
#define write8(x)     { write_8(x); WR_ACTIVE; WR_STROBE; }
//#define write8(x)     { write_8(x); WR_ACTIVE; WR_STROBE; WR_IDLE; }
#define write16(x)    { uint8_t h = (x)>>8, l = x; write8(h); write8(l); }
#define READ_8(dst)   { RD_STROBE; RD_ACTIVE; dst = read_8(); RD_IDLE; RD_IDLE; }
#define READ_16(dst)  { uint8_t hi; READ_8(hi); READ_8(dst); dst |= (hi << 8); }
 // Shield Control macros.
#define PIN_LOW(port, pin)    (port)->PIO_CODR = (1<<(pin))
#define PIN_HIGH(port, pin)   (port)->PIO_SODR = (1<<(pin))
#define PIN_OUTPUT(port, pin) (port)->PIO_OER = (1<<(pin))

#elif defined(__AVR_ATmega2560__) && defined(USE_BLD_BST_MEGA2560)   //regular UNO shield on MEGA2560 using BLD/BST
#warning regular UNO shield on MEGA2560 using BLD/BST
#define RD_PORT PORTF
#define RD_PIN  0
#define WR_PORT PORTF
#define WR_PIN  1
#define CD_PORT PORTF
#define CD_PIN  2
#define CS_PORT PORTF
#define CS_PIN  3
#define RESET_PORT PORTF
#define RESET_PIN  4

#define EMASK         0x38
#define GMASK         0x20
#define HMASK         0x78
static __attribute((always_inline)) void write_8(uint8_t val)
{
	asm volatile("lds __tmp_reg__,0x0102" "\n\t"
	"BST %0,0" "\n\t" "BLD __tmp_reg__,5" "\n\t"
	"BST %0,1" "\n\t" "BLD __tmp_reg__,6" "\n\t"
	"BST %0,6" "\n\t" "BLD __tmp_reg__,3" "\n\t"
	"BST %0,7" "\n\t" "BLD __tmp_reg__,4" "\n\t"
	"sts 0x0102,__tmp_reg__" : : "a" (val));
	asm volatile("in __tmp_reg__,0x0E" "\n\t"
	"BST %0,2" "\n\t" "BLD __tmp_reg__,4" "\n\t"
	"BST %0,3" "\n\t" "BLD __tmp_reg__,5" "\n\t"
	"BST %0,5" "\n\t" "BLD __tmp_reg__,3" "\n\t"
	"out 0x0E,__tmp_reg__" : : "a" (val));
	asm volatile("in __tmp_reg__,0x14" "\n\t"
	"BST %0,4" "\n\t" "BLD __tmp_reg__,5" "\n\t"
	"out 0x14,__tmp_reg__" : : "a" (val));
}

#define read_8()      ( ((PINH & (3<<5)) >> 5)\
| ((PINE & (3<<4)) >> 2)\
| ((PING & (1<<5)) >> 1)\
| ((PINE & (1<<3)) << 2)\
| ((PINH & (3<<3)) << 3)\
)
#define setWriteDir() { DDRH |=  HMASK; DDRG |=  GMASK; DDRE |=  EMASK;  }
#define setReadDir()  { DDRH &= ~HMASK; DDRG &= ~GMASK; DDRE &= ~EMASK;  }
#define write8(x)     { write_8(x); WR_STROBE; }
#define write16(x)    { uint8_t h = (x)>>8, l = x; write8(h); write8(l); }
#define READ_8(dst)  { RD_STROBE; dst = read_8(); RD_IDLE; }
#define READ_16(dst)  { RD_STROBE; dst = read_8(); RD_IDLE; RD_STROBE; dst = (dst<<8) | read_8(); RD_IDLE; }

#define PIN_LOW(p, b)        (p) &= ~(1<<(b))
#define PIN_HIGH(p, b)       (p) |= (1<<(b))
#define PIN_OUTPUT(p, b)     *(&p-1) |= (1<<(b))

#elif defined(__AVR_ATmega2560__) && defined(USE_MEGA_16BIT_SHIELD)
//LCD pins   |D15 |D14 |D13 |D12 |D11 |D10 |D9  |D8  |D7  |D6  |D5  |D4  |D3  |D2  |D1  |D0  |
//ATmega2560 |PA7 |PA6 |PA5 |PA4 |PA3 |PA2 |PA1 |PA0 |PC7 |PC6 |PC5 |PC4 |PC3 |PC2 |PC1 |PC0 |
//MEGA2560pin|29  |28  |27  |26  |25  |24  |23  |22  |30  |31  |32  |33  |34  |35  |36  |37  |
//LCD pins   |RD  |WR  |RS  |CS  |RST |
//ATmega2560 |PL6 |PG2 |PD7 |PG1 |PG0 |
//MEGA2560pin|43  |39  |38  |40  |41  |
#warning USE_MEGA_16BIT_SHIELD
#define USES_16BIT_BUS
#define RD_PORT PORTL
#define RD_PIN  6        //PL6 (D43).   Graham has PA15 (D24) on Due Shield 
#define WR_PORT PORTG
#define WR_PIN  2        //D39 CTE
#define CD_PORT PORTD
#define CD_PIN  7        //D38 CTE
#define CS_PORT PORTG
#define CS_PIN  1        //D40 CTE
#define RESET_PORT PORTG
#define RESET_PIN  0     //D41 CTE

#define write_8(x)    { PORTC = x; }
#define write_16(x)   { PORTA = (x) >> 8; PORTC = x; }

#define read_16()     ( (PINA<<8) | (PINC) )
#define setWriteDir() { DDRC = 0xFF; DDRA = 0xff; }
#define setReadDir()  { DDRC = 0x00; DDRA = 0x00; }
//#define write8(x)     { write_8(x); WR_STROBE; }
#define write8(x)     { write16((x) & 0xFF); }
#define write16(x)    { write_16(x); WR_ACTIVE; WR_STROBE; }
#define READ_16(dst)  { RD_STROBE; dst = read_16(); RD_IDLE; }
#define READ_8(dst)   { READ_16(dst); dst &= 0x00FF; }

#define PIN_LOW(p, b)        (p) &= ~(1<<(b))
#define PIN_HIGH(p, b)       (p) |= (1<<(b))
#define PIN_OUTPUT(p, b)     *(&p-1) |= (1<<(b))

#elif defined(__AVR_ATmega2560__) && defined(USE_MEGA_8BIT_SHIELD)
//LCD pins   |D7  |D6  |D5  |D4  |D3  |D2  |D1  |D0  |  |RD  |WR  |RS  |CS  |RST |
//ATmega2560 |PA7 |PA6 |PA5 |PA4 |PA3 |PA2 |PA1 |PA0 |  |PL6 |PG2 |PD7 |PG1 |PG0 |
//MEGA2560pin|29  |28  |27  |26  |25  |24  |23  |22  |  |43  |39  |38  |40  |41  |
#warning USE_MEGA_8BIT_SHIELD for vagos21
#define RD_PORT PORTL
#define RD_PIN  6        //PL6 (D43).   Graham has PA15 (D24) on Due Shield 
#define WR_PORT PORTG
#define WR_PIN  2        //D39 CTE
#define CD_PORT PORTD
#define CD_PIN  7        //D38 CTE
#define CS_PORT PORTG
#define CS_PIN  1        //D40 CTE
#define RESET_PORT PORTG
#define RESET_PIN  0     //D41 CTE

#define write_8(x)   { PORTA = x;}

#define read_8()      ( PINA )
#define setWriteDir() { DDRA = 0xFF; }
#define setReadDir()  { DDRA = 0x00; }
#define write8(x)     { write_8(x); WR_ACTIVE; WR_STROBE; } // HX8357-D is slower
#define write16(x)    { uint8_t h = (x)>>8, l = x; write8(h); write8(l); }
#define READ_8(dst)   { RD_STROBE; dst = read_8(); RD_IDLE; }
#define READ_16(dst)  { RD_STROBE; dst = read_8(); RD_IDLE; RD_STROBE; dst = (dst<<8) | read_8(); RD_IDLE; }

#define PIN_LOW(p, b)        (p) &= ~(1<<(b))
#define PIN_HIGH(p, b)       (p) |= (1<<(b))
#define PIN_OUTPUT(p, b)     *(&p-1) |= (1<<(b))

#elif defined(__AVR_ATmega2560__) && defined(USE_MEGA_8BIT_PORTC_SHIELD)
//LCD pins   |D7  |D6  |D5  |D4  |D3  |D2  |D1  |D0  |  |RD  |WR  |RS  |CS  |RST |
//ATmega2560 |PC7 |PC6 |PC5 |PC4 |PC3 |PC2 |PC1 |PC0 |  |PL6 |PG2 |PD7 |PG1 |PG0 |
//MEGA2560pin|30  |31  |32  |33  |34  |35  |36  |37  |  |43  |39  |38  |40  |41  |
#warning USE_MEGA_8BIT_PORTC_SHIELD for Mihael54
#define RD_PORT PORTL
#define RD_PIN  6        //PL6 (D43).   Graham has PA15 (D24) on Due Shield 
#define WR_PORT PORTG
#define WR_PIN  2        //D39 CTE
#define CD_PORT PORTD
#define CD_PIN  7        //D38 CTE
#define CS_PORT PORTG
#define CS_PIN  1        //D40 CTE
#define RESET_PORT PORTG
#define RESET_PIN  0     //D41 CTE

#define write_8(x)   { PORTC = x;}

#define read_8()      ( PINC )
#define setWriteDir() { DDRC = 0xFF; }
#define setReadDir()  { DDRC = 0x00; }
#define write8(x)     { write_8(x); WR_ACTIVE; WR_STROBE; } // HX8357-D is slower
#define write16(x)    { uint8_t h = (x)>>8, l = x; write8(h); write8(l); }
#define READ_8(dst)   { RD_STROBE; dst = read_8(); RD_IDLE; }
#define READ_16(dst)  { RD_STROBE; dst = read_8(); RD_IDLE; RD_STROBE; dst = (dst<<8) | read_8(); RD_IDLE; }

#define PIN_LOW(p, b)        (p) &= ~(1<<(b))
#define PIN_HIGH(p, b)       (p) |= (1<<(b))
#define PIN_OUTPUT(p, b)     *(&p-1) |= (1<<(b))

#elif defined(__AVR_ATmega2560__) && defined(USE_MEGA_8BIT_PROTOSHIELD)
//LCD pins  |D7 |D6 |D5 |D4 |D3 |D2 |D1 |D0 | |RD |WR |RS |CS |RST|
//AVR   pin |PA7|PA6|PA5|PA4|PA3|PA2|PA1|PA0| |PF0|PF1|PF2|PF3|PF4|
//digital#  | 29| 28| 27| 26| 25| 24| 23| 22| | A0| A1| A2| A3| A4|
#warning USE_MEGA_8BIT_PROTOSHIELD
#define RD_PORT PORTF
#define RD_PIN  0
#define WR_PORT PORTF
#define WR_PIN  1
#define CD_PORT PORTF
#define CD_PIN  2
#define CS_PORT PORTF
#define CS_PIN  3
#define RESET_PORT PORTF
#define RESET_PIN  4

#define write_8(x)   { PORTA = x;}

#define read_8()      ( PINA )
#define setWriteDir() { DDRA = 0xFF; }
#define setReadDir()  { DDRA = 0x00; }
#define write8(x)     { write_8(x); WR_STROBE; }
#define write16(x)    { uint8_t h = (x)>>8, l = x; write8(h); write8(l); }
#define READ_8(dst)   { RD_STROBE; dst = read_8(); RD_IDLE; }
#define READ_16(dst)  { RD_STROBE; dst = read_8(); RD_IDLE; RD_STROBE; dst = (dst<<8) | read_8(); RD_IDLE; }

#define PIN_LOW(p, b)        (p) &= ~(1<<(b))
#define PIN_HIGH(p, b)       (p) |= (1<<(b))
#define PIN_OUTPUT(p, b)     *(&p-1) |= (1<<(b))

#elif defined(__AVR_ATmega32U4__) && defined(USE_BLD_BST_MEGA32U4)  //regular UNO shield on Leonardo using BST/BLD
#warning regular UNO shield on Leonardo using BST/BLD
#define RD_PORT PORTF
#define RD_PIN  7
#define WR_PORT PORTF
#define WR_PIN  6
#define CD_PORT PORTF
#define CD_PIN  5
#define CS_PORT PORTF
#define CS_PIN  4
#define RESET_PORT PORTF
#define RESET_PIN  1

#define BMASK         (3<<4)
#define CMASK         (1<<6)
#define DMASK         ((1<<7)|(1<<4)|(3<<0))
#define EMASK         (1<<6)
static __attribute((always_inline)) void write_8(uint8_t val)
{
	asm volatile("in __tmp_reg__,0x05" "\n\t"
	"BST %0,0" "\n\t" "BLD __tmp_reg__,4" "\n\t"
	"BST %0,1" "\n\t" "BLD __tmp_reg__,5" "\n\t"
	"out 0x05,__tmp_reg__" : : "a" (val));
	asm volatile("in __tmp_reg__,0x0B" "\n\t"
	"BST %0,2" "\n\t" "BLD __tmp_reg__,1" "\n\t"
	"BST %0,3" "\n\t" "BLD __tmp_reg__,0" "\n\t"
	"BST %0,4" "\n\t" "BLD __tmp_reg__,4" "\n\t"
	"BST %0,6" "\n\t" "BLD __tmp_reg__,7" "\n\t"
	"out 0x0B,__tmp_reg__" : : "a" (val));
	asm volatile("in __tmp_reg__,0x08" "\n\t"
	"BST %0,5" "\n\t" "BLD __tmp_reg__,6" "\n\t"
	"out 0x08,__tmp_reg__" : : "a" (val));
	asm volatile("in __tmp_reg__,0x0E" "\n\t"
	"BST %0,7" "\n\t" "BLD __tmp_reg__,6" "\n\t"
	"out 0x0E,__tmp_reg__" : : "a" (val));
}
#define read_8()      ( ((PINB & (3<<4)) >> 4)\
| ((PIND & (1<<1)) << 1)\
| ((PIND & (1<<0)) << 3)\
| ((PIND & (1<<4)) >> 0)\
| ((PINC & (1<<6)) >> 1)\
| ((PIND & (1<<7)) >> 1)\
| ((PINE & (1<<6)) << 1)\
)
#define setWriteDir() { DDRB |=  BMASK; DDRC |=  CMASK; DDRD |=  DMASK; DDRE |=  EMASK;  }
#define setReadDir()  { DDRB &= ~BMASK; DDRC &= ~CMASK; DDRD &= ~DMASK; DDRE &= ~EMASK;  }
#define write8(x)     { write_8(x); WR_STROBE; }
#define write16(x)    { uint8_t h = (x)>>8, l = x; write8(h); write8(l); }
#define READ_8(dst)  { RD_STROBE; dst = read_8(); RD_IDLE; }
#define READ_16(dst)  { RD_STROBE; dst = read_8(); RD_IDLE; RD_STROBE; dst = (dst<<8) | read_8(); RD_IDLE; }

#define PIN_LOW(p, b)        (p) &= ~(1<<(b))
#define PIN_HIGH(p, b)       (p) |= (1<<(b))
#define PIN_OUTPUT(p, b)     *(&p-1) |= (1<<(b))

#elif defined(__SAM3X8E__) && defined(USE_DUE_8BIT_PROTOSHIELD)  //regular UNO shield on DUE
//LCD pins   |D7  |D6  |D5  |D4  |D3  |D2  |D1  |D0  | |RD  |WR  |RS  |CS  |RST |
//SAM3XE pin |PD7 |PD6 |PD5 |PD4 |PD3 |PD2 |PD1 |PD0 | |PA16|PA24|PA23|PA22|PA6 |
//Due pins   |11  |29  |15  |14  |28  |27  |26  |25  | |A0  |A1  |A2  |A3  |A4  |
#warning USE_DUE_8BIT_PROTOSHIELD
// configure macros for the control pins
  #define RD_PORT PIOA
  #define RD_PIN  16    //A0
  #define WR_PORT PIOA
  #define WR_PIN  24    //A1
  #define CD_PORT PIOA
  #define CD_PIN  23    //A2
  #define CS_PORT PIOA
  #define CS_PIN  22    //A3
  #define RESET_PORT PIOA
  #define RESET_PIN  6  //A4
// configure macros for data bus
#define DMASK         (0xFF<<0)
#define write_8(x)   {  PIOD->PIO_CODR = DMASK; PIOD->PIO_SODR = x; }

#define read_8()      ( PIOD->PIO_PDSR & DMASK)
  #define setWriteDir() { PIOD->PIO_OER = DMASK; PIOD->PIO_PER = DMASK; }
  #define setReadDir()  { PMC->PMC_PCER0 = (1 << ID_PIOD); PIOD->PIO_ODR = DMASK;}      
#define write8(x)     { write_8(x); WR_ACTIVE; WR_STROBE; WR_IDLE; WR_IDLE; }
#define write16(x)    { uint8_t h = (x)>>8, l = x; write8(h); write8(l); }
#define READ_8(dst)   { RD_STROBE; RD_ACTIVE4; dst = read_8(); RD_IDLE; RD_IDLE; RD_IDLE; }
#define READ_16(dst)  { uint8_t hi; READ_8(hi); READ_8(dst); dst |= (hi << 8); }
// Shield Control macros.
#define PIN_LOW(port, pin)    (port)->PIO_CODR = (1<<(pin))
#define PIN_HIGH(port, pin)   (port)->PIO_SODR = (1<<(pin))
#define PIN_OUTPUT(port, pin) (port)->PIO_OER = (1<<(pin))

#elif defined(__SAM3X8E__) && defined(USE_DUE_16BIT_SHIELD)  //regular CTE shield on DUE
#define USES_16BIT_BUS  //COMMENT THIS LINE IF YOU USE 8BIT BUS
// configure macros for the control pins
#define RD_PORT PIOA
#define RD_PIN  15     //D24 Graham
#define WR_PORT PIOD
#define WR_PIN  1      //D26
#define CD_PORT PIOD
#define CD_PIN  0      //D25
#define CS_PORT PIOD
#define CS_PIN  2      //D27
#define RESET_PORT PIOD
#define RESET_PIN  3   //D28
// configure macros for data bus 
// DB0..DB7 on PIOC1..PIOC8,  DB8..DB15 on PIOC12..PIOC19
// 
#define CMASKH        (0xFF00<<4)
#define CMASKL        (0x00FF<<1)
#define CMASK         (CMASKH | CMASKL)
#define write_8(x)    { PIOC->PIO_CODR = CMASKL; PIOC->PIO_SODR = (((x)&0x00FF)<<1); }
#define write_16(x)   { PIOC->PIO_CODR = CMASK; \
                        PIOC->PIO_SODR = (((x)&0x00FF)<<1)|(((x)&0xFF00)<<4); }
#define read_16()     (((PIOC->PIO_PDSR & CMASKH)>>4)|((PIOC->PIO_PDSR & CMASKL)>>1) )
//#define read_8()      (read_16() & 0xFF)
#define read_8()      ((PIOC->PIO_PDSR & CMASKL)>>1)
#define setWriteDir() { PIOC->PIO_OER = CMASK; PIOC->PIO_PER = CMASK; }
#define setReadDir()  { PMC->PMC_PCER0 = (1 << ID_PIOC); PIOC->PIO_ODR = CMASK; }
#if defined(USES_16BIT_BUS)
#warning USE_DUE_16BIT_SHIELD
#define write8(x)     { write16(x & 0xFF); }
#define write16(x)    { write_16(x); WR_ACTIVE; WR_STROBE; WR_IDLE; WR_IDLE; }
#define READ_16(dst)  { RD_STROBE; RD_ACTIVE4; dst = read_16(); RD_IDLE; RD_IDLE; RD_IDLE; }
#define READ_8(dst)   { READ_16(dst); dst &= 0xFF; }
#else
#warning USE_DUE_8BIT_SHIELD
#define write8(x)     { write_8(x); WR_ACTIVE4; WR_STROBE; WR_IDLE4; }
#define write16(x)    { uint8_t h = (x)>>8, l = x; write8(h); write8(l); }
#define READ_8(dst)   { RD_STROBE; RD_ACTIVE4; dst = read_8(); RD_IDLE; RD_IDLE; RD_IDLE; }
#define READ_16(dst)  { uint8_t hi; READ_8(hi); READ_8(dst); dst |= (hi << 8); }
#endif

// Shield Control macros.
#define PIN_LOW(port, pin)    (port)->PIO_CODR = (1<<(pin))
#define PIN_HIGH(port, pin)   (port)->PIO_SODR = (1<<(pin))
#define PIN_OUTPUT(port, pin) (port)->PIO_OER = (1<<(pin))

#elif defined(__SAM3X8E__) && defined(USE_ELECHOUSE_DUE_16BIT_SHIELD)  //ELECHOUSE_DUE shield on DUE
#warning USE_ELECHOUSE_DUE_16BIT_SHIELD
#define USES_16BIT_BUS
// configure macros for the control pins
#define RD_PORT PIOA
#define RD_PIN  15     //D24 Graham
#define WR_PORT PIOA
#define WR_PIN  14     //D23
#define CD_PORT PIOB
#define CD_PIN  26     //D22
#define CS_PORT PIOA
#define CS_PIN  7      //D31
#define RESET_PORT PIOC
#define RESET_PIN  1   //D33
// configure macros for data bus 
// DB0..DB7 on PIOC2..PIOC9,  DB8..DB15 on PIOC12..PIOC19
// 
#define CMASKH        (0xFF00<<4)
#define CMASKL        (0x00FF<<2)
#define CMASK         (CMASKH | CMASKL)
#define write_8(x)    { PIOC->PIO_CODR = CMASKL; PIOC->PIO_SODR = (((x)&0x00FF)<<2); }
#define write_16(x)   { PIOC->PIO_CODR = CMASK; \
                        PIOC->PIO_SODR = (((x)&0x00FF)<<2)|(((x)&0xFF00)<<4); }
#define read_16()     (((PIOC->PIO_PDSR & CMASKH)>>4)|((PIOC->PIO_PDSR & CMASKL)>>2) )
#define read_8()      (read_16() & 0xFF)
#define setWriteDir() { PIOC->PIO_OER = CMASK; PIOC->PIO_PER = CMASK; }
#define setReadDir()  { PMC->PMC_PCER0 = (1 << ID_PIOC); PIOC->PIO_ODR = CMASK; }
#define write8(x)     { write16(x & 0xFF); }
#define write16(x)    { write_16(x); WR_ACTIVE; WR_STROBE; WR_IDLE; WR_IDLE; }
#define READ_16(dst)  { RD_STROBE; RD_ACTIVE4; dst = read_16(); RD_IDLE; RD_IDLE; RD_IDLE; }
#define READ_8(dst)   { READ_16(dst); dst &= 0xFF; }

// Shield Control macros.
#define PIN_LOW(port, pin)    (port)->PIO_CODR = (1<<(pin))
#define PIN_HIGH(port, pin)   (port)->PIO_SODR = (1<<(pin))
#define PIN_OUTPUT(port, pin) (port)->PIO_OER = (1<<(pin))

#elif defined(__SAM3X8E__) && defined(USE_MEGA_16BIT_SHIELD)  //regular MEGA shield on DUE
//LCD pins   |D15 |D14 |D13 |D12 |D11 |D10 |D9  |D8  |D7  |D6  |D5  |D4  |D3  |D2  |D1  |D0  |
//SAM3XE pin |PD6 |PD3 |PD2 |PD1 |PD0 |PA15|PA14|PB26|PD9 |PA7 |PD10|PC1 |PC2 |PC3 |PC4 |PC5 |
//Due pins   |29  |28  |27  |26  |25  |24  |23  |22  |30  |31  |32  |33  |34  |35  |36  |37  |
//LCD pins   |RD  |WR  |RS  |CS  |RST |
//SAM3XE pin |PA20|PC7 |PC6 |PC8 |PC9 |
//Due pins   |43  |39  |38  |40  |41  |
#warning USE_MEGA_16BIT_SHIELD
#define USES_16BIT_BUS
#define WRITE_DELAY { WR_ACTIVE4; WR_ACTIVE2; }
#define IDLE_DELAY  { }
#define READ_DELAY  { RD_ACTIVE4; }
// configure macros for the control pins
#define RD_PORT PIOA
#define RD_PIN  20     //D43
#define WR_PORT PIOC
#define WR_PIN  7      //D39
#define CD_PORT PIOC
#define CD_PIN  6      //D38
#define CS_PORT PIOC
#define CS_PIN  8      //D40
#define RESET_PORT PIOC
#define RESET_PIN  9   //D41
// configure macros for data bus 
// 
#define AMASK         ((1<<7)|(3<<14))          //PA7, PA14-PA15
#define BMASK         (1<<26)                   //PB26
#define CMASK         (31<<1)                   //PC1-PC5
#define DMASK         ((15<<0)|(1<<6)|(3<<9))   //PD0-PD3, PD6, PD9-PD10

#define write_16(x)   { PIOA->PIO_CODR = AMASK; PIOB->PIO_CODR = BMASK; PIOC->PIO_CODR = CMASK; PIOD->PIO_CODR = DMASK; \
                        PIOA->PIO_SODR = (((x)&(1<<6))<<1)|(((x)&(3<<9))<<5); \
                        PIOB->PIO_SODR = (((x)&(1<<8))<<18); \
                        PIOC->PIO_SODR = (((x)&(1<<0))<<5); \
                        PIOC->PIO_SODR = (((x)&(1<<1))<<3); \
                        PIOC->PIO_SODR = (((x)&(1<<2))<<1); \
                        PIOC->PIO_SODR = (((x)&(1<<3))>>1); \
                        PIOC->PIO_SODR = (((x)&(1<<4))>>3); \
                        PIOD->PIO_SODR = (((x)&(1<<7))<<2)|(((x)&(1<<5))<<5)|(((x)&(15<<11))>>11)|(((x)&(1<<15))>>9); \
					  }

/*
#define write_16(VL)   { PIOA->PIO_CODR = AMASK; PIOC->PIO_CODR = CMASK; PIOD->PIO_CODR = DMASK; \
		REG_PIOA_SODR=((((VL)>>8) & 0x06)<<13) | ((VL & 0x40)<<1);\
		if ((VL)&(1<<8)) REG_PIOB_SODR=(1<<26); else REG_PIOB_CODR=(1<<26);\
		REG_PIOC_SODR=((VL & 0x01)<<5) | ((VL & 0x02)<<3) | ((VL & 0x04)<<1) | ((VL & 0x08)>>1) | ((VL & 0x10)>>3);\
		REG_PIOD_SODR=((((VL)>>8) & 0x78)>>3) | ((((VL)>>8) & 0x80)>>1) | ((VL & 0x20)<<5) | ((VL & 0x80)<<2);\
}
*/
#define read_16()     ( 0\
                        |((PIOC->PIO_PDSR & (1<<5))>>5)\
                        |((PIOC->PIO_PDSR & (1<<4))>>3)\
                        |((PIOC->PIO_PDSR & (1<<3))>>1)\
                        |((PIOC->PIO_PDSR & (1<<2))<<1)\
                        |((PIOC->PIO_PDSR & (1<<1))<<3)\
                        |((PIOD->PIO_PDSR & (1<<10))>>5)\
                        |((PIOA->PIO_PDSR & (1<<7))>>1)\
                        |((PIOD->PIO_PDSR & (1<<9))>>2)\
                        |((PIOB->PIO_PDSR & (1<<26))>>18)\
                        |((PIOA->PIO_PDSR & (3<<14))>>5)\
                        |((PIOD->PIO_PDSR & (15<<0))<<11)\
                        |((PIOD->PIO_PDSR & (1<<6))<<9)\
                      )
#define read_8()      (read_16() & 0xFF)
#define setWriteDir() {\
                        PIOA->PIO_OER = AMASK; PIOA->PIO_PER = AMASK; \
                        PIOB->PIO_OER = BMASK; PIOB->PIO_PER = BMASK; \
                        PIOC->PIO_OER = CMASK; PIOC->PIO_PER = CMASK; \
                        PIOD->PIO_OER = DMASK; PIOD->PIO_PER = DMASK; \
                      }
#define setReadDir()  { \
                        PMC->PMC_PCER0 = (1 << ID_PIOA)|(1 << ID_PIOB)|(1 << ID_PIOC)|(1 << ID_PIOD); \
						PIOA->PIO_ODR = AMASK; \
						PIOB->PIO_ODR = BMASK; \
						PIOC->PIO_ODR = CMASK; \
						PIOD->PIO_ODR = DMASK; \
					  }
#define write8(x)     { write16(x & 0xFF); }
// ILI9486 is slower than ILI9481
#define write16(x)    { write_16(x); WRITE_DELAY; WR_STROBE; IDLE_DELAY;}
#define READ_16(dst)  { RD_STROBE; READ_DELAY; dst = read_16(); RD_IDLE2; }
#define READ_8(dst)   { READ_16(dst); dst &= 0xFF; }

// Shield Control macros.
#define PIN_LOW(port, pin)    (port)->PIO_CODR = (1<<(pin))
#define PIN_HIGH(port, pin)   (port)->PIO_SODR = (1<<(pin))
#define PIN_OUTPUT(port, pin) (port)->PIO_OER = (1<<(pin))

#elif defined(__SAM3X8E__) && defined(USE_MEGA_8BIT_SHIELD)  //regular CTE shield on DUE
//LCD pins   |D7  |D6  |D5  |D4  |D3  |D2  |D1  |D0  |  |RD  |WR  |RS  |CS  |RST |
//SAM3XE pin |PD6 |PD3 |PD2 |PD1 |PD0 |PA15|PA14|PB26|  |PA20|PC7 |PC6 |PC8 |PC9 |
//Due pins   |29  |28  |27  |26  |25  |24  |23  |22  |  |43  |39  |38  |40  |41  |
#warning USE_MEGA_8BIT_SHIELD for peloxp
#define WRITE_DELAY { WR_ACTIVE4; }
#define IDLE_DELAY  { }
#define READ_DELAY  { RD_ACTIVE4; }
// configure macros for the control pins
#define RD_PORT PIOA
#define RD_PIN  20     //D43
#define WR_PORT PIOC
#define WR_PIN  7      //D39
#define CD_PORT PIOC
#define CD_PIN  6      //D38
#define CS_PORT PIOC
#define CS_PIN  8      //D40
#define RESET_PORT PIOC
#define RESET_PIN  9   //D41
// configure macros for data bus 
// 
#define AMASK         ((3<<14))                 //PA14-PA15    D23-D24
#define BMASK         (1<<26)                   //PB26         D22
#define DMASK         ((15<<0)|(1<<6))          //PD0-PD3, PD6 D25-D28,D29

#define write_8(x)   { PIOA->PIO_CODR = AMASK; PIOB->PIO_CODR = BMASK; PIOD->PIO_CODR = DMASK; \
                        PIOB->PIO_SODR = (((x)&(1<<0))<<26); \
                        PIOA->PIO_SODR = (((x)&(3<<1))<<13); \
                        PIOD->PIO_SODR = (((x)&(15<<3))>>3); \
                        PIOD->PIO_SODR = (((x)&(1<<7))>>1); \
					  }

#define read_8()     ( 0\
                        |((PIOB->PIO_PDSR & (1<<26))>>26)\
                        |((PIOA->PIO_PDSR & (3<<14))>>13)\
                        |((PIOD->PIO_PDSR & (15<<0))<<3)\
                        |((PIOD->PIO_PDSR & (1<<6))<<1)\
                      )

#define setWriteDir() {\
                        PIOA->PIO_OER = AMASK; PIOA->PIO_PER = AMASK; \
                        PIOB->PIO_OER = BMASK; PIOB->PIO_PER = BMASK; \
                        PIOD->PIO_OER = DMASK; PIOD->PIO_PER = DMASK; \
                      }
#define setReadDir()  { \
                        PMC->PMC_PCER0 = (1 << ID_PIOA)|(1 << ID_PIOB)|(1 << ID_PIOC)|(1 << ID_PIOD); \
						PIOA->PIO_ODR = AMASK; \
						PIOB->PIO_ODR = BMASK; \
						PIOD->PIO_ODR = DMASK; \
					  }

// ILI9486 is slower than ILI9481. HX8357-D is slower
#define write8(x)     { write_8(x); WRITE_DELAY; WR_STROBE; IDLE_DELAY; }
#define write16(x)    { uint8_t h = (x)>>8, l = x; write8(h); write8(l); }
#define READ_8(dst)   { RD_STROBE; READ_DELAY; dst = read_8(); RD_IDLE2; }
#define READ_16(dst)  { uint8_t hi; READ_8(hi); READ_8(dst); dst |= (hi << 8); }

// Shield Control macros.
#define PIN_LOW(port, pin)    (port)->PIO_CODR = (1<<(pin))
#define PIN_HIGH(port, pin)   (port)->PIO_SODR = (1<<(pin))
#define PIN_OUTPUT(port, pin) (port)->PIO_OER = (1<<(pin))

#elif defined(__SAM3X8E__) && defined(USE_MEGA_8BIT_PORTC_SHIELD)  //Surenoo 8/16bit shield on DUE
//LCD pins   |D7  |D6  |D5  |D4  |D3  |D2  |D1  |D0  |  |RD  |WR  |RS  |CS  |RST |
//SAM3XE pin |PD9 |PA7 |PD10|PC1 |PC2 |PC3 |PC4 |PC5 |  |PA20|PC7 |PC6 |PC8 |PC9 |
//Due pins   |30  |31  |32  |33  |34  |35  |36  |37  |  |43  |39  |38  |40  |41  |
#warning USE_MEGA_8BIT_PORTC_SHIELD on DUE
#define WRITE_DELAY { }
#define IDLE_DELAY  { }
#define READ_DELAY  { RD_ACTIVE4; }
// configure macros for the control pins
#define RD_PORT PIOA
#define RD_PIN  20     //D43
#define WR_PORT PIOC
#define WR_PIN  7      //D39
#define CD_PORT PIOC
#define CD_PIN  6      //D38
#define CS_PORT PIOC
#define CS_PIN  8      //D40
#define RESET_PORT PIOC
#define RESET_PIN  9   //D41
// configure macros for data bus 
// 
#define AMASK         (1<<7)                    //PA7          D31
#define CMASK         (31<<1)                   //PC1-PC5      D33-D37
#define DMASK         (3<<9)                    //PD9,PD10     D30,D32

#define write_8(x)   { PIOA->PIO_CODR = AMASK; PIOC->PIO_CODR = CMASK; PIOD->PIO_CODR = DMASK; \
                        PIOA->PIO_SODR = (((x)&(1<<6))<<1); \
                        PIOC->PIO_SODR = (((x)&(1<<0))<<5); \
                        PIOC->PIO_SODR = (((x)&(1<<1))<<3); \
                        PIOC->PIO_SODR = (((x)&(1<<2))<<1); \
                        PIOC->PIO_SODR = (((x)&(1<<3))>>1); \
                        PIOC->PIO_SODR = (((x)&(1<<4))>>3); \
                        PIOD->PIO_SODR = (((x)&(1<<7))<<2)|(((x)&(1<<5))<<5); \
					  }

#define read_8()     ( 0\
                        |((PIOC->PIO_PDSR & (1<<5))>>5)\
                        |((PIOC->PIO_PDSR & (1<<4))>>3)\
                        |((PIOC->PIO_PDSR & (1<<3))>>1)\
                        |((PIOC->PIO_PDSR & (1<<2))<<1)\
                        |((PIOC->PIO_PDSR & (1<<1))<<3)\
                        |((PIOD->PIO_PDSR & (1<<10))>>5)\
                        |((PIOA->PIO_PDSR & (1<<7))>>1)\
                        |((PIOD->PIO_PDSR & (1<<9))>>2)\
                      )

#define setWriteDir() {\
                        PIOA->PIO_OER = AMASK; PIOA->PIO_PER = AMASK; \
                        PIOC->PIO_OER = CMASK; PIOB->PIO_PER = CMASK; \
                        PIOD->PIO_OER = DMASK; PIOD->PIO_PER = DMASK; \
                      }
#define setReadDir()  { \
                        PMC->PMC_PCER0 = (1 << ID_PIOA)|(1 << ID_PIOB)|(1 << ID_PIOC)|(1 << ID_PIOD); \
						PIOA->PIO_ODR = AMASK; \
						PIOC->PIO_ODR = CMASK; \
						PIOD->PIO_ODR = DMASK; \
					  }

// ILI9486 is slower than ILI9481. HX8357-D is slower
#define write8(x)     { write_8(x); WRITE_DELAY; WR_STROBE; IDLE_DELAY; }
#define write16(x)    { uint8_t h = (x)>>8, l = x; write8(h); write8(l); }
#define READ_8(dst)   { RD_STROBE; READ_DELAY; dst = read_8(); RD_IDLE2; }
#define READ_16(dst)  { uint8_t hi; READ_8(hi); READ_8(dst); dst |= (hi << 8); }

// Shield Control macros.
#define PIN_LOW(port, pin)    (port)->PIO_CODR = (1<<(pin))
#define PIN_HIGH(port, pin)   (port)->PIO_SODR = (1<<(pin))
#define PIN_OUTPUT(port, pin) (port)->PIO_OER = (1<<(pin))

#elif defined(__MK20DX256__) && defined(USE_BOBCACHELOT_TEENSY) // special for BOBCACHEALOT_TEENSY
#warning  special for BOBCACHEALOT_TEENSY
#define RD_PORT GPIOD
#define RD_PIN  1
#define WR_PORT GPIOC
#define WR_PIN  0
#define CD_PORT GPIOB
#define CD_PIN  0
#define CS_PORT GPIOB
#define CS_PIN  1
#define RESET_PORT GPIOB
#define RESET_PIN  3

// configure macros for the data pins
#define CMASK ((1<<3))
#define DMASK ((1<<0)|(1<<2)|(1<<3)|(1<<4)|(1<<5)|(1<<6)|(1<<7))

  #define write_8(d) { \
   GPIOC_PCOR = CMASK; GPIOD_PCOR = DMASK; \
   GPIOC_PSOR = (((d) & (1<<1)) << 2); \
   GPIOD_PSOR = (d) & DMASK; \
  } 
  #define read_8() (          (GPIOD_PDIR & DMASK) | (GPIOC_PDIR & (1<<3)) >> 2 )
  #define setWriteDir() {GPIOC_PDDR |=  CMASK;GPIOD_PDDR |=  DMASK; }
  #define setReadDir()  {GPIOC_PDDR &= ~CMASK;GPIOD_PDDR &= ~DMASK; }

#define write8(x)     { write_8(x); WR_STROBE; }
#define write16(x)    { uint8_t h = (x)>>8, l = x; write8(h); write8(l); }
#define READ_8(dst)   { RD_STROBE; dst = read_8(); RD_IDLE; }
#define READ_16(dst)  { uint8_t hi; READ_8(hi); READ_8(dst); dst |= (hi << 8); }

#define PASTE(x, y)   x ## y

#define PIN_LOW(port, pin)    PASTE(port, _PCOR) =  (1<<(pin))
#define PIN_HIGH(port, pin)   PASTE(port, _PSOR) =  (1<<(pin))
#define PIN_OUTPUT(port, pin) PASTE(port, _PDDR) |= (1<<(pin))

#elif defined(USE_MY_BLUEPILL) && (defined(ARDUINO_GENERIC_STM32F103C) || defined(ARDUINO_BLUEPILL_F103C8) || defined(ARDUINO_BLUEPILL_F103CB))
#warning Uno Shield on MY BLUEPILL

//LCD pins  |D7  |D6  |D5 |D4 |D3 |D2 |D1  |D0 | |RD |WR |RS |CS |RST| |SD_SS|SD_DI|SD_DO|SD_SCK| |SDA|SCL|
//STM32 pin |PA3 |PA2 |PA1|PA0|PB7|PB6|PA10|PA9| |PB1|PB0|PA7|PA6|PA5| |PB12 |PB15 |PB14 |PB13  | |PB9|PB8|

#if defined(ARDUINO_BLUEPILL_F103C8) || defined(ARDUINO_BLUEPILL_F103CB)   //regular CMSIS libraries
#define REGS(x) x
#define GPIO_INIT()   { RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPBEN | RCC_APB2ENR_IOPCEN | RCC_APB2ENR_IOPDEN | RCC_APB2ENR_AFIOEN; \
        AFIO->MAPR |= AFIO_MAPR_SWJ_CFG_1;}
#else                                                                  //weird Maple libraries
#define REGS(x) regs->x
#endif

#define WRITE_DELAY { }
#define READ_DELAY  { RD_ACTIVE4; }
#define GROUP_MODE(port, reg, mask, val)  {port->REGS(reg) = (port->REGS(reg) & ~(mask)) | ((mask)&(val)); }
#define GP_OUT(port, reg, mask)           GROUP_MODE(port, reg, mask, 0x33333333)
#define GP_INP(port, reg, mask)           GROUP_MODE(port, reg, mask, 0x44444444)
#define PIN_OUTPUT(port, pin) {\
        if (pin < 8) {GP_OUT(port, CRL, 0xF<<((pin)<<2));} \
        else {GP_OUT(port, CRH, 0xF<<((pin&7)<<2));} \
    }
#define PIN_INPUT(port, pin) { \
        if (pin < 8) { GP_INP(port, CRL, 0xF<<((pin)<<2)); } \
        else { GP_INP(port, CRH, 0xF<<((pin&7)<<2)); } \
    }
#define PIN_HIGH(port, pin)   (port)-> REGS(BSRR) = (1<<(pin))
#define PIN_LOW(port, pin)    (port)-> REGS(BSRR) = (1<<((pin)+16))

#define RD_PORT GPIOB
#define RD_PIN  1
#define WR_PORT GPIOB
#define WR_PIN  0
#define CD_PORT GPIOA
#define CD_PIN  7
#define CS_PORT GPIOA
#define CS_PIN  6
#define RESET_PORT GPIOA
#define RESET_PIN  5

// configure macros for the data pins
#define AMASK 0x060F
#define BMASK 0x00C0
#define write_8(d)    { GPIOA->REGS(BSRR) = AMASK << 16; GPIOB->REGS(BSRR) = BMASK << 16; \
                       GPIOA->REGS(BSRR) = (((d) & 3) << 9) | (((d) & 0xF0) >> 4); \
                       GPIOB->REGS(BSRR) = (((d) & 0x0C) << 4); \
                       }
#define read_8()      (((GPIOA->REGS(IDR) & (3<<9)) >> 9) | ((GPIOA->REGS(IDR) & (0x0F)) << 4) | ((GPIOB->REGS(IDR) & (3<<6)) >> 4))
//                                     PA10,PA9                     PA3-PA0                         PB7,PB6  
#define setWriteDir() {GP_OUT(GPIOA, CRH, 0xFF0); GP_OUT(GPIOA, CRL, 0xFFFF); GP_OUT(GPIOB, CRL, 0xFF000000); }
#define setReadDir()  {GP_INP(GPIOA, CRH, 0xFF0); GP_INP(GPIOA, CRL, 0xFFFF); GP_INP(GPIOB, CRL, 0xFF000000); }

#define write8(x)     { write_8(x); WRITE_DELAY; WR_STROBE; }
#define write16(x)    { uint8_t h = (x)>>8, l = x; write8(h); write8(l); }
#define READ_8(dst)   { RD_STROBE; READ_DELAY; dst = read_8(); RD_IDLE; }
#define READ_16(dst)  { uint8_t hi; READ_8(hi); READ_8(dst); dst |= (hi << 8); }

//####################################### ADIGITALEU_TEENSY ############################
//UNTESTED
#elif defined(__MK66FX1M0__) && defined(USE_ADIGITALEU_TEENSY)  // 16bit on a Teensy 3.6
#warning "Teensy 3.6 16bit port C & D only (for now)"
// Note: Port usage explained in UTFT Teensy edition ...\libraries\UTFT\hardware\arm\HW_Teensy3.h"

#define USES_16BIT_BUS

#define WRITE_DELAY { WR_ACTIVE8; }
#define READ_DELAY  { RD_ACTIVE16; }

#define RD_PORT GPIOA
#define RD_PIN 16       //28 RD
#define WR_PORT GPIOA
#define WR_PIN 5        //25 WR
#define CD_PORT GPIOE
#define CD_PIN 26       //24 RS 
#define CS_PORT GPIOA
#define CS_PIN 14       //26 CS
#define RESET_PORT GPIOA
#define RESET_PIN 15    //27 Reset

#define write_8(d) { GPIOC_PDOR = d; } 
#define write_16(d) { GPIOC_PDOR = d; GPIOD_PDOR = (d >> 8);}

#define read_8() (GPIOC_PDIR)
#define read_16() (GPIOC_PDIR | GPIOD_PDIR << 8)

#define setWriteDir() {GPIOC_PDDR |=  0xFF; GPIOD_PDDR |=  0xFF; }
#define setReadDir()  {GPIOC_PDDR &= ~0xFF; GPIOD_PDDR &= ~0xFF; }

#define write8(x)     {write_8(x); WRITE_DELAY; WR_STROBE }
#define write16(x)    {write_16(x); WRITE_DELAY; WR_STROBE }

#define READ_8(dst) { RD_STROBE; READ_DELAY; dst = read_8(); RD_IDLE; } 
#define READ_16(dst) { RD_STROBE; READ_DELAY; dst = read_16(); RD_IDLE;}

//Data: Teensy pins -> D0-D15 :
// Teensy probably initialises some pins for Analog, Timer, Alternate, ...
// so it is probably wise to use pinMode(n, OUTPUT) for all the control and data lines
#define GPIO_INIT() {pinMode(2, OUTPUT); for (int i = 5; i <= 15; i++) pinMode(i, OUTPUT); for (int i = 20; i <= 28; i++) pinMode(i, OUTPUT);}

#define PASTE(x, y) x ## y

#define PIN_LOW(port, pin) PASTE(port, _PCOR) = (1<<(pin))
#define PIN_HIGH(port, pin) PASTE(port, _PSOR) = (1<<(pin))
#define PIN_OUTPUT(port, pin) PASTE(port, _PDDR) |= (1<<(pin))

#else
#define USE_SPECIAL_FAIL
#endif
