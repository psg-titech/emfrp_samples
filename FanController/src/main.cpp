#if defined(ARDUINO_M5Stack_Core_ESP32) || defined(ARDUINO_M5STACK_FIRE)
#include <M5Stack.h>
#elif defined(ARDUINO_M5Stick_C)
#include <M5StickC.h>
#endif

#include "FanController.h"

TickType_t lastWakeTime;

#if defined(ARDUINO_M5Stack_Core_ESP32) || defined(ARDUINO_M5STACK_FIRE)
const int lbl_x = 170;
const int dat_x = lbl_x + 20;
const int tmp_y = 30;
const int hmd_y = tmp_y + 50;
const int di_y = hmd_y + 50;
const int fan_y = di_y + 50;
const int dat_w = 320 - dat_x;
const int dat_h = 50;
const int dat2_h = 40;

// Taken from Free_Fonts.h
#define GFXFF 1
#define FF19 &FreeSans18pt7b
#define FF24 &FreeSansBold24pt7b

#define LFONT FF24
#define DFONT FF24

#elif defined(ARDUINO_M5Stick_C)

#endif

#if defined(FAN_RELAY)
const uint8_t fan_pin = FAN_PIN;

void initialize_fan() {
    pinMode(fan_pin, OUTPUT);
    digitalWrite(fan_pin, LOW);
}

void update_fan(int s) {
    digitalWrite(fan_pin, s);
}
#elif defined(FAN_PWM)
const int fan_pin = FAN_PIN;

void initialize_fan() {
    ledcSetup(0, 10000, 10);
    ledcAttachPin(fan_pin, 0);
}

void update_fan(int s) {
    ledcWrite(0, s ? 256 : 0);
}
#endif

#if defined(SENSOR_DHT12)
#include <DHT12.h>
DHT12 dht12;

void update_sensors() {
    dht12.update();
}

float get_temperature() {
    return dht12.temperature();
}

float get_humidity() {
    return dht12.humidity();
}

#elif defined(SENSOR_ENVII)
#include "M5_ENV.h"
SHT3X sht30;

void update_sensors() {
    sht30.get();
}

float get_temperature() {
    return sht30.cTemp;
}

float get_humidity() {
    return sht30.humidity;
}
#endif

void setup() {
    M5.begin();
#if defined(ARDUINO_M5Stick_C)
    Wire.begin(0, 26);
#else
    Wire.begin();
#endif
    initialize_fan();
    
#if defined(ARDUINO_M5Stack_Core_ESP32) || defined(ARDUINO_M5STACK_FIRE)
    M5.Lcd.setFreeFont(LFONT);
    M5.Lcd.setTextColor(TFT_WHITE, TFT_BLACK);
    M5.Lcd.setTextDatum(TR_DATUM);
    M5.Lcd.drawString("temp:", lbl_x, tmp_y, GFXFF);
    M5.Lcd.setTextDatum(TR_DATUM);
    M5.Lcd.drawString("humid:", lbl_x, hmd_y, GFXFF);
    M5.Lcd.setTextDatum(TR_DATUM);
    M5.Lcd.drawString("di:", lbl_x, di_y, GFXFF);
    M5.Lcd.setTextDatum(TR_DATUM);
    M5.Lcd.drawString("fan:", lbl_x, fan_y, GFXFF);
#elif defined(ARDUINO_M5Stick_C)
    M5.Lcd.setRotation(3);
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setCursor(0, 0, 2);
    M5.Lcd.println("Fan Controller");
#endif
    lastWakeTime = xTaskGetTickCount();
    ActivateFanController();
}

void loop() {}

void Input(double *tmp, double *hmd) {
    vTaskDelayUntil(&lastWakeTime, 500 / portTICK_PERIOD_MS);

    update_sensors();
    static float otmpf = -100;
    static float ohmdf = -100;
    float tmpf = get_temperature();
    float hmdf = get_humidity();
    *tmp = (double)tmpf;
    *hmd = (double)hmdf;
#if defined(ARDUINO_M5Stack_Core_ESP32) || defined(ARDUINO_M5STACK_FIRE)
    M5.Lcd.setFreeFont(DFONT);
    M5.Lcd.setTextColor(TFT_YELLOW, TFT_BLACK);
#endif
    if (tmpf != otmpf) {
        otmpf = tmpf;
#if defined(ARDUINO_M5Stack_Core_ESP32) || defined(ARDUINO_M5STACK_FIRE)
        M5.Lcd.fillRect(dat_x, tmp_y, dat_w, dat_h, TFT_BLACK);
        M5.Lcd.setTextDatum(TL_DATUM);
        M5.Lcd.drawFloat(tmpf, 1, dat_x, tmp_y, GFXFF);
#elif defined(ARDUINO_M5Stick_C)
        M5.Lcd.setCursor(0, 20, 2);
        M5.Lcd.printf("temp: %2.1f", tmpf);
#endif
    }
    if (hmdf != ohmdf) {
        ohmdf = hmdf;
#if defined(ARDUINO_M5Stack_Core_ESP32) || defined(ARDUINO_M5STACK_FIRE)
        M5.Lcd.fillRect(dat_x, hmd_y, dat_w, dat_h, TFT_BLACK);
        M5.Lcd.setTextDatum(TL_DATUM);
        M5.Lcd.drawFloat(hmdf, 1, dat_x, hmd_y, GFXFF);
#elif defined(ARDUINO_M5Stick_C)
        M5.Lcd.setCursor(0, 40, 2);
        M5.Lcd.printf("humid: %2.1f", hmdf);
#endif
    }
}

void Output(int *fan, double *di) {
    static float odif = -1000;
    static int ofan = -1;
    float dif = (float)*di;

#if defined(ARDUINO_M5Stack_Core_ESP32) || defined(ARDUINO_M5STACK_FIRE)
    M5.Lcd.setFreeFont(DFONT);
    M5.Lcd.setTextColor(TFT_CYAN, TFT_BLACK);
#endif
    if (odif != dif) {
        odif = dif;
#if defined(ARDUINO_M5Stack_Core_ESP32) || defined(ARDUINO_M5STACK_FIRE)
        M5.Lcd.fillRect(dat_x, di_y, dat_w, dat_h, TFT_BLACK);
        M5.Lcd.setTextDatum(TL_DATUM);
        M5.Lcd.drawFloat(dif, 1, dat_x, di_y, GFXFF);
#elif defined(ARDUINO_M5Stick_C)
        M5.Lcd.setCursor(0, 60, 2);
        M5.Lcd.printf("di: %2.1f", dif);
#endif
    }
#if defined(ARDUINO_M5Stack_Core_ESP32) || defined(ARDUINO_M5STACK_FIRE)
    M5.Lcd.setTextColor(TFT_PINK, TFT_BLACK);
#endif
    if (ofan != *fan) {
        ofan = *fan;
#if defined(ARDUINO_M5Stack_Core_ESP32) || defined(ARDUINO_M5STACK_FIRE)
        M5.Lcd.fillRect(dat_x, fan_y, dat_w, dat2_h, TFT_BLACK);
        M5.Lcd.setTextDatum(TL_DATUM);
        M5.Lcd.drawString(*fan ? "ON" : "OFF", dat_x, fan_y, GFXFF);
#elif defined(ARDUINO_M5Stick_C)
        M5.Lcd.setCursor(80, 60, 2);
        M5.Lcd.printf(*fan ? "fan: ON  " : "fan: OFF ");
#endif
    }
    update_fan(*fan);
}
