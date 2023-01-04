#ifndef mqtt_vars_H
#define mqtt_vars_H

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#define MSG_BUFFER_SIZE  (50)
char msg[MSG_BUFFER_SIZE];

WiFiClientSecure espClient;
PubSubClient client(espClient);

#endif