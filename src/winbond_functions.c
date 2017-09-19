/*
 * file: winbond_functions.c
 *
 * Functions for handling Windond W25Q128 SPI EEPROM.
 */

#include <stdint.h>
#include <stdlib.h>
#include <string.h>	// For memcpy()
#include "winbond_functions.h"
#include "winbond_defines.h"
#include "ports.h"
#include "error.h"
#include "defines.h"
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
		errvar = ERROR_REG_NOT_EXIST;
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
		errvar = ERROR_REG_NOT_EXIST;
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


/* readSecurityReg: Read Security Register 1-3
 *
 * Args: reg: Security Register number. 1-3
 * 		 data: Pointer to variable to save data
 * Return: error status. '0' on success.
 *
 * Security registers are 256-Bytes long.
 * They are byte-addressable, but that is currently not implemented.
 */
uint8_t readSecurityReg(uint8_t reg, uint8_t *data){
	uint8_t buffer[256 + 5];
	uint16_t i;
	uint32_t address;

	switch (reg){
	case 1:
		address = ADDR_SEC_R_1;
		break;
	case 2:
		address = ADDR_SEC_R_2;
		break;
	case 3:
		address = ADDR_SEC_R_3;
		break;
	default:
		errvar = ERROR_REG_NOT_EXIST;
		return 1;
	}

	buffer[0] = INS_READ_SECURITY_REG;
	// Beginning address.
	buffer[1] = (uint8_t) (address >> 16);
	buffer[2] = (uint8_t) (address >> 8);
	buffer[3] = (uint8_t) (address);
	// 8 dummy bytes 
	buffer[4] = 0x00;

	if(spiRW(buffer, 256 + 5)){
		return 1;
	}
	
	// Write out data
	for (i=0; i<256; i++){
		data[i] = buffer[i+5];
	}

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


/* writeEnable: Enable write access to the chip
 *
 * This must be called before any write instruction to the device
 * Return: error status. '0' on success.
 */
uint8_t writeEnable(void){
	uint8_t we = INS_WRITE_ENABLE;
	if (spiWrite(&we, 1)){
		return 1;
	}
	waitSPIAvailable();

	if (readSR(1, &we)){
		return 1;
	}
	if(!(we & SR1_WEL)){
		errvar = ERROR_SPI_WRITE_ENABLE;
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
 * READ_CHUNK_SIZE is the maximum to be read in single call.
 */
uint8_t readData(uint8_t *data, uint32_t num_bytes, uint32_t address){
	uint32_t i;
	uint8_t *buffer;
	
	// Check if enough bytes in memory
	if ((address + num_bytes) > MEMORY_SIZE){
		errvar = ERROR_OUT_OF_BOUNDS;
		return 1;
	}
	
	// Check if not too much data has been requested
	if (num_bytes > READ_CHUNK_SIZE){
		errvar = ERROR_TOO_BIG_READ;
		return 1;
	}
	
	buffer = (uint8_t *) malloc(READ_CHUNK_SIZE + 4);
	// Assemble read instruction
	buffer[0] = INS_READ_DATA;
	buffer[1] = (uint8_t) (address >> 16);
	buffer[2] = (uint8_t) (address >> 8);
	buffer[3] = (uint8_t) (address);
	
	if (spiRW(buffer, num_bytes+4)){
		free(buffer);
		return 1;
	}
	
	memcpy(data, buffer+4, num_bytes);
	
	free(buffer);
	return 0;
	
}
