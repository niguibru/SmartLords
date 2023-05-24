#ifndef Log_H
#define Log_H

#include <Arduino.h>

class Log {
    public:
        static void setup();
        static void title(String context, String title);
        static void keyValue(String key, String value);
        static void keyValue(String key, unsigned long value);
};

#endif