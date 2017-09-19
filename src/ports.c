/*
 * File: ports.c
 *
 * Edit these functions to port the code to your platform
 */
#include <stdint.h>
#include "ports.h"

// RaspberryPi SPI library
// Test if need to use mocks if not compiling on RaspberryPi
#ifdef __arm__
#include <wiringPiSPI.h>
#else
#include "mocks/mock_wiringPiSPI.h"
#endif

/* spiInit: Initialize SPI device. 
 *
 * Args: pointer to integer file_descriptor
 * Return: error status. '0' on success.
 * WiringPi returns '-1' on error.
 */
uint8_t spiInit(int *file_descriptor){
	*file_descriptor = wiringPiSPISetup(SPI_CHANNEL, SPI_SPEED);
	if (*file_descriptor != -1){
		return 0;
	}
	else{
		return 1;
	}
}


/* spiWrite: Write 'num_bytes' from the 'data' buffer to SPI device.
 *
 * Return: error status. '0' on success.
 * Array is copied, because WiringPi overwrites 'buffer' array.
 * WiringPi uses 'ioctl' in the manner:
 * 	ioctl (spiFds [channel], SPI_IOC_MESSAGE(1), &spi)
 *  It returns positive value on success.
 */
uint8_t spiWrite(uint8_t *data, uint8_t num_bytes){
	static uint8_t buffer[SPI_BUFFER_SIZE];
	uint8_t i;
	for (i=0; i<num_bytes; i++){
		buffer[i] = data[i];
	}
	uint8_t err;
	err = wiringPiSPIDataRW(SPI_CHANNEL, buffer, num_bytes);

	if (err > 0 ){
		return 0;
	}
	else{
		return 1;
	}
}


/* spiRW: Write data to SPI device and synchronously read it
 *
 * The number of bytes 'num_bytes' is read from 'data' and th read data is
 * saved back to it. Synchronous operation.
 *
 * Return: error status. '0' on success.
 *
 * Works as a simple wrapper for wiringPi's function
 * WiringPi uses 'ioctl' in the manner:
 * 	ioctl (spiFds [channel], SPI_IOC_MESSAGE(1), &spi)
 *  It returns positive value on success.
 */
uint8_t spiRW(uint8_t *data, uint32_t num_bytes){
	uint8_t err;
	err = wiringPiSPIDataRW(SPI_CHANNEL, data, num_bytes);
	if (err > 0 ){
		return 0;
	}
	else{
		return 1;
	}
}
