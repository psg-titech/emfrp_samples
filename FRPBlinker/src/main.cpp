#include <mbed.h>
#include "FRPBlinker.h"

Timer timer;
DigitalOut _led(LED1);

void Input(int *msec) {
    *msec = timer.read_ms();
}

void Output(int *led) {
    _led = *led;
}

int main() {
    timer.start();
    ActivateFRPBlinker();
}
