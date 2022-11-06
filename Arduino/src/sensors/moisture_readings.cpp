#include <Arduino.h>
#include "moisture_readings.h"

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
  Serial.println("-> Reading - Soil Moisture: ");
  SoilMoistureReading soilMoistureReading;
  
  soilMoistureReading.value = analogRead(SENSOR_IN);
  Serial.print("*  Value: ");
  Serial.println(soilMoistureReading.value);

  soilMoistureReading.percentage = calculatePercent(soilMoistureReading.value);
  Serial.print("*  Percentage: ");
  Serial.print(soilMoistureReading.percentage);
  Serial.println("%");

  return soilMoistureReading;
}

