#include "BMS.h"
#include "structs.h"

extern CAN can;
extern BMSData *bms;

void resizeBmsCells(char newMaxCell) {
	if(newMaxCell > 32) return;
	realloc((void*)bms->cells, newMaxCell*sizeof(CellData));
	for(int i = bms->cellMax; i<newMaxCell; i++) {
		bms->cells[i].cellId = i;
	}

	bms->cellMax = newMaxCell;
	
}

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
	if(cellId < bms->cellMax) {
		printf("Hello %d\n", bms->cellMax);
		CellData* cell = &bms->cells[cellId];
		cell->voltage = voltage;
		cell->openVoltage = openVoltage;
		cell->resistance = resistance;
	}
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
	unsigned char *data = recieve->data;
	unsigned char highT = 0, lowT = 0, soc = 0;

	highT = data[4]; lowT = data[5];
	soc = data[3];

	printf("High Temp: %d\t|\t Low Temp: %d\r\n", highT, lowT);
	bms->maxTemp = highT;
	bms->minTemp = lowT;
}

int initializeBmsCan(CanHandle* fxnList) {
	fxnList[0].header = 0x0653;
	fxnList[0].func = &bmsCellBroadcast;

	// High-Low-SOC Message
	fxnList[1].header = 0x360;
	fxnList[1].func = &bmsMessage1;

	return 2;

}
