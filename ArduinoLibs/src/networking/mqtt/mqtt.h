#ifndef MQTT_H
#define MQTT_H

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

typedef void (*messageArrivedCallack)(String topic, JsonObject jsonPayload);

class MQTT {

    public:
        void setup(const String topicsToSubscribe[], int topicsToSubscribeSize, messageArrivedCallack messageArrived);
        void loop();
        void publish(const String topic, DynamicJsonDocument json);    

};

#endif