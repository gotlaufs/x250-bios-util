/* 
 * File: ports.h
 *
 * Function prototypes for file IO and SPI. Modify for your system.
 * Current implementation is for RaspberryPi with WiringPI library.
 */

#ifndef _PORTS_H_
#define _PORTS_H_
#include <stdint.h>

// SPI buffer size in bytes
#define SPI_BUFFER_SIZE 256

// Raspberry Pi specific
#define SPI_CHANNEL 1
#define SPI_SPEED 500000

/* spiInit: Initialize SPI device. 
 *
 * Args: pointer to integer file_descriptor
 * Return: error status. '0' on success.
 */
uint8_t spiInit(int *file_descriptor);


/* spiWrite: Write 'num_bytes' from the 'data' buffer to SPI device.
 *
 * Return: error status. '0' on success.
 */
uint8_t spiWrite(uint8_t *data, uint8_t num_bytes);


/* spiRW: Write data to SPI device and synchronously read it
 *
 * The number of bytes 'num_bytes' is read from 'data' and th read data is
 * saved back to it. Synchronous operation.
 *
 * Return: error status. '0' on success.
 */
uint8_t spiRW(uint8_t *data, uint32_t num_bytes);


#endif  // _PORTS_H_
