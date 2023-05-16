#ifndef Led_H
#define Led_H

#include <Arduino.h>
#include <ArduinoJson.h>

class Led {
  
  private:
    byte _pin;
    void on();
    void off();
    void blink();
    
  public:
    Led(byte pin);
    void setup();
    void executeAction(JsonObject action);

};

#endif