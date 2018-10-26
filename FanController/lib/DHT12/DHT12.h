#ifndef DHT12_h 
#define DHT12_h 
#include "Wire.h"

class DHT12 {
public:
	enum {
		I2C_ADDR = 0xB8
	};
	DHT12(uint8_t addr8 = I2C_ADDR);
	uint8_t update();
	float temperature(bool need_update = false);
	float humidity(bool need_update = false);
private:
	uint8_t _addr7;
	uint8_t data[5];
	float _temperature, _humidity;
};

#endif
