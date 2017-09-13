#include <wiringPiSPI.h>
#include <stdio.h>
#include "winbond_defines.h"

int CHANNEL = 1;

unsigned char readSR(unsigned char reg);

int main(){
	int fd;
	unsigned char sr1, sr2, sr3;		
	fd = wiringPiSPISetup(CHANNEL, 500000);
	
	// wiringPiSPIDataRW(CHANNEL, buffer, length);
	printf("Init result: %d\n",fd);
	

	printf("Attempt to read out status registers 1-3\n");
	sr1 = readSR(1);
	sr2 = readSR(2);
	sr3 = readSR(3);	 
	
	printf("SR1 = %x\nSR2 = %x\nSR3 = %x\n", sr1, sr2, sr3);	
	return 0;
}

unsigned char readSR(unsigned char reg){
	// Read status register 1-3 specified by 'reg'
	unsigned char buffer[2];
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
	
	return buffer[1];
}

