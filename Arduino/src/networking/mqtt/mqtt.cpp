#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "mqtt.h"
#include "mqttSettings.h"
#include "./utils/utils.h"
#include "./utils/vars.h"
#include "./utils/mqttUtils.h"
// publishers
#include "./publishers/statusPublisher.h"
#include "./publishers/moisturePublisher.h"
// subscibers
const char* statusRequestSubscriber = "gardenr/status/request";
const char* moistureRequestedSubscriber = "test/gardenr/humidity/request";

void subscribe() {
  client.subscribe(statusRequestSubscriber);
  client.subscribe(moistureRequestedSubscriber);
}

void deliverToSubscribers(char* topic) {
  if ((String) topic == statusRequestSubscriber) publishStatus(client);
  if ((String) topic == moistureRequestedSubscriber) publishSoilMoistureReading(client);
}

void callback(char* topic, byte* payload, unsigned int length) {
  String payloadString = buildPayloadString(payload, length);

  blink();
  printArrivedInfo(topic, payloadString);

  // Stop if there is a payload and the mac address is not the same as the device
  if (payloadString != "" && WiFi.macAddress() != payloadString) {
    Serial.println("Message not for this device");
    return;
  }

  deliverToSubscribers(topic);
}

void reconnect() {
  while (!client.connected()) { // Loop until we're reconnected
    Serial.print("Attempting MQTT connection...");
    if (client.connect(createRandomClientId().c_str(), mqtt_user, mqtt_password)) {
      Serial.println(" -> connected!");
      publishStatus(client);
      subscribe();
    } else {
      Serial.print("failed (try again in 5 seconds), rc=");
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
