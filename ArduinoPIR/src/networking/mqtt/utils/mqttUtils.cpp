#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "./utils/utils.h"

// Debug
const String context = "MQTT";

void publishJson(PubSubClient &client, char* topic, DynamicJsonDocument json) {
    json["device_id"] = WiFi.macAddress();
    json["ip_address"] = WiFi.localIP().toString();  

    char buffer[256];
    serializeJson(json, buffer);
    if (client.publish(topic, buffer)) {
        printDebugTitle(context, "Message published");
        printDebugKeyValue("Topic", topic);
        printDebugKeyValue("Payload", buffer);
    } else {
        printDebugTitle(context, "Error publishing");
        printDebugKeyValue("Topic", topic);
        printDebugKeyValue("Payload", buffer);
    }
}

String buildPayloadString(byte* payload, unsigned int length) {
    String payloadMacString = "";
    for (int i = 0; i < length; i++) {
        payloadMacString += (char)payload[i];
    }
    return payloadMacString;
}

String createRandomClientId(){
    String clientId = "ESP8266Client-"; 
    clientId += String(random(0xffff), HEX);
    return clientId;
}
