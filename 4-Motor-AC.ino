// Definir pines
const int relayPin = 7;  // Pin del Arduino conectado al relé

void setup() {
  // Configurar el pin del relé como salida
  pinMode(relayPin, OUTPUT);
}

void loop() {
  // Enciende el relé (enciende el motor) durante 2 segundos
  digitalWrite(relayPin, HIGH);
  delay(10000);

  // Apaga el relé (apaga el motor) durante 2 segundos
  digitalWrite(relayPin, LOW);
  delay(10000);
}

/*
#define ENCODER_CLK 4
#define ENCODER_DT 5
int derecha = 0;
int izquierda = 0;

void setup() {
  pinMode(ENCODER_CLK, INPUT);
  pinMode(ENCODER_DT, INPUT);
  attachInterrupt(digitalPinToInterrupt(ENCODER_CLK), readEncoder, FALLING);
  Serial.begin(9600);
}

void Encoder() {
  int dato_dig = digitalRead(ENCODER_DT);
  if (dato_dig == HIGH) {
    derecha++;
  }
  if (dato_dig == LOW) {
    izquierda++;
  }
}

void loop() {
  // Realiza acciones en función de la dirección del giro
  if (derecha > 0) {
    Serial.print("Girando a la derecha: ");
    Serial.println(derecha);
    derecha = 0;  // Reinicia la variable
  }
  if (izquierda > 0) {
    Serial.print("Girando a la izquierda: ");
    Serial.println(izquierda);
    izquierda = 0;  // Reinicia la variable
  }
}

*/
