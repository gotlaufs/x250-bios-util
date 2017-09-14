#include <wiringPiSPI.h>
#include <stdio.h>
#include <stdint.h>
#include "winbond_defines.h"
#include "ports.h"
#include "winbond_functions.h"

int CHANNEL = 1;

int main(){
	int fd;
	uint8_t sr1 = 0, sr2 = 0, sr3 = 0;		
	spiInit(&fd);
	
	printf("Init result: %d\n",fd);
	
	printf("Attempt to read out status registers 1-3\n");
	readSR(1, &sr1);
	readSR(2, &sr2);
	readSR(3, &sr3);	 
	
	printf("SR1 = %x\nSR2 = %x\nSR3 = %x\n", sr1, sr2, sr3);
	
	uint8_t temp = 0;
	writeSR(1,  temp);
	waitSPIAvailable();
	readSR(1, &sr1);
	readSR(2, &sr2);
	readSR(3, &sr3);	 
	
	printf("SR1 = %x\nSR2 = %x\nSR3 = %x\n", sr1, sr2, sr3);
	
	temp = INS_WRITE_ENABLE;
	spiWrite(&temp, 1);
	readSR(1, &sr1);
	readSR(2, &sr2);
	readSR(3, &sr3);	 
	
	printf("SR1 = %x\nSR2 = %x\nSR3 = %x\n", sr1, sr2, sr3);
	
	return 0;
}
