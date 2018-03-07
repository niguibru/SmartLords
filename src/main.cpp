#include <Arduino.h>

#include <Webserver/Webserver.cpp>
Webserver webserver = Webserver("gini wifi's", "");

void setup() {
  Serial.begin(115200);
  webserver.setup();
}

void loop(){
  webserver.loop();
  delay(1000);
}
