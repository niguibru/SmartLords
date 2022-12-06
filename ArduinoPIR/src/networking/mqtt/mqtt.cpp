#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "mqttSettings.h"
#include "./utils/utils.h"
#include "./utils/vars.h"
#include "./utils/mqttUtils.h"

// Debug
const String context = "MQTT";

// Subscibers
const char* statusRequestSubscriber = "gardenr/status/request";

// Publishers
const char* pub_mqttStatus = "gardenr/status";
const char* pub_pirMotionDetected = "home/pir";

void subscribe() {
    client.subscribe(statusRequestSubscriber);
}

void deliverToSubscribers(char* topic) {
    if ((String) topic == statusRequestSubscriber) {
        DynamicJsonDocument json(1024);
        publishJson(client, (char*) pub_mqttStatus, json);
    }
}

void send_pirMotionDetected() {
    DynamicJsonDocument json(1024);
    publishJson(client, (char*) pub_pirMotionDetected, json);
}

void callback(char* topic, byte* payload, unsigned int length) {
    String payloadString = buildPayloadString(payload, length);

    blink();
    printDebugTitle(context, "Message Arrived");
    printDebugKeyValue("Topic", topic);
    printDebugKeyValue("Payload", payloadString);

    // Stop if there is a payload and the mac address is not the same as the device
    if (payloadString != "" && WiFi.macAddress() != payloadString) {
      printDebugTitle(context, "Message not for this device");
      return;
    }

    deliverToSubscribers(topic);
}

void reconnect() {
    while (!client.connected()) { // Loop until we're reconnected
        printDebugTitle(context, "Attempting MQTT connection..");
        if (client.connect(createRandomClientId().c_str(), mqtt_user, mqtt_password)) {
            printDebugKeyValue("Status", "connected");
            DynamicJsonDocument json(1024);
            publishJson(client, (char*) pub_mqttStatus, json);
            subscribe();
        } else {
            printDebugKeyValue("Status", "Failed (try again in 5 seconds)");
            Serial.println(client.state());
            delay(5000); // Wait 5 seconds before retrying
        }
    }
}

void mqtt_setup() {
    espClient.setInsecure();
    client.setServer(mqtt_server, mqtt_port);
    client.setCallback(callback);
}

void mqtt_loop() {
    if (!client.connected()) {
       reconnect();
    }
    client.loop();
}
