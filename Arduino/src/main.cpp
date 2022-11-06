#include <Arduino.h>
#include <AsyncElegantOTA.h>
#include "./networking/wifi/wifi.h"
#include "./networking/mqtt/mqtt.h"

AsyncWebServer server(80);

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  wifi_setup();
  
  AsyncElegantOTA.begin(&server);
  server.begin();

  mqtt_setup();
}

void loop() {
  mqtt_loop();
}
