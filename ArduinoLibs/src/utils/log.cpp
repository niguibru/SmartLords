#include "log.h"

void Log::setup() {
  Serial.begin(115200);
  Serial.println("");
}

void Log::title(String context, String title) {
  Serial.print(">> ");
  Serial.print(context);
  Serial.print(" - ");
  Serial.println(title);
}

void Log::keyValue(String key, String value) {
  Serial.print("   ");
  Serial.print(key);
  Serial.print(": ");
  Serial.println(value);
}

void Log::keyValue(String key, unsigned long value) {
  Serial.print("   ");
  Serial.print(key);
  Serial.print(": ");
  Serial.println(value);
}
