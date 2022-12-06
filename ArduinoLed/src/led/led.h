
enum LedState { OFF, LEFT, RIGHT, RAINBOW };

void led_setup();
void led_loop();
void setState(LedState newState);
