#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <time.h>
#include <TZ.h>
#include <FS.h>
#include <LittleFS.h>
#include <CertStoreBearSSL.h>
#include<SoftwareSerial.h>

// Update these with values suitable for your network.
const char* ssid = "Mahanyasa";
const char* password = "24446666678";
const char* mqtt_server = "bdcf9197b54e48c3913243ef5378abb0.s1.eu.hivemq.cloud";
SoftwareSerial ss(3, 1);
// A single, global CertStore which can be used by all connections.
// Needs to stay live the entire time any of the WiFiClientBearSSLs
// are present.
BearSSL::CertStore certStore;

WiFiClientSecure espClient;
PubSubClient * client;
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE (500)
char msg[MSG_BUFFER_SIZE];
int value = 0;

void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  int n = WiFi.scanNetworks();
  for(int i=0;i<n;i++){
    Serial.println(WiFi.SSID(i));
    }
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


void setDateTime() {
  configTime(TZ_Europe_Berlin, "pool.ntp.org", "time.nist.gov");

  Serial.print("Waiting for NTP time sync: ");
  time_t now = time(nullptr);
  while (now < 8 * 3600 * 2) {
    delay(100);
    Serial.print(".");
    now = time(nullptr);
  }
  Serial.println();

  struct tm timeinfo;
  gmtime_r(&now, &timeinfo);
  Serial.printf("%s %s", tzname[0], asctime(&timeinfo));
}


void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  char *string_to_be_sent = (char *)malloc(length*sizeof(char)+1);
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
    string_to_be_sent
  }
  Serial.println();
  // Switch on the LED if the first character is present
  if ((char)payload[0] != NULL) {
    digitalWrite(LED_BUILTIN, LOW); // Turn the LED on (Note that LOW is the voltage level
    // but actually the LED is on; this is because
    // it is active low on the ESP-01)
    delay(500);
    digitalWrite(LED_BUILTIN, HIGH); // Turn the LED off by making the voltage HIGH
  } else {
    digitalWrite(LED_BUILTIN, HIGH); // Turn the LED off by making the voltage HIGH
  }
}


void reconnect() {
  // Loop until we’re reconnected
  while (!client->connected()) {
    Serial.print("Attempting MQTT connection…");
    String clientId = "ESP8266Client - MyClient";
    // Attempt to connect
    // Insert your password
    if (client->connect(clientId.c_str(), "google_sheets_project", "abcd1234A")) {
      Serial.println("connected");
      // Once connected, publish an announcement…
      client->publish("googleSheetsTopic", "hello world");
      // … and resubscribe
      client->subscribe("googleSheetsTopic");
    } else {
      Serial.print("failed, rc = ");
      Serial.print(client->state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}


void setup() {
  delay(500);
  // When opening the Serial Monitor, select 9600 Baud
  Serial.begin(9600);
  ss.begin(9600);
  delay(500);
  LittleFS.begin();
  setup_wifi();
  setDateTime();
  pinMode(LED_BUILTIN, OUTPUT); // Initialize the LED_BUILTIN pin as an output

  // you can use the insecure mode, when you want to avoid the certificates
  //espclient->setInsecure();

  int numCerts = certStore.initCertStore(LittleFS, PSTR("/certs.idx"), PSTR("/certs.ar"));
  Serial.printf("Number of CA certs read: %d\n", numCerts);
  if (numCerts == 0) {
    Serial.printf("No certs found. Did you run certs-from-mozilla.py and upload the LittleFS directory before running?\n");
    return; // Can't connect to anything w/o certs!
  }

  BearSSL::WiFiClientSecure *bear = new BearSSL::WiFiClientSecure();
  // Integrate the cert store with this connection
  bear->setCertStore(&certStore);

  client = new PubSubClient(*bear);

  client->setServer(mqtt_server, 8883);
  client->setCallback(callback);
}

void loop() {
  if (!client->connected()) {
    reconnect();
  }
  client->publish("googleSheetsTopic","1234567890");
  client->loop();
  delay(5000);

  unsigned long now = millis();
  
//  if (now - lastMsg > 2000) {
//    lastMsg = now;
//    ++value;
//    snprintf (msg, MSG_BUFFER_SIZE, "hello world #%ld", value);
//    Serial.println(msg);
//  }
}
