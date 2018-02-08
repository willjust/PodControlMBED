#include "mbed.h"
#include "CanFunctions.h"

CanHandle* canHandles;
extern CAN can;
char dummy = 1;
#if PRIMARY
	int count = 0;
#endif

/**
  * CANOpen: Master sends heartbeat, slave consumes, responds to master
  */
int heartbeat() { 
#ifdef PRIMARY
	can.write(CANMessage(0x700, &dummy, 1));
	heartbeatCount++;
	printf("Heartbeat %d sent\n", heartbeatCount);
#else
	
#endif
	return 0;
}

void heartbeatMaster(int nBytes, int* canRecv) {
	// Send reply heart beat
	can.write(CANMessage(0x701, &dummy, 1)); // Dummy value for now, change to state
	return;
}

void heartbeatSlave(int nBytes, int* canRecv) {
	// Update states from slaves
		
	return;
}

/**
  * 
  */
void emergencyError(int nBytes, int* canRecv) {
	// Enter fail state

}

int initializeCanParser() {
	canHandles = (CanHandle*)malloc(sizeof(CanHandle[10]));

	// Heartbeat functions
	canHandles[0].header = 0x700;
	canHandles[0].func = &heartbeatMaster;

	canHandles[1].header = 0x701; // Need to add one of these for every slave
	canHandles[1].func = &heartbeatSlave;
	return 0;
}


