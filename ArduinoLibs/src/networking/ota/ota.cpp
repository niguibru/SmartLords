#include "ota.h"
#include "./utils/log.h"
#include <AsyncElegantOTA.h>

// Debug
const String logContext = "ota";

const uint16_t port = 80;
AsyncWebServer server = AsyncWebServer(port);

void OTAUpdate::setup() {
    log_title(logContext, "Enabling");
    log_keyValue("Port", 80);

    AsyncElegantOTA.begin(&server);
    server.begin();
}
