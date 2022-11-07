#include <Arduino.h>
#include "moisture_readings.h"
#include "./utils/utils.h"

// Debug
const String context = "Moisture Sensor";

// SENSOR PIN
#define SENSOR_IN 0

// CALIBRATION VALUES
const int DRY_MAX = 860;
const int WATER_MAX = 470;

int calculatePercent(int value) {
  int soilMoisturePercent = map(value, DRY_MAX, WATER_MAX, 0, 100);

  if (soilMoisturePercent < 0) {
    soilMoisturePercent = 0;
  }
  if (soilMoisturePercent > 100) {
    soilMoisturePercent = 100;
  }

  return soilMoisturePercent;
}

SoilMoistureReading getSoilMoistureReading() {
  printDebugTitle(context, "Moisture Read");

  SoilMoistureReading soilMoistureReading;

  soilMoistureReading.value = analogRead(SENSOR_IN);
  printDebugKeyValue("value", String(soilMoistureReading.value));

  soilMoistureReading.percentage = calculatePercent(soilMoistureReading.value);
  printDebugKeyValue("percentage", String(soilMoistureReading.percentage));

  return soilMoistureReading;
}
