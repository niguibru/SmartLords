#ifndef LedBuiltin_H
#define LedBuiltin_H

#include <Arduino.h>
#include <ArduinoJson.h>

enum LedBuiltinValue { LB_OFF, LB_ON, LB_BLINK };

class LedBuiltinState {
  public:
    LedBuiltinValue value = LB_OFF;
};

class LedBuiltin {
  
  private:
      // State
      LedBuiltinState state = LedBuiltinState();
    
  public:
      // Main methods
      void setup();
      void loop();
      // State
      void updateState(JsonObject jsonState);

};

#endif