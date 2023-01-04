#include "ir_led.h"

// Debug
const String context = "IR Led";

IR_Led::IR_Led(byte pin) {
    _pin = pin;
    // _irsend = IRsend(0);
    _irsend.begin();
}

void IR_Led::send(uint16_t rawData[], int count) {
    log_title(context, "Value Sent");
    _irsend.sendRaw(rawData, count, 38);
    delay(2000);
}
