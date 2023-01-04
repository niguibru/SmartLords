#ifndef mqtt_H
#define mqtt_H

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

typedef void (*messageArrivedCallack)(String topic, StaticJsonDocument<1000> jsonPayload);

void mqtt_setup(const String topicsToSubscribe[], int topicsToSubscribeSize, messageArrivedCallack messageArrived);
void mqtt_loop();

#endif
