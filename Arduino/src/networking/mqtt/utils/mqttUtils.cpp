#include <Arduino.h>

String buildPayloadString(byte* payload, unsigned int length) {
  String payloadMacString = "";
  for (int i = 0; i < length; i++) {
    payloadMacString += (char)payload[i];
  }
  return payloadMacString;
}

void printArrivedInfo(char* topic, String payloadString) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.println("] ");
  Serial.println("Payload: " + payloadString);
}

String createRandomClientId(){
  String clientId = "ESP8266Client-"; 
  clientId += String(random(0xffff), HEX);
  return clientId;
}
