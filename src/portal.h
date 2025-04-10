#pragma once

#include <DNSServer.h>
#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h> 
#include <WebSocketsServer.h>
#include <esp_wifi.h>

#include <LinkedList.h>
#include "ArduinoJson.h"

#include "global.h"

// Include HTML pages
#include "html_pages/login_page.h"
#include "html_pages/admin_panel.h"

// Define Struct for User
typedef struct User {
  String email;
  String pass;
} User;

// WI-FI SETTINGS
String defaultSSID = "Free Wifi";
const int http_port = 80;
const int max_clients = 4;
const int wifi_channel = 6;

// WEBSOCKET SETTINGS
const int ws_port = 1337;

// ADMIN PAGE
const char *auser = "admin";
const char *apass = "password";

// AP CONSTANTS
const IPAddress localIP(192, 168, 4, 1);
const IPAddress subnetMask(255, 255, 255, 0);

const String localIPURL = "http://192.168.4.1";
