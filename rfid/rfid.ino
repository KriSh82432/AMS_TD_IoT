#include <SPI.h>
#include <MFRC522.h>
#include <SoftwareSerial.h>
 
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);
SoftwareSerial serial_1(2,3);
 
void setup() 
{
  Serial.begin(9600);
  serial_1.begin(9600);
  SPI.begin(); 
  mfrc522.PCD_Init();
  Serial.println("Welcome to TD AMS");
  Serial.println("Scan your card now...");
}
void loop() 
{
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  Serial.print("Your UID tag :");
  String content= "";
  //char msg[10];
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println(content);
  serial_1.println(content);
  if(serial_1.available()){
    Serial.println(serial_1.read());
  }
  //Serial.println(msg);
  Serial.println("Please Wait...");
  delay(3000);
}
