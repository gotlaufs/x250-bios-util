#include <wiringPiSPI.h>
#include <stdio.h>
#include <stdint.h>
#include "winbond_defines.h"
#include "ports.h"

int CHANNEL = 1;

uint8_t readSR(uint8_t reg, uint8_t *data);
uint8_t writeSR(uint8_t reg, uint8_t data);

int main(){
	int fd;
	uint8_t sr1, sr2, sr3;		
	fd = wiringPiSPISetup(CHANNEL, 500000);
	
	// wiringPiSPIDataRW(CHANNEL, buffer, length);
	printf("Init result: %d\n",fd);
	

	printf("Attempt to read out status registers 1-3\n");
	readSR(1, &sr1);
	readSR(2, &sr2);
	readSR(3, &sr3);	 
	
	printf("SR1 = %x\nSR2 = %x\nSR3 = %x\n", sr1, sr2, sr3);

	printf("Attempt to write to SR1 (a 0)\n")
	writeSR(1, 0);	
	return 0;
}


uint8_t readSR(uint8_t reg, uint8_t *data){
	// Read status register 1-3 specified by 'reg'
	//
	// Returns error condition: '1' if error
	uint8_t buffer[2];
	switch (reg){
	case 1:
		buffer[0] = INS_READ_SR1;
		break;
	case 2:
		buffer[0] = INS_READ_SR2;
		break;
	case 3:
		buffer[0] = INS_READ_SR3;
		break;
	default:
		// Error condition
		printf("Received wrong reg value: %d\n", reg);
		return 1;	
	}
	wiringPiSPIDataRW(CHANNEL, buffer, 2);
	
	*data = buffer[1];
	return 0;
}


uint8_t writeSR(uint8_t reg, uint8_t data){
	// Write status register 1-3 specified by 'reg'
	//
	// Returns error condition: '1' if error
	uint8_t buffer[2];
	uint8_t we = INS_WRITE_ENABLE;

	switch (reg){
	case 1:
		buffer[0] = INS_WRITE_SR1;
		break;
	case 2:
		buffer[0] = INS_WRITE_SR2;
		break;
	case 3:
		buffer[0] = INS_WRITE_SR3;
		break;
	default:
		// Error condition
		printf("Received wrong reg value: %d\n", reg);
		return 1;	
	}

	// Unlock Write access to SR first
	wiringPiSPIDataRW(CHANNEL, we, 1);

	// Debug:
	readSR(1, &we);
	if(we && SR1_WEL){
		printf("Write enable SUCCESS!\n");
	}
	else{
		printf("Write enable FAIL\n");
		return 1;
	}

	buffer[1] = data;
	wiringPiSPIDataRW(CHANNEL, buffer, 2);	
	return 0;
}