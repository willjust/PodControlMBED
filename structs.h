#ifndef _HEADERS_H_
#define _HEADERS_H_
#include "CanFunctions.h"
#include "mbed.h"

/**
  * Contains function to be called when a header is recieved
  * @param int number of bytes recieved
  * @param int* recieve field of CANMessage
  */
typedef struct {
	unsigned int header;
	void (*func)(CANMessage *recieve);
} CanHandle;

typedef struct {
	char cellId;
	unsigned short voltage;
	unsigned short openVoltage;
	unsigned short resistance;
} CellData;

typedef struct {
	unsigned int cellMax = 0;
	CellData* cells;
	char maxTemp; // DegC*10
	char minTemp;
} BMSData;

typedef struct {

	// Temp x 10
	// Temp[0:2] = IGBT Module Phase A,B,C
	// Temp[3] = Gate Board Driver Temp
	// Temp[4] = control Board temp
	// Temp[5-9] = RTD Temp
	// Temp[10] = Motor Temp
	int temp[11] = {0};
	int torque = 0;
	// Voltage on each analog input x 100
	int analogIn[4] = {0};

	// digInput[0] = Forward switch
	// digInput[1] = Reverse switch
	// digInput[2] = Brake switch
	// digInput[3] = Regen disable
	// digInput[4] = Ignition
	// digInput[5] = Start
	// digInput[6] = input 7
	// digInput[7] = input 8Ignition
	// digInput[5] = Start
	// digInput[6] = input 7
	// digInput[7] = input 8
	bool digInput[8] = {0};



} RMSData;


#endif
