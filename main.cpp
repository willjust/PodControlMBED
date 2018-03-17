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

int main() {
	char *input = (char*)malloc(100*sizeof(char));

	printf("Successfully started program, %d.\n\r", PRIMARY);
    CANMessage msg;

	init(initSucceed);

#if PRIMARY 
	printf("Primary board set\n\r");
	Ticker masterHeartbeat;
	//masterHeartbeat.attach(&heartbeat, 1);
#endif
	while(1) {
		pc.gets(input, 100*sizeof(char));
		printf("%s\n\r", input);
		switch (input) {
			case "printStatus":
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
