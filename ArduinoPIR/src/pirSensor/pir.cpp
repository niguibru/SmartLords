#include <Arduino.h>
#include "./utils/utils.h"
#include "./../networking/mqtt/mqtt.h"

#define pin_pir1 5
#define pin_pir2 4

static String name_pir1 = "PIR-1";
int val_pir1 = 0;
bool motionState_pir1 = false;
static String name_pir2 = "PIR-2";
int val_pir2 = 0;
bool motionState_pir2 = false;

void pir_setup() {
  pinMode(pin_pir1, INPUT);
  pinMode(pin_pir2, INPUT);
}

void debug(uint8_t val, bool &state, String pirName) {
  if (val == HIGH) {
    if (state == false) {
      printDebugTitle(pirName, "Motion detected");
      printDebugKeyValue("Time (milis)", millis());
      state = true;
      send_pirMotionDetected();
    }
  } else {
    if (state == true) {
      printDebugTitle(pirName, "Motion ended");
      printDebugKeyValue("Time (milis)", millis());
      state = false;
    }
  }
}

void pir_loop() {
  debug(digitalRead(pin_pir1), motionState_pir1, name_pir1);
  debug(digitalRead(pin_pir2), motionState_pir2, name_pir2);
}
