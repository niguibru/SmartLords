#include <Arduino.h>
#include "config.h"
#include "./utils/log.h"
#include "./utils/arrays.h"
#include "./networking/wifi/wifi.h"
#include "./networking/ota/ota.h"
#include "./networking/mqtt/mqtt.h"
#include "./led/led.h"
#include "./led/ledStrip.h"
#include "./sensors/moisture.h"

// Networking
Wifi wifi = Wifi();
OTAUpdate ota = OTAUpdate();
MQTT mqtt = MQTT();

// Modules
Led led_builtin = Led(LED_BUILTIN);
// LedStrip led_strip = LedStrip(0);
MoistureSensor moisture_sensor = MoistureSensor(0);

// MQTT
const String MQTT_SUBSCRIBER_LED = "led";
const String MQTT_SUBSCRIBER_LED_STRIP = "led-strip";
const String MQTT_SUBSCRIBER_MOISTURE_PUBLISH = "moisture-sensor/state/publish";
const String MQTT_PUBLISHER_MOISTURE_STATE = "moisture-sensor/state";
const String MQTT_TOPICS_TO_SUBSCRIBE[] = { 
    MQTT_SUBSCRIBER_LED,
    MQTT_SUBSCRIBER_LED_STRIP,
    MQTT_SUBSCRIBER_MOISTURE_PUBLISH
};
void mqtt_messageArrived(String topic, JsonObject jsonPayload) {
    JsonObject jsonState = jsonPayload["set_state"].as<JsonObject>();
    // LED    
    if (topic == MQTT_SUBSCRIBER_LED) {
        led_builtin.executeAction(jsonState);
    }
    if (topic == MQTT_SUBSCRIBER_LED_STRIP) {
        // led_strip.state.setFromJson(jsonState);
    }
    // Moisture 
    if (topic == MQTT_SUBSCRIBER_MOISTURE_PUBLISH) {
        mqtt.publish(MQTT_PUBLISHER_MOISTURE_STATE, moisture_sensor.getState());
    }
}

void setup() {
    log_setup();

    // Networking
    wifi.setup(wifi_name, wifi_password);
    ota.setup();
    mqtt.setup(MQTT_TOPICS_TO_SUBSCRIBE, arraySize(MQTT_TOPICS_TO_SUBSCRIBE), mqtt_messageArrived);

    // Modules
    led_builtin.setup();
    // led_strip.setup();
}

void loop() {
    // Networking
    mqtt.loop();

    // Modules
    // led_strip.loop();
}
