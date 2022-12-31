#include "mqtt.h"
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "mqttSettings.h"
#include "./utils/log.h"
#include "./utils/vars.h"
#include "./utils/mqttUtils.h"

// Debug
const String context = "MQTT";

// Publishers
const char* pub_mqttStatus = "gardenr/status";

// Var
String _topicsToSubscribe[20];
int _topicsToSubscribeCount;
messageArrivedCallack _messageArrivedCallack;

void subscribe() {
    log_title(context, "Subscribing");
    for (int i=0; i < _topicsToSubscribeCount; i++) {
        const char* topic = _topicsToSubscribe[i].c_str();
        log_keyValue("Topic", topic);
        client.subscribe(topic);
    }
}

void callback(char* topic, byte* payload, unsigned int length) {
    String payloadString = buildPayloadString(payload, length);

    log_title(context, "Message Arrived");
    log_keyValue("Topic", topic);
    log_keyValue("Payload", payloadString);

    // Stop if there is a payload and the mac address is not the same as the device
    if (payloadString != "" && WiFi.macAddress() != payloadString) {
      log_title(context, "Message not for this device");
      return;
    }

    _messageArrivedCallack(topic);
}

void reconnect() {
    while (!client.connected()) { // Loop until we're reconnected
        log_title(context, "Attempting MQTT connection..");
        if (client.connect(createRandomClientId().c_str(), mqtt_user, mqtt_password)) {
            log_keyValue("Status", "connected");
            DynamicJsonDocument json(1024);
            publishJson(client, (char*) pub_mqttStatus, json);
            subscribe();
        } else {
            log_keyValue("Status", "Failed (try again in 5 seconds)");
            Serial.println(client.state());
            delay(5000); // Wait 5 seconds before retrying
        }
    }
}

void mqtt_setup(String topicsToSubscribe[], int topicsToSubscribeSize, messageArrivedCallack messageArrived){
    _topicsToSubscribeCount = topicsToSubscribeSize;
    for (int i=0; i < _topicsToSubscribeCount; i++) {
        _topicsToSubscribe[i] = topicsToSubscribe[i];
    }

    _messageArrivedCallack = messageArrived;

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
