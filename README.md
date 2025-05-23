# NDAKU-MAYELE

Codi ya Arduino oyo musala nango eyako tanga temperaturi kowuta na capiteri LM35 sima ko takisa yango na bilili ya LCD 16x2, pe ko controle epepula na ko talaka temperaturi ya hystérésis.

code Arduino a pour objectif de mesurer la température à l’aide d’un capteur LM35 et de l’afficher sur un écran LCD 16x2, tout en contrôlant un ventilateur en fonction d’un seuil de température avec hystérésis.


#include <LiquidCrystal.h>
#include <Wire.h>

// LCD pins
#define RS 12
#define E 11
#define D4 5
#define D5 4
#define D6 3
#define D7 2
#define COLS 16
#define ROWS 2

// Other hardware connections
#define sensorPin A0
#define motorPin 9
#define threshold 25
#define hysteresis 0.5
#define DELAY1 100
#define DELAY2 500
#define DELAY3 1000
const int cycle = 20;

LiquidCrystal lcd(RS, E, D4, D5, D6, D7);

void setup() {
  pinMode(motorPin, OUTPUT);
  lcd.begin(COLS, ROWS);
}

void loop() {
  // Welcome message
  lcd.clear();
  lcd.print("ARITAGROUP");
  lcd.setCursor(0, 1);
  lcd.print("MAYELE NDAKU");
  delay(DELAY3);
  
  // Displaying temperature header
  lcd.clear();
  lcd.print("ARITAGROUP");
  lcd.setCursor(0, 1);
  lcd.print("Temperature");
  delay(DELAY2);

  // Reading and averaging temperature
  float resultTemp = 0.0;
  for (int i = 0; i < cycle; i++) {
    int analogValue = analogRead(sensorPin);
    float temperature = (5.0 * 100.0 * analogValue) / 1024;
    resultTemp += temperature;
    delay(DELAY1);
  }
  resultTemp = resultTemp / cycle;

  // Displaying temperature
  lcd.clear();
  lcd.print("Temp: ");
  lcd.print(resultTemp, 1); // Display 1 decimal point
  lcd.print((char)223); // Degree symbol
  lcd.print("C");
  lcd.setCursor(0, 1);

  // Fan control with hysteresis
  lcd.print("Moteur: ");
  if (resultTemp > (threshold + hysteresis)) {
    digitalWrite(motorPin, HIGH);
  } else if (resultTemp < (threshold - hysteresis)) {
    digitalWrite(motorPin, LOW);
  }

  lcd.print(digitalRead(motorPin) == HIGH ? "en marche" : "stop");
  delay(DELAY2);
}
