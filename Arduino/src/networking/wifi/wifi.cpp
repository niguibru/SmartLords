#include "wifi.h"
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "./utils/utils.h"

// Debug
const String logContext = "WiFi";

void wifi_setup(const char * name, const char * pass) {
  delay(10);

  printDebugTitle(logContext, "Connecting");
  printDebugKeyValue("Network", name);

  WiFi.enableInsecureWEP(true);
  WiFi.begin(name, pass);

  Serial.print("   .");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");

  randomSeed(micros());

  printDebugTitle(logContext, "Connected");
  printDebugKeyValue("IP Address", WiFi.localIP().toString());
}
