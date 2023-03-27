#include "ledStrip.h"
#include <FastLED.h>
#include "./utils/log.h"

// Debug
const String context = "LED_STRIP";

// Definitions
#define NUM_LEDS 29 // 29 + 29 + 29 // LED Qty: 60LEDs/M or 300LEDs/5M
#define LED_PIN 4
CRGB leds[NUM_LEDS];

// Status
uint8_t hue = 0;
CRGB defaultColorCode = CRGB(143, 20, 41);

LedStrip::LedStrip(byte pin) {
  _pin = pin;
}

void LedStrip::setup() {
  log_title(context, "Setup");
  log_keyValue("Pin", _pin);

  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(50);
}

void setColor(int startLed, int endLed, CRGB colorCode) {
  int startLedArrayIndex = startLed - 1;
  int endLedArrayIndex = endLed - 1;
  for (int i = startLedArrayIndex; i <= endLedArrayIndex; i++) {
    leds[i] = colorCode;
  }
}

void setRainbow(int startLed, int endLed) {
  int startLedArrayIndex = startLed - 1;
  int endLedArrayIndex = endLed - 1;

  FastLED.clear();

  for (int i = startLedArrayIndex; i < endLedArrayIndex; i++) {
    leds[i] = CHSV(hue + (i * 10), 255, 255);
  }
  EVERY_N_MILLISECONDS(15){
    hue++;
  }

  FastLED.show();
}

void LedStrip::loop() {
  switch (state.value) {
    case ON: {
      switch (state.color) {
        case RAINBOW: {
          setRainbow(state.start, state.end);
          break;
        }
        case RED: {
          FastLED.clear();
          setColor(state.start, state.end, defaultColorCode);
          FastLED.show();
          break;
        }
      }
      break;
    }
    case OFF: {
      FastLED.clear();
      FastLED.show();
      break;
    }
  }
}

// LedState
void LedState::setFromJson(JsonObject jsonState) {
  log_title(context, "Set State");

  // value
  const String parsedValue = jsonState["value"].as<String>();
  if (parsedValue == "on") { value = ON; } 
  else if (parsedValue == "off") { value = OFF; }
  log_keyValue("Value", value);

  // color
  const String parsedColor = jsonState["color"].as<String>();
  if (parsedColor == "rainbow") { color = RAINBOW; } 
  else if (parsedColor == "red") { color = RED; } 
  log_keyValue("Color", color);

  // start
  const int parsedStart = jsonState["start"].as<int>();
  if (parsedStart > 0) { start = parsedStart; } 
  log_keyValue("Start", start);

  // end
  const int parsedEnd = jsonState["end"].as<int>();
  if (parsedEnd > 0) { end = parsedEnd; } 
  log_keyValue("End", end);
}