#pragma once

#include "M5StickCPlus2.h"
#include <M5GFX.h>
#include <lgfx/v1/panel/Panel_ST7789.hpp>

#include "arduinoFFT.h"

#define tft M5.Lcd

#define MAX_VOLTAGE 4300.0;

void global_setup();
void global_loop();

void openPortalSSID(const char *ssid);
void openPortal();
void closePortal();
void portalLoop();
bool isPortalOpen();
