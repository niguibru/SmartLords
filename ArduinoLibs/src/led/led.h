#ifndef Led_H
#define Led_H
#include <Arduino.h>

class Led {
  
  private:
    byte _pin;
    
  public:
    Led(byte pin);
    void init();
    void on();
    void off();
    void blink();

};

#endif