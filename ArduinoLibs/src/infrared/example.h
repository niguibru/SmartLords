/*
#include <Arduino.h>
#include "./utils/log.h"
#include "./led/led.h"
#include "./infrared/ir_receiver.h"
#include "./infrared/ir_led.h"
#include "./networking/wifi/wifi.h"
#include "./networking/ota/ota.h"
#include "./networking/mqtt/mqtt.h"

// WiFi Credentials
const char* wifi_name = "BT-NMCJWC";
const char* wifi_password = "bLXRnYmP9FJQR6";

// LED
Led led_builtin(LED_BUILTIN);

// IR
// IR_Receiver ir_receiver(2);
// IR_Led ir_led(0);

// MQTT
const String MQTT_SUBSCRIBER_LED_OFF = "led/off";
const String MQTT_SUBSCRIBER_LED_ON = "led/on";
const String MQTT_SUBSCRIBER_LED_BLINK = "led/blink";
const String MQTT_SUBSCRIBER_IR_SEND = "infrared/send";
const String MQTT_TOPICS_TO_SUBSCRIBE[] = { 
    MQTT_SUBSCRIBER_LED_OFF, 
    MQTT_SUBSCRIBER_LED_ON, 
    MQTT_SUBSCRIBER_LED_BLINK,
    MQTT_SUBSCRIBER_IR_SEND
};
void mqtt_messageArrived(String topic, StaticJsonDocument<1000> jsonPayload) {
    if (topic == MQTT_SUBSCRIBER_LED_OFF) {
        led_builtin.off();
    }
    if (topic == MQTT_SUBSCRIBER_LED_ON) {
        led_builtin.on();
    }
    if (topic == MQTT_SUBSCRIBER_LED_BLINK) {
        led_builtin.blink();
    }
    if (topic == MQTT_SUBSCRIBER_IR_SEND) {
        JsonArray jsonArray = jsonPayload["data"].as<JsonArray>();
        // ir_led.send(jsonArray);
    }
}

void setup() {
    log_setup();

    // Networking
    wifi_setup(wifi_name, wifi_password);
    ota_setup();
    mqtt_setup(MQTT_TOPICS_TO_SUBSCRIBE, 4, mqtt_messageArrived);

    led_builtin.setup();
}

void loop() {
    // Networking
    mqtt_loop();

    // IR_RECEIVER
    // ir_receiver.loop();
}
*/