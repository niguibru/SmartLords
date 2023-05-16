#ifndef LedStrip_H
#define LedStrip_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include <FastLED.h>

enum LedValue { OFF, ON };
enum LedColor { RED, RAINBOW };

class LedState {
  public:
    LedValue value = OFF;
    LedColor color = RED;
    int start = 1;
    int end = 1;
    void setFromJson(JsonObject jsonState);
};

class LedStrip {
  
  private:
    byte _pin;

  public:
    LedStrip(byte pin);
    // Main methods
    void setup();
    void loop();
    // State
    LedState state = LedState();
};

#endif
