#include "global.h"

void global_setup() {
  auto cfg = M5.config();
  StickCP2.begin(cfg);

  Serial.setTxBufferSize(1024);
  Serial.begin(115200);
  Serial.println();

  Console console;

  console.log("System Initialized.");
  delay(1000);

  for (int i = 0; i < 10; i++) {
      console.log("Log message " + (String) i);
      delay(500);
  }

  console.clear();
  console.log("Console cleared.");
  // delay(100);
  // console.clear();

  // tft.setRotation(1);
  // tft.setTextColor(TFT_WHITE);
  // tft.setTextDatum(middle_center);
  // tft.setTextFont(&fonts::Font0);
  // tft.setTextSize(1.8);
}

void global_loop() {
  StickCP2.update();
}
