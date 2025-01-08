#include "global.h"

void global_setup() {
  auto cfg = M5.config();
  StickCP2.begin(cfg);

  Serial.setTxBufferSize(1024);
  Serial.begin(115200);
  Serial.println();

  Console console;

  console.log("System Initialized");
}

void global_loop() {
  StickCP2.update();
}
