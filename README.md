# Phisher
Phishing firmware for the ESP32 using: 
* Access Point Captive Portal
* [ESPAsyncWebServer](https://github.com/me-no-dev/ESPAsyncWebServer)
* DNS Server 
* [WebSockets](https://github.com/Links2004/arduinoWebSockets/tree/master)
* [ArduinoJson](https://github.com/bblanchon/ArduinoJson)
* [LinkedList](https://github.com/ivanseidel/LinkedList/)

**DEVELOPED FOR EDUCATIONAL PURPOSES**

# Captive Portal
Main Captive Portal ( It is extremely easy to change this html to whatever page source you want )

![Google Login Portal](https://github.com/user-attachments/assets/8c280ccd-db60-46c7-9ba9-daaac468b154)

# Admin Credentials
To change Admin User and Password just go to the `portal.h` file and change them.

````
// ADMIN PAGE
const char *auser = "admin";
const char *apass = "password";
````

# Admin Panel
Reachable from the captive portal, from any device using specific login details

![Phisher Admin Panel](https://github.com/user-attachments/assets/a5a399ea-a1c1-4f2e-877a-210a160d23cf)

# Console Logging
Console logging for the LCD screen on the M5StickCPlus2 (I will mention that you can run the firmware in headless mode, which would have no physical graphics.)

In `console.h` file
````
// Set to false if you want to see the LCD Console.
#define HEADLESS true
````

![Console Mockup](https://github.com/user-attachments/assets/a121162a-2272-4080-99bc-7f1c5219ff88)
