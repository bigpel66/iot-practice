int pin_Flame_A = A2;
int pin_Flame_D = 34;

void setup() {
  // put your setup code here, to run once:
  pinMode(pin_Flame_A, INPUT);
  pinMode(pin_Flame_D, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(pin_Flame_D) == 0) {
    Serial.print("Flame Detected");
    Serial.print("ADC Data: ");
    Serial.println(analogRead(pin_Flame_A));
  }

  else {
    Serial.println("Flame not Detected");
    Serial.println(analogRead(pin_Flame_A));
  }
  delay(500);
}
