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

#endif // _WINBOND_FUNCTIONS_H_
