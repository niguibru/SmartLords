#include "LedBuiltin.h"
#include "./utils/log.h"

// Debug
const String context = "LED";

const byte pin = LED_BUILTIN;

void LedBuiltin::setup() {
  Log::title(context, "Setup");
  Log::keyValue("Pin", pin);
  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);
}

void LedBuiltin::updateState(JsonObject jsonState) {
  Log::title(context, "Set State");

  // value
  const String value = jsonState["value"].as<String>();
  if (value == "off") {
      state.value = LB_OFF;
  } else if (value == "on") {
      state.value = LB_ON;
  } else if (value == "blink") {
      state.value = LB_BLINK;
  } else {
      Log::keyValue("Error", "Unrecognized state");
  }
  Log::keyValue("Value", state.value);

}

void LedBuiltin::loop() {
  switch (state.value) {
      case LB_ON: {
          digitalWrite(pin, LOW);
          break;
      }
      case LB_OFF: {
          digitalWrite(pin, HIGH);
          break;
      }
      case LB_BLINK: {
          digitalWrite(pin, HIGH);
          delay(200);
          digitalWrite(pin, LOW);
          delay(200);
          break;
      }
  }
}
