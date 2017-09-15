/*
 * file: winbond_functions.h
 *
 * Functions for handling Windond W25Q128 SPI EEPROM.
 */

#include <stdint.h>
#include <stdlib.h>
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
	
	if(spiRW(buffer, 2)){
		return 1;
	}
	else{
		*data = buffer[1];
		return 0;
	}

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
	if (writeEnable()){
		return 1;
	}

	buffer[1] = data;
	if (spiWrite(buffer, 2)){
		return 1;
	}	
	else{
		return 0;
	}
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


/* writeEnable: Enable write access to the chip
 *
 * This must be called before any write instruction to the device
 * Return: error status. '0' on success.
 */
uint8_t writeEnable(void){
	uint8_t we = INS_WRITE_ENABLE;
	// TODO: Add error checking
	spiWrite(&we, 1);

	// Debug:
	readSR(1, &we);
	if(!(we & SR1_WEL)){
		// printf("writeSR: ERROR: Unable to get write access to SPI dev!\n");
		return 1;
	}
	else{
		return 0;
	}
}


/* readData: Read some bytes of data into data buffer from address
 *	
 * Args: 	data: data buffer to read data into
 * 			num_bytes: number of bytes to read
 * 			address: data address to begin read. Address is 24-bits long
 * Return:	error status. '0' on success.
 *
 * Entire memory (up to address 'MEMORY_SIZE') can be read in single read
 */
uint8_t readData(uint8_t *data, uint32_t num_bytes, uint32_t address){
	uint32_t i;
	// Check if enough bytes in memory
	// TODO: Check if '>' or '>='
	if ((address + num_bytes) >= MEMORY_SIZE){
		// Out of bounds
		printf("max address = %x, Mem size = %x\n",
			 	address + num_bytes, MEMORY_SIZE);
		return 1;
	}

	uint8_t *buffer; 
	buffer = (uint8_t *) malloc(num_bytes + 4);

	// Assemble read instruction
	buffer[0] = INS_READ_DATA;
	buffer[1] = (uint8_t) address >> 16;
	buffer[2] = (uint8_t) address >> 8;
	buffer[3] = (uint8_t) address;

	// Inefficient copying of data to temp buffer
	for (i=0; i<num_bytes; i++){
		buffer[i + 4] = data[i];
	}

	// Read the data
	if (spiRW(buffer, num_bytes + 4)){
		return 1;
	}

	// Inefficient copying of read data from temp buffer
	for (i=0; i<num_bytes; i++){
		data[i] = buffer[i + 4];
	}	

	free(buffer);
	return 0;
}
