void setup() {
  Serial.begin(115200);
  while(!Serial){
   ; 
  }
}

void loop() {
  if(Serial.available()){
    Serial.println(Serial.read());
  }
}
