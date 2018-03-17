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

int main() {
	char *input = (char*)malloc(100*sizeof(char));
	Command in;
    CANMessage msg;

	init(initSucceed);

	while(1) {
		pc.gets(input, 100*sizeof(char));
		printf("%s\n\r", input);
		switch (in) {
			case 1:
				printPodStatus();
				break;
			default:
				printf("Commands\r\n");
				printf("\tprintStatus - Prints BMS/RMS data.\r\n");

		}
		if(can.read(msg)) {
//			canLogger(&msg);
//			canHandler(&msg);	
		}
	}

	
	free(input);
    return 0;   
}
