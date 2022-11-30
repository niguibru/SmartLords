#include <Arduino.h>
#include "./networking/wifi/wifi.h"
#include "./networking/ota/ota.h"
#include "./networking/mqtt/mqtt.h"

//---- WiFi settings
const char* wifi_name = "BT-NMCJWC";
const char* wifi_password = "bLXRnYmP9FJQR6";

void setup() {
    Serial.begin(115200);
    Serial.println("");
    pinMode(LED_BUILTIN, OUTPUT);

    wifi_setup(wifi_name, wifi_password);
    ota_setup();
    mqtt_setup();
}

void loop() {
    mqtt_loop();
}
