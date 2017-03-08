#elif defined(__SAM3X8E__) && defined(USE_MEGA_16BIT_SHIELD)  //regular CTE shield on DUE
#warning USE_MEGA_16BIT_SHIELD
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
#define write_16(VL)   { PIOA->PIO_CODR = AMASK; PIOB->PIO_CODR = BMASK; PIOC->PIO_CODR = CMASK; PIOD->PIO_CODR = DMASK; \
		REG_PIOA_SODR=(((((VL)>>8) & 0x06)<<13) | ((VL & 0x40)<<1);\
		(((VL)>>8) & 0x01) ? REG_PIOB_SODR = 0x4000000 : REG_PIOB_CODR = 0x4000000;\
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
#define write16(x)    { write_16(x); WR_ACTIVE; WR_STROBE; WR_IDLE; WR_IDLE; }
#define READ_16(dst)  { RD_STROBE; RD_ACTIVE; RD_ACTIVE; RD_ACTIVE; RD_ACTIVE; dst = read_16(); RD_IDLE; RD_IDLE; RD_IDLE; }
#define READ_8(dst)   { READ_16(dst); dst &= 0xFF; }

// Shield Control macros.
#define PIN_LOW(port, pin)    (port)->PIO_CODR = (1<<(pin))
#define PIN_HIGH(port, pin)   (port)->PIO_SODR = (1<<(pin))
#define PIN_OUTPUT(port, pin) (port)->PIO_OER = (1<<(pin))

