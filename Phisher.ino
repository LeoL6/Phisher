#include "src/global.h"
 
void setup() {
  global_setup();

  tft.setCursor((tft.width() / 2) - (tft.textWidth("Click to open portal") / 2), 80);
  tft.print("Click to open portal");
}
 
void loop() {
  global_loop();

  if(StickCP2.BtnA.wasClicked()) {
    if(!isPortalOpen()) {
      openPortal();
    } else {
      closePortal();

      tft.setCursor((tft.width() / 2) - (tft.textWidth("Click to open portal") / 2), 80);
      tft.print("Click to open portal");
    }
  }

  if(isPortalOpen()) {
    // portalLoop();

    tft.setCursor((tft.width() / 2) - (tft.textWidth("Click to close portal") / 2), 80);
    tft.print("Click to close portal");
  }
}