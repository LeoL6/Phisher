# Phisher
Phishing firmware for the ESP32 using: 
* Access Point Captive Portal
* [ESPAsyncWebServer](https://github.com/me-no-dev/ESPAsyncWebServer)
* DNS Server 
* [WebSockets](https://github.com/Links2004/arduinoWebSockets/tree/master)
* [ArduinoJson](https://github.com/bblanchon/ArduinoJson)
* [LinkedList](https://github.com/ivanseidel/LinkedList/)

**DESIGNED FOR EDUCATIONAL PURPOSES**

# Captive Portal
Main Captive Portal ( It is extremely easy to change this html to whatever page you want )

![Google Login Portal](https://github.com/user-attachments/assets/8c280ccd-db60-46c7-9ba9-daaac468b154)

# Admin Credentials
To change Admin User and Password just go to the `portal.h` file and change them.

````
// ADMIN PAGE
const char *auser = "admin";
const char *apass = "password";
````

# Admin Panel
Reachable from captive portal on any device using specific logins

![Phisher Admin Panel](https://github.com/user-attachments/assets/a5a399ea-a1c1-4f2e-877a-210a160d23cf)
