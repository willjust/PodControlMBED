

all:
	mbed compile -t GCC_ARM -mNUCLEO_F303K8 
p: 
	mbed compile -t GCC_ARM -mNUCLEO_F303K8
	cp BUILD/NUCLEO_F303K8/GCC_ARM/PodControlMBED.bin /run/media/justin/NODE_F303K8
s:
	mbed compile -t GCC_ARM -mNUCLEO_F303K8
	cp BUILD/NUCLEO_F303K8/GCC_ARM/PodControlMBED.bin /run/media/justin/NODE_F303K81
l432:
	mbed compile -t GCC_ARM -mNUCLEO_L432KC
	cp BUILD/NUCLEO_L432KC/GCC_ARM/PodControlMBED.bin /run/media/justin/NODE_L432KC

