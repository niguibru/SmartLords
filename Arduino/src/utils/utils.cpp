#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>

void blink() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
  digitalWrite(LED_BUILTIN, HIGH);
}

void printDebugTitle(String context, String title) {
    Serial.print(">> ");
    Serial.print(context);
    Serial.print(" - ");
    Serial.println(title);
}

void printDebugKeyValue(String key, String value) {
    Serial.print("   ");
    Serial.print(key);
    Serial.print(": ");
    Serial.println(value);
}
