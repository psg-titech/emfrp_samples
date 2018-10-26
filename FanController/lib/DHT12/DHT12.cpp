#include "DHT12.h"

DHT12::DHT12(uint8_t addr8) : _addr7(addr8 >> 1) {
}

uint8_t DHT12::update() {
    Wire.beginTransmission(_addr7);
    Wire.write(0);
    if (Wire.endTransmission() != 0)
        return 1;
    if (Wire.requestFrom(_addr7, (uint8_t)5) != 5)
        return 2;
    Wire.readBytes(data, 5);
    // delay(50);
    if (Wire.available() != 0)
        return 3;
    if (data[0] + data[1] + data[2] + data[3] != data[4])
        return 4;
    _temperature = data[2] + (float)data[3] / 10;
    _humidity = data[0] + (float)data[1] / 10;
    return 0;
}

float DHT12::temperature(bool need_update) {
    if (need_update) update();
    return _temperature;
}

float DHT12::humidity(bool need_update) {
    if (need_update) update();
    return _humidity;
}
