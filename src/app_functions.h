/*
 * File: app_functions.h
 *
 * EEPROM read and write function prototypes
 */
#ifndef _APP_FUNCTIONS_H_
#define _APP_FUNCTIONS_H_
#include <stdio.h>

/* eepromDump: Dump entire EEPROM contents to file
 * 
 * Return:	error status. '0' on success.
 * 
 * Uses global file path defines and global SPI device.
 */
uint8_t eepromDump(void);


/* eepromProgram: Program entire EEPROM from file
 * 
 * Args:	fp: File to program. Must be MEMORY_SIZE long.
 * Return:	error status. '0' on success.
 * 
 * Uses global file path defines and global SPI device.
 */
uint8_t eepromProgram(FILE *fp);

#endif // _APP_FUNCTIONS_H_
