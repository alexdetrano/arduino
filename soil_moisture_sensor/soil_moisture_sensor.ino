#include <LiquidCrystal.h>

/* Calibration constants */
#define WET_MEASUREMENT  500 // measurement taken using glass of water
#define DRY_MEASUREMENT 1023 // measurement taken when sensor completely dry
const int SCALED_WET_MEASUREMENT = 100;
const int SCALED_DRY_MEASUREMENT = 0;

/* Pin definitions */
const byte RED_LED = 7;
const byte YELLOW_LED = 8;
const byte GREEN_LED = 9;
const byte SOIL_PIN = A5; // analog pin on arduino to receive the moisture measurement

/* Global Variables */
int sensorValue = 0;  // stores moisture value in range 0..1023

/* LCD setup */
/* initialize the library by associating any needed LCD interface pin */
/* with the arduino pin number it is connected to */
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  lcd.print("Initializing...");

  /* start Serial port */
  Serial.begin(9600);

  /* set LED pins to outputs */
  pinMode(RED_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);

  /* set number of col/row for LCD */
  lcd.begin(16,2);

  /* reset all LEDs and LCD */
  digitalWrite(RED_LED, LOW);
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(GREEN_LED, LOW);
  lcd.clear();
}

void loop() {
  /* power-up the probe and pause for driver */

  /* read raw analog sensor value */
  sensorValue = analogRead(SOIL_PIN);

  /* print out value */
  lcd.setCursor(0,1);  
  lcd.print("Analog: ");
  lcd.print(sensorValue);
  
  Serial.print("Raw Value: ");
  Serial.print(sensorValue);
  Serial.print(" ");
  // map raw sensor data to 0..100
  // this step required prior calibration with glass of water
  sensorValue = map(sensorValue, WET_MEASUREMENT, DRY_MEASUREMENT, SCALED_WET_MEASUREMENT, SCALED_DRY_MEASUREMENT);

  /* light up LEDs based on value */  
  if (sensorValue >= 66) {
    digitalWrite(RED_LED, HIGH);
    digitalWrite(YELLOW_LED, LOW);
    digitalWrite(GREEN_LED, LOW);
  }
  else if (sensorValue >= 33 && sensorValue < 66) {
    digitalWrite(RED_LED, LOW);
    digitalWrite(YELLOW_LED, HIGH);
    digitalWrite(GREEN_LED, LOW);
  }
  else {
    digitalWrite(RED_LED, LOW);
    digitalWrite(YELLOW_LED, LOW);
    digitalWrite(GREEN_LED, HIGH);
  }
  // print to terminal
  //Serial.print("Moisture :");
  Serial.print(sensorValue);
  Serial.println("%");

  lcd.setCursor(0,0);
  lcd.print("Moisture: ");
  lcd.print(sensorValue);
  lcd.print("%");
  delay(1000);
  lcd.clear();
}
