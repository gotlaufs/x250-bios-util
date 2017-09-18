/*
 * file: winbond_functions.c
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
		// Error condition
		printf("Received wrong reg value: %d\n", reg);
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
 * Memory will be read in 2kB chunks because default RaspberryPi SPI buffer is
 * 4 kB and 4 bytes are needed for instruction+address.
 */
uint8_t readData(uint8_t *data, uint32_t num_bytes, uint32_t address){
	const uint16_t CHUNK_SIZE = 0x800; // 2kB
	uint32_t i, j;
	uint16_t num_chunks;
	uint16_t rem_bytes;
	// Check if enough bytes in memory
	if ((address + num_bytes) > MEMORY_SIZE){
		// Out of bounds
		printf("readData: Out of bounds! max address = %x, Mem size = %x\n",
			 	address + num_bytes, MEMORY_SIZE);
		return 1;
	}

	// Calculate number of 2kB chunks to read and leftover bytes
	num_chunks = num_bytes / CHUNK_SIZE;
	rem_bytes = num_bytes - num_chunks * CHUNK_SIZE;

	uint8_t *buffer; 
	buffer = (uint8_t *) malloc(CHUNK_SIZE + 4);
	
	printf("Number of bytes to read: 0x%x or %d\n", num_bytes, num_bytes);
	printf("Number of chunks: 0x%x or %d\n", num_chunks, num_chunks);
	printf("Number of free bytes to read: 0x%x or %d\n", rem_bytes, rem_bytes);
	for (j=0; j<num_chunks; j++){
		// DEBUG:
		printf("Reading chunk %d out of %d\r", j, num_chunks);
		// Assemble read instruction
		buffer[0] = INS_READ_DATA;
		buffer[1] = (uint8_t) (address >> 16);
		buffer[2] = (uint8_t) (address >> 8);
		buffer[3] = (uint8_t) (address);

		// Read the data
		if (spiRW(buffer, CHUNK_SIZE + 4)){
			return 1;
		}

		for (i=0; i<CHUNK_SIZE; i++){
			data[i + j * CHUNK_SIZE] = buffer[i + 4];
		}

		address += CHUNK_SIZE;
	}
	printf("\n");

	// Leftover bytes
	if (rem_bytes){
		printf("Reading leftover bytes.. \n");
		buffer[0] = INS_READ_DATA;
		buffer[1] = (uint8_t) address >> 16;
		buffer[2] = (uint8_t) address >> 8;
		buffer[3] = (uint8_t) address;

		if (spiRW(buffer, rem_bytes + 4)){
			return 1;
		}

		for (i=0; i<rem_bytes; i++){
			data[i + num_chunks * CHUNK_SIZE] = buffer[i + 4];
		}
	}	

	free(buffer);
	return 0;
}
