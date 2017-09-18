/*
 * File: 	mock_wiringPiSPI.h
 *
 * Mock functions from wiringPi to be able to compile on non-RaspberryPi machine
 *
 */

#ifndef _MOCK_WIRINGPISPI_H_
#define _MOCK_WIRINGPISPI_H_

int wiringPiSPIGetFd     (int channel) ;
int wiringPiSPIDataRW    (int channel, unsigned char *data, int len) ;
int wiringPiSPISetupMode (int channel, int speed, int mode) ;
int wiringPiSPISetup     (int channel, int speed) ;

#endif // _MOCK_WIRINGPISPI_H_