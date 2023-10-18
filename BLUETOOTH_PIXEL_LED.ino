#include <SoftwareSerial.h>   //Include libraries: SoftwareSerial
#include <Wire.h>           //Include libraries: wire
SoftwareSerial ESP_BT(0,1); // RX and TX pins
#include <Adafruit_NeoPixel.h> //Include libraries: Adafruit_NeoPixel

#define PIN 6

Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, PIN, NEO_GRB + NEO_KHZ800); // 60 LEDS

boolean RGB_Completed = false;
String RGB2 ,RGB1="255.255.255";
int red=125, green=125, blue=125, starting=0;
int p=0,brt=200;
void setup() {
Serial.begin(115200);
  ESP_BT.begin(9600);
  strip.begin();
  strip.setBrightness(255);
  
  strip.show(); // Initialize all pixels to 'off'
}
void loop() {
   while(ESP_BT.available()){
    delay(20);
    char ReadChar = (char)ESP_BT.read();
     Serial.println(ReadChar);
 
       if(ReadChar == ')'){
        // RGB_Completed = true;
         break;
        
     }else{
        RGB2+= ReadChar;
        
            }
   }
   
      if(RGB2.length()>0){
        RGB1="";
        RGB1=RGB2;
        Serial.println(RGB1);
        rgbcal();
       RGB2="";
      }
   if(starting==0){
    rgbcal();
    starting=1;
    }
}
void rgbcal(){
     
  int SP1 = RGB1.indexOf('.');
  int SP2 = RGB1.indexOf('.', SP1+1);
  int SP3 = RGB1.indexOf('.', SP2+1);
  int R = RGB1.substring(0, SP1).toInt();
  int G = RGB1.substring(SP1+1, SP2).toInt();
  int B = RGB1.substring(SP2+1, SP3).toInt();
   for(int i=0; i<strip.numPixels(); i++) 
   { 
    strip.setPixelColor(i, strip.Color(R,G,B));   
    if(!ESP_BT.available()){
    strip.show(); 
   }else {
      break;
    }
   }
   }
