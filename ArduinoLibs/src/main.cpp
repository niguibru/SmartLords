#include <Arduino.h>
#include "./utils/log.h"
#include "./led/led.h"
#include "./led/ledStrip.h"
#include "./networking/wifi/wifi.h"
#include "./networking/ota/ota.h"
#include "./networking/mqtt/mqtt.h"

// Utils
#define arraySize(arg) ((unsigned int) (sizeof (arg) / sizeof (arg [0])))

// WiFi Credentials
// Nico Wifi
const char* wifi_name = "BT-NMCJWC";
const char* wifi_password = "bLXRnYmP9FJQR6";
// Maxi Wifi
// const char* wifi_name = "SKY45015";
// const char* wifi_password = "PRWYMTBPFT";

// LED
Led led_builtin(LED_BUILTIN);
LedStrip led_strip(0);

// MQTT
const String MQTT_SUBSCRIBER_LED = "led";
const String MQTT_SUBSCRIBER_LED_STRIP = "led-strip";
const String MQTT_TOPICS_TO_SUBSCRIBE[] = { 
    MQTT_SUBSCRIBER_LED,
    MQTT_SUBSCRIBER_LED_STRIP
};
void mqtt_messageArrived(String topic, JsonObject jsonPayload) {
    JsonObject jsonState = jsonPayload["set_state"].as<JsonObject>();
    if (topic == MQTT_SUBSCRIBER_LED) {
        led_builtin.executeAction(jsonState);
    }
    if (topic == MQTT_SUBSCRIBER_LED_STRIP) {
        led_strip.state.setFromJson(jsonState);
    }
}

void setup() {
    log_setup();

    // Networking
    wifi_setup(wifi_name, wifi_password);
    ota_setup();
    mqtt_setup(MQTT_TOPICS_TO_SUBSCRIBE, arraySize(MQTT_TOPICS_TO_SUBSCRIBE), mqtt_messageArrived);

    // LED
    led_builtin.setup();
    led_strip.setup();
}

void loop() {
    // Networking
    mqtt_loop();

    // LED
    led_strip.loop();
}
