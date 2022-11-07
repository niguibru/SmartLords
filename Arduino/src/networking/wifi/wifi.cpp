#include "wifi.h"
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "./utils/utils.h"

// Debug
const String context = "WiFi";

//---- WiFi settings
const char* wifi_name = "BT-NMCJWC";
const char* wifi_password = "bLXRnYmP9FJQR6";

void wifi_setup() {
  delay(10);

  printDebugTitle(context, "Connecting");
  printDebugKeyValue("Network", wifi_name);

  WiFi.enableInsecureWEP(true);
  WiFi.begin(wifi_name, wifi_password);

  Serial.print("   .");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");

  randomSeed(micros());

  printDebugTitle(context, "Connected");
  printDebugKeyValue("IP Address", WiFi.localIP().toString());
}
