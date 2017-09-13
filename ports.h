/* 
 * File: ports.h
 *
 * Function prototypes for file IO and SPI. Modify for your system.
 * Current implementation is for RaspberryPi with WiringPI library.
 */

#ifndef _PORTS_H_
#define _PORTS_H_
#include <stdint.h>


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