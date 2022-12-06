#include <Arduino.h>
#include "./utils/utils.h"
#include "./networking/wifi/wifi.h"
#include "./networking/ota/ota.h"
#include "./networking/mqtt/mqtt.h"
#include "./pirSensor/pir.h"

//---- WiFi settings
const char* wifi_name = "BT-NMCJWC";
const char* wifi_password = "bLXRnYmP9FJQR6";

void setup() {
  initial_setup();
  // Networking
  wifi_setup(wifi_name, wifi_password);
  ota_setup();
  mqtt_setup();
  // PIR
  pir_setup();
}

void loop() {
  // Networking
  mqtt_loop();
  // PIR
  pir_loop();
}
