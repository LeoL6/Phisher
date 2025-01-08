#include "src/global.h"
 
void setup() {
  global_setup();
}
 
void loop() {
  global_loop();

  if(StickCP2.BtnA.wasClicked()) {
    if(!isPortalOpen()) {
      openPortal();
    } else {
      closePortal();
    }
  }

  if(isPortalOpen()) {
    portalLoop();
  }
}