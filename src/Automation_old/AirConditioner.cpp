#include "../IR/IRDriver.cpp"
#include "IRAirCommands.cpp"

class AirConditioner {

  public:

    void setup() {
      irDriver.setup();
    }

    void Off() {
      IRSignal signal = IRAirCommands().OFF();
      irDriver.sendSignal(signal);
    }

    void On(int degrees) {
      IRSignal signal = getIRSignalByDegree(degrees);
      irDriver.sendSignal(signal);
    }

    void SetDegrees(int degrees) {
      IRSignal signal = getIRSignalByDegree(degrees);
      irDriver.sendSignal(signal);
    }

  private:

    IRDriver irDriver = IRDriver();

    IRSignal getIRSignalByDegree(int degrees) {
      switch (degrees) {
        case 18:
          return IRAirCommands().ON_18();
        case 19:
          return IRAirCommands().ON_19();
        case 20:
          return IRAirCommands().ON_20();
        case 21:
          return IRAirCommands().ON_21();
        case 22:
          return IRAirCommands().ON_22();
        case 23:
          return IRAirCommands().ON_23();
        case 24:
          return IRAirCommands().ON_24();
        case 25:
          return IRAirCommands().ON_25();
        case 26:
          return IRAirCommands().ON_26();
        case 27:
          return IRAirCommands().ON_27();
        case 28:
          return IRAirCommands().ON_28();
        case 29:
          return IRAirCommands().ON_29();
        case 30:
          return IRAirCommands().ON_30();
        default:
          return IRAirCommands().ON_18();
      }
    }
};
