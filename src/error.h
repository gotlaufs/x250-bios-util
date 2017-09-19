/* 
 * File: error.h
 *
 * Error codes and error examine function prorotype.
 *
 */

#ifndef _ERROR_H_
#define _ERROR_H_

#define ERROR_NO_ERROR 0

// Avoiding common 'errno'
extern uint8_t errvar;

/* printError: Decode global 'errvar' and print error message
 *
 * This will print out to stderr.
 */
void printError(void);

#endif // _ERROR_H_