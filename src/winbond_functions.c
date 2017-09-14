/*
 * file: winbond_functions.h
 *
 * Functions for handling Windond W25Q128 SPI EEPROM.
 */

#include <stdint.h>
#include "winbond_functions.h"
#include "winbond_defines.h"
#include "ports.h"
// DEBUG
#include <stdio.h>

/* readSR: Read Status Register 1-3
 *
 * Args: reg: Status Register number. 1-3
 * 		 data: Pointer to variable to save data
 * Return: error status. '0' on success.
 */
uint8_t readSR(uint8_t reg, uint8_t *data){
	// Read status register 1-3 specified by 'reg'
	//
	// Returns error condition: '1' if error
	uint8_t buffer[2];
	switch (reg){
	case 1:
		buffer[0] = INS_READ_SR1;
		break;
	case 2:
		buffer[0] = INS_READ_SR2;
		break;
	case 3:
		buffer[0] = INS_READ_SR3;
		break;
	default:
		// Error condition
		return 1;	
	}
	spiRW(buffer, 2);
	
	*data = buffer[1];
	return 0;
}


/* writeSR: Write Status Register 1-3
 *
 * Args: reg: Status Register number. 1-3
 * 		 data: Pointer to variable to read data from
 * Return: error status. '0' on success.
 */
uint8_t writeSR(uint8_t reg, uint8_t data){
	// Write status register 1-3 specified by 'reg'
	//
	// Returns error condition: '1' if error
	uint8_t buffer[2];
	uint8_t we = INS_WRITE_ENABLE;

	switch (reg){
	case 1:
		buffer[0] = INS_WRITE_SR1;
		break;
	case 2:
		buffer[0] = INS_WRITE_SR2;
		break;
	case 3:
		buffer[0] = INS_WRITE_SR3;
		break;
	default:
		// Error condition
		printf("Received wrong reg value: %d\n", reg);
		return 1;	
	}

	// Unlock Write access to SR first
	spiWrite(&we, 1);

	// Debug:
	readSR(1, &we);
	if(!(we & SR1_WEL)){
		printf("writeSR: ERROR: Unable to get write access to SPI dev!\n");
		return 1;
	}

	buffer[1] = data;
	spiWrite(buffer, 2);	
	return 0;
}


/* waitSPIAvailable: Wait until SPI device is not busy anymore
 *
 * This function will lock for the busy interval. It wil return when SPI is
 * available again
 */
void waitSPIAvailable(void){
	uint8_t sr1 = 0;
	while(1){
		readSR(1, &sr1);
		if (!(sr1 & SR1_BUSY)){
			break;
		}
	}
}
