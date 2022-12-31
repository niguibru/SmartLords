#include "wifi.h"
#include <ESP8266WiFi.h>
#include "./utils/log.h"

// Debug
const String logContext = "WiFi";

void wifi_setup(const char * name, const char * pass) {
  delay(10);

  log_title(logContext, "Connecting");
  log_keyValue("Network", name);

  WiFi.enableInsecureWEP(true);
  WiFi.begin(name, pass);

  Serial.print("   .");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");

  randomSeed(micros());

  log_title(logContext, "Connected");
  log_keyValue("IP Address", WiFi.localIP().toString());
}
