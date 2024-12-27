#pragma once
#include "M5StickCPlus2.h"
#include <M5GFX.h>
#include <lgfx/v1/panel/Panel_ST7789.hpp>

// #include <WiFi.h>
// #include <WiFiClient.h>
// #include <WiFiAP.h>

#include <DNSServer.h>
#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h> 

#include <esp_wifi.h>

#include "arduinoFFT.h"

#define tft M5.Lcd

#define MAX_VOLTAGE 4300.0;

void global_setup();
void global_loop();

void openPortal();
void closePortal();
void portalLoop();
bool isPortalOpen();
