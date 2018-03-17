#ifndef _CAN_FUNCTIONS_H_
#define _CAN_FUNCTIONS_H_

#include "mbed.h"
#include "main.h"
#include "BMS.h"

void tmpBmsCellBroadcast();
void heartbeat();
void canLogger(CANMessage *recieve);
int initializeCanParser();
int canHandler(CANMessage *msg);
#endif
