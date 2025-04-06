#ifndef CONSOLE_H
#define CONSOLE_H

#include "global.h"

#include <deque>

#define HEADLESS false
#define TEXT_SCALE 1.2
#define MAX_CHARS_PER_LINE 32

#define tft M5.Lcd

class Console {
public:
    Console();

    enum class LogType {
        INFO = 0x07E0,
        ALERT = 0x001F,
        ERROR = 0xF800
    };

    typedef struct LogMessage {
        String text;

        LogType logType;
    }LogMessage;

    void log(const String& message, LogType logType); // Adds a new log message
    void clear();                                     // Clears all log messages

private:
    void drawConsole();                                 // Renders logs to the screen

    int screenWidth, screenHeight, textSize, maxLines;
    std::deque<LogMessage> messages;                    // Stores log messages
};

#endif // CONSOLE_H