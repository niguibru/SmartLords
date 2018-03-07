#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

#include <ArduinoJson.h>
#include "GenericRoutes.cpp"

#include <IR/IRDriver.cpp>

class Webserver {

  public:

    Webserver(String ssid, String password) {
      ESP8266WebServer server(80);
      ssid = ssid;
      password = password;
    }

    void setup() {
      irDriver.setup();

      delay(1000);
      connectToServer();
      addRoutes();
      server.begin();
    }

    void loop() {
      server.handleClient();
    }

  private:

    IRDriver irDriver = IRDriver();
    ESP8266WebServer server;
    char* ssid;
    char* password;

    void connectToServer() {
      WiFi.begin(ssid, password);

      Serial.println("Wait for connection...");
      while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
      }

      if (MDNS.begin("esp8266")) {
        Serial.println("MDNS responder started");
      }
      printConnected();
    }

    void printConnected() {
      Serial.println("");
      Serial.println("HTTP server started");
      Serial.print("Connected to ");
      Serial.println(ssid);
      Serial.print("IP address: ");
      Serial.println(WiFi.localIP());
    }

    // ROUTES

    void addRoutes() {
      //GenericRoutes().addRoutes(server);
      server.onNotFound(std::bind(&Webserver::handleNotFound, this));

      server.on("/", std::bind(&Webserver::handleRoot, this));
      server.on("/infrared/send", HTTP_POST, std::bind(&Webserver::handleInfraredSend, this));
    }

    String buildLogMessage() {
      String message = "URI: ";
      message += server.uri();
      message += "\nMethod: ";
      message += (server.method() == HTTP_GET)?"GET":"POST";
      message += "\nArguments: ";
      message += server.args();
      message += "\n";
      for (uint8_t i=0; i<server.args(); i++){
        message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
      }
      return message;
    }

    void handleNotFound() {
      String message = "File Not Found\n\n";
      message +=  buildLogMessage();
      server.send(404, "text/plain", message);
    }

    void handleRoot() {
      server.send(200, "text/plain", "hello from esp8266!");
    }

    void handleInfraredSend() {
      server.send(200, "text/plain", "Infrared sended!");

      StaticJsonBuffer<2000> newBuffer;
      JsonObject& json = newBuffer.parseObject(server.arg("plain"));
      if (!json.success())
      {
        Serial.println("parseObject() failed");
        return;
      }

      int repetitions = json["repetitions"];
      int count = json["count"];

      IRSignal signal = {
        repetitions,
        count,
        {}
      };

      int durationArray[100];
      json["duration"].asArray().copyTo(durationArray);
      uint16_t duration[100];
      for (size_t i = 0; i < count; i++) {
        signal.duration[i] = durationArray[i];
      }

      irDriver.sendSignal(signal);
    }

};
