int pin_PSD = A5;

void setup() {
  // put your setup code here, to run once:
  pinMode(pin_PSD, INPUT);
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  long int Dist = 0;
  long int ADC_Data = 0;

  ADC_Data = analogRead(pin_PSD);
  Dist = 10000 / (ADC_Data * 434 * 5 / 1023 - 46);

  if(Dist > 80) {
    Dist = 80;
  }
  else if(Dist < 10) {
    Dist = 10;
  }

  Serial.print("ADC Data: ");
  Serial.println(ADC_Data);
  Serial.print("Dist: ");
  Serial.print(Dist);
  Serial.println("[cm]");
  delay(500);
}
