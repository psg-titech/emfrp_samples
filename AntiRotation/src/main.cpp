/*
 * Rotation Resistance Demo for Zumo32U4 / Zumo Robot for Arduino
 * (adapted from RotationResist demo for Zumo32U4)
 * Copyright (c) 2017 Takuo Watanabe
 */

#include <Wire.h>
#include <Zumo32U4.h>

#include "AntiRotation.h"

L3G gyro;
Zumo32U4Motors motors;

int16_t gyroOffset;

void Input(int *gyroZ, int *t) {
    gyro.read();
    *gyroZ = gyro.g.z - gyroOffset;
    *t = micros();
}

void Output(int *motorL, int *motorR) {
    motors.setSpeeds(*motorL, *motorR);
}

void turnSensorSetup() {
    digitalWrite(LED_BUILTIN, HIGH);
    Wire.begin();
    gyro.init();

    // 800 Hz output data rate,
    // low-pass filter cutoff 100 Hz
    gyro.writeReg(L3G::CTRL1, 0b11111111);

    // 2000 dps full scale
    gyro.writeReg(L3G::CTRL4, 0b00100000);

    // High-pass filter disabled
    gyro.writeReg(L3G::CTRL5, 0b00000000);

    // Calibrate the gyro.
    int32_t total = 0;
    for (uint16_t i = 0; i < 1024; i++) {
        while(!gyro.readReg(L3G::STATUS_REG) & 0x08);
        gyro.read();
        total += gyro.g.z;
    }
    gyroOffset = total / 1024;
    digitalWrite(LED_BUILTIN, LOW);
}

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    turnSensorSetup();
    delay(500);
    ActivateAntiRotation();
}

void loop() {
}
