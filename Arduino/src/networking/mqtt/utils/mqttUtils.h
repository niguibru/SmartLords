#include <Arduino.h>

String buildPayloadString(byte* payload, unsigned int length);
void printArrivedInfo(char* topic, String payloadString);
String createRandomClientId();
