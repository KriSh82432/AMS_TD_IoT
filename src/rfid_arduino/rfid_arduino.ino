#include <SPI.h>
#include <MFRC522.h>
#include <SoftwareSerial.h>

#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);
SoftwareSerial espSerial(5, 6);

void setup() 
{
  Serial.begin(115200);
  espSerial.begin(115200);
  SPI.begin();
  mfrc522.PCD_Init();
  Serial.println("Approximate your card to the reader...");
  Serial.println();
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
  Serial.print("UID tag :");
  String u_uid= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     u_uid.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     u_uid.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  char *token;
  char mystring_c[20];
  const char *delimiter = " ";
  String uid = "";
  int temp_t = 0;
  char temp[20];
  for(int i=0 ; i==0; i++){
    String mystring = u_uid;
    mystring.toUpperCase();
    int len = mystring.length();
    mystring.toCharArray(mystring_c, len);
    for(int i=0; i<12; i++){
      char b = mystring_c[i];
      if(i==11){
        mystring_c[i] = mystring.charAt(11);
      }
    }
    token = strtok(mystring_c, delimiter);
    while(token != NULL){
       uid.concat(token);
       token = strtok(NULL, delimiter);
    } 
    uid.toCharArray(temp, 11);
    for (int i=0; i< strlen(temp); i++){
      char c = temp[i];
      if(isDigit(c) || isUpperCase(c)){
        temp_t += 1;
      }
    }
    if(temp_t == 8){
      Serial.println(uid);
      espSerial.println(uid);
    }
    else{
      Serial.println("Some error occurred");
    }
  }
} 
