#include "mbed.h"
#include "CanFunctions.h"
#include "main.h"

CAN can(PA_11, PA_12);
BMSData bms;

char CanBMS = 0; // Do we have a BMS on CAN?

extern CanHandle* canHandles;

int initializeCan() {
	can.frequency(250e3);
	initializeCanParser();
	return 0;
}

int checkCanDevices() {
	char dummy = 1;
	CAN.write(0x700, &dummy, 1);
	CANMessage* incoming;

	unsigned int time = 0;
	while (time < 1000) {
		if(CAN.read(incoming)) {
			switch (incoming.id) {
				case 0x7E3:
					CanBMS = 1;
					break;
				default:
					printf("Unrecognized CAN ID: 0x%x\n\r", incoming.id);
	
			}
		}
		time++;
		wait(0.001);
	}
	if(CanBMS) {
		initializeBms();
	}
}
int initializeBms() {
	printf("Attempting to initialize BMS...");
	bms = malloc(sizeof(BMSData);
	bms->cells = malloc(8);
	for(int i = 0; i<8; i++) {
		bms->cells[i].cellId = i;
	}
	printf("Done\r\n");
	return 0;
}

/*****************************************************************************/
/*                      Primary Board Code                                   */
/*****************************************************************************/

#if PRIMARY
Serial pc(USBTX, USBRX);

/**
  * Initialization for test board 1
  */
short init(DigitalOut outPin) {
	pc.baud(9600);
	initializeCan();
	printf("Initilization Complete.\n");
    outPin = 1;
    return 0;   
}

#else
/*****************************************************************************/
/*                     Secondary Board Code                                  */
/*****************************************************************************/

/**
  * Initialization for test board 2
  */
short init(DigitalOut outPin) {
	initializeCan();

    outPin = 1;
    return 0;   
}

#endif


