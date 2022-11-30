#include <Arduino.h>
#include "./networking/wifi/wifi.h"
#include "./networking/ota/ota.h"
#include "./networking/mqtt/mqtt.h"
#include "./led/led.h"
#include "./utils/utils.h"

//---- WiFi settings
const char* wifi_name = "BT-NMCJWC";
const char* wifi_password = "bLXRnYmP9FJQR6";

void setup() {
  initial_setup();
  // Networking
  wifi_setup(wifi_name, wifi_password);
  ota_setup();
  mqtt_setup();
  // Led
  led_setup();
}

void loop() {
  // Networking
  mqtt_loop();
  // Led
  led_loop();
  setRainbow();
}
