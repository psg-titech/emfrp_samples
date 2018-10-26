#include <M5Stack.h>
#include <DHT12.h>
#include "FanController.h"

DHT12 dht12;
TickType_t lastWakeTime;
const uint8_t fan_pin = G2;

const int lbl_x = 170;
const int dat_x = lbl_x + 20;
const int tmp_y = 30;
const int hmd_y = tmp_y + 50;
const int di_y = hmd_y + 50;
const int ctime_y = di_y + 60;
const int dat_w = 320 - dat_x;
const int dat_h = 50;
const int dat2_h = 40;

// Taken from Free_Fonts.h
#define GFXFF 1
#define FF19 &FreeSans18pt7b
#define FF24 &FreeSansBold24pt7b

#define LFONT1 FF24
#define DFONT1 FF24
#define LFONT2 FF19
#define DFONT2 FF19

void setup() {
    M5.begin();
    Wire.begin();
    pinMode(fan_pin, OUTPUT);

    M5.Lcd.setFreeFont(LFONT1);
    M5.Lcd.setTextColor(TFT_WHITE, TFT_BLACK);
    M5.Lcd.setTextDatum(TR_DATUM);
    M5.Lcd.drawString("temp:", lbl_x, tmp_y, GFXFF);
    M5.Lcd.setTextDatum(TR_DATUM);
    M5.Lcd.drawString("humid:", lbl_x, hmd_y, GFXFF);
    M5.Lcd.setTextDatum(TR_DATUM);
    M5.Lcd.drawString("di:", lbl_x, di_y, GFXFF);
    M5.Lcd.setFreeFont(LFONT2);
    M5.Lcd.setTextDatum(TR_DATUM);
    M5.Lcd.drawString("ctime:", lbl_x, ctime_y, GFXFF);

    lastWakeTime = xTaskGetTickCount();
    ActivateFanController();
}

void loop() {}

void Input(double *tmp, double *hmd, int *clock) {
    vTaskDelayUntil(&lastWakeTime, 500 / portTICK_PERIOD_MS);

    dht12.update();
    static float otmpf = -100;
    static float ohmdf = -100;
    float tmpf = dht12.temperature();
    float hmdf = dht12.humidity();
    *tmp = (double)tmpf;
    *hmd = (double)hmdf;
    *clock = millis() / 1000;

    M5.Lcd.setFreeFont(DFONT1);
    M5.Lcd.setTextColor(TFT_YELLOW, TFT_BLACK);
    if (tmpf != otmpf) {
        otmpf = tmpf;
        M5.Lcd.fillRect(dat_x, tmp_y, dat_w, dat_h, TFT_BLACK);
        M5.Lcd.setTextDatum(TL_DATUM);
        M5.Lcd.drawFloat(tmpf, 1, dat_x, tmp_y, GFXFF);
    }
    if (hmdf != ohmdf) {
        ohmdf = hmdf;
        M5.Lcd.fillRect(dat_x, hmd_y, dat_w, dat_h, TFT_BLACK);
        M5.Lcd.setTextDatum(TL_DATUM);
        M5.Lcd.drawFloat(hmdf, 1, dat_x, hmd_y, GFXFF);
    }
}

void Output(double *di, int *fan, int *ctime) {
    float dif = (float)*di;
    static float odif = -1000;
    static int octime = -1;
    M5.Lcd.setFreeFont(DFONT1);
    M5.Lcd.setTextColor(TFT_CYAN, TFT_BLACK);
    if (odif != dif) {
        odif = dif;
        M5.Lcd.fillRect(dat_x, di_y, dat_w, dat_h, TFT_BLACK);
        M5.Lcd.setTextDatum(TL_DATUM);
        M5.Lcd.drawFloat(dif, 1, dat_x, di_y, GFXFF);
    }
    M5.Lcd.setFreeFont(DFONT2);
    M5.Lcd.setTextColor(TFT_PINK, TFT_BLACK);
    if (octime != *ctime) {
        octime = *ctime;
        M5.Lcd.fillRect(dat_x, ctime_y, dat_w, dat2_h, TFT_BLACK);
        M5.Lcd.setTextDatum(TL_DATUM);
        M5.Lcd.drawNumber(*ctime, dat_x, ctime_y, GFXFF);
    }
    digitalWrite(fan_pin, *fan);
}
