#ifndef _CAN_BMS_H_
#define _CAN_BMS_H_
#include "mbed.h"

typedef struct {
	unsigned int header;
	void (*func)(CANMessage *recieve);
} CanHandle;

int initializeBmsCan(CanHandle *funcList, int start);

#endif
