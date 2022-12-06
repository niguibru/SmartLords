#include <Arduino.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

void publishJson(PubSubClient &client, char* topic, DynamicJsonDocument json);
String buildPayloadString(byte* payload, unsigned int length);
String createRandomClientId();
