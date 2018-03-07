#include <IRremoteESP8266.h>

#ifndef IRSignal_H
#define IRSignal_H

struct IRSignal {
  int repetitions;
  int count;
  uint16_t duration[100];
};

#endif
