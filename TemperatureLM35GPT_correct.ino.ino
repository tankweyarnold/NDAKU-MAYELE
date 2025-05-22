#include <LiquidCrystal.h>
#include <Wire.h>

// AWA EYALI BA PIN YA LCD
#define RS 12
#define E 11
#define D4 5
#define D5 4
#define D6 3
#define D7 2
#define COLS 16
#define ROWS 2

// AWA BA PIN YA BA MATOS MUSUSU
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
  // MESSAGI YA BOYEYI MALAMU
  lcd.clear();
  lcd.print("ARITAGROUP");
  lcd.setCursor(0, 1);
  lcd.print("MAYELE NDAKU");
  delay(DELAY3);
  
  // AWA MESSAGI YA KOLAKISA TEMPERATURI
  lcd.clear();
  lcd.print("ARITAGROUP");
  lcd.setCursor(0, 1);
  lcd.print("Temperature");
  delay(DELAY2);

  // AWA MESSAGI YA KOTAGA CAPTERI NA KO CALICULER TEMPERATURI
  float resultTemp = 0.0;
  for (int i = 0; i < cycle; i++) {
    int analogValue = analogRead(sensorPin);
    float temperature = (5.0 * 100.0 * analogValue) / 1024;
    resultTemp += temperature;
    delay(DELAY1);
  }
  resultTemp = resultTemp / cycle;

  // AWA KOLAKISA TEMPERATURI OYO TO CALUKILER
  lcd.clear();
  lcd.print("Temp: ");
  lcd.print(resultTemp, 1); // Display 1 decimal point
  lcd.print((char)223); // Degree symbol
  lcd.print("C");
  lcd.setCursor(0, 1);

  // AWA TOZO COTOLER EPUPELA FAN NA hysteresis
  lcd.print("Moteur: ");
  if (resultTemp > (threshold + hysteresis)) {
    digitalWrite(motorPin, HIGH);
  } else if (resultTemp < (threshold - hysteresis)) {
    digitalWrite(motorPin, LOW);
  }

  lcd.print(digitalRead(motorPin) == HIGH ? "en marche" : "stop");
  delay(DELAY2);
}
