#include "mqttUtils.h"
#include "./utils/log.h"

// Debug
const String context = "MQTT";

void publishJson(PubSubClient &client, const String topic, DynamicJsonDocument json) {
    json["device_id"] = WiFi.macAddress();
    json["ip_address"] = WiFi.localIP().toString();  

    char buffer[256];
    serializeJson(json, buffer);
    if (client.publish(topic.c_str(), buffer)) {
        Log::title(context, "Message published");
        Log::keyValue("Topic", topic);
        Log::keyValue("Payload", buffer);
    } else {
        Log::title(context, "Error publishing");
        Log::keyValue("Topic", topic);
        Log::keyValue("Payload", buffer);
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
