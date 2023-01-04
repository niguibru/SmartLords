#ifndef IRReceiver_H
#define IRReceiver_H
#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>
#include "./utils/log.h"

class IR_Receiver {
  
  private:
    byte _pin;
    IRrecv _irrecv = IRrecv(2);
    decode_results results;

  public:
    IR_Receiver(byte pin);
    void loop();

};

#endif