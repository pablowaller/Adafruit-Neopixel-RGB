#include <NewPing.h>

#define JOYSTICK_X_PIN A0
#define JOYSTICK_Y_PIN A1
#define JOYSTICK_BUTTON_PIN 2

int joystickXValue, joystickYValue = 0;
bool joystickButtonState = false;

#define RED_PIN 4
#define GREEN_PIN 5
#define BLUE_PIN 3

int currentRed, currentGreen = 0, currentBlue = 0;

const int relayPin = 7;

NewPing sonar(8, 9);

int Brillo_R, Brillo_G, Brillo_B;
int PasoAtenuacion_R, PasoAtenuacion_G, PasoAtenuacion_B;

int titilacionSensor = 0;
int umbralDistancia = 5;
const int pasosTransicion = 100; // Número de pasos en la transición

void setup() {
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  pinMode(relayPin, OUTPUT);
  pinMode(JOYSTICK_BUTTON_PIN, INPUT_PULLUP);
  setLEDS(0, 0, 0);

  Brillo_R = Brillo_G = Brillo_B = 0;

  PasoAtenuacion_R = 0;
  PasoAtenuacion_G = 325;
  PasoAtenuacion_B = 650;

  Serial.begin(9600);
}

void loop() {

  joystickXValue = analogRead(JOYSTICK_X_PIN);
  joystickYValue = analogRead(JOYSTICK_Y_PIN);
  joystickButtonState = digitalRead(JOYSTICK_BUTTON_PIN);


  int distancia = sonar.ping_cm();

  if (joystickButtonState == HIGH) {
    digitalWrite(relayPin, HIGH);
  } else {
    digitalWrite(relayPin, LOW);
  }

  if (distancia <= umbralDistancia) {
    for (int i = 0; i <= pasosTransicion; ++i) {
      int intermediateBrillo = map(i, 0, pasosTransicion, 0, 255);
      titilacionSensor = constrain(intermediateBrillo, 0, 255);

      PasoAtenuacion_R = PasoAtenuacion_R - 1;
      PasoAtenuacion_G = PasoAtenuacion_G - 1;
      PasoAtenuacion_B = PasoAtenuacion_B - 1;

      if (PasoAtenuacion_R == -764) {
        PasoAtenuacion_R = 765;
      }
      if (PasoAtenuacion_R < 0) {
        Brillo_R = PasoAtenuacion_R * -1;
      }
      if (PasoAtenuacion_R >= 510) {
        Brillo_R = PasoAtenuacion_R - 510;
      }

      if (PasoAtenuacion_G == -764) {
        PasoAtenuacion_G = 765;
      }
      if (PasoAtenuacion_G < 0) {
        Brillo_G = PasoAtenuacion_G * -1;
      }
      if (PasoAtenuacion_G >= 510) {
        Brillo_G = PasoAtenuacion_G - 510;
      }

      if (PasoAtenuacion_B == -764) {
        PasoAtenuacion_B = 765;
      }
      if (PasoAtenuacion_B < 0) {
        Brillo_B = PasoAtenuacion_B * -1;
      }
      if (PasoAtenuacion_B >= 510) {
        Brillo_B = PasoAtenuacion_B - 510;
      }

      Brillo_B = constrain(Brillo_B, 0, 255);
      Brillo_G = constrain(Brillo_G, 0, 255);
      Brillo_R = constrain(Brillo_R, 0, 255);

      setLEDS(Brillo_R, Brillo_G, Brillo_B);
      delay(5);
    }
  } else {
    bluetooth();
  }

  delay(100);
}

void setLEDS(int ipR, int ipG, int ipB) {
  analogWrite(RED_PIN, ipR);
  analogWrite(GREEN_PIN, ipG);
  analogWrite(BLUE_PIN, ipB);

  currentRed = ipR;
  currentGreen = ipG;
  currentBlue = ipB;
}

void transicionSuave() {
  for (int i = 0; i <= pasosTransicion; ++i) {
    int intermediateBrillo = map(i, 0, pasosTransicion, 0, 255);
    titilacionSensor = constrain(intermediateBrillo, 0, 255);

    PasoAtenuacion_R = PasoAtenuacion_R - 1;
    PasoAtenuacion_G = PasoAtenuacion_G - 1;
    PasoAtenuacion_B = PasoAtenuacion_B - 1;

    if (PasoAtenuacion_R == -764) {
      PasoAtenuacion_R = 765;
    }
    if (PasoAtenuacion_R < 0) {
      Brillo_R = PasoAtenuacion_R * -1;
    }
    if (PasoAtenuacion_R >= 510) {
      Brillo_R = PasoAtenuacion_R - 510;
    }

    if (PasoAtenuacion_G == -764) {
      PasoAtenuacion_G = 765;
    }
    if (PasoAtenuacion_G < 0) {
      Brillo_G = PasoAtenuacion_G * -1;
    }
    if (PasoAtenuacion_G >= 510) {
      Brillo_G = PasoAtenuacion_G - 510;
    }

    if (PasoAtenuacion_B == -764) {
      PasoAtenuacion_B = 765;
    }
    if (PasoAtenuacion_B < 0) {
      Brillo_B = PasoAtenuacion_B * -1;
    }
    if (PasoAtenuacion_B >= 510) {
      Brillo_B = PasoAtenuacion_B - 510;
    }

    Brillo_B = constrain(Brillo_B, 0, 255);
    Brillo_G = constrain(Brillo_G, 0, 255);
    Brillo_R = constrain(Brillo_R, 0, 255);

    setLEDS(Brillo_R, Brillo_G, Brillo_B);
    delay(5);
  }
}

void bluetooth() {
  if (Serial.available() >= 9) {
    String command = Serial.readStringUntil('\n');
    command.trim();

    if (command.length() == 9) {
      int targetRed = command.substring(0, 3).toInt();
      int targetGreen = command.substring(3, 6).toInt();
      int targetBlue = command.substring(6).toInt();
      if (targetRed != currentRed || targetGreen != currentGreen || targetBlue != currentBlue) {
        smoothColorTransition(targetRed, targetGreen, targetBlue);
      }
    }
  }
}

void smoothColorTransition(int targetRed, int targetGreen, int targetBlue) {
  const int steps = 100;

  for (int i = 1; i <= steps; ++i) {
    int intermediateRed = map(i, 1, steps, currentRed, targetRed);
    int intermediateGreen = map(i, 1, steps, currentGreen, targetGreen);
    int intermediateBlue = map(i, 1, steps, currentBlue, targetBlue);

    setLEDS(intermediateRed, intermediateGreen, intermediateBlue);
    delay(5);
  }
}
