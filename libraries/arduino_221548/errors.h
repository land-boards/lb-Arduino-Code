/*!
 * @file errors.h
 */

#ifndef _ERRORS_H_
#define _ERRORS_H_
/*!
 * GENERIC ERRORS                                         0x0000 .. 0x00FF
 *
 * -----------------------------------------------------------------------
 * These error codes can be used anywhere in the system
 */
typedef enum {
  ERROR_NONE = 0x0,              /**< Indicates no error occurred */
  ERROR_OPERATIONTIMEDOUT = 0x1, /**< Operation timed out before completion */
  ERROR_ADDRESSOUTOFRANGE = 0x2, /**< The supplied address is out of range */
  ERROR_BUFFEROVERFLOW =
      0x3, /**< The proposed action will cause a buffer overflow */
  ERROR_INVALIDPARAMETER = 0x4, /**< An invalid parameter value was provided */
  ERROR_DEVICENOTINITIALISED = 0x5, /**< Attempting to execute a function on an
                                       uninitialised peripheral */
  ERROR_UNEXPECTEDVALUE =
      0x6, /**< An unexpected value was found inside a function */
  /*=======================================================================*/

  /*=======================================================================
    I2C ERRORS                                             0x0100 .. 0x010F
    -----------------------------------------------------------------------
    Errors related to the I2C bus
    -----------------------------------------------------------------------*/
  ERROR_I2C_DEVICENOTFOUND =
      0x101,               /**< Device didn't ACK after an I2C transfer */
  ERROR_I2C_NOACK = 0x102, /**< No ACK signal received during an I2C transfer */
  ERROR_I2C_TIMEOUT =
      0x103, /**< Device timed out waiting for response (missing pullups?) */
  /*=======================================================================*/
} err_t;

#endif
