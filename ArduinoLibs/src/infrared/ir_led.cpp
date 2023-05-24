#include "ir_led.h"
#include "./utils/log.h"

// Debug
const String context = "IR Led";

IR_Led::IR_Led(byte pin) {
    _pin = pin;
    // _irsend = IRsend(0);
    _irsend.begin();
}

void IR_Led::send(uint16_t rawData[], int count) {
    Log::title(context, "Value Sent");
    _irsend.sendRaw(rawData, count, 38);
    delay(2000);
}

void IR_Led::send(JsonArray jsonArray) {
    int count = jsonArray.size();
        
    uint16_t rawData[count] = {};
    int i = 0;
    for (JsonVariant value : jsonArray) {
        rawData[i] = value.as<int>();
        i++;
    }
            
    send(rawData, count);
}
