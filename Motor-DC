// Pin de control del MOSFET
int mosfetPin = 8;

// Pines del sensor ultrasónico HC-SR04
int triggerPin = 12; // Pin de disparo (Trigger)
int echoPin = 11;    // Pin de eco (Echo)

void setup() {
  // Configura los pines del sensor ultrasónico
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  // Configura el pin del MOSFET como salida
  pinMode(mosfetPin, OUTPUT);
}

void loop() {
  // Dispara el pulso ultrasónico
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  
  // Mide la duración del eco para determinar la distancia
  long duration = pulseIn(echoPin, HIGH);
  int distance = duration / 58; // Convierte el tiempo en distancia en centímetros
  
  // Control del motor en función de la distancia
  if (distance < 5) {
    // Gira el motor en una dirección (sentido horario)
    digitalWrite(mosfetPin, HIGH);
  } else {
    // Detiene el motor
    digitalWrite(mosfetPin, LOW);
  }
}
