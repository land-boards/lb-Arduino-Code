/*!
 * @file asserts.h
 */
#ifndef _ASSERTS_H_
#define _ASSERTS_H_

#include "errors.h"

/**************************************************************************/
/*!
    @brief Checks the condition, and if the assert fails the supplied
           returnValue will be returned in the calling function.

    @code
    // Make sure 'addr' is within range
    ASSERT(addr <= MAX_ADDR, ERROR_ADDRESSOUTOFRANGE);
    @endcode
*/
/**************************************************************************/
#define ASSERT(condition, returnValue)                                         \
  do {                                                                         \
    if (!(condition)) {                                                        \
      return (returnValue);                                                    \
    }                                                                          \
  } while (0)

/**************************************************************************/
/*!
    @brief  Checks the supplied \ref err_t value (sts), and if it is
            not equal to \ref ERROR_NONE the sts value will be returned.

    @details
    This macro is useful to check if a function returned an error without
    bloating your own code with endless "if (error) {...}".

    @code
    // If anything other than ERROR_NONE is returned by tsl2561Enable()
    // this macro will log the error and exit the function returning the
    // error_t value.
    ASSERT_STATUS(tsl2561Enable());
    @endcode
*/
/**************************************************************************/
#define ASSERT_STATUS(sts)                                                     \
  do {                                                                         \
    err_t status = (sts);                                                      \
    if (ERROR_NONE != status) {                                                \
      return status;                                                           \
    }                                                                          \
  } while (0)

#endif
