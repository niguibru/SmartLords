#include "ir_receiver.h"

// Debug
const String context = "IR Receiver";

IR_Receiver::IR_Receiver(byte pin) {
    _pin = pin;
   // _irrecv = IRrecv(pin);
   _irrecv.enableIRIn();
}

void IR_Receiver::loop() {
    if (_irrecv.decode(&results)) {
        Log::title(context, "Value Received");
        serialPrintUint64(results.value, HEX);
        Serial.println(resultToHumanReadableBasic(&results));
        Serial.println(resultToSourceCode(&results));
        _irrecv.resume();  // Receive the next value
    }
    delay(100);
}
