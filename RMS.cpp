#include "BMS.h"

extern CAN can;
extern RMSData *rms;

void RMS_temp1(CANMessage *msg) {
	int offset = 0;
	unsigned char *tmp = msg->data;
	
	memcpy(&rms->temp[0], tmp+offset, sizeof(int)); offset+=sizeof(int);
	memcpy(&rms->temp[1], tmp+offset, sizeof(int)); offset+=sizeof(int);
	memcpy(&rms->temp[2], tmp+offset, sizeof(int)); offset+=sizeof(int);
	memcpy(&rms->temp[3], tmp+offset, sizeof(int)); offset+=sizeof(int);
}


void RMS_temp2(CANMessage *msg) {
	int offset = 0;
	unsigned char *tmp = msg->data;
	
	memcpy(&rms->temp[4], tmp+offset, sizeof(int)); offset+=sizeof(int);
	memcpy(&rms->temp[5], tmp+offset, sizeof(int)); offset+=sizeof(int);
	memcpy(&rms->temp[6], tmp+offset, sizeof(int)); offset+=sizeof(int);
	memcpy(&rms->temp[7], tmp+offset, sizeof(int)); offset+=sizeof(int);
}


void RMS_temp3(CANMessage *msg) {
	int offset = 0;
	unsigned char *tmp = msg->data;
	
	memcpy(&rms->temp[8], tmp+offset, sizeof(int)); offset+=sizeof(int);
	memcpy(&rms->temp[9], tmp+offset, sizeof(int)); offset+=sizeof(int);
	memcpy(&rms->temp[10], tmp+offset,sizeof(int)); offset+=sizeof(int);
	memcpy(&rms->torque, tmp+offset, sizeof(int)); offset+=sizeof(int);
}

void RMS_analogVoltages(CANMessage *msg) {
	int offset = 0;
	unsigned char *tmp = msg->data;

	// 9 bits/value?
	memcpy(&rms->analogIn[0], tmp+offset, 8); 
}

void RMS_digitalInputs(CANMessage *msg) {
	for(int i = 0; i < 8; i++)
		rms->digInput[i] = msg->data[i];
}

void RMS_motorPosition(CANMessage *msg) {
	printf("Recieved analog voltages\r\n");
}

void RMS_current(CANMessage *msg) {
	printf("Recieved analog voltages\r\n");
}


void RMS_voltage(CANMessage *msg) {
	printf("Recieved analog voltages\r\n");
}

void RMS_flux(CANMessage *msg) {
	printf("Recieved analog voltages\r\n");
}

void RMS_intVoltages(CANMessage *msg) {
	printf("Recieved analog voltages\r\n");
}

void RMS_states(CANMessage *msg) {
	printf("Recieved analog voltages\r\n");
}

void RMS_fault(CANMessage *msg) {
	printf("Recieved analog voltages\r\n");
}

void RMS_torque(CANMessage *msg) {
	printf("Recieved analog voltages\r\n");
}

void RMS_modulation(CANMessage *msg) {
	printf("Recieved analog voltages\r\n");
}

void RMS_diagnostics(CANMessage *msg) {
	printf("Recieved analog voltages\r\n");
}

void RMS_firmware(CANMessage *msg) {
	printf("Recieved analog voltages\r\n");
}



int initializeRmsCan(CanHandle *fxnList, int start) {
	int count = 0;
	// Temperatures #1
	fxnList[start + count].header = 0x0A0;
	fxnList[start+count].func = &RMS_temp1;
	count++;

	// Temperatures #2
	fxnList[start + count].header = 0x0A1;
	fxnList[start+count].func = &RMS_temp2;
	count++;

	//Temperatures #3
	fxnList[start+count].header = 0x0A2;
	fxnList[start+count].func = &RMS_temp3;
	count++;

	// Analog Input Voltages
	fxnList[start+count].header = 0x0A3;
	fxnList[start+count].func = &RMS_analogVoltages;
	count++;

	// Digital Input Status
	fxnList[start+count].header = 0x0A4;
	fxnList[start+count].func = &RMS_digitalInputs;
	count++;

	// Motor Position Information
	fxnList[start+count].header = 0x0A5;
	fxnList[start+count].func = &RMS_motorPosition;
	count++;

	// Current Information
	fxnList[start+count].header = 0x0A6;
	fxnList[start+count].func = &RMS_current;
	count++;

	// Voltage Information
	fxnList[start+count].header = 0x0A7;
	fxnList[start+count].func = &RMS_voltage;
	count++;

	// Flux Information
	fxnList[start+count].header = 0x0A8;
	fxnList[start+count].func = &RMS_flux;
	count++;

	// Internal Voltages
	fxnList[start+count].header = 0x0A9;
	fxnList[start+count].func = &RMS_intVoltages;
	count++;

	// Internal STates
	fxnList[start+count].header = 0x0AA;
	fxnList[start+count].func = &RMS_states;
	count++;

	// Fault Codes
	fxnList[start+count].header = 0x0AB;
	fxnList[start+count].func = &RMS_fault;
	count++;

	// Torque and Timer info
	fxnList[start+count].header = 0x0AC;
	fxnList[start+count].func = &RMS_torque;
	count++;

	// Modulation Index & Flux
	fxnList[start+count].header = 0x0AD;
	fxnList[start+count].func = &RMS_modulation;
	count++;

	// Firmware Information
	fxnList[start+count].header = 0x0AE;
	fxnList[start+count].func = &RMS_firmware;
	count++;

	// Diagnostic Information
	fxnList[start+count].header = 0x0AF;
	fxnList[start+count].func = &RMS_diagnostics;
	count++;

	return count;
}
