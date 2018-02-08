#ifndef _CAN_FUNCTIONS_H_
#define _CAN_FUNCTIONS_H_

/**
  * Contains function to be called when a header is recieved
  * @param int number of bytes recieved
  * @param int* recieve field of CANMessage
  */
typedef struct {
	int header;
	void (*func)(int, int*);
} CanHandle;

int initializeCanParser();

#endif
