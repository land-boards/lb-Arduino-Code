#ifndef UART_ADDON_H
#define UART_ADDON_H
/************************************************************************
Title:     UART addon-library 
Author:    Martin Thomas <eversmith@heizung-thomas.de>   
           http://www.siwawi.arubi.uni-kl.de/avr_projects
Software:  AVR-GCC 3.3/3.4, Peter Fleury's UART-Library
************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/** 
 *  @defgroup UART library-addon
 *  @code #include <uart_addon.h> @endcode
 * 
 *  @brief Additional functions for send numbers as decimal and hex to UART
 *
 *  @note needs Peter Fleury's UART-Library http://jump.to/fleury
 *  @author  Martin Thomas eversmith@heizung-thomas.de   
 */
 
/*@{*/

/**
 * @brief    Put long integer to ringbuffer for transmitting via UART.
 *
 * The integer is converted to a string which is buffered by the uart 
 * library in a circular buffer and one character at a time is transmitted 
 * to the UART using interrupts.
 *
 * @param    value to transfer
 * @return   none
 * @see      uart_puts_p
 */
extern void uart_put_longint( long int i );


/**
 * @brief    Put unsigned long integer to ringbuffer for transmitting via UART.
 *
 * The integer is converted to a string which is buffered by the uart 
 * library in a circular buffer and one character at a time is transmitted 
 * to the UART using interrupts.
 *
 * @param    value to transfer
 * @return   none
 * @see      uart_puts_p
 */
extern void uart_put_ulongint( unsigned long int i );


/**
 * @brief    Put integer to ringbuffer for transmitting via UART.
 *
 * The integer is converted to a string which is buffered by the uart 
 * library in a circular buffer and one character at a time is transmitted 
 * to the UART using interrupts.
 *
 * @param    value to transfer
 * @return   none
 * @see      uart_puts_p
 */
extern void uart_put_int( int i );


/**
 * @brief    Put nibble as hex to ringbuffer for transmit via UART.
 *
 * The lower nibble of the parameter is convertet to correspondig
 * hex-char and put in a circular buffer and one character at a time 
 * is transmitted to the UART using interrupts.
 *
 * @param    value to transfer (byte, only lower nibble converted)
 * @return   none
 * @see      uart_putc
 */
extern void uart_puthex_nibble( const unsigned char b );

/**
 * @brief    Put byte as hex to ringbuffer for transmit via UART.
 *
 * The upper and lower nibble of the parameter are convertet to 
 * correspondig hex-chars and put in a circular buffer and one 
 * character at a time is transmitted to the UART using interrupts.
 *
 * @param    value to transfer
 * @return   none
 * @see      uart_puthex_nibble
 */
extern void uart_puthex_byte( const unsigned char b );

/**
 * @brief    Put unsigned long as ASCII to ringbuffer for transmit via UART.
 *
 * @param    value to transfer
 * @return   none
 * @see      none
 */
extern void uart_puthex_long( unsigned long l );

/**
 * @brief    Put byte as bin to ringbuffer for transmit via UART.
 *
 * @param    value to transfer
 * @return   none
 * @see      uart_putc
 */
extern void uart_putbin_byte( const unsigned char b );


/*@}*/

#ifdef __cplusplus
}
#endif


#endif /* UART_ADDON_H */

