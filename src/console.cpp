#include "console.h"

Console::Console() {
  if (!HEADLESS) {
    screenWidth = 240; //tft.width();                    // Default screen width
    screenHeight = 135; //tft.height();                  // Default screen height
    maxLines = (screenHeight - 28) / (TEXT_SCALE * 8);   // Estimate lines based on text size
    tft.setRotation(1);
    tft.setTextColor(TFT_WHITE);
    tft.setTextDatum(middle_center);
    tft.setTextFont(&fonts::Font0);
  } else {
    tft.sleep();
  }
}

void Console::log(const String& logText, LogType logType) {
  if (!HEADLESS) {
    // Calculate line height of current message
    int backLineHeight = std::max(1, (int) std::ceil(logText.length() / (double) MAX_CHARS_PER_LINE));

    while (maxLines < backLineHeight && !messages.empty()) {
        // Calculate line height of message at from of dequeue
        int frontLineHeight = std::max(1, (int) std::ceil(messages.front().text.length() / (double) MAX_CHARS_PER_LINE));

        // Remove old messages
        messages.pop_front();

        // Reclaim lines from old messages
        maxLines += frontLineHeight;
    }

    // Remove lines from current message
    maxLines -= backLineHeight;

    // Create new message
    LogMessage message;
    message.text = logText;
    message.logType = logType;

    // Add the new message 
    messages.push_back(message);

    // Draw the console with the updates lines
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
    tft.setTextColor(TFT_WHITE);
    tft.print(portalOpen ? "Click to close portal" : "Click to open portal");

    tft.fillRoundRect(screenWidth - 20, 10, 10, 10, 4, portalOpen ? TFT_GREEN : TFT_RED);
    tft.drawRoundRect(screenWidth - 20, 10, 10, 10, 4, TFT_WHITE);

    tft.drawRect(0, 25, screenWidth, 1, TFT_WHITE);

    tft.setTextSize(TEXT_SCALE);

    int y = 35;
    for (const auto& message : messages) {
        const String msg = "$" + getSSID() + " - " +  message.text;

        tft.setCursor(5, y);
        tft.setTextColor(static_cast<int>(message.logType));
        tft.print(msg);

        int spacing = std::max(1.0, std::ceil(msg.length() / (double) MAX_CHARS_PER_LINE));

        y += spacing * TEXT_SCALE * 8; // Move to the next line
    }
}
