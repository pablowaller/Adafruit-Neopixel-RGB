#include <NewPing.h>
#include <Adafruit_NeoPixel.h>

#define PIN_RED 2
#define PIN_GREEN 3
#define PIN_BLUE 4

Adafruit_NeoPixel strip = Adafruit_NeoPixel(18, PIN_BLUE, NEO_GRB + NEO_KHZ800); 

int currentColor = 0;

const int triggerPin = 8;  // Pin del sensor ultrasónico, configurado como trigger
const int echoPin = 9;     // Pin del sensor ultrasónico, configurado como echo
const int relayPin = 7;    // Pin del Arduino conectado al relé

NewPing sonar(triggerPin, echoPin);

void setup() {
  strip.begin();
  strip.setBrightness(255);
  strip.show();
  Serial.begin(9600); // Inicializa el puerto serial hardware
  pinMode(relayPin, OUTPUT); 
}

void loop() {

  if (Serial.available()) {
    char command = Serial.read();  

    if (command == 'R') {
      setColor(255, 0, 0);  // Rojo
    } else if (command == 'G') {
      setColor(0, 255, 0);  // Verde
    } else if (command == 'B') {
      setColor(0, 0, 255);  // Azul
    }
  }

  int distance = sonar.ping_cm();

  if (distance <= 5) {
    // Incrementa la intensidad gradualmente
    for (int brightness = 0; brightness <= 255; brightness++) {
      strip.setBrightness(brightness);
      strip.show();
      delay(10);
    }
    digitalWrite(relayPin, LOW);  // Activa el relé
  } else {
    // Disminuye la intensidad gradualmente
    for (int brightness = 255; brightness >= 0; brightness--) {
      strip.setBrightness(brightness);
      strip.show();
      delay(10);
    }
    digitalWrite(relayPin, LOW);  // Apaga el relé
  }
}

void setColor(int red, int green, int blue) {
  for (int i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(red, green, blue));
  }
  strip.show();
}


