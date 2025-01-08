#include "console.h"

Console::Console() {
  if (!HEADLESS) {
    screenWidth = 240; //tft.width();                       // Default screen width
    screenHeight = 135; //tft.height();                     // Default screen height
    maxLines = (screenHeight - 28) / (TEXT_SCALE * 8);   // Estimate lines based on text size
    tft.setRotation(1);
    tft.setTextColor(TFT_WHITE);
    tft.setTextDatum(middle_center);
    tft.setTextFont(&fonts::Font0);
  }
}

void Console::log(const String& message) { // IMPLEMENT CUSTOM COLORS FOR EACH MESSAGE AS A SECONDARY METHOD ASWELL
  if (!HEADLESS) {
    if (messages.size() >= maxLines) {
        messages.pop_front(); // Remove the oldest message
    }
    messages.push_back(message); // Add the new message
    drawConsole();
  }
}

void Console::clear() {
  if (!HEADLESS) {
    messages.clear();
    tft.fillScreen(TFT_BLACK); // Clear the screen
  }
}

void Console::drawConsole() {
    tft.fillScreen(TFT_BLACK); // Clear the screen

    tft.setTextSize(1.8);

    const bool portalOpen = isPortalOpen();

    tft.setCursor(5, 15);
    tft.print(portalOpen ? "Click to close portal" : "Click to open portal");

    tft.fillRoundRect(screenWidth - 20, 10, 10, 10, 4, portalOpen ? TFT_GREEN : TFT_RED);
    tft.drawRoundRect(screenWidth - 20, 10, 10, 10, 4, TFT_WHITE);

    tft.drawRect(0, 25, screenWidth, 1, TFT_WHITE);

    tft.setTextSize(TEXT_SCALE);

    int y = 35;
    for (const auto& message : messages) {
        tft.setCursor(5, y);
        tft.print("$" + getSSID() + " - " +  message);
        y += TEXT_SCALE * 8; // Move to the next line
    }
}
