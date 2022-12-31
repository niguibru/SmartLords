#ifndef mqtt_H
#define mqtt_H

#include <Arduino.h>

typedef void (*messageArrivedCallack)(String topic);

void mqtt_setup(String topicsToSubscribe[], int topicsToSubscribeSize, messageArrivedCallack messageArrived);
void mqtt_loop();

#endif
