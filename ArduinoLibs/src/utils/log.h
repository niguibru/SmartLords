#ifndef LOG_H
#define LOG_H

#include <ArduinoJson.h>

void log_setup();
void log_title(String context, String title);
void log_keyValue(String key, String value);
void log_keyValue(String key, unsigned long value);

#endif