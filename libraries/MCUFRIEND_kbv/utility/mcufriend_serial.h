#if ARDUINO >= 165
#include <SPI.h>
#endif

#if 0
#elif defined(__AVR_ATmega328P__)

#define SPI_INIT()   { DDRB |= (1<<5)|(1<<3)|(1<<2); SPCR = (1<<SPE)|(1<<MSTR); SPSR = (1<<SPI2X); SPSR; SPDR; }
static inline uint8_t spi_xfer(uint8_t c)
{
    SPDR = c;
	while ((SPSR & (1<<SPIF)) == 0) ;
	return SPDR;
}
extern uint8_t running;
static inline void write8(uint8_t x)    {
                         if (running) {
							 while ((SPSR & 0x80) == 0);
							 SPDR;
						 }
                         SPDR = x;
                         running = 1;
                     }
static inline uint8_t read8(void)    {
                         if (running) while ((SPSR & 0x80) == 0);
                         running = 0;
						 return SPDR;
                     }
static inline uint8_t xchg8(uint8_t x) { write8(x); return read8(); }
static inline void flush(void)   {
                      if (running) {
                          while ((SPSR & 0x80) == 0);
                      }
                      running = 0;
    				  SPDR;
                  }

#if defined(SUPPORT_8347D)
#warning using HX8347D hardware
#define CD_PORT PORTD
#define CD_PIN  PD7
#define CS_PORT PORTB
#define CS_PIN  PB2
#define RESET_PORT PORTB
#define RESET_PIN  PB1
#define SD_PIN  PD5
#define XPT_PIN PD4
#define RD_IDLE
#define WR_IDLE
#else
#warning using regular SPI hardware
#define CD_PORT PORTB
#define CD_PIN  1
#define CS_PORT PORTB
#define CS_PIN  2
#define RESET_PORT PORTB
#define RESET_PIN  0
#define RD_IDLE
#define WR_IDLE
#endif

#define setWriteDir() { }
#define setReadDir()  { }
//#define write8(x)     spi_xfer(x)
#define write16(x)    { uint8_t h = (x)>>8, l = x; write8(h); write8(l); }
#define READ_8(dst)   { dst = xchg8(0); }
#define READ_16(dst)  { dst = xchg8(0); dst = (dst << 8) | xchg8(0);  }

#define PIN_LOW(p, b)        (p) &= ~(1<<(b))
#define PIN_HIGH(p, b)       (p) |= (1<<(b))
#define PIN_OUTPUT(p, b)     *(&p-1) |= (1<<(b))
#elif defined(__SAMD21G18A__)

#define SPI_INIT()   { SPI.begin(); SPI.setDataMode(SPI_MODE0); SPI.setClockDivider(6); }

#define CD_PORT PORT->Group[0]
#define CD_PIN  7
#define CS_PORT PORT->Group[0]
#define CS_PIN  18
#define RESET_PORT PORT->Group[0]
#define RESET_PIN  6
#define RD_IDLE
#define WR_IDLE


uint8_t running;
static inline void write8(uint8_t c)
{
  running = 1;
  while( SERCOM1->SPI.INTFLAG.bit.DRE == 0) ;
  SERCOM1->SPI.DATA.bit.DATA = c; // Writing data into Data register
}

static inline void flush(void)
{
  if (running) while( SERCOM1->SPI.INTFLAG.bit.TXC == 0) ;
  running = 0;
}

static inline uint8_t xchg8(uint8_t c)
{
//  flush();
  while( SERCOM1->SPI.INTFLAG.bit.RXC != 0) SERCOM1->SPI.DATA.bit.DATA; //eat up
  while( SERCOM1->SPI.INTFLAG.bit.DRE == 0) ;
  SERCOM1->SPI.DATA.bit.DATA = c; // Writing data into Data register
  while( SERCOM1->SPI.INTFLAG.bit.RXC == 0) ;
  return SERCOM1->SPI.DATA.bit.DATA;
}


#define setWriteDir() { }
#define setReadDir()  { }
//#define flush()
//#define write8(x) xchg8(x)
//#define xchg8(x)     SPI.transfer(x)
#define write16(x)    { uint8_t h = (x)>>8, l = x; write8(h); write8(l); }
#define READ_8(dst)   { dst = xchg8(0); }
#define READ_16(dst)  { dst = xchg8(0); dst = (dst << 8) | xchg8(0);  }

// Shield Control macros.
#define PIN_LOW(port, pin)    (port).OUTCLR.reg = (1<<(pin))
#define PIN_HIGH(port, pin)   (port).OUTSET.reg = (1<<(pin))
#define PIN_OUTPUT(port, pin) (port).DIR.reg |= (1<<(pin))

#elif defined(__AVR_ATxmega128A1__)     //3.49s @ 32MHz -O2
  #define CD_PORT VPORT2
  #define CD_PIN  1
  #define CS_PORT VPORT3
  #define CS_PIN  4
  #define RESET_PORT VPORT2
  #define RESET_PIN  0
#define SPCRVAL (USART_CLK2X_bm | USART_RXEN_bm | USART_TXEN_bm)
#define SETDDR  {VPORT3.DIR |= (1<<4)|(1<<5)|(1<<7); VPORT2.DIR |= 0x03; }
#define SPI_INIT()  { PORTCFG.VPCTRLB=PORTCFG_VP3MAP_PORTF_gc | PORTCFG_VP2MAP_PORTC_gc; CS_IDLE; RESET_IDLE; SETDDR; spi_init(); }

void spi_init(void)
{
   SPIF.CTRL=SPI_ENABLE_bm | SPI_MODE_3_gc | (1<<SPI_MASTER_bp) | (1<<SPI_CLK2X_bp);
}

#define write8(x)    {\
						 SPIF.DATA=x;\
                         while ((SPIF.STATUS & SPI_IF_bm)==0);\
                         SPIF.DATA;\
                     }
#define flush()   {\
                  }

#define PIN_LOW(p, b)        (p).OUT &= ~(1<<(b))
#define PIN_HIGH(p, b)       (p).OUT |= (1<<(b))
#define PIN_OUTPUT(p, b)     (p).DIR |= (1<<(b))

#elif defined(__AVR_ATxmega32A4U__)     //3.49s @ 32MHz -O2.  
// 100ns/150ns for ILI9341 W/R cycle.   100ns/200ns for ILI920.  20ns/150ns HX8347
// Xmega @ 60MHz i.e. 30MHz SCK works with 9341.
#warning Using ATxmega32A4U USART_MSPI
  #define CD_PORT VPORT2
  #define CD_PIN  1
  #define CS_PORT VPORT3
  #define CS_PIN  0
  #define RESET_PORT VPORT2
  #define RESET_PIN  0
  #define SD_PORT    PORTC
  #define SD_PIN     4
#define SPCRVAL (USART_CLK2X_bm | USART_RXEN_bm | USART_TXEN_bm)
#define SETDDR  {PORTCFG.VPCTRLB=PORTCFG_VP13MAP_PORTD_gc | PORTCFG_VP02MAP_PORTC_gc; VPORT3.DIR |= (1<<0)|(1<<1)|(1<<3); VPORT2.DIR |= 0x03; PIN_HIGH(SD_PORT, SD_PIN); SD_PORT.DIR |= (1<<SD_PIN); }
#define SPI_INIT()  { CS_IDLE; RESET_IDLE; SETDDR; spi_init(); }

static inline void spi_init(void)
{
   USARTD0.CTRLB = SPCRVAL;
   USARTD0.CTRLC = USART_CMODE_MSPI_gc | 0x00 | 0x00;   //mode #0 
//   PORTD.PIN1CTRL |= PORT_INVEN_bm;   //CPOL
   USARTD0.BAUDCTRLA = 0x00;     //F_CPU/2
   USARTD0.BAUDCTRLB = ((0x00 << USART_BSCALE_gp) & USART_BSCALE_gm) | 0x00;
   USARTD0.DATA; 
}

extern uint8_t running;

#define write8(x)    {\
						 while ((USARTD0.STATUS & USART_DREIF_bm) == 0) ;\
                         asm("cli");\
						 USARTD0.DATA = x;\
						 USARTD0.STATUS = USART_TXCIF_bm;\
						 asm("sei");\
						 running = 1;\
                     }
static inline uint8_t read8(void)    {
                         if (running) while ((USARTD0.STATUS & USART_RXCIF_bm) == 0) ;
						 return USARTD0.DATA;
                     }
#define flush()   {\
                         if (running) while ((USARTD0.STATUS & USART_TXCIF_bm) == 0) ;\
						 while ((USARTD0.STATUS & USART_RXCIF_bm) != 0) USARTD0.DATA;\
						 running = 0;\
                  }
static inline uint8_t xchg8(uint8_t x)    {
						 USARTD0.DATA = x;
                         while ((USARTD0.STATUS & USART_RXCIF_bm) == 0) ;
						 return USARTD0.DATA;
                     }
/*
#define write8(x)    {\
                         while ((USARTD0.STATUS & USART_DREIF_bm) == 0) ;\
                         USARTD0.DATA = x;\
                         while ((USARTD0.STATUS & USART_RXCIF_bm) == 0) ;\
                         USARTD0.DATA;\
                     }
#define flush()
*/

#define RD_IDLE
#define WR_IDLE
//#define SPI_INIT()    spi_init()
#define setWriteDir() { }
#define setReadDir()  { }
//#define write8(x)     spi_xfer(x)
#define write16(x)    { uint8_t h = (x)>>8, l = x; write8(h); write8(l); }
#define READ_8(dst)   { dst = xchg8(0); }
#define READ_16(dst)  { dst = xchg8(0); dst = (dst << 8) | xchg8(0);  }

#define PIN_LOW(p, b)        (p).OUT &= ~(1<<(b))
#define PIN_HIGH(p, b)       (p).OUT |= (1<<(b))
#define PIN_OUTPUT(p, b)     (p).DIR |= (1<<(b))

#endif

#define CD_COMMAND {flush(); PIN_LOW(CD_PORT, CD_PIN); }
#define CD_DATA    {flush(); PIN_HIGH(CD_PORT, CD_PIN); }
#define CD_OUTPUT  PIN_OUTPUT(CD_PORT, CD_PIN)
#define CS_ACTIVE  PIN_LOW(CS_PORT, CS_PIN)
#define CS_IDLE    {flush(); PIN_HIGH(CS_PORT, CS_PIN); }
#define CS_OUTPUT  PIN_OUTPUT(CS_PORT, CS_PIN)
#define RESET_ACTIVE  PIN_LOW(RESET_PORT, RESET_PIN)
#define RESET_IDLE    PIN_HIGH(RESET_PORT, RESET_PIN)
#define RESET_OUTPUT  PIN_OUTPUT(RESET_PORT, RESET_PIN)

// General macros.   IOCLR registers are 1 cycle when optimised.

#define CTL_INIT()   { CD_OUTPUT; CS_OUTPUT; RESET_OUTPUT; SPI_INIT(); }
#define WriteCmd(x)  { CD_COMMAND; write8(x); }
#define WriteData(x) { CD_DATA; write16(x); }
