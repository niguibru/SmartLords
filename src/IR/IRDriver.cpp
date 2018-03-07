#include "IRSignal.cpp"

#include <IRremoteESP8266.h>
#include <IRsend.h>

class IRDriver {

  #define irSenderPin 4

  public:

    void setup() {
      sender.begin();
    }

    void Receive() {
      // Pending
    }

    void sendSignal(IRSignal signal) {
      for (int i = 0; i < signal.repetitions; i++) {
        sender.sendRaw(signal.duration, signal.count, 38);
      }
    }

  private:

    IRsend sender = IRsend(irSenderPin);

};
