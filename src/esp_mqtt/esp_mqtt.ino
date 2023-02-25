#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "Krishna";
const char* password = "KriShna824@32";
const char* mqtt_server = "192.168.5.233";

WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE  (8)
char msg[MSG_BUFFER_SIZE];
int value = 0;

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
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
  Serial.print("] ");
  String message = "";
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
    message += (char)payload[i];
  }
  Serial.println();
  if (strcmp(topic, "ams/uid/result") == 0 && message == "200") {
    digitalWrite(LED_BUILTIN, LOW);
  } else {
    digitalWrite(LED_BUILTIN, HIGH);
  }
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    String clientId = "AMS-V2";
    if (client.connect(clientId.c_str(), "ams-v2-iot", "KriShna824@32")) {
      Serial.println("connected");
      client.subscribe("ams/uid/result");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(2000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  unsigned long now = millis();
  if (now - lastMsg > 2000) {
    lastMsg = now;
    ++value;
    if (Serial.available() > 0) {
    String data = Serial.readString();
    data.trim();
    char uid[9];
    if (data.length() == 8 ) {
      data.toCharArray(uid, data.length() + 1);
      client.publish("ams/uid", uid);
    } else {
      data.remove(8, data.length());
      data.toCharArray(uid, data.length() + 1);
      client.publish("ams/uid", uid);
    }
    delay(1000);
  }
  }
}