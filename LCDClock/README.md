# LCDClock
A simple digital clock (a sample application included in Emfrp distribution)  
Originally developed by [Kensuke Sawada](https://github.com/sawaken)

## To run
Connect your mbed via USB and do the following.

```sh
$ (cd src && make)
$ platformio run -t upload
```

## Functions
* Center (push) button (of joystick) toggles on-off of time-set mode.
* Right button moves cursor of time-set targets (hour, minute and second).
* Up button raises time-set target's value (+1) if time-set mode is on.

## Requirements
* [mbed LPC1768](https://os.mbed.com/platforms/mbed-LPC1768/)
* [mbed application board](https://os.mbed.com/cookbook/mbed-application-board)
