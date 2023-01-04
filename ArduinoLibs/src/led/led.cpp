#include "led.h"

Led::Led(byte pin) {
  _pin = pin;
  init();
}

void Led::init() {
  pinMode(_pin, OUTPUT);
  off();
}

void Led::on() {
  digitalWrite(_pin, LOW);
}

void Led::off() {
  digitalWrite(_pin, HIGH);
}

void Led::blink() {
  digitalWrite(_pin, HIGH);
  delay(200);
  digitalWrite(_pin, LOW);
  delay(200);
}
