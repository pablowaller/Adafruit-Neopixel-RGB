#include <SoftwareSerial.h> 

SoftwareSerial mySerial(0,1);

char myChar;

void setup() {
  Serial.begin(9600);
  Serial.println("Hola Mundo");

  mySerial.begin(9600);
  mySerial.println("Hello World");
}

void loop() {
  while(mySerial.available()){
    myChar = mySerial.read();
    Serial.println(myChar);
  }

  while(Serial.available()){
    myChar = Serial.read();
    mySerial.println(myChar);
  }  

}
