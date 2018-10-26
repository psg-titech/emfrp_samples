/*
 * Controlls Zumo32U4 to face uphill
 * (adapted from FaceUphill demo for Zumo32U4)
 * Copyright (c) 2017 Takuo Watanabe
 */

#include <Wire.h>
#include <Zumo32U4.h>

#include "FaceUphill.h"

LSM303 lsm303;
Zumo32U4Motors motors;
Zumo32U4Encoders encoders;

void Input(int *accX, int *accY, int *encL, int *encR) {
    lsm303.read();
    *accX = lsm303.a.x;
    *accY = lsm303.a.y;
    *encL = encoders.getCountsLeft();
    *encR = encoders.getCountsRight();
}

void Output(int *motorL, int *motorR) {
    motors.setSpeeds(*motorL, *motorR);
}

void setup() {
    Wire.begin();
    lsm303.init();
    lsm303.enableDefault();
    ActivateFaceUphill();
}

void loop() {
}
