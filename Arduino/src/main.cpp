#include <Arduino.h>
#include "./networking/wifi/wifi.h"
#include "./networking/ota/ota.h"
#include "./networking/mqtt/mqtt.h"

void setup() {
    Serial.begin(115200);
    Serial.println("");
    pinMode(LED_BUILTIN, OUTPUT);

    wifi_setup();
    ota_setup();
    mqtt_setup();
}

void loop() {
    mqtt_loop();
}
