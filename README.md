# PodControlMBED
Justin's area to play around with MBED OS related to the Badgerloop Pod 3 (AKA: Not an ICBM)

# Instructions on use
This repo is meant to serve as an MVP (minimumly viable product) for the control system. To do so, no drivers were written and solely the end objectives are produced. To do so, MBED OS is used and therefor requires MBED CLI. 

1. Install MBed CLI
2. Clone directory
3. Run make if using Nucleo 32 -F303K8 or use mbed -t GNU_ARM -m<BOARD>. Feel free to add to make <BOARD NAME> to accelerate dev
