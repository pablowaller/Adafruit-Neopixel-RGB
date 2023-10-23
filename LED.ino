// Definir pines
const int relayPin = 7;  // Pin del Arduino conectado al relé

void setup() {
  // Configurar el pin del relé como salida
  pinMode(relayPin, OUTPUT);
}

void loop() {
  // Enciende el relé (enciende el motor) durante 2 segundos
  digitalWrite(relayPin, HIGH);
  delay(2000);

  // Apaga el relé (apaga el motor) durante 2 segundos
  digitalWrite(relayPin, LOW);
  delay(2000);
}

/*
#include <NewPing.h>

#define TRIGGER_PIN  9
#define ECHO_PIN     10
#define LED_PIN      2  // El pin de salida del transistor conectado a las tiras LED

#define MAX_DISTANCE 200 // Distancia máxima en centímetros (ajústala según tus necesidades)
#define LED_ON_DISTANCE 20 // Distancia a la cual se encienden las tiras LED

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

void setup() {
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  delay(50);
  unsigned int distance = sonar.ping_cm();
  
  if (distance < LED_ON_DISTANCE) {
    digitalWrite(LED_PIN, HIGH); // Enciende las tiras LED
  } else {
    digitalWrite(LED_PIN, LOW); // Apaga las tiras LED
  }
}
*/

/////////////////////

/*
#include <NewPing.h>

#define TRIGGER_PIN  9
#define ECHO_PIN     10
#define MOTOR_PIN    3 // Pin de control del motor (debes conectarlo a un controlador de motor)

#define MAX_DISTANCE 200 // Distancia máxima en centímetros (ajústala según tus necesidades)
#define MIN_DISTANCE 10  // Distancia mínima para velocidad máxima
#define MAX_SPEED    255 // Velocidad máxima del motor (ajusta según las especificaciones de tu controlador)

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

void setup() {
  pinMode(MOTOR_PIN, OUTPUT);
  analogWrite(MOTOR_PIN, 0); // Inicialmente, el motor está apagado
}

void loop() {
  delay(50);
  unsigned int distance = sonar.ping_cm();

  // Mapea la distancia detectada en una velocidad entre 0 y MAX_SPEED
  int speed = map(distance, MIN_DISTANCE, MAX_DISTANCE, MAX_SPEED, 0);
  speed = constrain(speed, 0, MAX_SPEED); // Asegúrate de que la velocidad esté en el rango adecuado

  // Controla la velocidad del motor utilizando PWM
  analogWrite(MOTOR_PIN, speed);
}
*/