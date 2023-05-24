#include "ledStrip.h"
#include "./utils/log.h"

// Debug
const String context = "LED_STRIP";

// Definitions
#define NUM_LEDS 29 // 29 + 29 + 29 // LED Qty: 60LEDs/M or 300LEDs/5M
CRGB leds[NUM_LEDS];

// Status
uint8_t hue = 0;
CRGB defaultColorCode = CRGB(143, 20, 41);

LedStrip::LedStrip(byte pin) {
  _pin = pin;
}

void LedStrip::setup() {
  Log::title(context, "Setup");
  Log::keyValue("Pin", _pin);

  switch (_pin) {
    case 3:
      FastLED.addLeds<WS2812B, 3, GRB>(leds, NUM_LEDS);
      break;

    case 4:
      FastLED.addLeds<WS2812B, 4, GRB>(leds, NUM_LEDS);
      break;

    case 5:
      FastLED.addLeds<WS2812B, 5, GRB>(leds, NUM_LEDS);
      break;

    default:
      Serial.println("Unsupported Pin");
      break;
  }
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
    case LS_ON: {
      switch (state.color) {
        case LS_RAINBOW: {
          setRainbow(state.start, state.end);
          break;
        }
        case LS_RED: {
          FastLED.clear();
          setColor(state.start, state.end, defaultColorCode);
          FastLED.show();
          break;
        }
      }
      break;
    }
    case LS_OFF: {
      FastLED.clear();
      FastLED.show();
      break;
    }
  }
}

void LedStrip::updateState(JsonObject jsonState) {
  Log::title(context, "Set State");

  // value
  const String parsedValue = jsonState["value"].as<String>();
  if (parsedValue == "on") { state.value = LS_ON; } 
  else if (parsedValue == "off") { state.value = LS_OFF; }
  Log::keyValue("Value", state.value);

  // color
  const String parsedColor = jsonState["color"].as<String>();
  if (parsedColor == "rainbow") { state.color = LS_RAINBOW; } 
  else if (parsedColor == "red") { state.color = LS_RED; } 
  Log::keyValue("Color", state.color);

  // start
  const int parsedStart = jsonState["start"].as<int>();
  if (parsedStart > 0) { state.start = parsedStart; } 
  Log::keyValue("Start", state.start);

  // end
  const int parsedEnd = jsonState["end"].as<int>();
  if (parsedEnd > 0) { state.end = parsedEnd; } 
  Log::keyValue("End", state.end);
}