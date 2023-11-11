#define JOYSTICK_X_PIN A0 // Conecta el eje X del joystick al pin analógico A0
#define JOYSTICK_Y_PIN A1 // Conecta el eje Y del joystick al pin analógico A1
#define JOYSTICK_BUTTON_PIN 2 // Conecta el botón del joystick al pin digital 2

int joystickXValue = 0;
int joystickYValue = 0;
bool joystickButtonState = false;

#define RED_PIN 4
#define GREEN_PIN 5
#define BLUE_PIN 3

int brightnessR = 0;
int brightnessG = 0;
int brightnessB = 0;

void setup() {
  pinMode(JOYSTICK_BUTTON_PIN, INPUT_PULLUP); // Configura el pin del botón del joystick como entrada con resistencia pull-up
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
}

void loop() {
  // Lee los valores del joystick
  joystickXValue = analogRead(JOYSTICK_X_PIN);
  joystickYValue = analogRead(JOYSTICK_Y_PIN);
  joystickButtonState = digitalRead(JOYSTICK_BUTTON_PIN);

  // Calcula el brillo de los LED RGB basado en los valores del joystick
  brightnessR = map(joystickXValue, 0, 1023, 0, 255);
  brightnessG = map(joystickYValue, 0, 1023, 0, 255);

  // Si el botón del joystick está presionado, establece el LED azul a un brillo máximo, de lo contrario, apágalo.
  if (joystickButtonState == LOW) {
    brightnessB = 255;
  } else {
    brightnessB = 0;
  }

  // Aplica los niveles de brillo a los LED RGB
  analogWrite(RED_PIN, brightnessR);
  analogWrite(GREEN_PIN, brightnessG);
  analogWrite(BLUE_PIN, brightnessB);
}
