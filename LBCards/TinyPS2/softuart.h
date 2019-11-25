/*--------------------------------------------------------------------------*
* Software UART for ATtiny processors
*---------------------------------------------------------------------------*
* 14-Apr-2014 ShaneG
*
* Provides an implementation of a UART for serial communications. Includes
* some formatted output utility functions and debug output support.
*--------------------------------------------------------------------------*/
#ifndef __SOFTUART_H
#define __SOFTUART_H

//--- Required definitions
#include <stdint.h>
#include <avr/pgmspace.h>

#ifdef __cplusplus
extern "C" {
#endif

//---------------------------------------------------------------------------
// Core operations
//---------------------------------------------------------------------------

/** Initialise the UART
 */
void uartInit();

/** Write a single character
 *
 * Send a single character on the UART.
 *
 * @param ch the character to send.
 */
void uartSend(char ch);

/** Determine if characters are available
 *
 * Check the number of characters available for immediate reading. If this
 * function returns a non-zero value the next call to uartRecv() will be
 * guaranteed to return immediately with a value. This function is only valid
 * if you are using the interrupt driven version of the UART.
 *
 * @return the number of characters available in the input buffer.
 */
uint8_t uartAvail();

/** Receive a single character
 *
 * Wait for a single character on the UART and return it. If data is not
 * immediately available this function will block until data has been
 * received.
 *
 * @return the character received.
 */
char uartRecv();

//---------------------------------------------------------------------------
// Basic output for data types.
//---------------------------------------------------------------------------

/** Print a string from RAM
 *
 * This function simply prints the nul terminated string from RAM to the
 * serial port.
 *
 * @param cszString pointer to a character array in RAM.
 */
void uartPrint(const char *cszString);

/** Print a string from PROGMEM
 *
 * This function simply prints the nul terminated string from PROGMEM to the
 * serial port.
 *
 * @param cszString pointer to a character array in PROGMEM.
 */
void uartPrintP(const char *cszString);

/** Print an unsigned 16 bit value in decimal
 *
 * Print the given value in decimal format to the UART.
 *
 * @param value the value to print.
 */
void uartInt(uint16_t value);

/** Print an unsigned 16 bit value in hexadecimal
 *
 * Print the given value in hexadecimal format to the UART.
 *
 * @param value the value to print.
 */
void uartHex(uint16_t value);

//---------------------------------------------------------------------------
// Formatted output
//---------------------------------------------------------------------------

/** Print a formatted string from RAM
 *
 * Prints a formatted string from RAM to the serial port. This function
 * supports a subset of the 'printf' string formatting syntax. Allowable
 * insertion types are:
 *
 *  %% - Display a % character. There should be no entry in the variable
 *       argument list for this entry.
 *  %u - Display an unsigned integer in decimal. The matching argument may
 *       be any 16 bit value.
 *  %x - Display an unsigned integer in hexadecimal. The matching argument may
 *       be any 16 bit value.
 *  %c - Display a single ASCII character. The matching argument may be any 8
 *       bit value.
 *  %s - Display a NUL terminated string from RAM. The matching argument must
 *       be a pointer to a RAM location.
 *  %S - Display a NUL terminated string from PROGMEM. The matching argument
 *       must be a pointer to a PROGMEM location.
 *
 * @param cszString pointer to a nul terminated format string in RAM.
 */
void uartFormat(const char *cszString, ...);

/** Print a formatted string from PROGMEM
 *
 * Prints a formatted string from PROGMEM to the serial port. This function
 * supports a subset of the 'printf' string formatting syntax. Allowable
 * insertion types are:
 *
 *  %% - Display a % character. There should be no entry in the variable
 *       argument list for this entry.
 *  %u - Display an unsigned integer in decimal. The matching argument may
 *       be any 16 bit value.
 *  %x - Display an unsigned integer in hexadecimal. The matching argument may
 *       be any 16 bit value.
 *  %c - Display a single ASCII character. The matching argument may be any 8
 *       bit value.
 *  %s - Display a NUL terminated string from RAM. The matching argument must
 *       be a pointer to a RAM location.
 *  %S - Display a NUL terminated string from PROGMEM. The matching argument
 *       must be a pointer to a PROGMEM location.
 *
 * @param cszString pointer to a nul terminated format string in PROGMEM.
 */
void uartFormatP(const char *cszString, ...);

//---------------------------------------------------------------------------
// Debugging output support (requires formatted print functions)
//---------------------------------------------------------------------------

#if defined(DEBUG)
#  define PRINT(msg)       uartPrintP(PSTR("DEBUG: ")), uartPrintP(PSTR(msg))
#  define PRINTF(fmt, ...) uartPrintP(PSTR("DEBUG: ")), uartFormatP(PSTR(fmt), __VA_ARGS__)
#else
#  define PRINT(msg)
#  define PRINTF(fmt, ...)
#endif

#ifdef __cplusplus
}
#endif

#endif /* __SOFTUART_H */
