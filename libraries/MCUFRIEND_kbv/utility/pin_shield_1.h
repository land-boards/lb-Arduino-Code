#ifndef PIN_SHIELD_1_H_
#define PIN_SHIELD_1_H_

// just provide macros for the Arduino pins
// i.e. PIN_LOW(), PIN_HIGH(), PIN_OUTPUT(), PIN_INPUT(), PIN_READ()

#define LPC810  810
#define LPC812  812
#define LPC1343 1343
#define LPC1768 1768
#define LPC2103 2103
#define LPC2148 2148
//#warning Using pin_SHIELD_1.h

#if 0
#elif defined(MY_BLUEPILL)
#define PIN_MODE2(reg, pin, mode) reg=(reg&~(0x3<<((pin)<<1)))|(mode<<((pin)<<1))
  #if defined(__CC_ARM)
  #include <STM32F10X.h>
  #else
  #include <STM32F1XX.h>
  #endif
  #define D0_PORT GPIOB
  #define D0_PIN  11
  #define D1_PORT GPIOB
  #define D1_PIN  10
  #define D2_PORT GPIOB
  #define D2_PIN  6
  #define D3_PORT GPIOB
  #define D3_PIN  7
  #define D4_PORT GPIOA
  #define D4_PIN  0
  #define D5_PORT GPIOA
  #define D5_PIN  1
  #define D6_PORT GPIOA
  #define D6_PIN  2
  #define D7_PORT GPIOA
  #define D7_PIN  3
  #define D8_PORT GPIOA
  #define D8_PIN  9
  #define D9_PORT GPIOA
  #define D9_PIN  10
  #define D10_PORT GPIOB
  #define D10_PIN  12
  #define D11_PORT GPIOB
  #define D11_PIN  15
  #define D12_PORT GPIOB
  #define D12_PIN  14
  #define D13_PORT GPIOB
  #define D13_PIN  13
  #define A0_PORT GPIOB
  #define A0_PIN  1
  #define A1_PORT GPIOB
  #define A1_PIN  0
  #define A2_PORT GPIOA
  #define A2_PIN  7
  #define A3_PORT GPIOA
  #define A3_PIN  6
  #define A4_PORT GPIOA
  #define A4_PIN  5
  #define A5_PORT GPIOB
  #define A5_PIN  4
// Shield Control macros
#define PIN_LOW(port, pin)    (port)->BSRR = (1<<((pin)+16))
#define PIN_HIGH(port, pin)   (port)->BSRR = (1<<(pin))
#define PIN_READ(port, pin)   (port)->IDR & (1<<(pin))
#define PIN_MODE4(reg, pin, mode) reg=(reg&~(0xF<<((pin)<<2)))|(mode<<((pin)<<2))
#define PIN_OUTPUT(port, pin) {if (pin > 7) PIN_MODE4((port)->CRH, (pin&7), 0x3); else  PIN_MODE4((port)->CRL, pin, 0x3); } //50MHz push-pull only 0-7
#define PIN_INPUT(port, pin) {if (pin > 7) PIN_MODE4((port)->CRH, (pin&7), 0x4); else  PIN_MODE4((port)->CRL, pin, 0x4); }  //input


#elif defined(BLUEPILL)
#define PIN_MODE2(reg, pin, mode) reg=(reg&~(0x3<<((pin)<<1)))|(mode<<((pin)<<1))
  #if defined(__CC_ARM)
  #include <STM32F10X.h>
  #else
  #include <STM32F1XX.h>
  #endif
  #define D0_PORT GPIOA
  #define D0_PIN  10
  #define D1_PORT GPIOA
  #define D1_PIN  9
  #define D2_PORT GPIOA
  #define D2_PIN  2
  #define D3_PORT GPIOA
  #define D3_PIN  3
  #define D4_PORT GPIOA
  #define D4_PIN  4
  #define D5_PORT GPIOA
  #define D5_PIN  5
  #define D6_PORT GPIOA
  #define D6_PIN  6
  #define D7_PORT GPIOA
  #define D7_PIN  7
  #define D8_PORT GPIOA
  #define D8_PIN  0
  #define D9_PORT GPIOA
  #define D9_PIN  1
  #define D10_PORT GPIOB //GPIOA
  #define D10_PIN  12    //15
  #define D11_PORT GPIOB
  #define D11_PIN  15    //5
  #define D12_PORT GPIOB
  #define D12_PIN  14    //4
  #define D13_PORT GPIOB
  #define D13_PIN  13    //3
  #define A0_PORT GPIOB
  #define A0_PIN  5      //original pcb uses SPI pin 
//  #define A0_PIN  0      //hardware mod to Adapter to PB0.  Allows use of PB5 for SD Card
  #define A1_PORT GPIOB
  #define A1_PIN  6
  #define A2_PORT GPIOB
  #define A2_PIN  7
  #define A3_PORT GPIOB
  #define A3_PIN  8
  #define A4_PORT GPIOB
  #define A4_PIN  9
  #define A5_PORT GPIOB
  #define A5_PIN  10
// Shield Control macros
#define PIN_LOW(port, pin)    (port)->BSRR = (1<<((pin)+16))
#define PIN_HIGH(port, pin)   (port)->BSRR = (1<<(pin))
#define PIN_READ(port, pin)   (port)->IDR & (1<<(pin))
#define PIN_MODE4(reg, pin, mode) reg=(reg&~(0xF<<((pin)<<2)))|(mode<<((pin)<<2))
#define PIN_OUTPUT(port, pin) {if (pin > 7) PIN_MODE4((port)->CRH, (pin&7), 0x3); else  PIN_MODE4((port)->CRL, pin, 0x3); } //50MHz push-pull only 0-7
#define PIN_INPUT(port, pin) {if (pin > 7) PIN_MODE4((port)->CRH, (pin&7), 0x4); else  PIN_MODE4((port)->CRL, pin, 0x4); }  //input


#elif defined(ITEADMAPLE)
#define PIN_MODE2(reg, pin, mode) reg=(reg&~(0x3<<((pin)<<1)))|(mode<<((pin)<<1))
  #if defined(__CC_ARM)
  #include <STM32F10X.h>
  #else
  #include <STM32F1XX.h>
  #endif
  #define D0_PORT GPIOA
  #define D0_PIN  3
  #define D1_PORT GPIOA
  #define D1_PIN  2
  #define D2_PORT GPIOA
  #define D2_PIN  0
  #define D3_PORT GPIOA
  #define D3_PIN  1
  #define D4_PORT GPIOB
  #define D4_PIN  5
  #define D5_PORT GPIOB
  #define D5_PIN  6
  #define D6_PORT GPIOA
  #define D6_PIN  8
  #define D7_PORT GPIOA
  #define D7_PIN  9
  #define D8_PORT GPIOA
  #define D8_PIN  10
  #define D9_PORT GPIOB
  #define D9_PIN  7
  #define D10_PORT GPIOA
  #define D10_PIN  4
  #define D11_PORT GPIOA
  #define D11_PIN  7
  #define D12_PORT GPIOA
  #define D12_PIN  6
  #define D13_PORT GPIOA
  #define D13_PIN  5
  #define A0_PORT GPIOC
  #define A0_PIN  0
  #define A1_PORT GPIOC
  #define A1_PIN  1
  #define A2_PORT GPIOC
  #define A2_PIN  2
  #define A3_PORT GPIOC
  #define A3_PIN  3
  #define A4_PORT GPIOC
  #define A4_PIN  4
  #define A5_PORT GPIOC
  #define A5_PIN  5
// Shield Control macros
#define PIN_LOW(port, pin)    (port)->BSRR = (1<<((pin)+16))
#define PIN_HIGH(port, pin)   (port)->BSRR = (1<<(pin))
#define PIN_READ(port, pin)   (port)->IDR & (1<<(pin))
#define PIN_MODE4(reg, pin, mode) reg=(reg&~(0xF<<((pin)<<2)))|(mode<<((pin)<<2))
#define PIN_OUTPUT(port, pin) {if (pin > 7) PIN_MODE4((port)->CRH, (pin&7), 0x3); else  PIN_MODE4((port)->CRL, pin, 0x3); } //50MHz push-pull only 0-7
#define PIN_INPUT(port, pin) {if (pin > 7) PIN_MODE4((port)->CRH, (pin&7), 0x4); else  PIN_MODE4((port)->CRL, pin, 0x4); }  //input


#elif defined(NUCLEO) || defined(TARGET_NUCLEO_F072RB) || defined(TARGET_NUCLEO_F401RE) || defined(TARGET_NUCLEO_F411RE) || defined(TARGET_NUCLEO_F103RB) || defined(TARGET_NUCLEO_L476RG) || defined(TARGET_NUCLEO_F446RE)
#define PIN_MODE2(reg, pin, mode) reg=(reg&~(0x3<<((pin)<<1)))|(mode<<((pin)<<1))
#if __MBED__
#warning MBED knows everything
#elif defined(STM32F072xB)
  #include <STM32F0XX.h>
#elif defined(STM32F103xB)
  #if defined(__CC_ARM)
  #include <STM32F10X.h>
  #else
  #include <STM32F1XX.h>
  #endif
#elif defined(STM32L476xx)
  #include <STM32L4XX.h>
#elif defined(STM32F401xE) || defined(STM32F411xE) || defined(STM32F446xx)
  #include <STM32F4XX.h>
#endif
  #define D0_PORT GPIOA
  #define D0_PIN  3
  #define D1_PORT GPIOA
  #define D1_PIN  2
  #define D2_PORT GPIOA
  #define D2_PIN  10
  #define D3_PORT GPIOB
  #define D3_PIN  3
  #define D4_PORT GPIOB
  #define D4_PIN  5
  #define D5_PORT GPIOB
  #define D5_PIN  4
  #define D6_PORT GPIOB
  #define D6_PIN  10
  #define D7_PORT GPIOA
  #define D7_PIN  8
  #define D8_PORT GPIOA
  #define D8_PIN  9
  #define D9_PORT GPIOC
  #define D9_PIN  7
  #define D10_PORT GPIOB
  #define D10_PIN  6
  #define D11_PORT GPIOA
  #define D11_PIN  7
  #define D12_PORT GPIOA
  #define D12_PIN  6
  #define D13_PORT GPIOA
  #define D13_PIN  5
  #define A0_PORT GPIOA
  #define A0_PIN  0
  #define A1_PORT GPIOA
  #define A1_PIN  1
  #define A2_PORT GPIOA
  #define A2_PIN  4
  #define A3_PORT GPIOB
  #define A3_PIN  0
  #define A4_PORT GPIOC
  #define A4_PIN  1
  #define A5_PORT GPIOC
  #define A5_PIN  0
// Shield Control macros
#define PIN_LOW(port, pin)    (port)->BSRR = (1<<((pin)+16))
#define PIN_HIGH(port, pin)   (port)->BSRR = (1<<(pin))
//#define PIN_LOW(port, pin)    (port)->ODR &= ~(1<<(pin))
//#define PIN_HIGH(port, pin)   (port)->ODR |=  (1<<(pin))
#define PIN_READ(port, pin)   (port)->IDR & (1<<(pin))
#if defined(STM32F103xB)
  #warning STM32F103xB ******************************
#define PIN_MODE4(reg, pin, mode) reg=(reg&~(0xF<<((pin)<<2)))|(mode<<((pin)<<2))
#define PIN_OUTPUT(port, pin) PIN_MODE4((port)->CRL, pin, 0x3)   //50MHz push-pull only 0-7
#define PIN_INPUT(port, pin)  PIN_MODE4((port)->CRL, pin, 0x4)   //digital input 
#else
#define PIN_OUTPUT(port, pin) PIN_MODE2((port)->MODER, pin, 0x1)
#define PIN_INPUT(port, pin) PIN_MODE2((port)->MODER, pin, 0x0)   //.kbv check this
#endif

#elif __TARGET_PROCESSOR == LPC1768
  #include <LPC17xx.h>
// configure macros for the control pins
  #define D0_PORT LPC_GPIO0
  #define D0_PIN  3
  #define D1_PORT LPC_GPIO0
  #define D1_PIN  2
  #define D2_PORT LPC_GPIO0
  #define D2_PIN  24           //p16
  #define D3_PORT LPC_GPIO0
  #define D3_PIN  23           //p15
  #define D4_PORT LPC_GPIO0
  #define D4_PIN  16           //p14
  #define D5_PORT LPC_GPIO0
  #define D5_PIN  15           //p13
  #define D6_PORT LPC_GPIO0
  #define D6_PIN  17           //p12
  #define D7_PORT LPC_GPIO0
  #define D7_PIN  18           //p11
  #define D8_PORT LPC_GPIO0
  #define D8_PIN  1            //p10
  #define D9_PORT LPC_GPIO0
  #define D9_PIN  0            //p9
  #define D10_PORT LPC_GPIO0
  #define D10_PIN  6           //p8
  #define D11_PORT LPC_GPIO0
  #define D11_PIN  9           //p5
  #define D12_PORT LPC_GPIO0
  #define D12_PIN  8           //p6 miso
  #define D13_PORT LPC_GPIO0
  #define D13_PIN  7           //p7
  #define A0_PORT LPC_GPIO0
  #define A0_PIN  25           //p17
  #define A1_PORT LPC_GPIO0
  #define A1_PIN  26           //p18
  #define A2_PORT LPC_GPIO1
  #define A2_PIN  30           //p19
  #define A3_PORT LPC_GPIO1
  #define A3_PIN  31           //p20
  #define A4_PORT LPC_GPIO0
  #define A4_PIN  10           //p28
  #define A5_PORT LPC_GP100
  #define A5_PIN  11           //p27
// Shield Control macros
#define PIN_LOW(port, pin)    (port)->FIOCLR = (1u<<(pin))
#define PIN_HIGH(port, pin)   (port)->FIOSET = (1u<<(pin))
#define PIN_OUTPUT(port, pin) (port)->FIODIR |= (1u<<(pin))
#define PIN_INPUT(port, pin)  (port)->FIODIR &= ~(1u<<(pin))
#define PIN_READ(port, pin)   (port)->FIOPIN & (1u<<(pin))

#elif (defined(MK20D7) && defined(TEENSY)) || defined(TARGET_TEENSY3_1)
#if __MBED__
#warning MBED knows everything
#else
  #include <MK20D5.h>
#endif
  #define D0_PORT PTB
  #define D0_PIN  16
  #define D1_PORT PTB
  #define D1_PIN  17
  #define D2_PORT PTD
  #define D2_PIN  0
  #define D3_PORT PTA
  #define D3_PIN  12
  #define D4_PORT PTA
  #define D4_PIN  13
  #define D5_PORT PTD
  #define D5_PIN  7
  #define D6_PORT PTD
  #define D6_PIN  4
  #define D7_PORT PTD
  #define D7_PIN  2
  #define D8_PORT PTD
  #define D8_PIN  3
  #define D9_PORT PTC
  #define D9_PIN  3
  #define D10_PORT PTC
  #define D10_PIN  4
  #define D11_PORT PTC
  #define D11_PIN  6
  #define D12_PORT PTC
  #define D12_PIN  7
  #define D13_PORT PTC
  #define D13_PIN  5
  #define A0_PORT PTD
  #define A0_PIN  1
  #define A1_PORT PTC
  #define A1_PIN  0
  #define A2_PORT PTB
  #define A2_PIN  0
  #define A3_PORT PTB
  #define A3_PIN  1
  #define A4_PORT PTB
  #define A4_PIN  3
  #define A5_PORT PTB
  #define A5_PIN  2
// Shield Control macros.   Deliberately avoid the IOSET registers
#define PIN_LOW(port, pin)    (port)->PCOR =  (1<<(pin))
#define PIN_HIGH(port, pin)   (port)->PSOR =  (1<<(pin))
//#define PIN_LOW(port, pin)    (port)->PDOR &= ~(1<<(pin))
//#define PIN_HIGH(port, pin)   (port)->PDOR |=  (1<<(pin))
#define PIN_OUTPUT(port, pin) (port)->PDDR |= (1<<(pin))
#define PIN_INPUT(port, pin)  (port)->PDDR &= ~(1u<<(pin))
#define PIN_READ(port, pin)   (port)->PDIR & (1u<<(pin))


#elif defined(MKL25Z4) || defined(TARGET_KL25Z)
  #include <MKL25Z4.h>
  #define D0_PORT PTA
  #define D0_PIN  1
  #define D1_PORT PTA
  #define D1_PIN  2
  #define D2_PORT PTD
  #define D2_PIN  4
  #define D3_PORT PTA
  #define D3_PIN  12
  #define D4_PORT PTA
  #define D4_PIN  4
  #define D5_PORT PTA
  #define D5_PIN  5
  #define D6_PORT PTC
  #define D6_PIN  8
  #define D7_PORT PTC
  #define D7_PIN  9
  #define D8_PORT PTA
  #define D8_PIN  13
  #define D9_PORT PTD
  #define D9_PIN  5
  #define D10_PORT PTD
  #define D10_PIN  0
  #define D11_PORT PTD
  #define D11_PIN  2
  #define D12_PORT PTD
  #define D12_PIN  3
  #define D13_PORT PTD
  #define D13_PIN  1
  #define A0_PORT PTB
  #define A0_PIN  0
  #define A1_PORT PTB
  #define A1_PIN  1
  #define A2_PORT PTB
  #define A2_PIN  2
  #define A3_PORT PTB
  #define A3_PIN  3
  #define A4_PORT PTC
  #define A4_PIN  2
  #define A5_PORT PTC
  #define A5_PIN  1
// Shield Control macros.   Deliberately avoid the IOSET registers
#define PIN_LOW(port, pin)    (port)->PCOR =  (1<<(pin))
#define PIN_HIGH(port, pin)   (port)->PSOR =  (1<<(pin))
//#define PIN_LOW(port, pin)    (port)->PDOR &= ~(1<<(pin))
//#define PIN_HIGH(port, pin)   (port)->PDOR |=  (1<<(pin))
#define PIN_OUTPUT(port, pin) (port)->PDDR |= (1<<(pin))
#define PIN_INPUT(port, pin)  (port)->PDDR &= ~(1u<<(pin))
#define PIN_READ(port, pin)   (port)->PDIR & (1u<<(pin))

#elif defined(MKL26Z4)
  #include <MKL26Z4.h>
  #define D0_PORT PTA
  #define D0_PIN  1
  #define D1_PORT PTA
  #define D1_PIN  2
  #define D2_PORT PTD
  #define D2_PIN  3      //PTD4 on KL25
  #define D3_PORT PTA
  #define D3_PIN  12
  #define D4_PORT PTA
  #define D4_PIN  4
  #define D5_PORT PTA
  #define D5_PIN  5
  #define D6_PORT PTC
  #define D6_PIN  8
  #define D7_PORT PTC
  #define D7_PIN  9
  #define D8_PORT PTA
  #define D8_PIN  13
  #define D9_PORT PTD
  #define D9_PIN  2      //PTD5 on KL25
  #define D10_PORT PTD
  #define D10_PIN  4      //PTD0
  #define D11_PORT PTD
  #define D11_PIN  6      //PTD2
  #define D12_PORT PTD
  #define D12_PIN  7      //PTD3
  #define D13_PORT PTD
  #define D13_PIN  5      //PTD1
  #define A0_PORT PTB
  #define A0_PIN  0
  #define A1_PORT PTB
  #define A1_PIN  1
  #define A2_PORT PTB
  #define A2_PIN  2
  #define A3_PORT PTB
  #define A3_PIN  3
  #define A4_PORT PTC
  #define A4_PIN  2
  #define A5_PORT PTC
  #define A5_PIN  1
// Shield Control macros.   Deliberately avoid the IOSET registers
#define PIN_LOW(port, pin)    (port)->PCOR =  (1<<(pin))
#define PIN_HIGH(port, pin)   (port)->PSOR =  (1<<(pin))
//#define PIN_LOW(port, pin)    (port)->PDOR &= ~(1<<(pin))
//#define PIN_HIGH(port, pin)   (port)->PDOR |=  (1<<(pin))
#define PIN_OUTPUT(port, pin) (port)->PDDR |= (1<<(pin))
#define PIN_INPUT(port, pin)  (port)->PDDR &= ~(1u<<(pin))
#define PIN_READ(port, pin)   (port)->PDIR & (1u<<(pin))

#elif defined(MKL05Z4)
  #include <MKL05Z4.h>
  #define D0_PORT PTB
  #define D0_PIN  2
  #define D1_PORT PTB
  #define D1_PIN  1
  #define D2_PORT PTA
  #define D2_PIN  11
  #define D3_PORT PTB
  #define D3_PIN  5
  #define D4_PORT PTA
  #define D4_PIN  10
  #define D5_PORT PTA
  #define D5_PIN  12
  #define D6_PORT PTB
  #define D6_PIN  6
  #define D7_PORT PTB
  #define D7_PIN  7
  #define D8_PORT PTB
  #define D8_PIN  13
  #define D9_PORT PTB
  #define D9_PIN  5
  #define D10_PORT PTA
  #define D10_PIN  0
  #define D11_PORT PTA
  #define D11_PIN  2
  #define D12_PORT PTA
  #define D12_PIN  3
  #define D13_PORT PTB
  #define D13_PIN  1
  #define A0_PORT PTB
  #define A0_PIN  8
  #define A1_PORT PTB
  #define A1_PIN  9
  #define A2_PORT PTA
  #define A2_PIN  8
  #define A3_PORT PTA
  #define A3_PIN  0
  #define A4_PORT PTA
  #define A4_PIN  9
  #define A5_PORT PTB
  #define A5_PIN  13
// Shield Control macros
//#define PIN_LOW(port, pin)    (port)->PCOR =  (1<<(pin))
//#define PIN_HIGH(port, pin)   (port)->PSOR =  (1<<(pin))
#define PIN_LOW(port, pin)    (port)->PDOR &= ~(1<<(pin))
#define PIN_HIGH(port, pin)   (port)->PDOR |=  (1<<(pin))
#define PIN_OUTPUT(port, pin) (port)->PDDR |= (1<<(pin))
#define PIN_INPUT(port, pin)  (port)->PDDR &= ~(1u<<(pin))
#define PIN_READ(port, pin)   (port)->PDIR & (1u<<(pin))

#elif defined(MK20D5) || defined(TARGET_K20D50M)
  #include <MK20D5.h>
  #define D0_PORT PTE
  #define D0_PIN  1
  #define D1_PORT PTE
  #define D1_PIN  0
  #define D2_PORT PTA
  #define D2_PIN  5
  #define D3_PORT PTD
  #define D3_PIN  4
  #define D4_PORT PTC
  #define D4_PIN  8
  #define D5_PORT PTA
  #define D5_PIN  1
  #define D6_PORT PTC
  #define D6_PIN  3
  #define D7_PORT PTC
  #define D7_PIN  4
  #define D8_PORT PTA
  #define D8_PIN  12
  #define D9_PORT PTA
  #define D9_PIN  2
  #define D10_PORT PTC
  #define D10_PIN  2
  #define D11_PORT PTD
  #define D11_PIN  2
  #define D12_PORT PTD
  #define D12_PIN  3
  #define D13_PORT PTD
  #define D13_PIN  1
  #define A0_PORT PTC
  #define A0_PIN  0
  #define A1_PORT PTC
  #define A1_PIN  1
  #define A2_PORT PTD
  #define A2_PIN  6
  #define A3_PORT PTD
  #define A3_PIN  5
  #define A4_PORT PTB
  #define A4_PIN  1
  #define A5_PORT PTB
  #define A5_PIN  0
// Shield Control macros.   Deliberately avoid the IOSET registers
#define PIN_LOW(port, pin)    (port)->PCOR =  (1<<(pin))
#define PIN_HIGH(port, pin)   (port)->PSOR =  (1<<(pin))
//#define PIN_LOW(port, pin)    (port)->PDOR &= ~(1<<(pin))
//#define PIN_HIGH(port, pin)   (port)->PDOR |=  (1<<(pin))
#define PIN_OUTPUT(port, pin) (port)->PDDR |= (1<<(pin))
#define PIN_INPUT(port, pin)  (port)->PDDR &= ~(1u<<(pin))
#define PIN_READ(port, pin)   (port)->PDIR & (1u<<(pin))


#elif defined(ZERO)
  #include <samd21.h>
// configure macros for the data pins
#if defined(D21_XPRO)
  #define D0_PORT PORT->Group[1]
  #define D0_PIN  9
  #define D1_PORT PORT->Group[1]
  #define D1_PIN  8
  #define D2_PORT PORT->Group[1]
  #define D2_PIN  14
  #define D3_PORT PORT->Group[1]
  #define D3_PIN  2
  #define D4_PORT PORT->Group[1]
  #define D4_PIN  5
  #define D5_PORT PORT->Group[0]
  #define D5_PIN  21
  #define D6_PORT PORT->Group[1]
  #define D6_PIN  15
  #define D7_PORT PORT->Group[0]
  #define D7_PIN  17
  #define D8_PORT PORT->Group[1]
  #define D8_PIN  6
  #define D9_PORT PORT->Group[1]
  #define D9_PIN  7
  #define D10_PORT PORT->Group[0]
  #define D10_PIN  5
  #define D11_PORT PORT->Group[0]
  #define D11_PIN  6
  #define D12_PORT PORT->Group[0]
  #define D12_PIN  4
  #define D13_PORT PORT->Group[0]
  #define D13_PIN  7
  #define A0_PORT PORT->Group[1]
  #define A0_PIN  0
  #define A1_PORT PORT->Group[1]
  #define A1_PIN  1
  #define A2_PORT PORT->Group[0]
  #define A2_PIN  10
  #define A3_PORT PORT->Group[0]
  #define A3_PIN  11
  #define A4_PORT PORT->Group[0]
  #define A4_PIN  8
  #define A5_PORT PORT->Group[0]
  #define A5_PIN  9
#elif defined(M0_PRO)
  #define D0_PORT PORT->Group[0]
  #define D0_PIN  11
  #define D1_PORT PORT->Group[0]
  #define D1_PIN  10
  #define D2_PORT PORT->Group[0]
  #define D2_PIN  8
  #define D3_PORT PORT->Group[0]
  #define D3_PIN  9
  #define D4_PORT PORT->Group[0]
  #define D4_PIN  14
  #define D5_PORT PORT->Group[0]
  #define D5_PIN  15
  #define D6_PORT PORT->Group[0]
  #define D6_PIN  20
  #define D7_PORT PORT->Group[0]
  #define D7_PIN  21
  #define D8_PORT PORT->Group[0]
  #define D8_PIN  6
  #define D9_PORT PORT->Group[0]
  #define D9_PIN  7
  #define D10_PORT PORT->Group[0]
  #define D10_PIN  18
  #define D11_PORT PORT->Group[0]
  #define D11_PIN  16
  #define D12_PORT PORT->Group[0]
  #define D12_PIN  19
  #define D13_PORT PORT->Group[0]
  #define D13_PIN  17
  #define A0_PORT PORT->Group[0]
  #define A0_PIN  2
  #define A1_PORT PORT->Group[1]
  #define A1_PIN  8
  #define A2_PORT PORT->Group[1]
  #define A2_PIN  9
  #define A3_PORT PORT->Group[0]
  #define A3_PIN  4
  #define A4_PORT PORT->Group[0]
  #define A4_PIN  5
  #define A5_PORT PORT->Group[1]
  #define A5_PIN  2

#endif
// Shield Control macros.
#define PIN_LOW(port, pin)    (port).OUTCLR.reg = (1<<(pin))
#define PIN_HIGH(port, pin)   (port).OUTSET.reg = (1<<(pin))
#define PIN_OUTPUT(port, pin) (port).DIR.reg |= (1<<(pin))
#define PIN_INPUT(port, pin)  (port).DIR.reg &= ~(1u<<(pin))
#define PIN_READ(port, pin)   (port).IN.reg & (1u<<(pin))


#elif defined(__AVR_ATxmegaA4U__)
  #include <avr/io.h>
  // PD6, PD7 is used for USB.   I could have used PORTA for bus,  PORTC for MSPI, SPI and remap
    #define D0_PORT PORTE
  #define D0_PIN  2
  #define D1_PORT PORTE
  #define D1_PIN  3
  #define D2_PORT PORTC
  #define D2_PIN  2
  #define D3_PORT PORTC
  #define D3_PIN  3
  #define D4_PORT PORTC
  #define D4_PIN  4
  #define D5_PORT PORTC
  #define D5_PIN  5
  #define D6_PORT PORTC
  #define D6_PIN  6
  #define D7_PORT PORTC
  #define D7_PIN  7
  #define D8_PORT PORTC
  #define D8_PIN  0
  #define D9_PORT PORTC
  #define D9_PIN  1
  #define D10_PORT PORTD
  #define D10_PIN  0
  #define D11_PORT PORTD
  #define D11_PIN  3
  #define D12_PORT PORTD
  #define D12_PIN  2
  #define D13_PORT PORTD
  #define D13_PIN  1
  #define A0_PORT PORTB
  #define A0_PIN  0
  #define A1_PORT PORTB
  #define A1_PIN  1
  #define A2_PORT PORTB
  #define A2_PIN  2
  #define A3_PORT PORTB
  #define A3_PIN  3
  #define A4_PORT PORTE
  #define A4_PIN  0
  #define A5_PORT PORTE
  #define A5_PIN  1
// Shield Control macros.
#define PIN_LOW(port, pin)    (port).OUTCLR.reg = (1<<(pin))
#define PIN_HIGH(port, pin)   (port).OUTSET.reg = (1<<(pin))
#define PIN_OUTPUT(port, pin) (port).DIR.reg |= (1<<(pin))
#define PIN_INPUT(port, pin)  (port).DIR.reg &= ~(1u<<(pin))
#define PIN_READ(port, pin)   (port).IN.reg & (1u<<(pin))


#elif defined(__AVR_ATtiny1634__)
  #include <avr/io.h>
  // 
  #define D0_PORT PORTA //PA7
  #define D0_PIN  7
  #define D1_PORT PORTB //PB0
  #define D1_PIN  0
  #define D2_PORT PORTC //PC2
  #define D2_PIN  2
  #define D3_PORT PORTA //PA3
  #define D3_PIN  3
  #define D4_PORT PORTA //PA4
  #define D4_PIN  4
  #define D5_PORT PORTC //PC4
  #define D5_PIN  4
  #define D6_PORT PORTA //PA1
  #define D6_PIN  1
  #define D7_PORT PORTA //PA0
  #define D7_PIN  0
  #define D8_PORT PORTA //PA2
  #define D8_PIN  2
  #define D9_PORT PORTC //PC5
  #define D9_PIN  5
  #define D10_PORT PORTA //PA6
  #define D10_PIN  6
  #define D11_PORT PORTB //PB2
  #define D11_PIN  2
  #define D12_PORT PORTB //PB1
  #define D12_PIN  1
  #define D13_PORT PORTC //PC1
  #define D13_PIN  1
  #define A0_PORT PORTB //PB3
  #define A0_PIN  3
  #define A1_PORT PORTC //PC0
  #define A1_PIN  0
  #define A2_PORT PORTA //PA5
  #define A2_PIN  5
  #define A3_PORT PORTB //PB2
  #define A3_PIN  2
  #define A4_PORT PORTB //PB1
  #define A4_PIN  1
  #define A5_PORT PORTC //PC1
  #define A5_PIN  1
#else
#error MCU unselected
#endif        // MCUs

#endif     //PIN_SHIELD_1_H
#if 0
#if defined(M0_PRO)
#endif
#if defined(D21_XPRO)
#endif
#endif
