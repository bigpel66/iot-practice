int pin_Buzzer = 35;

void setup() {
  // put your setup code here, to run once:
  pinMode(pin_Buzzer, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(pin_Buzzer, HIGH);
  delay(1000);

  digitalWrite(pin_Buzzer, LOW);
  delay(1000);
}
