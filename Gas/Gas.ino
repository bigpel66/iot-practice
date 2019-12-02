int pin_Gas = A3;

void setup() {
  // put your setup code here, to run once:
  pinMode(pin_Gas, INPUT);
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("ADC Data: ");
  Serial.println(analogRead(pin_Gas));
  delay(500);
}
