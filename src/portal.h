#pragma once

#include <DNSServer.h>
#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h> 
#include <esp_wifi.h>

#include "global.h"

// WI-FI SETTINGS
const char *ssid = "Free Wifi";
const int max_clients = 4;
const int wifi_channel = 6;

// ADMIN PAGE
const char *auser = "admin";
const char *apass = "password";

// AP CONSTANTS
const IPAddress localIP(192, 168, 4, 1);
const IPAddress subnetMask(255, 255, 255, 0);

const String localIPURL = "http://192.168.4.1";
