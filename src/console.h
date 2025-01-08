#ifndef CONSOLE_H
#define CONSOLE_H

#include "global.h"

#include <deque>

#define TEXT_SCALE 1.2
#define tft M5.Lcd

class Console {
public:
    Console();
    void log(const String& message); // Adds a new log message
    void clear();                         // Clears all log messages

private:
    void drawConsole();                   // Renders logs to the screen

    int screenWidth, screenHeight, textSize, maxLines;
    std::deque<String> messages;          // Stores log messages
};

#endif // CONSOLE_H