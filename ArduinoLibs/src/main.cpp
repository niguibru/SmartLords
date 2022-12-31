#include <Arduino.h>
#include "./utils/log.h"
#include "./led/led.h"
#include "./networking/wifi/wifi.h"
#include "./networking/ota/ota.h"
#include "./networking/mqtt/mqtt.h"

// LED
Led led_builtin(LED_BUILTIN);

// MQTT
String MQTT_SUBSCRIBER_LED_OFF = "led/off";
String MQTT_SUBSCRIBER_LED_ON = "led/on";
String MQTT_SUBSCRIBER_LED_BLINK = "led/blink";
String mqtt_topicsToSubscribe[] = { 
    MQTT_SUBSCRIBER_LED_OFF, 
    MQTT_SUBSCRIBER_LED_ON, 
    MQTT_SUBSCRIBER_LED_BLINK
};
void mqtt_messageArrived(String topic) {
    if (topic == MQTT_SUBSCRIBER_LED_OFF) {
        led_builtin.off();
    }
    if (topic == MQTT_SUBSCRIBER_LED_ON) {
        led_builtin.on();
    }
    if (topic == MQTT_SUBSCRIBER_LED_BLINK ) {
        led_builtin.blink();
    }
}

void setup() {
    log_setup();

    // Networking
    wifi_setup("WiFi Distefano ", "argentina2015");
    ota_setup();
    mqtt_setup(mqtt_topicsToSubscribe, sizeof(mqtt_topicsToSubscribe), mqtt_messageArrived);
}

void loop() {
    // Networking
    mqtt_loop();
}
