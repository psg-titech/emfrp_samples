/*
 * Balancing Demo for Pololu Balboa 32U4 Robot
 * (adapted from Balancer demo for Balboa 32U4)
 * Copyright (c) 2017 Takuo Watanabe
 */

#include <Balboa32U4.h>
#include <Wire.h>
#include <LSM6.h>

#include "Balancer.h"

const uint8_t UPDATE_TIME_MS = 10;
const uint8_t CALIBRATION_ITERATIONS = 100;

LSM6 imu;
Balboa32U4Motors motors;
Balboa32U4Encoders encoders;
Balboa32U4ButtonA buttonA;

int32_t gYZero;
uint16_t lastMs = 0;

void setup() {
    ledRed(1);
    // Initialize IMU.
    Wire.begin();
    imu.init();
    imu.enableDefault();
    imu.writeReg(LSM6::CTRL2_G, 0b01011000); // 208 Hz, 1000 deg/s
    // Wait for IMU readings to stabilize.
    delay(1000);
    // Calibrate the gyro.
    int32_t total = 0;
    for (int i = 0; i < CALIBRATION_ITERATIONS; i++) {
        imu.read();
        total += imu.g.y;
        delay(1);
    }
    gYZero = total / CALIBRATION_ITERATIONS;
    ledRed(0);
    motors.setSpeeds(0, 0);

    // start
    ActivateBalancer();
}

void loop() {}

void Input(int32_t *gyroY, int32_t *accX, int32_t *encL, int32_t *encR) {
    uint16_t ms;
    do {
        ms = millis();
    } while (ms - lastMs < UPDATE_TIME_MS);
    lastMs = ms;
    imu.read();
    *gyroY = (imu.g.y - gYZero) / 29;
    *accX = imu.a.x;
    *encL = encoders.getCountsLeft();
    *encR = encoders.getCountsRight();
}

void Output(int32_t *motorL, int32_t *motorR, int *ledR, int *ledG, int *ledY) {
    motors.setSpeeds(*motorL, *motorR);
    ledRed(*ledR);
    ledGreen(*ledG);
    ledYellow(*ledY);
}
