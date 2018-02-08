#include "mbed.h"
#include "initialize.h"
#include "CanFunctions.h"

char PRIMARY = 0;
DigitalOut initSucceed(PB_0);
DigitalOut errorPin(PB_1);


int main() {
    init(initSucceed);
#if PRIMARY 
	Ticker masterHeartbeat;
	masterHeartbeat.attach(&heartbeat, 1);
#endif
	while(1) {

	}
    return 0;   
}
