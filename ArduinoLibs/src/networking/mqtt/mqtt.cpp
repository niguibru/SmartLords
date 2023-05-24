#include "mqtt.h"
#include "mqttSettings.h"
#include "./utils/log.h"
#include "./utils/vars.h"
#include "./utils/mqttUtils.h"

// Debug
const String context = "MQTT";

// Publishers
const String MQTT_PUBLISHER_STATUS = "status";

// Subscribers
const String MQTT_SUBSCRIBER_STATUS = "status/request";

// Var
String _topicsToSubscribe[20];
int _topicsToSubscribeCount;
messageArrivedCallack _messageArrivedCallack;

void subscribe() {
    Log::title(context, "Subscribing");
    for (int i=0; i < _topicsToSubscribeCount; i++) {
        const char* topic = _topicsToSubscribe[i].c_str();
        Log::keyValue("Topic", topic);
        client.subscribe(topic);
    }
    client.subscribe(MQTT_SUBSCRIBER_STATUS.c_str());
}

void publishStatus() {
    DynamicJsonDocument json(1024);
    publishJson(client, MQTT_PUBLISHER_STATUS, json);
}

void callback(char* topic, byte* payload, unsigned int length) {
    String payloadString = buildPayloadString(payload, length);

    // LOG
    Log::title(context, "Message Arrived");
    Log::keyValue("Topic", topic);
    Log::keyValue("Payload", payloadString);

    // Deserialization
    StaticJsonDocument<1000> jsonPayload;
    DeserializationError error = deserializeJson(jsonPayload, payloadString);
    if (error) {
        Log::title(context, "deserializeJson failed");
        Log::keyValue("Error", error.f_str());
        return;
    }
    JsonObject jsonObject = jsonPayload.as<JsonObject>();

    // Stop if message is for the device
    const char* deviceID = jsonObject["device_id"];
    if (strcmp(deviceID, "#") == 0 || WiFi.macAddress() == deviceID) {
        // Check for status topic
        if ((String) topic == MQTT_SUBSCRIBER_STATUS) {
            publishStatus();
        } else {
            // Callack
            _messageArrivedCallack(topic, jsonObject);
        }
    } else {
      Log::title(context, "Message not for this device");
      return;
    }
}

void reconnect() {
    while (!client.connected()) { // Loop until we're reconnected
        Log::title(context, "Attempting MQTT connection..");
        if (client.connect(createRandomClientId().c_str(), mqtt_user, mqtt_password)) {
            Log::keyValue("Status", "connected");
            publishStatus();
            subscribe();
        } else {
            Log::keyValue("Status", "Failed (try again in 5 seconds)");
            Serial.println(client.state());
            delay(5000); // Wait 5 seconds before retrying
        }
    }
}

void MQTT::setup(const String topicsToSubscribe[], int topicsToSubscribeSize, messageArrivedCallack messageArrived){
    _topicsToSubscribeCount = topicsToSubscribeSize;
    for (int i=0; i < _topicsToSubscribeCount; i++) {
        _topicsToSubscribe[i] = topicsToSubscribe[i];
    }

    _messageArrivedCallack = messageArrived;

    espClient.setInsecure();
    client.setServer(mqtt_server, mqtt_port);
    client.setCallback(callback);
}

void MQTT::loop() {
    if (!client.connected()) {
       reconnect();
    }
    client.loop();
}

void MQTT::publish(const String topic, DynamicJsonDocument json) {
    publishJson(client, topic, json);
}
