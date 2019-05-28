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

void setup() {
    M5.begin();
    Wire.begin();
    pinMode(21, OUTPUT);
    digitalWrite(21, LOW);
    
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

    lastWakeTime = xTaskGetTickCount();
    ActivateFanController();
}

void loop() {}

void Input(double *tmp, double *hmd) {
    vTaskDelayUntil(&lastWakeTime, 500 / portTICK_PERIOD_MS);

    dht12.update();
    static float otmpf = -100;
    static float ohmdf = -100;
    float tmpf = dht12.temperature();
    float hmdf = dht12.humidity();
    *tmp = (double)tmpf;
    *hmd = (double)hmdf;

    M5.Lcd.setFreeFont(DFONT);
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

void Output(int *fan, double *di) {
    static float odif = -1000;
    static int ofan = -1;
    float dif = (float)*di;

    M5.Lcd.setFreeFont(DFONT);
    M5.Lcd.setTextColor(TFT_CYAN, TFT_BLACK);
    if (odif != dif) {
        odif = dif;
        M5.Lcd.fillRect(dat_x, di_y, dat_w, dat_h, TFT_BLACK);
        M5.Lcd.setTextDatum(TL_DATUM);
        M5.Lcd.drawFloat(dif, 1, dat_x, di_y, GFXFF);
    }
    M5.Lcd.setTextColor(TFT_PINK, TFT_BLACK);
    if (ofan != *fan) {
        ofan = *fan;
        M5.Lcd.fillRect(dat_x, fan_y, dat_w, dat2_h, TFT_BLACK);
        M5.Lcd.setTextDatum(TL_DATUM);
        M5.Lcd.drawString(*fan ? "ON" : "OFF", dat_x, fan_y, GFXFF);
    }
    digitalWrite(21, LOW);
}
