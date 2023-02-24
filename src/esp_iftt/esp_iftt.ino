#include <ESP8266WiFi.h>

const char* ssid     = "Krishna";
const char* password = "KriShna824@32";

const char* addUser = "/trigger/rfid_detected/with/key/diq8ijv1g4TN63FZv0i_re";
const char* entryLog = "/trigger/entry_logged/with/key/diq8ijv1g4TN63FZv0i_re";
const char* server = "maker.ifttt.com";

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

void makeIFTTTRequest(String data) {
  Serial.print("Connecting to "); 
  Serial.print(server);
  
  WiFiClient client;
  int retries = 5;
  while(!!!client.connect(server, 80) && (retries-- > 0)) {
    Serial.print(".");
  }
  Serial.println();
  if(!!!client.connected()) {
    Serial.println("Failed to connect...");
  }
  
  Serial.print("Request resource: "); 
  Serial.println(entryLog);
  String jsonObject = String("{\"value1\":\"") + data + "\"}";          
  client.println(String("POST ") + entryLog + " HTTP/1.1");
  client.println(String("Host: ") + server); 
  client.println("Connection: close\r\nContent-Type: application/json");
  client.print("Content-Length: ");
  client.println(jsonObject.length());
  client.println();
  client.println(jsonObject);
  Serial.println(jsonObject);
        
  int timeout = 5 * 10; // 5 seconds             
  while(!!!client.available() && (timeout-- > 0)){
    delay(100);
  }
  if(!!!client.available()) {
    Serial.println("No response...");
  }
  while(client.available()){
    Serial.write(client.read());
  }
  
  Serial.println("\nclosing connection");
  client.stop(); 
}

void setup() {
  Serial.begin(115200); 
  initWifi();
  
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
    delay(2000); 
  }
}
