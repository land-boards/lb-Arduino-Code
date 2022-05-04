/*--------------------------------------------------------------------------*
* Internal configuration for software UART implementation
*---------------------------------------------------------------------------*
* 14-Apr-2014 ShaneG
*
* Provides additional configuration for the software UART implementation
* based on the values set in 'hardware.h'.
*--------------------------------------------------------------------------*/
#ifndef __UART_DEFS_H
#define __UART_DEFS_H

// See what mode we are in
#if UART_TX == UART_RX
#  define UART_ONEPIN
#  undef  UART_INTERRUPT
#else
#  define UART_TWOPIN
#endif

// Calculate delays for the bit bashing functions
#ifdef F_CPU
/* account for integer truncation by adding 3/2 = 1.5 */
#  define TXDELAY   (int)(((F_CPU/BAUD_RATE)-7 +1.5)/3)
#  define RXDELAY   (int)(((F_CPU/BAUD_RATE)-5 +1.5)/3)
#  ifdef UART_INTERRUPT
     // Reduce the stop bit delay to allow for ISR entry code
#    define RXDELAY2  (int)(((RXDELAY*1.5)-2.5) - 8)
#  else
#    define RXDELAY2  (int)((RXDELAY*1.5)-2.5)
#  endif
#  define RXROUNDED (((F_CPU/BAUD_RATE)-5 +2)/3)
#  if RXROUNDED > 127
#    error low baud rates unsupported - use higher BAUD_RATE
#  endif
#else
#  error CPU frequency F_CPU undefined
#endif

#endif /* __UART_DEFS_H */
