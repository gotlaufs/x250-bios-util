/*
 * File: 	mock_wiringPiSPI.c
 *
 * Mock functions from wiringPi to be able to compile on non-RaspberryPi machine
 *
 */

#include "mock_wiringPiSPI.h"

int wiringPiSPIGetFd     (int channel){
	return 0;
}


int wiringPiSPIDataRW    (int channel, unsigned char *data, int len){
	return 0;
}


int wiringPiSPISetupMode (int channel, int speed, int mode){
	return 0;
}


int wiringPiSPISetup     (int channel, int speed){
	return 0;
}
