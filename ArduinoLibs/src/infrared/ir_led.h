#ifndef IR_Led_H
#define IR_Led_H
#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include "./utils/log.h"

class IR_Led {
  
  private:
    byte _pin;
    IRsend _irsend = IRsend(4);

  public:
    IR_Led(byte pin);
    void send(uint16_t rawData[], int count);

};

#endif