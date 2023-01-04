#include <Arduino.h>

void log_setup() {
  Serial.begin(115200);
  Serial.println("");
}

void log_debug(String value) {
  Serial.print("--------------");
  Serial.println("--------------");
  Serial.println(value);
  Serial.print("--------------");
  Serial.println("--------------");
}

void log_title(String context, String title) {
  Serial.print(">> ");
  Serial.print(context);
  Serial.print(" - ");
  Serial.println(title);
}

void log_keyValue(String key, String value) {
  Serial.print("   ");
  Serial.print(key);
  Serial.print(": ");
  Serial.println(value);
}

void log_keyValue(String key, unsigned long value) {
  Serial.print("   ");
  Serial.print(key);
  Serial.print(": ");
  Serial.println(value);
}