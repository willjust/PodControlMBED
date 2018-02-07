#include "mbed.h"

CAN can(PA_11, PA_12);

/*****************************************************************************/
/*                      Primary Board Code                                   */
/*****************************************************************************/

#ifdef PRIMARY
Serial pc(USBTX, USBRX);

/**
  * Initialization for test board 1
  */
short init(DigitalOut outPin) {
	pc.baud(9600);
	can.frequency(1e9);

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
   	can.frequency(1e9);

    outPin = 1;
    return 0;   
}

#endif
