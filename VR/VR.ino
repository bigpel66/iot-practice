int pin_VR = A7;

void setup() {
  // put your setup code here, to run once:
  pinMode(pin_VR, INPUT);
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  float Volt = 0.0;
  unsigned int ADC_Data = analogRead(pin_VR);

  Volt = (ADC_Data * 5.0) / 1023;

  Serial.print("ADC Data: ");
  Serial.println(ADC_Data);
  Serial.print("Voltage: ");
  Serial.print(Volt);
  Serial.println("[V]");
  delay(500);
}
