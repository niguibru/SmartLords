#include "ota.h"
#include "./utils/log.h"
#include <AsyncElegantOTA.h>

// Debug
const String logContext = "OTAUpdate";

const uint16_t port = 80;
AsyncWebServer server = AsyncWebServer(port);

void OTAUpdate::setup() {
    Log::title(logContext, "Enabling");
    Log::keyValue("Port", 80);

    AsyncElegantOTA.begin(&server);
    server.begin();
}
