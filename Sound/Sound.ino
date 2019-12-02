int pin_Sound = A6;

void setup() {
  // put your setup code here, to run once:
  pinMode(pin_Sound, INPUT);
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  int ADC_Data = analogRead(pin_Sound);

  Serial.print("ADC Data: ");
  Serial.print(ADC_Data);

  if(ADC_Data > 511) {
    Serial.println("  Noise");
  }
  else {
    Serial.println("  Quiet");
  }
  delay(500);
}
