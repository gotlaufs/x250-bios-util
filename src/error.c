/* 
 * File: error.c
 *
 * Implementation of printError() function
 *
 */
#include <stdio.h>
#include <stdint.h>
#include "error.h"

void errForm(char *msg);

/* printError: Decode global 'errvar' and print error message
 *
 */
void printError(void){
	switch(errvar){
		case ERROR_NO_ERROR:
			errForm("No error");
			break;
		case ERROR_SPI_INIT_FAIL:
			errForm("Unable to initialize SPI inteface");
			break;
		case ERROR_SPI_WRITE_FAIL:
			errForm("Failed to write to SPI interface");
			break;
		case ERROR_SPI_WRITE_ENABLE:
			errForm("Failed to get write access to EEPROM chip");
		case ERROR_REG_NOT_EXIST:
			errForm("Register does not exist (wrong number)");
			break;
		case ERROR_OUT_OF_BOUNDS:
			errForm("Attempted to access memory out of bounds");
			break;
		case ERROR_OPEN_FILE:
			errForm("Unable to open file");
			break;
		default:
			errForm("Unknown error");
	}
}


/* errForm: Format and print out error message
 *
 * Args:	msg: String error message to print to stderr.
 * This is short wrapper for fprintf.
 *
 */
void errForm(char *msg){
	fprintf(stderr, "Error %d: %s\n", errvar, msg);
}
