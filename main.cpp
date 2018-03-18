#include "mbed.h"
#include "initialize.h"
#include "CanFunctions.h"
#include "main.h"
#include "logging.h"

DigitalOut initSucceed(PA_0);
DigitalOut errorPin(PA_1);
DigitalOut heartBeatLED(PA_3);
extern CAN can;
extern Serial pc;

typedef enum{
	printStatus = 1
} Command;

void commandline() {
	char *input = (char*) malloc(100*sizeof(char));
	while(true) {
		if(pc.readable()) {
			pc.gets(input,100);
			if (strcmp(input, "printStatus")) {
				printPodStatus();
			}
		} else {
			Thread::wait(500);
		}
	}
	free(input);
}

void CanListener() {
	CANMessage msg;
	while(true) {
		if(can.read(msg)) {
//			canLogger(&msg);
			canHandler(&msg);
		}
	}
	
}

int main() {
	init(initSucceed);

	Thread cli, canBus;
	cli.start(commandline);
	canBus.start(CanListener);

	while(true) {
		Thread::wait(1000);
	}
	
    return 0;   
}
