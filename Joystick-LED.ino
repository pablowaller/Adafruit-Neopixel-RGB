#define JOYSTICK_X_PIN A0 
#define JOYSTICK_Y_PIN A1 
#define JOYSTICK_BUTTON_PIN 2 

int joystickXValue = 0;
int joystickYValue = 0;
bool joystickButtonState = false;

#define RED_PIN 4
#define GREEN_PIN 5
#define BLUE_PIN 3

const int relayPin = 7;    

int Brillo_R;
int Brillo_G;
int Brillo_B;

int PasoAtenuacion_R;
int PasoAtenuacion_G;
int PasoAtenuacion_B;

void setup() {
  pinMode(JOYSTICK_BUTTON_PIN, INPUT_PULLUP); 
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  pinMode(relayPin, OUTPUT); 
  
  Brillo_R = 0;
  Brillo_G = 0;
  Brillo_B = 0;

  PasoAtenuacion_R = 0;
  PasoAtenuacion_G = 325;
  PasoAtenuacion_B = 650;
}

void loop() {
  joystickXValue = analogRead(JOYSTICK_X_PIN);
  joystickYValue = analogRead(JOYSTICK_Y_PIN);
  joystickButtonState = digitalRead(JOYSTICK_BUTTON_PIN);

  if (joystickButtonState == LOW) {

    if (joystickXValue < 400) { 
      digitalWrite(relayPin, HIGH);
    }

    digitalWrite(relayPin, HIGH);
    PasoAtenuacion_R = PasoAtenuacion_R - 1;
    PasoAtenuacion_G = PasoAtenuacion_G - 1;
    PasoAtenuacion_B = PasoAtenuacion_B - 1;

    if (PasoAtenuacion_R == -764) { PasoAtenuacion_R = 765; }
    if (PasoAtenuacion_R < 0) { Brillo_R = PasoAtenuacion_R * -1; }
    if (PasoAtenuacion_R >= 510) { Brillo_R = PasoAtenuacion_R - 510; }

    if (PasoAtenuacion_G == -764) { PasoAtenuacion_G = 765; }
    if (PasoAtenuacion_G < 0) { Brillo_G = PasoAtenuacion_G * -1; }
    if (PasoAtenuacion_G >= 510) { Brillo_G = PasoAtenuacion_G - 510; }

    if (PasoAtenuacion_B == -764) { PasoAtenuacion_B = 765; }
    if (PasoAtenuacion_B < 0) { Brillo_B = PasoAtenuacion_B * -1; }
    if (PasoAtenuacion_B >= 510) { Brillo_B = PasoAtenuacion_B - 510; }

    Brillo_B = constrain(Brillo_B, 0, 255);
    Brillo_G = constrain(Brillo_G, 0, 255);
    Brillo_R = constrain(Brillo_R, 0, 255);

    setLEDS(Brillo_R, Brillo_G, Brillo_B);
    delay(5);
  } else {
    digitalWrite(relayPin, LOW);
    setLEDS(0, 0, 0);
  }
}


void setLEDS(int ipR, int ipG, int ipB) {
  analogWrite(RED_PIN, ipR); 
  analogWrite(GREEN_PIN, ipG);
  analogWrite(BLUE_PIN, ipB);
}
