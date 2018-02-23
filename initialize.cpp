#include "mbed.h"
#include "CanFunctions.h"
#include "main.h"

CAN can(PA_11, PA_12);
extern CanHandle* canHandles;

int initializeCan() {
	can.frequency(250e3);
	initializeCanParser();
	return 0;
}

/*****************************************************************************/
/*                      Primary Board Code                                   */
/*****************************************************************************/

#if PRIMARY
Serial pc(USBTX, USBRX);

/**
  * Initialization for test board 1
  */
short init(DigitalOut outPin) {
	pc.baud(9600);
	initializeCan();
	printf("Initilization Complete.\n");
    outPin = 1;
    return 0;   
}

#else
/*****************************************************************************/
/*                     Secondary Board Code                                  */
/*****************************************************************************/

/**
  * Initialization for test board 2
  */
short init(DigitalOut outPin) {
	initializeCan();

    outPin = 1;
    return 0;   
}

#endif


