#include <ESP8266WebServer.h>

class GenericRoutes {

  public:

    GenericRoutes(ESP8266WebServer server) {
      server = server;
    }

    void addRoutes() {
      server.onNotFound(std::bind(&GenericRoutes::handleNotFound, this));

      server.on("/", std::bind(&GenericRoutes::handleRoot, this));
    }

  private:

    ESP8266WebServer server;

    void handleRoot() {
      server.send(200, "text/plain", "hello from esp8266!");
    }

    void handleNotFound() {
      String message = "File Not Found\n\n";
      message += "URI: ";
      message += server.uri();
      message += "\nMethod: ";
      message += (server.method() == HTTP_GET)?"GET":"POST";
      message += "\nArguments: ";
      message += server.args();
      message += "\n";
      for (uint8_t i=0; i<server.args(); i++){
        message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
      }
      server.send(404, "text/plain", message);
    }

};
