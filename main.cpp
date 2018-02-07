#include "mbed.h"
#include "initialize.h"

char PRIMARY = 0;
DigitalOut initSucceed(PB_0);

int main() {
    init(initSucceed);
    return 0;   
}
