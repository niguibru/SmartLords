#ifndef MoistureSensorState_H
#define MoistureSensorState_H

#include <Arduino.h>
#include <ArduinoJson.h>

class MoistureSensorState {
  public:
    int value = 0;
    int percentage = 0;
};

class MoistureSensor {
  
  private:
    byte _pin;
    // State
    MoistureSensorState _state = MoistureSensorState();
    void updateState();

  public:
    MoistureSensor(byte pin);
    // State
    DynamicJsonDocument getState();
};

#endif