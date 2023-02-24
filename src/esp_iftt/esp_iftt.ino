#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "Krishna";
const char* password = "KriShna824@32";

const char* mqtt_server = "localhost";
const int mqtt_port = 1883;
const char* mqtt_username = "Krishna";
const char* mqtt_password = "KriShna824@32";

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

void initWifi() {
  Serial.print("Connecting to: "); 
  Serial.print(ssid);
  WiFi.begin(ssid, password);  

  int timeout = 10 * 4;
  while(WiFi.status() != WL_CONNECTED  && (timeout-- > 0)) {
  delay(250);
  Serial.print(".");
  }
  Serial.println("");

  if(WiFi.status() != WL_CONNECTED) {
    Serial.println("Failed to connect, going back to sleep");
  }

  Serial.print("WiFi connected in: "); 
  Serial.print(millis());
  Serial.print(", IP address: "); 
  Serial.println(WiFi.localIP());
}

void setup() {
  mqttClient.setServer(mqtt_server, mqtt_port);
  mqttClient.setCredentials(mqtt_username, mqtt_password);

  // Connect to MQTT broker
  while (!mqttClient.connected()) {
    if (mqttClient.connect("ESP32_client")) {
      Serial.println("Connected to MQTT broker");
    } else {
      Serial.println("Failed to connect to MQTT broker");
      delay(1000);
    }
  }
}

void loop() {
  // Publish a message to the topic "test"
  mqttClient.publish("test", "Hello, world!");

  // Wait for 5 seconds before publishing another message
  delay(5000);
}

void loop() {
  while (Serial.available() > 0) {
    String data = Serial.readString();
    data.trim();
    if (data.length() == 8 ) {
      makeIFTTTRequest(data);
    } else {
      data.remove(8, data.length());
      makeIFTTTRequest(data);
    }
    delay(3000); 
  }
}
