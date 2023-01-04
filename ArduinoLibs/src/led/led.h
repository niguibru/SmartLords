#ifndef Led_H
#define Led_H
#include <Arduino.h>

class Led {
  
  private:
    byte _pin;
    void init();
    
  public:
    Led(byte pin);
    void on();
    void off();
    void blink();

};

#endif