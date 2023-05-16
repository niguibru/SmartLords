#ifndef LedStrip_H
#define LedStrip_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include <FastLED.h>

enum LedStripValue { LS_OFF, LS_ON };
enum LedStripColor { LS_RED, LS_RAINBOW };

class LedStripState {
  public:
    LedStripValue value = LS_OFF;
    LedStripColor color = LS_RED;
    int start = 1;
    int end = 1;
};

class LedStrip {
  
  private:
    byte _pin;
    // State
    LedStripState state = LedStripState();

  public:
    LedStrip(byte pin);
    // Main methods
    void setup();
    void loop();
    // State
    void updateState(JsonObject jsonState);
  
};

#endif
