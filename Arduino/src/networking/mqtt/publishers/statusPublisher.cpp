#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* pub_mqttStatus = "gardenr/status";

void publishStatus(PubSubClient &client) {
  char data[80];
  String deviceIdJSON = " \"device_id\" : \"" + WiFi.macAddress() + "\"";
  String ipAddress = " \"ip_address\" : \"" + WiFi.localIP().toString() + "\"";
  String payload = "{" + deviceIdJSON + "," + ipAddress + " }";
  payload.toCharArray(data, (payload.length() + 1));
  client.publish(pub_mqttStatus, data);
}
