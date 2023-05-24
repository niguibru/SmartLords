#include <Arduino.h>
#include <ArduinoJson.h>
#include <PubSubClient.h>
#include <ESP8266WiFi.h>

void publishJson(PubSubClient &client, const String topic, DynamicJsonDocument json);
String buildPayloadString(byte* payload, unsigned int length);
String createRandomClientId();
