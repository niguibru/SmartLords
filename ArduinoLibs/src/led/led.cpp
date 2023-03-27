#include "led.h"
#include "./utils/log.h"

// Debug
const String context = "LED";

Led::Led(byte pin) {
  _pin = pin;
}

void Led::setup() {
  log_title(context, "Setup");
  log_keyValue("Pin", _pin);
  pinMode(_pin, OUTPUT);
  off();
}

void Led::executeAction(JsonObject action) {
  log_title(context, "Execute Action");

  const String type = action["type"].as<String>();
  log_keyValue("Type", type);

  if (type == "on") {
    on();
  } else if (type == "off") {
    off();
  } else if (type == "blink") {
    blink();
  } else {
    log_keyValue("Error", "Unrecognized Action");
  }
}

void Led::on() {
  digitalWrite(_pin, LOW);
}

void Led::off() {
  digitalWrite(_pin, HIGH);
}

void Led::blink() {
  on();
  delay(200);
  off();
  delay(200);
}
