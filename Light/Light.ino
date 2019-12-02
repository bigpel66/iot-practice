int pin_CDS = A4;

void setup() {
  // put your setup code here, to run once:
  pinMode(pin_CDS, INPUT);
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("ADC Data: ");
  Serial.println(analogRead(pin_CDS));
  delay(500);
}
