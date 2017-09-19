/* 
 * File: error.h
 *
 * Error codes and error examine function prorotype.
 *
 */

#ifndef _ERROR_H_
#define _ERROR_H_

#define ERROR_NO_ERROR			0
#define ERROR_SPI_INIT_FAIL		10
#define ERROR_SPI_WRITE_FAIL	11
#define ERROR_SPI_WRITE_ENABLE	12

#define ERROR_REG_NOT_EXIST		20

#define ERROR_OUT_OF_BOUNDS 	30
#define ERROR_TOO_BIG_READ		31

#define ERROR_OPEN_FILE			40

// Avoiding common 'errno'
extern uint8_t errvar;

/* printError: Decode global 'errvar' and print error message
 *
 * This will print out to stderr.
 */
void printError(void);

#endif // _ERROR_H_
