#include "mbed.h"
#include "initialize.h"
#include "CanFunctions.h"
#include "main.h"

DigitalOut initSucceed(PA_0);
DigitalOut errorPin(PA_1);
DigitalOut heartBeatLED(PA_3);
extern CAN can;

int main() {
	printf("Successfully started program, %d.\n", PRIMARY);
    CANMessage msg;

	init(initSucceed);

#if PRIMARY 
	printf("Primary board set\n");
	Ticker masterHeartbeat;
//	masterHeartbeat.attach(&heartbeat, 1);
#endif
	while(1) {
		if(can.read(msg)) {
			canLogger(&msg);
			canHandler(&msg);	
			heartBeatLED = !heartBeatLED;
		}
	}
    return 0;   
}
