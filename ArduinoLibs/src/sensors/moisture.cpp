#include "moisture.h"
#include "./utils/log.h"

// Debug
const String context = "Moisture Sensor";

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

MoistureSensor::MoistureSensor(byte pin) {
    _pin = pin;
}

void MoistureSensor::updateState() {
    Log::title(context, "Moisture Read");

    _state.value = analogRead(_pin);
    _state.percentage = calculatePercent(_state.value);

    Log::keyValue("value", String(_state.value));
    Log::keyValue("percentage", String(_state.percentage));
}

DynamicJsonDocument MoistureSensor::getState() {
    updateState();
    DynamicJsonDocument json(1024);
    json["state"]["value"] = String(_state.value);
    json["state"]["percent"] = String(_state.percentage);  
    return json;
}
