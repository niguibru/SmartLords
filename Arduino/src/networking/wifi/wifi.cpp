#include "wifi.h"
#include <Arduino.h>
#include <ESP8266WiFi.h>

//---- WiFi settings
const char* wifi_name = "BT-NMCJWC";
const char* wifi_password = "bLXRnYmP9FJQR6";

void wifi_setup() {
  delay(10);

  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(wifi_name);

  WiFi.enableInsecureWEP(true);
  WiFi.begin(wifi_name, wifi_password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}
