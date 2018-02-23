#include "mbed.h"
#include "CanFunctions.h"
#include "main.h"

extern DigitalOut heartBeatLED;
extern CAN can;
extern BMSData bms;
char dummy = 1;
int numCodes = 10;
CanHandle canHandles[10];

#if PRIMARY
const int numNodes = 2;
int count = 0;
char aliveNodes[numNodes];
int heartbeatCount = 0;
int nodeIds[numNodes];
#endif

void tmpBmsCellBroadcast() {
	char *data = (char*)malloc(sizeof(char[8]));
	data[0] = 25; 
	data[1] = 148;
	data[2] = 169;
	data[3] = 1;
	data[4] = 152;
	data[5] = 148;
	data[6] = 169;
	data[7] = 116;
	CANMessage msg(0x0036, data);
	can.write(msg);
	printf("Sent message test\n\r");
	free(data);
}

void resizeBmsCells(char newMaxCell) {
	realloc((void*)bms->cells, newMaxCell*sizeof(CellData));
	for(i = bms->cellMax; i++; i<newMaxCell) {
		bms->cells[i].cellId = i;
	}

	bms->cellMax = newMaxCell;
	
}

void bmsCellBroadcast(CANMessage *recieve) {
	void *tmp = (void*)calloc(8,1); // 8 bytes recieved from CAN	
	memcpy(tmp, recieve->data, 8);
	// byte 0: cell id
	// byte 1/2: instant voltage (0.1mv)
	// byte 3/4: interal resistance (0.01mOhm)
	// byte 5/6: open voltage (0.1mv)
	// byte 7: checksum
	char cellId = 0, checkSum = 0, validation = 0;
	unsigned short voltage = 0, openVoltage = 0, resistance = 0;
	char offset = 0;
	
	memcpy(&cellId, tmp + offset, sizeof(cellId)); offset += sizeof(cellId);
	memcpy(&voltage, tmp + offset, sizeof(voltage)); offset += sizeof(voltage);
	memcpy(&resistance, tmp + offset, sizeof(resistance)); offset += sizeof(resistance);

	memcpy(&openVoltage, tmp + offset, sizeof(openVoltage)); offset += sizeof(openVoltage);
	memcpy(&checkSum, tmp + offset, sizeof(checkSum)); offset += sizeof(checkSum);

	if(offset != 8) 
		printf("ERROR: bmsCellBroadcast in CanFunctions.cpp did not reach correct offset.i %d\n\r", offset);

	printf("\n\r");
	printf("Cell id: %d\n\rVoltage: %d\n\rOpenVoltage: %d\n\rCheck: %d\n\rCheck 2: %d\n\r",
		cellId, voltage, openVoltage, checkSum, validation);
	
	// Save data to bms struct
	if(cellId > bms->cellMax)
		resizeBmsCells(cellId);
	CellData* cell = bms->cells[cellId];
	cell->voltage = voltage;
	cell->openVoltage = openVoltage;
	cell->resistance = resistance;

	free(tmp);
}

void bmsMessage1(CANMessage *recieve) {
	// byte 0: const
	// byte 1: const
	// byte 2: blank
	// byte 3: simulated SOC
	// byte 4: high temp
	// byte 5: low temp
	// byte 6: CRC Checksum
 	// byte 7: blank
	char *data = recieve->data;
	unsigned char highT = 0, lowT = 0, soc = 0;

	highT = data[4]; lowT = data[5];
	soc = data[3];

	printf("High Temp: %d\t|\t Low Temp: %d\r\n", highT, lowT);
	bms->maxTemp = highT;
	bms->minTemp = lowT;
}

void bmsDischargeEnable() {
	// TODO Add specifics

	CANMessage(0x000, &dummy, 1);
}

void canLogger(CANMessage *recieve) {
#if PRIMARY
	printf("Incoming CAN Frame: 0x%04x\t\n\r", recieve->id);
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
	printf("Heartbeat %d sent\n", heartbeatCount);
	aliveNodes[0] = 1;
	// Reset alive nodes
	for(int i = 0; i<numNodes; i++) {
		if(aliveNodes[i] != 1) {
			printf("WARNING: Node %d offline\n", nodeIds[i]);
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
  * TODO Better method?
  */
int initializeCanParser() {
	printf("Initialize CAN functions...");
	// Heartbeat functions
	canHandles[0].header = 0x700;
	canHandles[0].func = &heartbeatMaster;

	canHandles[1].header = 0x701; // Need to add one of these for every slave
	canHandles[1].func = &heartbeatSlave;

	canHandles[2].header = 0x0036;
	canHandles[2].func = &bmsCellBroadcast;

	canHandles[3].header = 0x360;
	canHandles[3].func = &bmsMessage1;

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
