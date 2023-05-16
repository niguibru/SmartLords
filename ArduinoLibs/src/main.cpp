#include <Arduino.h>
#include "config.h"
#include "./utils/log.h"
#include "./utils/arrays.h"
#include "./networking/wifi/wifi.h"
#include "./networking/ota/ota.h"
#include "./networking/mqtt/mqtt.h"
#include "./led/ledBuiltin.h"
#include "./led/ledStrip.h"
#include "./sensors/moisture.h"

// LED BUILTIN
LedBuiltin led_builtin = LedBuiltin();
const String MQTT_SUBSCRIBER_LED_BUILTIN_STATE_UPDATE = "led-builtin/state/update";
// LED STRIP
LedStrip led_strip = LedStrip(4);
const String MQTT_SUBSCRIBER_LED_STRIP_STATE_UPDATE = "led-strip/state/update";
// MOISTURE SENSOR
MoistureSensor moisture_sensor = MoistureSensor(0);
const String MQTT_SUBSCRIBER_MOISTURE_PUBLISH = "moisture-sensor/state/publish";
const String MQTT_PUBLISHER_MOISTURE_STATE = "moisture-sensor/state";

// NETWORKING
Wifi wifi = Wifi();
OTAUpdate ota = OTAUpdate();
MQTT mqtt = MQTT();

// NETWORKING - MQTT
const String MQTT_TOPICS_TO_SUBSCRIBE[] = { 
    MQTT_SUBSCRIBER_LED_BUILTIN_STATE_UPDATE,
    MQTT_SUBSCRIBER_LED_STRIP_STATE_UPDATE,
    MQTT_SUBSCRIBER_MOISTURE_PUBLISH
};
void mqtt_messageArrived(String topic, JsonObject jsonPayload) {
    // LED BUILTIN
    if (topic == MQTT_SUBSCRIBER_LED_BUILTIN_STATE_UPDATE) {
        led_builtin.updateState(jsonPayload["state"]);
    }
    // LED STRIP
    if (topic == MQTT_SUBSCRIBER_LED_STRIP_STATE_UPDATE) {
        led_strip.updateState(jsonPayload["state"]);
    }
    // MOISTURE SENSOR
    if (topic == MQTT_SUBSCRIBER_MOISTURE_PUBLISH) {
        mqtt.publish(MQTT_PUBLISHER_MOISTURE_STATE, moisture_sensor.getState());
    }
}

void setup() {
    log_setup();

    // NETWORKING
    wifi.setup(wifi_name, wifi_password);
    ota.setup();
    mqtt.setup(MQTT_TOPICS_TO_SUBSCRIBE, arraySize(MQTT_TOPICS_TO_SUBSCRIBE), mqtt_messageArrived);

    // LED BUILTIN
    led_builtin.setup();
    // LED STRIP
    led_strip.setup();
}

void loop() {
    // NETWORKING
    mqtt.loop();

    // LED BUILTIN
    led_builtin.loop();
    // LED STRIP
    led_strip.loop();
}
