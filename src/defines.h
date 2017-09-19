/*
 * File: 	defines.h
 *
 * Various constants used in program
 *
 */
#ifndef _DEFINES_H_
#define _DEFINES_H_

/* Read buffer size
 * PI's default SPI buffer is 4 kB, and must add 4 bytes for instruction
 * + address.
 * Pi's buffer can be increased, but that could make porting harder for
 * small memory devices.
 */
#define READ_CHUNK_SIZE 0x800 // 2 kB

#define EEPROM_FILE		"eeprom_dump"
#define REGISTER_FILE	"status_registers.txt"
#define SEC_REG_FILE_1 	"security_register1"
#define SEC_REG_FILE_2	"security_register2"
#define SEC_REG_FILE_3	"security_register3"

#endif // _DEFINES_H_
