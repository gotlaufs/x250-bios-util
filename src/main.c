#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "winbond_defines.h"
#include "ports.h"
#include "winbond_functions.h"
#include "defines.h"

int main(){
	int spi_dev;
	uint8_t sr1 = 0, sr2 = 0, sr3 = 0;
	uint8_t *eeprom_buffer;
	char *filename;
	FILE *eeprom_file, *sr_file;

	printf("x250 BIOS chip utility\n\n");
	
	printf("Opening SPI device..\n");
	if (spiInit(&spi_dev)){
		return 1;
	}

	printf("Reading status registers..\n");

	if (readSR(1, &sr1)){
		return 1;
	}
	if (readSR(2, &sr2)){
		return 1;
	}
	if (readSR(3, &sr3)){
		return 1;
	}
	printf("SR1 = %x; SR2 = %x; SR3 = %x\n\n", sr1, sr2, sr3);

	printf("Writing status register info to file: %s\n", REGISTER_FILE);
	filename = REGISTER_FILE;
	sr_file = fopen(filename, "w");
	if (sr_file == NULL){
		return 1;
	}

	fprintf(sr_file, "Status registers (hex):\n");
	fprintf(sr_file, "SR1 = %x\n", sr1);
	fprintf(sr_file, "SR2 = %x\n", sr2);
	fprintf(sr_file, "SR3 = %x\n", sr3);
	fclose(sr_file);

	printf("Reading entire BIOS chip into memory..\n");
	eeprom_buffer = (uint8_t *) malloc(MEMORY_SIZE);

	if (readData(eeprom_buffer, MEMORY_SIZE, 0x0)){
		free(eeprom_buffer);
		return 1;
	}

	printf("Writing EEPROM dump to file: %s\n", EEPROM_FILE);
	// Write in binary mode
	eeprom_file = fopen(EEPROM_FILE, "wb");
	if (eeprom_file == NULL){
		free(eeprom_buffer);
		return 1;
	}
	fwrite(eeprom_buffer, sizeof(uint8_t), sizeof(eeprom_buffer), eeprom_file);
	fclose(eeprom_file);

	printf("All done!\n");
	printf("Exiting..\n");
	free(eeprom_buffer);
	return 0;
}
