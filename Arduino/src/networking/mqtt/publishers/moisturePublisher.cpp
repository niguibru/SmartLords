#include "./sensors/moisture_readings.h"
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* pub_humidity = "gardenr/humidity/value";

void publishSoilMoistureReading(PubSubClient &client) {
  SoilMoistureReading soilMoistureReading = getSoilMoistureReading();

  // Build JSON
  char data[80];
  String deviceIdJSON = " \"device_id\" : \"" + WiFi.macAddress() + "\"";
  String soilMoistureValueJSON = " \"soil_moisture_value\" : " + String(soilMoistureReading.value);
  String soilMoisturePercentJSON = " \"soil_moisture_percent\" : " + String(soilMoistureReading.percentage);
  String payload = "{" + deviceIdJSON + "," + soilMoistureValueJSON + "," + soilMoisturePercentJSON + " }";
  payload.toCharArray(data, (payload.length() + 1));

  // Publish value
  client.publish(pub_humidity, data);
}
