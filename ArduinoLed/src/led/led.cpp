#include <FastLED.h>
#include "./utils/utils.h"

#define NUM_LEDS  140
#define LED_PIN   4
CRGB leds[NUM_LEDS];
uint8_t hue = 0;

String active = "";

void setOff() {
  active = "off";
}

void setRainbow() {
  active = "rainbow";
}

void led_setup() {
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(50);
  setOff();
}

void led_loop() {
  if (active == "off") {
    FastLED.clear();
    FastLED.show();
  }
  if (active == "rainbow") {
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CHSV(hue + (i * 10), 255, 255);
    }

    EVERY_N_MILLISECONDS(15){
      hue++;
    }

    FastLED.show();
  }
}

