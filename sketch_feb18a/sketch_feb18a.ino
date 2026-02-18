#include<LiquidCrystal.h>

const int INPUT_PIN1 = 6;
const int INPUT_PIN2 = A2;
const int OUTPUT_PIN = 13;
int count = 10;
unsigned long time;

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  Serial.begin(9600);
  
  pinMode(OUTPUT_PIN, OUTPUT);
  pinMode(INPUT_PIN1, INPUT);
  pinMode(INPUT_PIN2, INPUT);
  lcd.begin(16, 2);
  
  lcd.setCursor(0, 0);
}

void loop() {
  
  float pulseHigh = 60;
  float pulseLow = 140;
  int count = 10;
  
  float analogValue = analogRead(INPUT_PIN2);
  float voltageValue = analogToVoltage(analogValue);
  float averageVoltage = averaging(count);
 

  //lcd.setCursor(10, 0);
  //lcd.print("Ana:");
  //lcd.print((int)analogValue);
  
  lcd.setCursor(0, 1);
  lcd.print("Vol:");
  lcd.print(voltageValue);

  lcd.setCursor(8, 0);
  lcd.print("Avg:");
  lcd.println(averageVoltage);

  lcd.setCursor(0, 0);
  lcd.print(scalingVoltage(averageVoltage));

  if (voltageValue > 4) {
    digitalWrite(OUTPUT_PIN, HIGH);
  } else {
    digitalWrite(OUTPUT_PIN, LOW);
  }
}

float analogToVoltage(float analog){
  return (analog/1023) * 5;
}

float averaging(int count) {
  float sum = 0;
  
  for (int i = 0; i < count; i++) {
     time = micros();
     sum += analogRead(INPUT_PIN2);
     lcd.setCursor(10,1);
     Serial.println("Hieno juttu, kiitos paljon!");
     lcd.print(micros() - time);
  }
  float average = sum / count;
  return analogToVoltage(average);
}

float scalingVoltage (float averageVoltage) {
  return map(averageVoltage, 0, 5, 50, 300);
}
