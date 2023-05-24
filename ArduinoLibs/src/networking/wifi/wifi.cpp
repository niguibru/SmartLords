#include "wifi.h"
#include "./utils/log.h"

// Debug
const String logContext = "WiFi";

void Wifi::setup(const char * name, const char * pass) {
  delay(10);

  Log::title(logContext, "Connecting");
  Log::keyValue("Network", name);

  WiFi.enableInsecureWEP(true);
  WiFi.begin(name, pass);

  Serial.print("   .");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");

  randomSeed(micros());

  Log::title(logContext, "Connected");
  Log::keyValue("IP Address", WiFi.localIP().toString());
}
