# FanController
A simple fan controller for M5Stack

## To build and run
Connect your M5Stack via USB and do the following.

```sh
$ (cd src && make)
$ platformio run -t upload
```

## Configuration

* Connect I2C port to DHT12.
* Connect GPIO pin #2 to a relay controller circuit.

## Requirements

* [M5Stack Core](http://www.m5stack.com)
* DHT12 (I2C Temperature-Humidity Sensor)
  - included in [this kit](https://www.aliexpress.com/store/product/M5Stack-Official-Experimental-Proto-Board-Set-included-DHT12-Bus-Socke-Grove-Cable-for-ESP32-Basic-Kit/3226069_32841004439.html)
* A relay to control an electric fan
  - e.g. [Grove - Relay](https://www.seeedstudio.com/Grove-Relay-p-769.html)
