#include "CanFunctions.h"
#include "RMS.h"
#include "BMS.h"

extern DigitalOut heartBeatLED;
extern CAN can;
char dummy = 1;
int numCodes = 10;
CanHandle canHandles[20];


#if PRIMARY
const int numNodes = 2;
int count = 0;
char aliveNodes[numNodes];
int heartbeatCount = 0;
int nodeIds[numNodes];
#endif


int printAllow = 0;
void resetTime() {
	printAllow = 0;
}

void canLogger(CANMessage *recieve) {
#if PRIMARY
//	if(printAllow == 1) return;
	Ticker ticker;
	ticker.attach(&resetTime, 1);

	printf("Incoming CAN Frame: 0x%04x\t\n\r", recieve->id);
	printAllow = 1;
	for(int i = 0; i < recieve->len; i++)
		printf("%d, ", recieve->data[i]);
	printf("\r\n");
	
#endif

}

/**
  * CANOpen: Master sends heartbeat, slave consumes, responds to master
  */
void heartbeat() { 
#if PRIMARY
	can.write(CANMessage(0x700, &dummy, 1));
	heartbeatCount++;
	printf("Heartbeat %d sent\n\r", heartbeatCount);
	aliveNodes[0] = 1;
	// Reset alive nodes
	for(int i = 0; i<numNodes; i++) {
		if(aliveNodes[i] != 1) {
		//	printf("WARNING: Node %d offline\n", nodeIds[i]);
		}
		aliveNodes[i] = 0;
	}

#else
	
#endif
}

void heartbeatMaster(CANMessage *recieve) {
	// Send reply heart beat
	can.write(CANMessage(0x701, &dummy, 1)); // Dummy value for now, change to state
	return;
}


void heartbeatSlave(CANMessage *recieve) {
#if PRIMARY
	// Update states from slaves
	aliveNodes[1] = 1;			
	printf("Heartbeat, node 01\n");
#endif
	return;
}

/**
  * 
  */
void emergencyError(CANMessage *recieve) {
	// Enter fail state
	
}

/**
  * Better method?
  */
int initializeCanParser() {
	printf("Initialize CAN functions...");
	// Heartbeat functions
	canHandles[0].header = 0x700;
	canHandles[0].func = &heartbeatMaster;

	canHandles[1].header = 0x701; // Need to add one of these for every slave
	canHandles[1].func = &heartbeatSlave;

	// TODO Make better
	int numFuncs = initializeBmsCan(canHandles, 2);
	initializeRmsCan(canHandles, 2+numFuncs);	

	printf("Done\n\r");
	return 0;
}

int canHandler(CANMessage* msg) {
	printf("Recieved CAN Message\n\r");
	for(int i = 0; i<numCodes; i++) {
		if(canHandles[i].header == msg->id) {
			canHandles[i].func(msg);
			heartBeatLED = !heartBeatLED;
			return 0;
		}
	}
	return 1;
}
