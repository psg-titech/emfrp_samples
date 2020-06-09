#include <M5Stack.h>
#include "DoubleClick.h"

int x, y;

void setup() {
    M5.begin();
    x = M5.Lcd.width() / 2;
    y = M5.Lcd.height() / 2;
    ActivateDoubleClick();
}

void loop() {}

void Input(int *button, int *millis_) {
    *button = m5.BtnA.isPressed();
    *millis_ = millis();
}

void Output(int *led) {
  if (*led) {
      M5.Lcd.fillEllipse(x, y, 100, 100, TFT_YELLOW);
  }
  else {
      M5.Lcd.clearDisplay();
  }
  m5.update();
}
