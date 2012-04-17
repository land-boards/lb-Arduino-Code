/*************************************************************************
Title:     UART addon-library 
Author:    Martin Thomas <eversmith@heizung-thomas.de>   
           http://www.siwawi.arubi.uni-kl.de/avr_projects
Software:  AVR-GCC 3.3/3.4, Peter Fleury's UART-Library

DESCRIPTION:
    
USAGE:
    Refere to the header file uart_addon.h for a description of the routines. 

*************************************************************************/

#include <stdlib.h>

#include <avr/io.h>
#include "uart.h"


/*************************************************************************
Function: uart_put_int()
Purpose:  transmit integer as ASCII to UART
Input:    integer value
Returns:  none
**************************************************************************/
void uart_put_int( const int val )
{
	char buffer[10];
	uart_puts( itoa( val, buffer, 10 ) );
} /* uart_puti */

/*************************************************************************
Function: uart_put_longint()
Purpose:  transmit long integer as ASCII to UART
Input:    integer value
Returns:  none
**************************************************************************/
void uart_put_longint( const long int val )
{
	char buffer[15];
	uart_puts( ltoa( val, buffer, 10 ) );
} /* uart_puti */

/*************************************************************************
Function: uart_put_ulongint()
Purpose:  transmit long integer as ASCII to UART
Input:    integer value
Returns:  none
**************************************************************************/
void uart_put_ulongint( const unsigned long int val )
{
	char buffer[15];
	uart_puts( utoa( val, buffer, 10 ) );
} /* uart_puti */

/*************************************************************************
Function: uart_puthex_nibble()
Purpose:  transmit lower nibble as ASCII-hex to UART
Input:    byte value
Returns:  none
**************************************************************************/
void uart_puthex_nibble(const unsigned char b)
{
	unsigned char  c = b & 0x0f;
	if ( c > 9 ) { 
		c += 'A'-10; 
	}
	else {
		c += '0';
	}
	uart_putc(c);
} /* uart_puthex_nibble */

/*************************************************************************
Function: uart_puthex_byte()
Purpose:  transmit upper and lower nibble as ASCII-hex to UART
Input:    byte value
Returns:  none
**************************************************************************/
void uart_puthex_byte( const unsigned char  b )
{
	uart_puthex_nibble( b >> 4 );
	uart_puthex_nibble( b );
} /* uart_puthex_byte */

/*************************************************************************
Function: uart_puthex_long()
Purpose:  transmit unsigned long as ASCII-hex to UART
Input:    uint32_t value
Returns:  none
**************************************************************************/
void uart_puthex_long( const unsigned long l )
{
	uart_puthex_byte( (unsigned char)( l >> 24 ) );
	uart_puthex_byte( (unsigned char)( l >> 16 ) );
	uart_puthex_byte( (unsigned char)( l >> 8 ) );
	uart_puthex_byte( (unsigned char)( l ) );
} /* uart_puthex_byte */


/*************************************************************************
Function: uart_putbin_byte()
Purpose:  transmit byte as ASCII-bin to UART
Input:    byte value
Returns:  none
**************************************************************************/
void uart_putbin_byte( const unsigned char b )
{
	signed char i;
	for ( i= 7;i >= 0;i-- ) {
		if ( b & ( 1 << i ) ) {
			uart_putc( '1' );
		}
		else {
			uart_putc( '0' );
		}
	}
} /* uart_putbin_byte */
