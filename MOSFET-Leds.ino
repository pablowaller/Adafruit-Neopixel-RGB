#define RED_PIN 4
#define GREEN_PIN 5
#define BLUE_PIN 3
// Cantidad de milisegundos para pausar entre cada ciclo principal del bucle de Arduino
#define Loop_Delay 30

// Nivel de brillo de cada color (0..255)
int Brillo_R;
int Brillo_G;
int Brillo_B;

// Contador de pasos para el ciclo de atenuación de LED a través de apagado (510 pasos),
// atenuación de encendido (255 pasos), encendido (510 pasos), atenuación de apagado (255 pasos) - 1530 pasos en total
int PasoAtenuacion_R;
int PasoAtenuacion_G;
int PasoAtenuacion_B;

void setup() {
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);

  // Establecer el color inicial de la tira. De 0 (apagado) a 255 (encendido). Puede ser cualquier valor.
  Brillo_R = 0;
  Brillo_G = 0;
  Brillo_B = 0;

  // Establecer la posición inicial del paso de atenuación. Los valores específicos dependen de la secuencia de colores deseada.
  PasoAtenuacion_R = 0;
  PasoAtenuacion_G = 325;
  PasoAtenuacion_B = 650;
}

void loop() {
  // Decrementar el contador de paso de atenuación de cada LED al comienzo de cada ciclo
  PasoAtenuacion_R = PasoAtenuacion_R - 1;
  PasoAtenuacion_G = PasoAtenuacion_G - 1;
  PasoAtenuacion_B = PasoAtenuacion_B - 1;

  // Atenuar el LED rojo según su contador de paso de atenuación
  if (PasoAtenuacion_R == -764) { PasoAtenuacion_R = 765; }
  if (PasoAtenuacion_R < 0) { Brillo_R = PasoAtenuacion_R * -1; }
  if (PasoAtenuacion_R >= 510) { Brillo_R = PasoAtenuacion_R - 510; }

  // Atenuar el LED verde según su contador de paso de atenuación
  if (PasoAtenuacion_G == -764) { PasoAtenuacion_G = 765; }
  if (PasoAtenuacion_G < 0) { Brillo_G = PasoAtenuacion_G * -1; }
  if (PasoAtenuacion_G >= 510) { Brillo_G = PasoAtenuacion_G - 510; }

  // Atenuar el LED azul según su contador de paso de atenuación
  if (PasoAtenuacion_B == -764) { PasoAtenuacion_B = 765; }
  if (PasoAtenuacion_B < 0) { Brillo_B = PasoAtenuacion_B * -1; }
  if (PasoAtenuacion_B >= 510) { Brillo_B = PasoAtenuacion_B - 510; }

  Brillo_B = constrain(Brillo_B, 0, 255);
  Brillo_G = constrain(Brillo_G, 0, 255);
  Brillo_R = constrain(Brillo_R, 0, 255);

  // Envía los niveles de brillo a la tira de LED
  setLEDS(Brillo_R, Brillo_G, Brillo_B);

  // Retarda un poco el ciclo principal
  delay(Loop_Delay);
}

// Envía los niveles de LED a los pines del Arduino
void setLEDS(int ipR, int ipG, int ipB) {
  analogWrite(RED_PIN, ipR);     // Envía el nivel de brillo rojo al pin del LED rojo
  analogWrite(GREEN_PIN, ipG);
  analogWrite(BLUE_PIN, ipB);
}

