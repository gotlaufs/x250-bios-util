/*
 * File: 	winbond_defines.h
 *
 * This file includes all neccessary WINBOND 25Q128 SPI EEPROM chip register defines
 *
 */

#ifndef _WINBOND_DEFINES_H_
#define _WINBOND_DEFINES_H_

// Entire memory size in bytes. 16 MB = 128 Mbit
#define MEMORY_SIZE 0x1000000

// Status register bits
// Status register 1
#define SR1_BUSY 0x01 // Read only
#define SR1_WEL  0x02 // Read only (Write-enable latch)
#define SR1_BP0  0x04
#define SR1_BP1  0x08
#define SR1_BP2  0x10
#define SR1_TB   0x20
#define SR1_SEC  0x40
#define SR1_SRP0 0x80

// Status register 2
#define SR2_SRP1 0x01
#define SR2_QE   0x02
#define SR2_RES  0x04 // Reserved
#define SR2_LB1  0x08
#define SR2_LB2  0x10
#define SR2_LB3  0x20
#define SR2_CMP  0x40
#define SR2_SUS  0x80  // Read only

// Status register 3
#define SR3_RES1     0x01 // Reserved
#define SR3_RES2     0x02 // Reserved
#define SR3_WPS      0x04
#define SR3_RES4     0x08 // Reserved
#define SR3_RES5     0x10 // Reserved
#define SR3_DRV0     0x20
#define SR3_DRV1     0x40
#define SR3_HOLD_RST 0x80

// Device instructions
// Write enable
#define INS_WRITE_ENABLE 0x06
#define INS_VOLATILE_SR_WRITE_ENABLE 0x50
#define INS_WRITE_DISABLE 0x04

// Status registers Read/Write
// B2 = S[7..0]
#define INS_READ_SR1  0x05
#define INS_WRITE_SR1 0x01
#define INS_READ_SR2  0x35
#define INS_WRITE_SR2 0x31
#define INS_READ_SR3  0x15
#define INS_WRITE_SR3 0x11

// Erase
#define INS_CHIP_ERASE 0xC7
// B2 = A[23..16]; B3 = A[15..8]; B4 = A[7..0] 
#define INS_SECTOR_ERASE_4KB 0x20
#define INS_SECTOR_ERASE_32KB 0x52
#define INS_SECTOR_ERASE_64KB 0xD8
#define INS_ERASE_SECURITY_REG 0x5A

#define INS_ERASE_PR_SUSPEND 0x75
#define INS_ERASE_PR_RESUME 0x7A

// Program
// B2 = A[23..16]; B3 = A[15..8]; B4 = A[7..0]; B5 = D[7..0]; B6=D[7..0]
// Up to 256 data bytes
#define INS_PAGE_PROGRAM 0x02
#define INS_PROGRAM_SECURITY_REG 0x42

// Read
// B2 = A[23..16]; B3 = A[15..8]; B4 = A[7..0]; B5 = D[7..0]
#define INS_READ_DATA 0x03
// B2 = A[23..16]; B3 = A[15..8]; B4 = A[7..0]; B5 = [DUMMY]; B6 = D[7..0]
#define INS_FAST_READ_DATA 0x0B
// B2 = A[23..16]; B3 = A[15..8]; B4 = A[7..0]; B5 = [DUMMY]; B6 = D[7..0]
#define INS_READ_SFDP_REG 0x5A
// B2 = A[23..16]; B3 = A[15..8]; B4 = A[7..0]; B5 = [DUMMY]; B6 = D[7..0]
#define INS_READ_SECURITY_REG 0x48

// Lock
// B2 = A[23..16]; B3 = A[15..8]; B4 = A[7..0]
#define INS_IND_BLOCK_LOCK 0x36
#define INS_IND_BLOCK_UNLOCK 0x39
// B2 = A[23..16]; B3 = A[15..8]; B4 = A[7..0]; B5 = L[7..0]
#define INS_READ_BLOCK_LOCK 0x3D

// Power
#define INS_POWER_DOWN 0xB9


#endif // _WINBOND_DEFINES_H_
