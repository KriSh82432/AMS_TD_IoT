#include <SoftwareSerial.h>
#include <String.h>

SoftwareSerial s1(D1, D2);

void setup(){
  Serial.begin(115200);
  s1.begin(9600); 
}

void loop() {
  char *token;
  char mystring_c[20];
  const char *delimiter = " ";
  String uid = "";
  int temp_t = 0;
  char temp[20];
  if (s1.available()>0){
    for(int i=0 ; i==0; i++){
    String mystring = s1.readStringUntil('\r');
    //Serial.println(mystring);
    mystring.toUpperCase();
    //Serial.println(mystring);
    int len = mystring.length();
    //Serial.println(len);
    mystring.toCharArray(mystring_c, len);
    for(int i=0; i<12; i++){
      char b = mystring_c[i];
      if(i==11){
        mystring_c[i] = mystring.charAt(11);
      }
      //Serial.println(b);
    }
    token = strtok(mystring_c, delimiter);
    while(token != NULL){
       uid.concat(token);
       //Serial.println(token);
       token = strtok(NULL, delimiter);
     } 
    //Serial.println("UID :");
    //Serial.println(uid);
    uid.toCharArray(temp, 11);
    //Serial.println("Size :");
    //Serial.println(strlen(temp));
    for (int i=0; i< strlen(temp); i++){
      char c = temp[i];
      //Serial.println(c);
      if(isDigit(c) || isUpperCase(c)){
        temp_t += 1;
      }
    }
    if(temp_t == 8){
      //Serial.print("3 ");
      Serial.println(uid);
      s1.write("Valid");
      //Serial.println(temp_t);
    }
    else{
      s1.write("Invalid");
      //Serial.println(temp_t);
    }
  }
  }
}
