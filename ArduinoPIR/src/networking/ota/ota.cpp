#include <AsyncElegantOTA.h>

AsyncWebServer server(80);

void ota_setup() {
    AsyncElegantOTA.begin(&server);
    server.begin();
}
