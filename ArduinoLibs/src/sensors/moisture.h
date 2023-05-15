#include <Arduino.h>
#include <ArduinoJson.h>

typedef struct {
    int value;
    int percentage;
} SoilMoistureReading;

SoilMoistureReading getSoilMoistureReading();
DynamicJsonDocument getSoilMoistureState();
