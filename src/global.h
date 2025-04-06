#pragma once

#include "M5StickCPlus2.h"

#include "console.h"

#define MAX_VOLTAGE 4300.0; // PUT THE BATTERY AMOUNT ON THE HTML PAGE, NEAR THE TOP RIGHT

void global_setup();
void global_loop();

// void openPortalSSID(const char *ssid);
void openPortalSSID(String ssid);
void openPortal();
void closePortal();
void portalLoop();
bool isPortalOpen();
String getSSID();
