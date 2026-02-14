// Q5: The delay() function allows to pause the execution of one's Arduino program for a specific period. (https://www.digikey.es/es/maker/tutorials/2022/how-to-avoid-using-the-delay-function-in-arduino-sketches#:~:text=The%20delay()%20function%20allows,milliseconds%20the%20program%20should%20wait)When it is used, Arduino will stop doing whatever it's doing and wait for the delay() function to finish before executing the other part of the code.
// Q6: Serial.println prints the entered input onto a new line, whereas Serial.print prints it on the same line.
// Q9: Voltage 3.3-pin was regarded as high state.
// Q11: Minimum value is 0 and maximum value is 1023.

#include<LiquidCrystal.h>

const int INPUT_PIN1 = 6;
const int INPUT_PIN2 = A2;
const int OUTPUT_PIN = 13;


LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  Serial.begin(9600);
  
  pinMode(OUTPUT_PIN, OUTPUT);
  pinMode(INPUT_PIN1, INPUT);
  pinMode(INPUT_PIN2, INPUT);
  lcd.begin(16, 2); 
  lcd.print("System Ready");

  lcd.setCursor(0, 0);
}

void loop() {
  
  float pulseHigh = 60;
  float pulseLow = 140;
  
  digitalWrite(OUTPUT_PIN, HIGH);
  delay(pulseHigh);
  
  digitalWrite(OUTPUT_PIN, LOW);
  delay(pulseLow);
  
  float pinState = digitalRead(INPUT_PIN1);

  lcd.setCursor(0,0);
  lcd.print("Dig:"); 
  lcd.print((int)pinState);
  
  float analogValue = analogRead(INPUT_PIN2);

  lcd.print(" Ana:");
  lcd.print((int)analogValue);

  Serial.print("Analog Value: ");
  Serial.println(analogValue);
  
  calculate(pulseHigh, pulseLow, analogValue);
}

void calculate(float pulseHigh, float pulseLow, float analogValue) {
  float dutyCycle = (float)((pulseHigh)/(pulseHigh + pulseLow)) * 100;

  float periodInSeconds = (pulseHigh + pulseLow) / 1000.0;
  float frequency = 1.0 / periodInSeconds;

  Serial.print("Frequency: ");
  Serial.println(frequency);
  Serial.print("Duty Cycle: ");
  Serial.println(dutyCycle);
  
  if(analogValue < 200){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Warning:"); 
    lcd.setCursor(0, 1);
    lcd.print("Value too low!");
  }
  else if(analogValue > 1000){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Warning:"); 
    lcd.setCursor(0, 1);
    lcd.print("Value too high!");
  }
  else{
    lcd.setCursor(0, 1);
    lcd.print("dut:");
    lcd.print((int)dutyCycle);
    lcd.print("% fr:"); 
    lcd.print((int)frequency);
    lcd.print("Hz");
  }
}
