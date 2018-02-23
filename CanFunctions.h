#ifndef _CAN_FUNCTIONS_H_
#define _CAN_FUNCTIONS_H_

/**
  * Contains function to be called when a header is recieved
  * @param int number of bytes recieved
  * @param int* recieve field of CANMessage
  */
typedef struct {
	uint header;
	void (*func)(CANMessage *recieve);
} CanHandle;

void tmpBmsCellBroadcast();
void heartbeat();
void canLogger(CANMessage *recieve);
int initializeCanParser();
int canHandler(CANMessage *msg);
#endif
