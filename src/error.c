/* 
 * File: error.c
 *
 * Implementation of printError() function
 *
 */
#include <stdio.h>
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
