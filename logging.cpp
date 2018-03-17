#include "structs.h"
#include "mbed.h"

extern BMSData *bms;
extern RMSData *rms;

char sep[80] = "============================================================================\n\r";

void printBms() {
	printf(sep);
	printf("BMS Data\n\r");
	printf("Temperature\t| High: %2.1fC \t| Low: %2.1fC |\r\n", 
		(float)(bms->maxTemp)/10, (float)(bms->minTemp)/10);
	printf("Cell Data\r\n");
	for(uint i = 0; i<bms->cellMax; i++) {
		printf("\t%d: Voltage %2.1fV\t| Resistance %2.1fOhm\t|\r\n", i, 
			(float)(bms->cells[i].voltage)/10, 
			(float)(bms->cells[i].resistance)/10);
	}
}

void printRms() {
	printf(sep);
	printf("RMS Data\n\r");
	printf("Temperatures\r\n");
	printf("\tPhase A: %2.2fC\r\n", (float)(rms->temp[0])/10);
	printf("\tPhase B: %2.2fC\r\n", (float)(rms->temp[1])/10);
	printf("\tPhase C: %2.2fC\r\n", (float)(rms->temp[2])/10);
	printf("\tGate Board Driver: %2.2fC\r\n", (float)(rms->temp[3])/10);
	printf("\tControl Board: %2.2fC\r\n", (float)(rms->temp[4])/10);
	printf("\tRTD 1: %2.2fC\r\n", (float)(rms->temp[5])/10);
	printf("\tRTD 2: %2.2fC\r\n", (float)(rms->temp[6])/10);
	printf("\tRTD 3: %2.2fC\r\n", (float)(rms->temp[7])/10);
	printf("\tRTD 4: %2.2fC\r\n", (float)(rms->temp[8])/10);
	printf("\tRTD 5: %2.2fC\r\n", (float)(rms->temp[9])/10);
	printf("\tMotor: %2.2fC\r\n", (float)(rms->temp[10])/10);

}

void printPodStatus() {
	printRms();
	printBms();
}
