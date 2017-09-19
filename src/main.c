#include <stdint.h>
#include <stdio.h>
#include "app_functions.h"
#include "error.h"

// Global error variable
uint8_t errvar = ERROR_NO_ERROR;

int main(){
	
	eepromDump();
	
	if (errvar != ERROR_NO_ERROR){
		printError();
		return 1;
	}
	else{
		printf("All done!\n");
		printf("Exiting..\n");
		return 0;
	}
}
