#ifndef _HEADERS_H_
#define _HEADERS_H_
#include "CanFunctions.h"
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
	char maxTemp;
	char minTemp;
} BMSData;

#endif
