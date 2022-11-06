#include <Arduino.h>

typedef struct {
    int value;
    int percentage;
} SoilMoistureReading;

SoilMoistureReading getSoilMoistureReading();
