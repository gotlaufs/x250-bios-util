/*
 * file: winbond_functions.h
 *
 * Functions for handling Windond W25Q128 SPI EEPROM.
 */

#ifndef _WINBOND_FUNCTIONS_H_
#define _WINBOND_FUNCTIONS_H_

/* readSR: Read Status Register 1-3
 *
 * Args: reg: Status Register number. 1-3
 * 		 data: Pointer to variable to save data
 * Return: error status. '0' on success.
 */
uint8_t readSR(uint8_t reg, uint8_t *data);


/* writeSR: Write Status Register 1-3
 *
 * Args: reg: Status Register number. 1-3
 * 		 data: Pointer to variable to read data from
 * Return: error status. '0' on success.
 */
uint8_t writeSR(uint8_t reg, uint8_t data);


/* readSecurityReg: Read Security Register 1-3
 *
 * Args: reg: Security Register number. 1-3
 * 		 data: Pointer to variable to save data
 * Return: error status. '0' on success.
 *
 * Security registers are 256-Bytes long.
 */
uint8_t readSecurityReg(uint8_t reg, uint8_t *data);


/* waitSPIAvailable: Wait until SPI device is not busy anymore
 *
 * This function will lock for the busy interval. It wil return when SPI is
 * available again
 */
void waitSPIAvailable(void);


/* writeEnable: Enable write access to the chip
 *
 * This must be called before any write instruction to the device
 * Return: error status. '0' on success.
 */
uint8_t writeEnable(void);


/* readData: Read some bytes of data into data buffer from address
 *	
 * Args: 	data: data buffer to read data into
 * 			num_bytes: number of bytes to read
 * 			address: data address to begin read. Address is 24-bits long
 * Return:	error status. '0' on success.
 *
 * Entire memory (up to address 'MEMORY_SIZE') can be read in single instruction
 * 'data' array must be allocated for full read. 
 */
uint8_t readData(uint8_t *data, uint32_t num_bytes, uint32_t address);


/* pageProgram: Write number of bytes to a page in EEPROM
 *	
 * Args: 	data: data buffer to write to EEPROM
 * 			num_bytes: number of bytes to write
 * 			address: data address to begin write
 . Address is 24-bits long
 * Return:	error status. '0' on success.
 *
 * Up to 256 bytes can be written. If 'address' is not a page border (last byte)
 * not '0x00', less than 256 bytes can be programmed. This is checked by the
 * function.
 * Only previously erased (0xFF) bytes can be programmed. This will
 * automatically erase number of bytes if they are not '0xFF'.
 */
uint8_t pageProgram(uint8_t *data, uint32_t num_bytes, uint32_t address);


/* sectorErase: Erase 4-kB data sector in the EEPROM
 *
 * Args: 	address: data address to begin read. Address is 24-bits long
 * Return:	error status. '0' on success.
 *
 * The sector is defined by A[24:12]. There are 4096 pages in total for 128 Mbit
 * EEPROM.
 * If the sector contains write-protected blocks/sectors/pages, they will remain
 * un-erased.
 */
uint8_t sectorErase(uint32_t address);


/* chipErase: Write number of bytes to a page in EEPROM
 *
 * Return:	error status. '0' on success.
 *
 * If the memory contains write-protected blocks/sectors/pages, they will remain
 * un-erased.
 */
uint8_t chipErase(void);

#endif // _WINBOND_FUNCTIONS_H_
