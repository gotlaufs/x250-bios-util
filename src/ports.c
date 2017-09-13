/*
 * File: ports.c
 *
 * Edit these functions to port the code to your platform
 */
#include <stdint.h>
#include "ports.h"

// RaspberryPi SPI library
#include <wiringPiSPI.h>

int CHANNEL = 1;
short SPEED = 500000;

/* spiInit: Initialize SPI device. 
 *
 * Args: pointer to integer file_descriptor
 * Return: error status. '0' on success.
 * WiringPi returns '-1' on error.
 */
uint8_t spiInit(int *file_descriptor){
	*file_descriptor = wiringPiSPISetup(CHANNEL, SPEED);
	if (*file_descriptor != -1){
		return 0;
	}
	else{
		return 1;
	}
}


/* spiRead: Read 'num_bytes' into 'data' buffer.
 *
 * Return: error status. '0' on success.
 * Buffer array is used, because WiringPi overwrites 'buffer' array.
 */ 
uint8_t spiRead(uint8_t *data, uint8_t num_bytes){
	static uint8_t buffer[num_bytes];
	uint8_t err;
	err = wiringPiSPIDataRW(CHANNEL, buffer, num_bytes);
	printf("DEBUG: err = %d\n", err);
	data = buffer;
	// TODO: Add return error variables
}


/* spiWrite: Write 'num_bytes' from the 'data' buffer to SPI device.
 *
 * Return: error status. '0' on success.
 * Array is copied, because WiringPi overwrites 'buffer' array.
 * WiringPi uses 'ioctl' in the manner:
 * 	ioctl (spiFds [channel], SPI_IOC_MESSAGE(1), &spi)
 */
uint8_t spiWrite(uint8_t *data, uint8_t num_bytes){
	static uint8_t buffer[num_bytes];
	uint8_t i;
	for (i=0; i<num_bytes; i++){
		buffer[i] = data[i];
	}
	uint8_t err;
	err = wiringPiSPIDataRW(CHANNEL, buffer, num_bytes);
	printf("DEBUG: err = %d\n", err);
	// TODO: Add return error variables
}
