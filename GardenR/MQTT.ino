#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// WIFI - Config
const char* ssid = "BT-NMCJWC";
const char* password = "bLXRnYmP9FJQR6";

// MQTT - Config
const char* mqtt_server = "test.mosquitto.org";
// MQTT Topics - SUB
const char* sub_requestValue = "gardenr/humidity/request";
// MQTT Topics - PUB
const char* pub_mqttStatus = "gardenr/connected";
const char* pub_humidity = "gardenr/humidity/value";

// MQTT Server - Vars
WiFiClient espClient;
PubSubClient client(espClient);
#define MSG_BUFFER_SIZE  (50)
char msg[MSG_BUFFER_SIZE];

// Sensor - Vars
const int DRY_MAX = 860;
const int WATER_MAX = 470;
int soilMoistureValue;
int soilMoisturePercent = 0;
#define SENSOR_IN 0

void setup_wifi() {
  delay(10);

  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.enableInsecureWEP(true);
  // WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.println("] ");
  String wifiMacString = WiFi.macAddress();
  String payloadMacString = "";
  for (int i = 0; i < length; i++) {
    payloadMacString += (char)payload[i];
  }
  Serial.println("Payload: " + payloadMacString);
  if (payloadMacString != "" && wifiMacString != payloadMacString) {
    // Stop if there is a payload and the mac address is not the same as the device
    Serial.println("Message not for this device");
    Serial.println();
    return;
  }

  String topicStr = topic;
  digitalWrite(BUILTIN_LED, HIGH);
  if (topicStr == sub_requestValue) {
    blink();
    readSoilMoistureValue();

    // Build JSON
    char data[80];
    String deviceIdJSON = " \"device_id\" : \"" + WiFi.macAddress() + "\"";
    String soilMoistureValueJSON = " \"soil_moisture_value\" : " + String(soilMoistureValue);
    String soilMoisturePercentJSON = " \"soil_moisture_percent\" : " + String(soilMoisturePercent);
    String payload = "{" + deviceIdJSON + "," + soilMoistureValueJSON + "," + soilMoisturePercentJSON + " }";
    payload.toCharArray(data, (payload.length() + 1));

    // Publish value
    client.publish(pub_humidity, data);
    Serial.println();
  }
}

void blink() {
  digitalWrite(BUILTIN_LED, HIGH);
  delay(1000);
  digitalWrite(BUILTIN_LED, LOW);
  delay(1000);
  digitalWrite(BUILTIN_LED, HIGH);
}

void readSoilMoistureValue() {
  soilMoistureValue = analogRead(SENSOR_IN);
  Serial.print("Moisture Value: ");
  Serial.println(soilMoistureValue);
  soilMoisturePercent = map(soilMoistureValue, DRY_MAX, WATER_MAX, 0, 100);
  if (soilMoisturePercent < 0) {
    soilMoisturePercent = 0;
  }
  if (soilMoisturePercent > 100) {
    soilMoisturePercent = 100;
  }
  Serial.print("Moisture %: ");
  Serial.print(soilMoisturePercent);
  Serial.println("%");
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      char data[80];
      String deviceIdJSON = " \"device_id\" : \"" + WiFi.macAddress() + "\"";
      String payload = "{" + deviceIdJSON + " }";
      payload.toCharArray(data, (payload.length() + 1));
      client.publish(pub_mqttStatus, data);
      // Subscribe reqValue
      client.subscribe(sub_requestValue);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
  pinMode(BUILTIN_LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  // readSoilMoistureValue(); // To test and calibrate
}
