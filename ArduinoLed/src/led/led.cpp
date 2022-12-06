#include "./led.h"
#include <FastLED.h>
#include "./utils/utils.h"

// Definitions
#define NUM_LEDS  180 // LED Qty: 60LEDs/M or 300LEDs/5M
#define LED_PIN   4
CRGB leds[NUM_LEDS];

// Status
uint8_t hue = 0;
LedState ledState = OFF;
CRGB defaultColorCode = CRGB(29, 2, 36);

void setState(LedState newState) {
  ledState = newState;
}

void led_setup() {
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

void led_loop() {
  if (ledState == OFF) {
    FastLED.clear();
    FastLED.show();
  }
  if (ledState == LEFT) {
    FastLED.clear();
    setColor(1, 120, defaultColorCode);
    FastLED.show();
  }
  if (ledState == RIGHT) {
    FastLED.clear();
    setColor(60, NUM_LEDS, defaultColorCode);
    FastLED.show();
  }
  if (ledState == RAINBOW) {
    FastLED.clear();

    for (int i = 0; i < NUM_LEDS - 1; i++) {
      leds[i] = CHSV(hue + (i * 10), 255, 255);
    }
    EVERY_N_MILLISECONDS(15){
      hue++;
    }

    FastLED.show();
  }
}

