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


/* spiRead: Read 'num_bytes' into 'data' buffer.
 *
 * Return: error status. '0' on success.
 */ 
uint8_t spiRead(uint8_t *data, uint8_t num_bytes);


/* spiWrite: Write 'num_bytes' from the 'data' buffer to SPI device.
 *
 * Return: error status. '0' on success.
 */
uint8_t spiWrite(uint8_t *data, uint8_t num_bytes);


#endif  // _PORTS_H_
